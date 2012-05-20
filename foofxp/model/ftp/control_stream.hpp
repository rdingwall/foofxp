#ifndef FOOFXP_CONTROL_STREAM_HPP_INCLUDED
#define FOOFXP_CONTROL_STREAM_HPP_INCLUDED

#include <stdexcept>
#include <string>
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <boost/date_time/posix_time/posix_time_types.hpp>
#include "port_type.hpp"

namespace foofxp {
namespace model {
namespace ftp {

template<class client_type>
class control_stream
{
public:
	
	typedef unsigned short port_type;
	
	control_stream(client_type & client,
		const std::string & host, port_type port, bool ipv6,
		boost::asio::io_service & io_service,
		boost::asio::ssl::context & context,
		const boost::posix_time::time_duration & timeout);
	
	~control_stream();
	
	bool encrypted() const { return encrypted_; };
	bool connected() const { return socket_.is_open(); };
	boost::posix_time::time_duration timeout() const { return timeout_; };
	
	void timeout(boost::posix_time::time_duration timeout)
	{
		timeout_ = timeout;
	};
	
	void begin_connect() throw (std::runtime_error);
	void disconnect();
	void begin_send_command(const std::string & cmd) throw (std::runtime_error);
	void begin_handshake() throw (std::runtime_error);
	void begin_read_line() throw (std::runtime_error);
	
private:
	
	void begin_connect(boost::asio::ip::tcp::resolver::iterator
		endpoint_iterator) throw (std::runtime_error);
	void begin_timeout();
	
	typedef boost::asio::ssl::stream<boost::asio::ip::tcp::socket &>
		ssl_stream_type;
	
	client_type & client_;
	std::string host_;
	port_type port_;
	bool ipv6_;
	bool encrypted_;
	boost::asio::io_service & io_service_;
	boost::asio::ssl::context & context_;
	boost::asio::streambuf reply_;
	boost::asio::ip::tcp::socket socket_;
	ssl_stream_type stream_;
	boost::asio::ip::tcp::resolver resolver_;
	boost::posix_time::time_duration timeout_;
	boost::asio::deadline_timer timer_;
	
	void handle_resolve(const boost::system::error_code & error,
		boost::asio::ip::tcp::resolver::iterator endpoint_iterator)
		throw (std::runtime_error);
	
	void handle_connect(const boost::system::error_code & error,
		boost::asio::ip::tcp::resolver::iterator next_endpoint_iterator);
		
	void handle_handshake(const boost::system::error_code & error)
		throw (std::runtime_error);
	
	void handle_read_line(const boost::system::error_code & error)
		throw (std::runtime_error);
	
	void handle_write_line(const boost::system::error_code & error,
		std::size_t bytes_transferred) throw (std::runtime_error);
	
	void handle_timeout(const boost::system::error_code & error)
		throw (std::runtime_error);
	
}; // class control_stream

} // namespace ftp
} // namespace model
} // namespace foofxp

#endif // FOOFXP_CONTROL_STREAM_HPP_INCLUDED
