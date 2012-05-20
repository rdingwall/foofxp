#include <limits> // numeric_limits
#include <cstdlib> // strtol(), strtoul()
#include <cerrno> // errno
#include <boost/system/error_code.hpp>
#include "from_string.hpp"
#include "../enforce_that.hpp"

using std::string;
using std::invalid_argument;
using std::out_of_range;
using std::numeric_limits;

/// @def error_msg
///
/// @brief Returns a string description of the error number.
///
/// @param[in] error The error number to describe (e.g. @c errno for the current
/// error).	
#define error_msg(error) \
	(boost::system::error_code(error, \
	                           boost::system::errno_ecat).message())

namespace foofxp
{

namespace utility
{

namespace lexical_cast
{

// ------------------------------------------------------------------//
// to_long() and to_unsigned_long().
// ------------------------------------------------------------------//

/// @brief Helper function to parse a long integer from a string.
///
/// @param[in] str The string to parse.
///
/// @return A long.
///
/// @exception invalid_argument Thrown if a valid integer cannot be parsed.
/// @exception out_of_range Thrown if the number is out of range.
static inline long
to_long(const string & str)
throw(invalid_argument, out_of_range)
{
	const char * start_ptr(str.c_str());
	char * end_ptr;
	
	// Reset errno.
	errno = 0;
	
	long output_value(std::strtol(start_ptr, &end_ptr, 10));
	
	// If end_ptr has been set equal to start_ptr, then str does not contain
	// a valid number.
	enforce_that(end_ptr != start_ptr, invalid_argument, error_msg(errno));
	
	// Check errno values.
	enforce_that(errno != EINVAL, invalid_argument, error_msg(errno));
	enforce_that(errno != ERANGE, out_of_range, error_msg(errno));
	
	return output_value;
}

/// @brief Helper function to parse an unsigned long integer from a string.
///
/// @param[in] str The string to parse.
///
/// @return An unsigned long.
///
/// @exception invalid_argument Thrown if a valid integer cannot be parsed.
/// @exception out_of_range Thrown if the number is out of range.
static inline unsigned long
to_unsigned_long(const string & str)
throw(invalid_argument, out_of_range)
{	
	// If str depicts a negative number, strtoul acts the same as strtol but
	// casts the result to an unsigned integer. So we must check for 
	// negative values ourselves.
	enforce_that(str.find('-') == string::npos, out_of_range, error_msg(ERANGE));
	
	const char * start_ptr(str.c_str());
	char * end_ptr;
	
	// Reset errno.
	errno = 0;
	
	unsigned long output_value(std::strtoul(start_ptr, &end_ptr, 10));
	
	// If end_ptr has been set equal to start_ptr, then str does not contain
	// a valid number.
	enforce_that(end_ptr != start_ptr, invalid_argument, error_msg(errno));
	
	// Check errno values.
	enforce_that(errno != EINVAL, invalid_argument, error_msg(errno));
	enforce_that(errno != ERANGE, out_of_range, error_msg(errno));
	
	return output_value;
}

/// @brief Helper function to parse a float from a string.
///
/// @param[in] str The string to parse.
///
/// @return A float.
///
/// @exception invalid_argument Thrown if a valid float cannot be parsed.
/// @exception out_of_range Thrown if the number is out of range.
static inline float
to_float(const string & str)
throw(invalid_argument, out_of_range)
{
	const char * start_ptr(str.c_str());
	char * end_ptr;
	
	// Reset errno.
	errno = 0;
	
	float output_value(std::strtof(start_ptr, &end_ptr));
	
	// If end_ptr has been set equal to start_ptr, then str does not contain
	// a valid number.
	enforce_that(end_ptr != start_ptr, invalid_argument, error_msg(errno));
	
	// Check errno.
	enforce_that(errno != ERANGE, out_of_range, error_msg(errno));
	
	return output_value;
}

/// @brief Helper function to parse a double from a string.
///
/// @param[in] str The string to parse.
///
/// @return A float.
///
/// @exception invalid_argument Thrown if a valid double cannot be parsed.
/// @exception out_of_range Thrown if the number is out of range.
static inline double
to_double(const string & str)
throw(invalid_argument, out_of_range)
{
	const char * start_ptr(str.c_str());
	char * end_ptr;
	
	// Reset errno.
	errno = 0;
	
	double output_value(std::strtod(start_ptr, &end_ptr));
	
	// If end_ptr has been set equal to start_ptr, then str does not contain
	// a valid number.
	enforce_that(end_ptr != start_ptr, invalid_argument, error_msg(errno));
	
	// Check errno.
	enforce_that(errno != ERANGE, out_of_range, error_msg(errno));
	
	return output_value;
}

// ------------------------------------------------------------------//
// from_string() template specialisations.
// ------------------------------------------------------------------//

// A template specialisation to cast from a string to a long integer.
template<>
long
from_string(const string & input_value) throw(invalid_argument, out_of_range)
{
	return to_long(input_value);
}

// A template specialisation to cast from a string to an integer.
template<>
int 
from_string(const string & input_value)
throw(invalid_argument, out_of_range)
{
	long output_value(to_long(input_value));
	
	// Check output_value is within integer range.
	enforce_that(output_value >= numeric_limits<int>::min() && 
		output_value <= numeric_limits<int>::max(), 
		out_of_range, "Value too large to be stored as int.");
	
	return static_cast<int>(output_value);
}

// A template specialisation to cast from a string to a short integer.
template<>
short 
from_string(const string & input_value)
throw(invalid_argument, out_of_range)
{
	long output_value(to_long(input_value));
	
	// Check output_value is within short integer range.
	enforce_that(output_value >= numeric_limits<short>::min() && 
		output_value <= numeric_limits<short>::max(),
		out_of_range, "Value too large to be stored as short.");
	
	return static_cast<short>(output_value);
}

// A template specialisation to cast from a string to an unsigned long integer.
template<>
unsigned long 
from_string(const string & input_value)
throw(invalid_argument, out_of_range)
{
	return to_unsigned_long(input_value);
}

// A template specialisation to cast from a string to an unsigned integer.
template<>
unsigned int 
from_string(const string & input_value)
throw(invalid_argument, out_of_range)
{
	unsigned long output_value(to_unsigned_long(input_value));

	// Check output_value is within usigned integer range.
	enforce_that(output_value <= numeric_limits<unsigned int>::max(), 
		out_of_range, "Value too large to be stored as unsigned int.");

	return static_cast<unsigned int>(output_value);
}

// A template specialisation to cast from a string to an unsigned short integer.
template<>
unsigned short 
from_string(const string & input_value)
throw(invalid_argument, out_of_range)
{
	unsigned long output_value(to_unsigned_long(input_value));
	
	// Check output_value is within usigned short integer range.
	enforce_that(output_value <= numeric_limits<unsigned short>::max(), 
		out_of_range, "Value too large to be stored as unsigned short.");
	
	return static_cast<unsigned short>(output_value);
}

// A template specialisation to cast from a string to a float.
template<>
float 
from_string(const string & input_value)
throw(invalid_argument, out_of_range)
{
	return to_float(input_value);
}

// A template specialisation to cast from a string to a double.
template<>
double 
from_string(const string & input_value)
throw(invalid_argument, out_of_range)
{
	return to_double(input_value);
}

// A template specialisation to cast from a string to a string (i.e., no cast).
template<>
string 
from_string(const string & input_value) throw()
{
	return input_value;
}

} // namespace lexical cast

} // namespace utility

} // namespace foofxp
