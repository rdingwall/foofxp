#include "logger.hpp"

using std::string;

namespace foofxp {
namespace model {

logger::logger(size_type size) : lines_(), max_size_(size) {}
	
logger::logger(const logger & other) : 
	lines_(other.lines_), max_size_(other.max_size_)
{}
	
logger::~logger() {}

string logger::last_line() const
{
	if (lines_.empty())
		// Return empty string.
		return string();
		
	else
		return string(lines_.front());
}
	
void logger::add_line(const string & line)
{
	lines_.push_front(line);
	trim_size();
	updated(*this);
}

void logger::trim_size()
{
	// Trim log.
	if (lines_.size() > max_size_)
		lines_.resize(max_size_);
}

} // namespace model
} // namespace foofxp
