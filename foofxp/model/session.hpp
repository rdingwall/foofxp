#ifndef FOOFXP_CLIENT_HPP_INCLUDED
#define FOOFXP_CLIENT_HPP_INCLUDED

#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/thread_safe_signal.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <string>
#include "logger.hpp"

using std::deque;
using std::string;
using boost::posix_time::ptime;
using boost::signal;

namespace foofxp {
namespace model {

class session : public boost::enable_shared_from_this<session>
{
public:
	
	typedef ptime time_type;
	
	typedef signal<void(session & session)> session_event;
	typedef signal<void(session & session, const string & message)>
		session_error_event;
	
	virtual ~session() {};
	
	session_event idle;
	session_event busy;
	session_error_event error_occurred;
	session_error_event fatal_error_occurred;
	session_event changed_directory;
	session_error_event change_directory_failed;
	
	virtual void begin_open(bool ghost_kick) = 0;
	virtual void begin_change_directory(const string & directory) = 0;
	virtual void begin_get_directory_contents() = 0;
	virtual void begin_close() = 0;
	
	virtual string name() const = 0;
	virtual string working_directory() const = 0;
	virtual bool is_busy() const = 0;
	virtual const logger & log() const = 0;
	
	const time_type connected_time() const { return active_since_; };
	
protected:
	
	session() : active_since_() {};
	
	time_type active_since_;
	
private:
	
	session(const session & other);
	
	session & operator=(const session & other);
	
}; // class session

} // namespace model
} // namespace foofxp

#endif // FOOFXP_BASIC_SESSION_HPP_INCLUDED
