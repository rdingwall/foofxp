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

/// @file enforce.hpp
///
/// @brief Header file containing enforce function.

#ifndef FOOFXP_ENFORCE_HPP_INCLUDED
#define FOOFXP_ENFORCE_HPP_INCLUDED

#include <string>
#include <boost/preprocessor/stringize.hpp>

/// @def enforce_that
/// 
/// @brief Enforce a condition.
///
/// Somewhat similar to @c assert(). If the condition is violated, an exception 
/// is thrown with the specified message.
///
/// Based on <a href="http://www.ddj.com/dept/cpp/184403864">Enforcements</a>
/// (Andrei Alexandrescu, June 2003).
///
/// @param[in] expression The expression to evaluate.
/// @param[in] exception_type The type of exception to throw.
/// @param[in] message The message to construct the exception with.
///
/// @exception exception_type Thrown if the expression evaluates to false.
///
/// @ingroup exception_handling
#define enforce_that(expression, exception_type, message) \
	foofxp::utility::__enforce_that<exception_type>((expression), (message), \
		BOOST_PP_STRINGIZE(__FILE__), \
		BOOST_PP_STRINGIZE(__LINE__));

namespace foofxp {
namespace utility {

template<class exception_type>
inline void __enforce_that(bool expression, const std::string & message,
	const std::string & file_name, 
	const std::string & line_number)
{
	if (!expression)
		throw exception_type(message);
}

} // namespace utility
} // namespace foofxp

#endif // FOOFXP_ENFORCE_HPP_INCLUDED
