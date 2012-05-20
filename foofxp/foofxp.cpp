#include <iostream>
#include <vector>
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <boost/shared_ptr.hpp>
#include "model/ftp/client.hpp"
#include "curses/curses.hpp"
#include "utility/trace.hpp"
#include "model/file.hpp"

//using namespace foofxp::curses;
using namespace std;
using namespace foofxp::model;
using namespace foofxp::model::ftp;
using foofxp::model::file;

void print_line(const logger & log)
{
	cout << "Session: " << log.last_line() << endl;
}

void print_error(const client & client, const string & msg)
{
	cout << "Error: " << msg << endl;
}

void print_fatal_error(const client & client, const string & msg)
{
	cout << "Fatal error: " << msg << endl;
}

void print_directory_list(const client & client, const vector<file> & files)
{
	for (vector<file>::const_iterator iter = files.begin(); iter != files.end();
		iter++)
	{
		cout << (*iter).name() << ": ";
		
		switch ((*iter).type())
		{
			case file::plain_old_file:
				cout << "file";
				break;
			
			case file::directory:
				cout << "dir";
				break;
			
			case file::link:
				cout << "link";
				break;
			
			case file::other:
				cout << "other";
				break;
		}
		
		cout << ", " << (*iter).size() << " bytes, " << (*iter).time() << endl;
	}
}

int main()
{
	trace("started application.");
	
	//map<string, bookmark> bookmarks_;
	//curses::terminal::enter_fullscreen_mode();
	//curses::terminal::exit_fullscreen_mode();
	
	boost::asio::io_service io_service;
	boost::asio::io_service::work work(io_service);
	boost::asio::ssl::context ctx(io_service, boost::asio::ssl::context::tlsv1_client);
	
	client c("192.168.0.7", 666, false, false, "test", "test", io_service, ctx);
	
	c.log().updated.connect(&print_line);
	c.error_occurred.connect(&print_error);
	c.fatal_error_occurred.connect(&print_fatal_error);
	c.received_directory_list.connect(&print_directory_list);
	
	c.begin_connect();

#if 0
	for (;;)
		io_service.poll();
#endif
	io_service.run();
	
	trace("exiting application.");
	
	return EXIT_SUCCESS;
}
