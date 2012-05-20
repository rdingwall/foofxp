// Copyright (c) 2007, Richard Dingwall
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
//     * Redistributions of source code must retain the above copyright notice,
//       this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above copyright
//       notice, this list of conditions and the following disclaimer in the
//       documentation and/or other materials provided with the distribution.
//     * Neither the name of the organization nor the names of its contributors
//       may be used to endorse or promote products derived from this software
//       without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE 
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
// POSSIBILITY OF SUCH DAMAGE.

#include <limits> // numeric_limits
#include <cstdio> // snprintf
#include <boost/preprocessor/stringize.hpp>
#include "to_string.hpp"

using std::string;

namespace foofxp
{

namespace utility
{

namespace lexical_cast
{

/// @def bytes_max
///
/// Returns the maximum number of bytes required to store this type in a buffer.
#define bytes_max(type) \
	(sizeof(BOOST_PP_STRINGIZE(std::numeric_limits<type>::max())))

// A template specialisation to cast to a string from a boolean value.
template<>
string
to_string<bool>(const bool & input_value)
{
	return input_value ? "true" : "false";
}

// A template specialisation to cast to a string from a string.
template<>
string
to_string<string>(const string & input_value)
{
	return input_value;
}

// A template specialisation to cast to a string from an integer.
template<>
string
to_string<int>(const int & input_value)
{
	char buf[bytes_max(int)];
	return string(&buf[0], size_t(::snprintf(&buf[0], sizeof(buf), "%d", 
	                                         input_value)));
}

// A template specialisation to cast to a string from an unsigned integer.
template<>
string
to_string<unsigned int>(const unsigned int & input_value)
{
	char buf[bytes_max(unsigned int)];
	return string(&buf[0], size_t(::snprintf(&buf[0], sizeof(buf), "%u", 
	                                         input_value)));
}

// A template specialisation to cast to a string from long.
template<>
string
to_string<long>(const long & input_value)
{
	char buf[bytes_max(long)];
	return string(&buf[0], size_t(::snprintf(&buf[0], sizeof(buf), "%ld", 
	                                         input_value)));
}

// A template specialisation to cast to a string from an unsigned long.
template<>
string
to_string<unsigned long>(const unsigned long & input_value)
{
	char buf[bytes_max(unsigned long)];
	return string(&buf[0], size_t(::snprintf(&buf[0], sizeof(buf), "%lu", 
	                                         input_value)));
}

// A template specialisation to cast to a string from a short.
template<>
string
to_string<short>(const short & input_value)
{
	char buf[bytes_max(short)];
	return string(&buf[0], size_t(::snprintf(&buf[0], sizeof(buf), "%hd",
	                                         input_value)));
}

// A template specialisation to cast to a string from an unsigned short.
template<>
string
to_string<unsigned short>(const unsigned short & input_value)
{
	char buf[bytes_max(unsigned short)];
	return string(&buf[0], size_t(::snprintf(&buf[0], sizeof(buf), "%hu",
	                                         input_value)));
}

} // namespace lexical cast

} // namespace utility

} // namespace foofxp
