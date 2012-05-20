#ifndef FOOFXP_TRACE_HPP_INCLUDED
#define FOOFXP_TRACE_HPP_INCLUDED

#include <string>
#include <boost/preprocessor/stringize.hpp>

#define FOOFXP_TRACE

#if defined(FOOFXP_TRACE)
#	define trace(message) \
		foofxp::utility::__trace((message), \
			BOOST_PP_STRINGIZE(__FILE__), __LINE__)
#	define trace_this(message) \
		foofxp::utility::__trace_this((message), \
			BOOST_PP_STRINGIZE(__FILE__), __LINE__, this)
#else
#	define trace(message) 
#	define trace_this(message) 
#endif

namespace foofxp {
namespace utility {

void __trace(const std::string & message, const std::string & path, 
	int line_number);
	
void __trace_this(const std::string & message, const std::string & path, 
	int line_number, const void * sender);

} // namespace utility
} // namespace foofxp

#endif // FOOFXP_TRACE_HPP_INCLUDED
