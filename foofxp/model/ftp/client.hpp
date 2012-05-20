#ifndef FOOFXP_CLIENT_HPP_INCLUDED
#define FOOFXP_CLIENT_HPP_INCLUDED

#include <string>
#include <vector>
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/thread_safe_signal.hpp>
#include "../file.hpp"
#include "port_type.hpp"
#include "control_stream.hpp"
#include "../logger.hpp"
#include "server_reply.hpp"

namespace foofxp {
namespace model {
namespace ftp {

class client
{
public:

	typedef enum
	{
		not_connected,
		awaiting_welcome_message,
		awaiting_auth_tls_reply,
		awaiting_handshake,
		awaiting_pbsz_reply,
		awaiting_user_reply,
		awaiting_pass_reply,
		logged_in,
		awaiting_cwd_reply,
		awaiting_pwd_reply,
		awaiting_stat_l_reply
	}
	state_type;
	
	client(const std::string & host, port_type port, bool ipv6, bool auth_tls, 
		const std::string & username, const std::string & password,
		boost::asio::io_service & io_service,
		boost::asio::ssl::context & context);
	
	~client();
	
	typedef boost::signal<void(client & client)> client_event;
	typedef boost::signal<void(client & client, const std::string & message)>
		client_error_event;
	typedef boost::signal<void(client & client, const std::string & path)>
		client_changed_directory_event;
	typedef boost::signal<void(client & client, 
		const std::vector<file> & files)>
		received_directory_list_event;
	
	client_event idle;
	client_event busy;
	client_error_event error_occurred;
	client_error_event fatal_error_occurred;
	client_changed_directory_event changed_directory;
	client_error_event change_directory_failed;
	received_directory_list_event received_directory_list;
	
	const logger & log() const { return log_; };
	logger & log() { return log_; };
	
	void begin_connect();
	void begin_change_directory(const std::string & directory);
	void begin_get_directory_contents();
	void begin_close();
	
	void handle_connect();
	void handle_line_received(const std::string & line);
	void handle_control_stream_error(const std::string & message, bool fatal);
	void handle_handshake();
	
private:
	
	bool handle_basic_reply_details(const server_reply & reply);
	
	void handle_welcome_message(const server_reply & reply);
	void handle_auth_tls_reply(const server_reply & reply);
	void handle_pbsz_reply(const server_reply & reply);
	void handle_user_reply(const server_reply & reply);
	void handle_pass_reply(const server_reply & reply);
	void handle_cwd_reply(const server_reply & reply);
	void handle_pwd_reply(const server_reply & reply);
	void handle_stat_l_reply(const server_reply & reply);
	
	void handle_unexpected_message(const server_reply & reply);
	
	inline void send_command(const std::string & command);
	
	state_type state_;
	
	bool auth_tls_;
	std::string username_;
	std::string password_;
	
	std::vector<std::string> directory_list_output_buffer_;
	
	ftp::control_stream<client> control_stream_;
	logger log_;
	
}; // class client

} // namespace ftp
} // namespace model
} // namespace foofxp

#endif // FOOFXP_CLIENT_HPP_INCLUDED
