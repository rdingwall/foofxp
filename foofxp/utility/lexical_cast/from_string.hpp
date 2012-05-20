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

/// @file from_string.hpp
///
/// @brief Header file containing the lexical cast from_string() methods.

#ifndef FOOFXP_FROM_STRING_HPP_INCLUDED
#define FOOFXP_FROM_STRING_HPP_INCLUDED

#include <string>
#include <stdexcept>

namespace foofxp
{

namespace utility
{

namespace lexical_cast
{

/// @brief Cast from a string to a user-specified output_type.
///
/// The output type is specified at compile time as a template parameter.
///
/// @param[in] input_value The input string.
///
/// @returns An object of output type.
///
/// @par Examples:
///
/// Casting an unsigned short from a string:
///
/// @code
/// string str = "42";
/// unsigned short n = lexical_cast::from_string<unsigned short>(str);
/// @endcode
///
/// @par Specialisations:
///
/// High performance template specialisations exist for the following types:
///
/// @li @c string
/// @li @c short and @c unsigned @c short
/// @li @c int and @c unsigned @c int
/// @li @c long and @c unsigned @c long
/// @li @c float and @c double
///
/// @exception std::invalid_argument Thrown if the input value cannot be parsed
/// successfully.
/// @exception std::out_of_range Thrown if the input value contains a valid 
/// value, but is out of range.
///
/// @ingroup lexical_cast
template<typename output_type>
output_type from_string(const std::string & input_value)
throw(std::invalid_argument, std::out_of_range);

} // namespace lexical_cast

} // namespace utility

} // namespace foofxp

#endif // FOOFXP_FROM_STRING_HPP_INCLUDED
