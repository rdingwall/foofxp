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

/// @file io.hpp
///
/// @brief Header file containing IO-related utility functions.

#ifndef FOOFXP_IO_HPP_INCLUDED
#define FOOFXP_IO_HPP_INCLUDED

#include <string>
#include <istream>
#include <boost/asio/streambuf.hpp>

namespace foofxp
{

namespace utility
{

namespace io
{

/// @brief Pop the entire contents of a stream buffer to a string.
///
/// @param[in, out] buffer The stream buffer to read.
/// @param[in, out] str The string to write to.
///
/// @ingroup io
inline void
pop_line(boost::asio::streambuf & buffer, std::string & str)
{
	std::istream stream(&buffer);
	std::getline(stream, str);
}

} // namespace io

} // namespace utility

} // namespace foofxp

#endif // FOOFXP_IO_HPP_INCLUDED