#ifndef FOOFXP_FTP_SESSION_HPP_INCLUDED
#define FOOFXP_FTP_SESSION_HPP_INCLUDED

#include <string>
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <boost/shared_ptr.hpp>
#include "session.hpp"
#include "ftp/client.hpp"

using std::string;
using boost::shared_ptr;
using boost::asio::io_service;
using boost::asio::ssl::context;

namespace foofxp {
namespace model {

class client_task;

class ftp_session : public session
{
public:
	
	
	public ftp_session(shared_ptr<bookmark> bookmark, io_service & service,
		context & context) : client_(bookmark, service, context)
	{};
	
	~ftp_session() {};
	
	void begin_open(bool ghost_kick)
	{
		client_.begin_open(ghost_kick);
	};
	
	void begin_change_directory(const string & path)
	{
		string command = commands::cwd(path);
		client_.begin_send_command(command);
	};
	
	void begin_get_directory_contents()
	{
		
	};
	
	void begin_close()
	{
		client_.disconnect();
	};

private:

	ftp_client client_;
}; // class ftp_session

} // namespace model
} // namespace foofxp

#endif // FOOFXP_FTP_SESSION_HPP_INCLUDED
