#ifndef FOOFXP_SESSION_LOG_HPP_INCLUDED
#define FOOFXP_SESSION_LOG_HPP_INCLUDED

#include <string>
#include <deque>
#include <boost/thread_safe_signal.hpp>

namespace foofxp {
namespace model {

class logger
{
public:
	
	typedef boost::signal<void(const logger &)> log_event;
	typedef std::deque<std::string> string_deque;
	typedef string_deque::size_type size_type;
	
	logger(size_type size);
	logger(const logger & other);
	~logger();
	
	log_event updated;
	
	std::string last_line() const;
	
	string_deque lines() const { return lines_; };
	
	void add_line(const std::string & line);
		
private:
	
	void trim_size();
	
	string_deque lines_;
	size_type max_size_;
	
}; // class logger

} // namespace model
} // namespace foofxp

#endif // FOOFXP_SESSION_LOG_HPP_INCLUDED
