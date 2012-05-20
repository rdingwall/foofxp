#include "commands.hpp"
#include "../../utility/enforce_that.hpp"
#include "../../utility/format.hpp"

using std::invalid_argument;
using std::size_t;
using std::string;
using namespace foofxp::utility;

namespace foofxp {
namespace model {
namespace ftp {
namespace commands {

string auth_tls() { return "AUTH TLS"; }

string cwd(const string & path)
{
	enforce_that(!path.empty(), invalid_argument, "Empty path.");
	
	string command_format = "CWD %s";
	size_t size = command_format.length() + path.length();
	
	return format(size, command_format, path.c_str());
}

string dele(const string & path) throw (invalid_argument)
{
	enforce_that(!path.empty(), invalid_argument, "Empty path.");
	
	string command_format = "DELE %s";
	size_t size = command_format.length() + path.length();
	
	return format(size, command_format, path.c_str());
}

string feat() { return "FEAT"; }

string mkdir(const string & path) throw (invalid_argument)
{
	enforce_that(!path.empty(), invalid_argument, "Empty path.");
	
	string command_format = "MKD %s";
	size_t size = command_format.length() + path.length();
	
	return format(size, command_format, path.c_str());
}

string pass(const string & password) throw (invalid_argument)
{
	enforce_that(!password.empty(), invalid_argument, "Empty password.");
	
	string command_format = "PASS %s";
	size_t size = command_format.length() + password.length();
	
	return format(size, command_format, password.c_str());
}

string pasv() { return "PASV"; }

string pbsz()
{
	// Does anyone ever use a protection buffer size > 0?
	return "PBSZ 0";
}

string pwd() { return "PWD"; }

string site(const string & command) throw (invalid_argument)
{
	enforce_that(!command.empty(), invalid_argument, "Empty command.");
	
	string command_format = "SITE %s";
	size_t size = command_format.length() + command.length();
	
	return format(size, command_format, command.c_str());
}

string stat_l() { return "STAT -l"; }

string user(const string & username) throw (invalid_argument)
{
	enforce_that(!username.empty(), invalid_argument, "Empty username.");
	
	string command_format = "USER %s";
	size_t size = command_format.length() + username.length();
	
	return format(size, command_format, username.c_str());
}

} // namespace commands
} // namespace ftp
} // namespace model
} // namespace foofxp
