#include <ctime>
#include <fstream>

// These two are for getpid().
#include <sys/types.h>
#include <unistd.h>

#include "format.hpp"
#include "trace.hpp"

using namespace std;

namespace foofxp {
namespace utility {

static std::string get_trace_prefix(const std::string & path, 
	int line_number)
{
	string file_name = path;
	
	// Clean-up the path.
	if (file_name.length() > 0)
	{
		// Trim surrounding quotes, e.g. "foofxp.cpp" -> foofxp.cpp.
		if (file_name[0] == '"' && file_name[file_name.length() - 1] == '"')
			file_name = file_name.substr(1, file_name.length() - 2);
		
		// Trim path. We don't care where it was compiled, just the file name.
		string::size_type pos = file_name.find_last_of("\\/");
		if (pos != string::npos)
			file_name = file_name.substr(pos + 1);
	}
	
	// Get the time prefix.
	time_t now = time(0);
	char time_buf[20];
	strftime(time_buf, sizeof(time_buf), "%Y-%m-%d %X", localtime(&now));
	
	char buf[256];
	snprintf(buf, sizeof(buf), "[%s %s:%i]", time_buf, file_name.c_str(),
		line_number);
	
	return buf;
}

void __trace(const std::string & message, const std::string & path, 
	int line_number)
{	
	// Get the file name: foofxp.<pid>.log.
	string trace_file = format(24, "foofxp-trace-%d.log", getpid());
	
	ofstream stream(trace_file.c_str(), ios_base::app);
	
	string prefix = get_trace_prefix(path, line_number);
	
	stream << prefix << " " << message << endl;
	
	stream.close();
}

void __trace_this(const std::string & message, const std::string & path, 
	int line_number, const void * sender)
{	
	// Get the file name: foofxp.<pid>.log.
	string trace_file = format(24, "foofxp-trace-%d.log", getpid());
	
	ofstream stream(trace_file.c_str(), ios_base::app);
	
	string prefix = get_trace_prefix(path, line_number);
	
	stream << prefix << " " << "(this=" << sender << ") " << message << endl;
	
	stream.close();
}

} // namespace utility
} // namespace foofxp