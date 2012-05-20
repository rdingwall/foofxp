#include <boost/algorithm/string/predicate.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
#include "file_mapper.hpp"
#include "../../utility/lexical_cast/from_string.hpp"

using namespace std;
using namespace boost::algorithm;
using namespace boost::posix_time;
using boost::posix_time::ptime;
using namespace boost::gregorian;
using boost::gregorian::date;
using namespace boost::algorithm;
using namespace foofxp::utility;

namespace foofxp {
namespace model {
namespace ftp {

static file to_file(const string & line) throw();
static int get_month_index(const string & month_name) throw();
static bool is_year(const string & clock_token);
static ptime assemble_date_time(const string & month_token, 
	const string & day_token, const string & clock_token);
static bool has_link_target(const string & item);
static void trim_link_target(string & file_name);
static string::size_type get_file_name_offset(const string & line) throw();
static file::file_type get_file_type(const char type);
static string::size_type get_month_offset(const string & line);

vector<file> get_files(const vector<string> & lines)
{
	vector<file> files;
	
	for (vector<string>::const_iterator iter = lines.begin(); 
		iter != lines.end(); iter++)
	{
		const string & entry = *iter;
		try
		{
			if (!boost::algorithm::starts_with(entry, "total"))
				files.push_back(to_file(entry));
		}
		catch (runtime_error e)
		{
			ostringstream s;
			
			s << "Could not parse directory list entry '";
			s << entry;
			s << "': ";
			s << e.what();
			
			throw runtime_error(s.str());
		}
		
	}
	
	return files;
}

file to_file(const string & line) throw()
{
	string::size_type name_offset = get_file_name_offset(line);
	
	if (name_offset == string::npos)
		throw runtime_error("No month token found.");
	
	string meta_block = line.substr(0, name_offset - 1);
	
	vector<string> meta_tokens;

	// Split meta data tokens.
	split(meta_tokens, meta_block, is_space(), token_compress_on);

	if (meta_tokens.size() < 6)
		throw runtime_error("Too few tokens in line.");
	
	string size_token;
	string month_token;
	string day_token;
	string clock_token;
	string permissions_token;
	
	switch (meta_tokens.size())
	{
	case 8: 
		// The entry has permissions, link count, owner, group,
		// size, month, day, and time/year, e.g.:
		// "-rw-r--r--  1 root  other  531 Jan 29 03:26 README"
		permissions_token = meta_tokens[0];
		size_token = meta_tokens[4];
		month_token = meta_tokens[5];
		day_token = meta_tokens[6];
		clock_token = meta_tokens[7];
		break;
	
	case 7:
		// The entry has permissions, link count, group, size,
		// month, day, and time/year, but no user, e.g.:
		// "-rw-r--r--  1 other  531 Jan 29 03:26 README"
		permissions_token = meta_tokens[0];
		size_token = meta_tokens[3];
		month_token = meta_tokens[4];
		day_token = meta_tokens[5];
		clock_token = meta_tokens[6];
		break;
	
	case 6:
		// The entry has permissions, link count, size, month,
		// day, and time/year, but no user or group, e.g.:
		// "-rw-r--r--  1  531 Jan 29 03:26 README"
		permissions_token = meta_tokens[0];
		size_token = meta_tokens[2];
		month_token = meta_tokens[3];
		day_token = meta_tokens[4];
		clock_token = meta_tokens[5];
		break;
	
	default:
		throw runtime_error("Too few meta-data tokens.");
	}
	
	file f;
	
	// Get file name.
	string file_name = line.substr(name_offset);
	
	// Handle link name -> link target syntax, e.g. 
	// "lrwxrwxrwx   1        7 Jan 25 00:17 bin -> usr/bin"
	if (has_link_target(file_name))
	{
		trim_link_target(file_name);
		f.type(file::link);
	}
	else
		f.type(get_file_type(permissions_token[0]));
	
	f.name(file_name);
	f.time(assemble_date_time(month_token, day_token, clock_token));
	f.size(lexical_cast::from_string<unsigned long>(size_token));
	
	return f;
}

int get_month_index(const string & month_name) throw()
{
	if (month_name.length() != 3)
		throw runtime_error("Month must be 3 characters long.");
	
	if (month_name == "Jan")
		return 1;
	else if (month_name == "Feb")
		return 2;
	else if (month_name == "Mar")
		return 3;
	else if (month_name == "Apr")
		return 4;
	else if (month_name == "May")
		return 5;
	else if (month_name == "Jun")
		return 6;
	else if (month_name == "Jul")
		return 7;
	else if (month_name == "Aug")
		return 8;
	else if (month_name == "Sep")
		return 9;
	else if (month_name == "Oct")
		return 10;
	else if (month_name == "Nov")
		return 11;
	else if (month_name == "Dec")
		return 12;
	else
		throw runtime_error("Unknown month.");
}
	
bool is_year(const string & clock_token)
{
	return clock_token.find(':') == string::npos;
}

ptime assemble_date_time(const string & month_token, 
                   const string & day_token,
                   const string & clock_token)
{	
	// Get month index.
	int month = get_month_index(month_token);
	
	// Get day of month.
	int day = lexical_cast::from_string<short>(day_token);
	
	if (is_year(clock_token)) // Server has given us a date only.
	{
		// Get year.
		int year = lexical_cast::from_string<int>(clock_token);
		
		// Construct date time.
		return ptime(date(year, month, day), 
		             hours(0) + minutes(0));
	}
	
	// Server has given us an hh:mm time, with no year.
	else if (clock_token.length() == 5)
	{
		// Get hours.
		int hrs = lexical_cast::from_string<int>(clock_token.substr(0, 2));
		
		// Get mins.
		int mins = lexical_cast::from_string<int>(clock_token.substr(3, 2));
		
		// Get today's date.
		date today(day_clock::local_day());
		
		// Construct date using today's year.
		date file_date(today.year(), month, day);
		
		if (file_date > today)
			// Date must have been last year.
			file_date -= years(1);
		
		// Construct date time.
		return ptime(file_date, hours(hrs) + minutes(mins));	
	}
	
	else
		throw runtime_error("Unknown clock/year format.");
}

bool has_link_target(const string & item)
{
	return item.find(" -> ") != string::npos;
}
	
void trim_link_target(string & file_name)
{
	string::size_type link_offset = file_name.find(" -> ");
	
	if (link_offset != string::npos)
		file_name = file_name.substr(0, link_offset);
}
	
string::size_type get_file_name_offset(const string & line) throw()
{
	string::size_type month_offset = get_month_offset(line);
	if (month_offset == string::npos)
		throw runtime_error("No month found in line.");
	
	string::size_type offset = month_offset;
	
	// Step to the end of the month token.
	offset = line.find_first_of(' ', offset);
	
	// Step to the end of the day token.
	offset = line.find_first_not_of(' ', offset);
	offset = line.find_first_of(' ', offset);
	
	// Step to the end of the time or year token.
	offset = line.find_first_not_of(' ', offset);
	offset = line.find_first_of(' ', offset);
	
	return line.find_first_not_of(' ', offset);
}

file::file_type get_file_type(const char type)
{
	switch (type)
	{
		case '-': // Ordinary file.
			return file::plain_old_file;
		
		case 'l': // Symbolic link.
		case 'd': // Directory.
			return file::directory;
		
		case 'b': // Block special file.
		case 'c': // Character special file.
		case 'p': // FIFO special file.
		case 's': // Socket link.
		default:
			return file::other;
	}
}
	
string::size_type get_month_offset(const string & line)
{
	string::size_type offset;

	offset = line.find("Jan ");
	if (offset != string::npos)
		return offset;

	offset = line.find("Feb ");
	if (offset != string::npos)
		return offset;

	offset = line.find("Mar ");
	if (offset != string::npos)
		return offset;

	offset = line.find("Apr ");
	if (offset != string::npos)
		return offset;

	offset = line.find("May ");
	if (offset != string::npos)
		return offset;

	offset = line.find("Jun ");
	if (offset != string::npos)
		return offset;

	offset = line.find("Jul ");
	if (offset != string::npos)
		return offset;

	offset = line.find("Aug ");
	if (offset != string::npos)
		return offset;

	offset = line.find("Sep ");
	if (offset != string::npos)
		return offset;

	offset = line.find("Oct ");
	if (offset != string::npos)
		return offset;

	offset = line.find("Nov ");
	if (offset != string::npos)
		return offset;

	offset = line.find("Dec ");
	if (offset != string::npos)
		return offset;

	return string::npos;
}

} // namespace ftp
} // namespace model
} // namespace foofxp
