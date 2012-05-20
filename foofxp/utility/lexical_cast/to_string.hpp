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

/// @file to_string.hpp
///
/// @brief Header file containing the lexical cast to_string() method.

#ifndef FOOFXP_TO_STRING_HPP_INCLUDED
#define FOOFXP_TO_STRING_HPP_INCLUDED

#include <string>
#include <stdexcept>

namespace foofxp
{

namespace utility
{

namespace lexical_cast
{
	
/// @brief Cast to a string from a user-specified input_type.
///
/// @param[in] input_value A reference to the input value.
///
/// @returns A string representation of the input value.
///
///
/// @par Examples:
///
/// Casting from an unsigned int to a string:
///
/// @code
/// unsigned int n = 42;
/// std::string s = lexical_cast::to_string(n);
/// @endcode
///
/// @par Specialisations:
///
/// High performance template specialisations exist for the following types:
///
/// @li @c string
/// @li @c boolean
/// @li @c int and @c unsigned @c int
/// @li @c long and @c unsigned @c long
/// @li @c short and @c unsigned @c short
///
/// @par References:
/// 
/// @li Wilson, M. (2007). Shims, Template Tools. In: <em>Extended STL, 
/// Volume 1: Collections and Iterators.</em> Stoughton, MA: Pearson Education, 
/// Inc. p49-50, p67-68.
///
/// @ingroup lexical_cast
template<typename input_type>
std::string to_string(const input_type & input_value);

} // namespace lexical_cast

} // namespace utility

} // namespace foofxp

#endif // FOOFXP_TO_STRING_HPP_INCLUDED
