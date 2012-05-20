#include <cassert>
#include "../../utility/enforce_that.hpp"
#include "../../utility/lexical_cast/lexical_cast.hpp"
#include "server_reply.hpp"

using namespace std;
using namespace foofxp::utility;

namespace foofxp {
namespace model {
namespace ftp {

server_reply::server_reply(const string & line) : 
	line_(line), is_valid_format_(is_valid_format(line))
{}

bool server_reply::is_end_of_reply() const
{	
	// 3-digit reply code followed by a space, e.g.:
	//    213- status of -l:    <--- not the end
	//    213 End of Status.    <--- end
	return is_valid_format_ && line_[3] == ' ';
}

bool server_reply::is_transient_negative_reply() const throw(invalid_argument)
{
	if (!is_valid_format_)
		throw invalid_argument("Invalid server reply format.");
	
	return line_[0] == '4';
}
	
bool server_reply::is_permanent_negative_reply() const throw(invalid_argument)
{
	if (!is_valid_format_)
		throw invalid_argument("Invalid server reply format.");
	
	return is_valid_format_ && line_[0] == '5';
}

bool server_reply::is_negative_reply() const throw(invalid_argument)
{
	if (!is_valid_format_)
		throw invalid_argument("Invalid server reply format.");
	
	return line_[0] == '4' || line_[0] == '5';
}

server_reply::reply_code_type server_reply::get_reply_code() const
	throw(invalid_argument, out_of_range)
{
	if (!is_valid_format_)
		throw new invalid_argument("Invalid server reply format.");
		
	short code = lexical_cast::from_string<short>(line_.substr(0, 3));
	
	if (code < 1)
		throw out_of_range("Server reply code out of range.");
	
	else if (code > 699)
		throw out_of_range("Server reply code out of range.");
	
	return code;
}

string server_reply::get_pwd_path() const throw(invalid_argument)
{
	if (!is_valid_format_)
		throw new invalid_argument("Invalid server reply format.");
	
	// Find the start of the path.
	string::size_type start = line_.find('"');
	
	enforce_that(start != string::npos, invalid_argument,
		"Invalid path format in PWD reply.");
	
	start++;
	
	// Find the end of the path.
	string::size_type end = line_.find('"', start);
	
	enforce_that(end != string::npos, invalid_argument,
		"Invalid path format in PWD reply.");
	
	return line_.substr(start, end - start);
}

string server_reply::get_message() const throw(invalid_argument)
{
	if (!is_valid_format_)
		throw new invalid_argument("Invalid server reply format.");
	
	// Where does the message start? I.e. "421 Blah" starts at pos 4, 
	// "421- Blah" starts at 5.
	if (line_[3] == '-')
		return line_.substr(5);
	else
		return line_.substr(4);
}

bool server_reply::is_valid_format(const string & line)
{
	// Line must be big enough to fit 3 digits and a space.
	if (line.length() < 4)
		return false;
	
	if (!isdigit(line[0]) ||
		!isdigit(line[1]) ||
		!isdigit(line[2]))
		return false;
	
	// Possibly followed by a hyphen, which pushes everything out by one.
	if (line[3] == '-')
	{
		// Line must be a bit longer to fit the hyphen.
		if (line.length() < 5)
			return false;
		
		return line[4] == ' ';
	}
	else
		return line[3] == ' ';
}

} // namespace ftp
} // namespace model
} // namespace foofxp
