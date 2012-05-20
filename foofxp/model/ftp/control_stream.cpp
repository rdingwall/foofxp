#include <algorithm>
#include <iostream>
#include <istream>
#include <boost/algorithm/string/trim.hpp>
#include "control_stream.hpp"
#include "../../utility/enforce_that.hpp"
#include "../../utility/format.hpp"
#include "../../utility/trace.hpp"
#include "../../utility/asio.hpp"

using namespace std;
using namespace boost::algorithm;
using namespace boost::asio;
using namespace boost::asio::ip;
using boost::bind;
using namespace boost::posix_time;
using namespace boost::system;
using namespace foofxp::utility;

namespace foofxp {
namespace model {
namespace ftp {

static const string end_of_line = "\r\n";

template<class client_type>
control_stream<client_type>::control_stream(client_type & client,
	const string & host, port_type port, bool ipv6, io_service & io_service,
	ssl::context & context, const time_duration & timeout) :
	client_(client),
	host_(host),
	port_(port),
	ipv6_(ipv6),
	encrypted_(false),
	io_service_(io_service),
	context_(context),
	reply_(),
	socket_(io_service),
	stream_(socket_, context),
	resolver_(io_service),
	timeout_(timeout),
	timer_(io_service)
{
	trace_this(format(128, "control_stream created for %s:%i (ipv6=%i)", 
		host.c_str(), port, ipv6));

	enforce_that(!host_.empty(), runtime_error, "Empty host.");
}

template<class client_type>
control_stream<client_type>::~control_stream() {}

template<class client_type>
void control_stream<client_type>::begin_connect() throw (runtime_error)
{
	enforce_that(!socket_.is_open(), runtime_error, "Socket is already open.");
	
	if (ipv6_)
	{
		trace_this("control_stream starting async_resolve \"" + host_ + 
			"\" (ipv6)");
		
		// v6 query (AAAA records).
		tcp::resolver::query query(tcp::v6(), host_, string());

		resolver_.async_resolve(query, 
			bind(&control_stream::handle_resolve, this, placeholders::error, 
				placeholders::iterator));
	}
	else
	{
		trace_this("control_stream starting async_resolve \"" + host_ + 
			"\" (ipv4)");
	
		// v4 query (A records).
		tcp::resolver::query query(tcp::v4(), host_, string());

		resolver_.async_resolve(query, 
			bind(&control_stream::handle_resolve, this, placeholders::error,
				placeholders::iterator));
	}
}

template<class client_type>
void control_stream<client_type>::disconnect()
{
	trace_this("control_stream disconnecting");
	
	// Cancel timeout.
	timer_.cancel();

	// Close socket (cancels any remaining async operations).
	socket_.close();
}

template<class client_type>
void control_stream<client_type>::begin_send_command(const string & cmd)
	throw (runtime_error)
{	
	enforce_that(socket_.is_open(), runtime_error, "Socket is not open.");
	
	if (encrypted_)
	{
		trace_this("control_stream starting async_write \"" + cmd +
			"\" (encrypted)");
		
		async_write(stream_, buffer(cmd + end_of_line), 
			bind(&control_stream::handle_write_line, this, placeholders::error,
				placeholders::bytes_transferred));
	}
	else
	{
		trace_this("control_stream starting async_write \"" + cmd + "\"");
		
		async_write(socket_, buffer(cmd + end_of_line), 
			bind(&control_stream::handle_write_line, this, placeholders::error,
				placeholders::bytes_transferred));
	}
	
	begin_timeout();
}

template<class client_type>
void control_stream<client_type>::begin_connect(tcp::resolver::iterator
	endpoint_iterator) throw (runtime_error)
{
	trace_this("control_stream starting async_connect");
	
	enforce_that(endpoint_iterator != tcp::resolver::iterator(), 
		runtime_error, "Invalid endpoint_iterator.");
	enforce_that(!socket_.is_open(), runtime_error, "Socket is already open.")
	
	tcp::endpoint remote_endpoint = *endpoint_iterator;

	// Set port.
	remote_endpoint.port(port_);

	// Begin async connect.
	socket_.async_connect(remote_endpoint,
		bind(&control_stream::handle_connect, this, placeholders::error, 
			++endpoint_iterator));

	begin_timeout();
}

template<class client_type>
void control_stream<client_type>::begin_handshake() throw (runtime_error)
{
	trace_this("control_stream starting async_handshake");
	
	enforce_that(socket_.is_open(), runtime_error, "Socket is not open.");
	
	// Begin async handshake.
	stream_.async_handshake(ssl::stream_base::client,
		bind(&control_stream::handle_handshake, this, placeholders::error));
}

template<class client_type>
void control_stream<client_type>::begin_read_line() throw (runtime_error)
{
	enforce_that(socket_.is_open(), runtime_error, "Socket is not open.");
	
	if (encrypted_)
	{
		trace_this("control_stream waiting for a line (SSL stream)");
		
		async_read_until(stream_, reply_, end_of_line,
			bind(&control_stream::handle_read_line, this, placeholders::error));
	}
	else
	{
		trace_this("control_stream waiting for a line (TCP socket)");
		
		async_read_until(socket_, reply_, end_of_line,
			bind(&control_stream::handle_read_line, this, placeholders::error));
	}
	
	// Note that read line cannot timeout. This is particularly
	// useful for long-running SITE command e.g. dupecheck.
}

template<class client_type>
void control_stream<client_type>::handle_resolve(const error_code & error,
		tcp::resolver::iterator endpoint_iterator) throw (runtime_error)
{	
	enforce_that(!socket_.is_open(), runtime_error, "Socket is already open.");
	
	// Cancel timeout timer.
	timer_.cancel();

	if (!error)
	{
		trace_this("control_stream resolved endpoints " 
			+ to_delimited_list(endpoint_iterator));
		
		// Notify observers that we resolved the host.
		begin_connect(endpoint_iterator);
	}
	else
	{
		trace_this("control_stream async_resolve failed: " + error.message());
		
		// Notify observers that an error occured.
		client_.handle_control_stream_error(error.message(), true);
	}
}

template<class client_type>
void control_stream<client_type>::handle_connect(const error_code & error,
		tcp::resolver::iterator next_endpoint_iterator)
{	
	// Cancel timeout timer.
	timer_.cancel();
	
	if (!error)
	{
		trace_this("control_stream connected");
		
		// Notify the client that we are connected.
		client_.handle_connect();
		
		return;
	}
	else if (error == error::operation_aborted)
		// Ignore.
		return;
	
	trace_this("control_stream async_connect failed: " + error.message());
	
	// Notify the client that an endpoint failed.
	client_.handle_control_stream_error(error.message(), false);
	
	if (next_endpoint_iterator == tcp::resolver::iterator())
	{
		trace_this("control_stream has no more endpoints "
			"-- all endpoints failed");
		
		// That was the last endpoint. Notify the client that ALL endpoints have
		// failed.
		client_.handle_control_stream_error("Connection failed.", true);
	}
	else
	{
		trace_this("control_stream trying next endpoint");
		
		// Try the next endpoint.
		begin_connect(next_endpoint_iterator);
	}
}

template<class client_type>
void control_stream<client_type>::handle_handshake(const error_code & error)
	throw (runtime_error)
{	
	enforce_that(socket_.is_open(), runtime_error, "Socket is not open.");
	
	// Cancel timeout timer.
	timer_.cancel();

	if (!error)
	{
		trace_this("control_stream handshake successful");
			
		encrypted_ = true;

		// Notify observers that the handshake was performed
		// successfully.
		client_.handle_handshake();
	}
	else if (error != error::operation_aborted)
	{
		trace_this("control_stream async_handshake failed: "
			+ error.message());
		
		// Notify observers that an error was encountered.
		client_.handle_control_stream_error(error.message(), true);
	}
	else
		trace_this("control_stream handshake aborted");
}

template<class client_type>
void control_stream<client_type>::handle_read_line(const error_code & error)
	throw (runtime_error)
{	
	enforce_that(socket_.is_open(), runtime_error, "Socket is not open.");
	
	if (!error)
	{
		trace_this("control_stream got line");
			
		// Read line from reply buffer.
		string line;
		istream stream(&reply_);
		getline(stream, line);
		
		// Trim any whitespace/new line crap off the end.
		trim_right(line);

		// Notify observers that we recieved a line.
		client_.handle_line_received(line);
	}
	else if (error != posix_error::operation_canceled)
	{
		trace_this("control_stream async_read_until failed: " 
			+ error.message());
			
		// Notify observers that an error was encountered.
		client_.handle_control_stream_error(error.message(), true);
	}
	else
		trace_this("control_stream read aborted");
}

template<class client_type>
void control_stream<client_type>::handle_write_line(const error_code & error,
	size_t bytes_transferred) throw (runtime_error)
{	
	enforce_that(socket_.is_open(), runtime_error, "Socket is not open.");
	
	// Cancel timeout timer.
	timer_.cancel();

	if (!error)
		trace_this(format(64, "control_stream wrote line (%ld bytes)",
			bytes_transferred));
	
	else if (error != error::operation_aborted)
	{
		trace_this("control_stream async_write failed: " 
			+ error.message());
		
		// Notify observers that an error was encountered.
		client_.handle_control_stream_error(error.message(), true);
	}
	else
		trace_this("control_stream write aborted");
}

template<class client_type>
void control_stream<client_type>::handle_timeout(const error_code & error)
	throw (runtime_error)
{	
	enforce_that(socket_.is_open(), runtime_error, "Socket is not open.");
		
	if (error != error::operation_aborted)
	{
		trace_this("control_stream timed out, error = " + error.message());
		
		socket_.close();
		client_.handle_control_stream_error("Control stream timed out.", true);
	}
	else
		trace_this("control_stream timeout aborted");
}

template<class client_type>
void control_stream<client_type>::begin_timeout()
{
	trace_this("control_stream starting timeout");
	
	// Begin timeout timer.
	timer_.expires_from_now(timeout_);
	timer_.async_wait(bind(&control_stream::handle_timeout, this,
		placeholders::error));
}

} // namespace ftp
} // namespace model
} // namespace foofxp
