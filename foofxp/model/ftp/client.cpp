
#include "client.hpp"
#include "commands.hpp"
#include "file_mapper.hpp"
#include "../../utility/format.hpp"
#include "../../utility/trace.hpp"

using namespace std;
using namespace boost::asio;
using namespace boost::asio::ip;
using namespace boost::system;
using namespace foofxp::model::ftp;
using namespace foofxp::utility;

namespace foofxp {
namespace model {
namespace ftp {

client::client(const string & host, port_type port, bool ipv6,
	bool auth_tls, const string & username, const string & password,
	io_service & io_service, ssl::context & context) :
	state_(not_connected),
	auth_tls_(auth_tls),
	username_(username),
	password_(password),
	control_stream_(*this, host, port, ipv6, io_service, context, 
		boost::posix_time::seconds(15)),
	log_(200)
{
	trace_this(format(256,
		"creating new client for ftp://%s@%s:%i (ipv6=%i, auth_tls=%i)", 
		username.c_str(), host.c_str(), port, ipv6, auth_tls));
}

client::~client() {}

// ----------------------------------------------------------------------------
// public asynchronous operations
// ----------------------------------------------------------------------------

void client::begin_connect()
{
	// Note that we could start connecting immediately in the constructor, but
	// it's left as a second step to give users time to set up client signal
	// handlers.
	
	trace_this("client connecting");
	
	// Log event.
	log_.add_line("Connecting...");
	
	control_stream_.begin_connect();
}

void client::begin_close() {}

void client::begin_get_directory_contents()
{
	assert(state_ == logged_in);
	
	trace_this("client beginning get directory contents");
	
	directory_list_output_buffer_.clear();
	
	send_command(commands::stat_l());
	state_ = awaiting_stat_l_reply;
}

void client::begin_change_directory(const string & directory)
{
	trace_this("client beginning change directory");
	
	send_command(commands::cwd(directory));
	state_ = awaiting_cwd_reply;
}

// ----------------------------------------------------------------------------
// control_stream event handlers
// ----------------------------------------------------------------------------

void client::handle_connect()
{
	trace_this("client connected");
	
	// Log event.
	log_.add_line("Connected.");
	
	// Wait for the server's welcome message.
	trace_this("client waiting for welcome message");
	control_stream_.begin_read_line();
	
	// Get ready for the server's "220 Blah FTP Server ready" welcome message.
	state_ = awaiting_welcome_message;
}

void client::handle_control_stream_error(const string & message, bool fatal)
{
	// Log error and notify listeners.
	string msg = format(128, "Connection error: %s", message.c_str());
	log_.add_line(msg);
	error_occurred(*this, msg);
	
	if (fatal)
		// All endpoints failed.
		fatal_error_occurred(*this, "Connection failed.");
}

void client::handle_handshake()
{
	trace_this("client handshake successful, setting protection buffer size");
	
	// Follow a successful handshake by sending PBSZ 0.
	send_command(commands::pbsz());
	state_ = awaiting_pbsz_reply;
}

void client::handle_line_received(const string & line)
{
	trace_this("client received line from server \"" + line + "\"");
	
	// Create server reply instance from line.
	server_reply reply(line);
	
	// Pass the line to an appropriate handler method.
	switch (state_)
	{
		case awaiting_welcome_message:
			handle_welcome_message(reply);
			return;
			
		case awaiting_auth_tls_reply:
			handle_auth_tls_reply(reply);
			return;
		
		case awaiting_pbsz_reply:
			handle_pbsz_reply(reply);
			return; 
		
		case awaiting_user_reply:
			handle_user_reply(reply);
			return;
		
		case awaiting_pass_reply:
			handle_pass_reply(reply);
			return;
			
		case awaiting_cwd_reply:
			handle_cwd_reply(reply);
			return;
		
		case awaiting_pwd_reply:
			handle_pwd_reply(reply);
			return;
		
		case awaiting_stat_l_reply:
			handle_stat_l_reply(reply);
			return;
			
		default:
			// No state set. This means that the client has received a line
			// from the server out of the blue (i.e. not in response to any
			// command we sent).
			//
			// Usually this will be a "550 Goodbye!" farewell message before
			// the server kicks us off for being idle too long.
			handle_unexpected_message(reply);
			return;
	}
}

bool client::handle_basic_reply_details(const server_reply & reply)
{
	log_.add_line(reply.original_line());
	
	if (!reply.is_valid_format())
	{
		fatal_error_occurred(*this, "Invalid reply received.");
		return false;
	}
	else if (!reply.is_end_of_reply())
	{
		// Didn't get the whole reply yet...
		control_stream_.begin_read_line();
		return false;
	}
	else if (reply.is_negative_reply())
	{
		fatal_error_occurred(*this, reply.original_line());
		return false;
	}
	
	return true;
}

// ----------------------------------------------------------------------------
// client reply handlers
// ----------------------------------------------------------------------------

void client::handle_welcome_message(const server_reply & reply)
{
	if (!handle_basic_reply_details(reply))
		return;
	
	if (auth_tls_)
	{
		// Begin TLS handshake by sending AUTH TLS command.
		send_command(commands::auth_tls());
		state_ = awaiting_auth_tls_reply;
	}
	else
	{
		// Begin log-in by sending USER command.
		send_command(commands::user(username_));
		state_ = awaiting_user_reply;
	}
}

void client::handle_auth_tls_reply(const server_reply & reply)
{
	if (!handle_basic_reply_details(reply))
		return;
	
	// Start handshake.
	control_stream_.begin_handshake();
	state_ = awaiting_handshake;
}

void client::handle_pbsz_reply(const server_reply & reply)
{
	if (!handle_basic_reply_details(reply))
		return;
	
	// Begin log-in by sending USER command.
	send_command(commands::user(username_));
	state_ = awaiting_user_reply;
}

void client::handle_user_reply(const server_reply & reply)
{
	if (!handle_basic_reply_details(reply))
		return;
	
	send_command(commands::pass(password_));
	state_ = awaiting_pass_reply;
}

void client::handle_pass_reply(const server_reply & reply)
{
	if (!handle_basic_reply_details(reply))
		return;
	
	trace_this("user logged in");
	
	state_ = logged_in;
	
	// Tell anyone who's listening that we've logged in.
	idle(*this);
	
	
	begin_get_directory_contents();
}

void client::handle_cwd_reply(const server_reply & reply)
{
	if (!handle_basic_reply_details(reply))
		return;
	
	trace_this("user changed directory");
	
	// Send PWD to ask the server where we are now -- expands symlink paths etc.
	//
	// E.g. CWD ~ actually might send us to "/users/richard".
	send_command(commands::pwd());
	state_ = awaiting_pwd_reply;
}

void client::handle_pwd_reply(const server_reply & reply)
{
	if (!handle_basic_reply_details(reply))
		return;
	
	string path;
	try
	{
		// Parse PWD reply.
		path = reply.get_pwd_path();
	}
	catch (const invalid_argument & ex)
	{
		// Not much we can do to recover if the server is feeding us rubbish
		// PWDs...
		fatal_error_occurred(*this, ex.what());
		return;
	}
	
	trace_this("user successfully changed directory to " + path);
	
	// All done! Notify any subscribers that we've changed directory.
	state_ = logged_in;
	changed_directory(*this, path);
}

void client::handle_stat_l_reply(const server_reply & reply)
{
	// If this line is a valid FTP reply, process it as such. Otherwise, process
	// it as a file entry - append it to the dirlist output buffer, and do not
	// log it.
	if (!reply.is_valid_format())
	{
		// Insert a placeholder message into the session log to mark where the
		// directory list was.
		if (directory_list_output_buffer_.empty())
			log_.add_line("(directory list was here)");
		
		directory_list_output_buffer_.push_back(reply.original_line());
		
		// Wait for more entries or the end of the reply.
		control_stream_.begin_read_line();
		return;
	}
	else if (!handle_basic_reply_details(reply))
		return;
	
	trace_this("received directory list");
	
	// All done! Notify any subscribers that we've received a directory list.
	state_ = logged_in;
	
	vector<file> files = get_files(directory_list_output_buffer_);
	
	received_directory_list(*this, files);
}

void client::handle_unexpected_message(const server_reply & reply)
{
	trace_this("client received unexpected message from server");
	
	if (!handle_basic_reply_details(reply))
		return;
}

// ----------------------------------------------------------------------------
// internal client stuff
// ----------------------------------------------------------------------------

void client::send_command(const string & command)
{
	trace_this("client sending command \"" + command + "\"");
	
	log_.add_line(">>> " + command);
	
	control_stream_.begin_send_command(command);
	
	control_stream_.begin_read_line();
}

} // namespace ftp
} // namespace model
} // namespace foofxp
