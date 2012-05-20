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

/// @file unrecoverable_session_error.hpp
///
/// @brief Header file for unrecoverable_session_error exception class
/// definition.

#ifndef FOOFXP_UNRECOVERABLE_SESSION_ERROR_HPP_INCLUDED
#define FOOFXP_UNRECOVERABLE_SESSION_ERROR_HPP_INCLUDED

#include <stdexcept>
#include <string>

namespace foofxp {
namespace model {

/// @brief A fatal exception raised by a session. Not recoverable.
class unrecoverable_session_error : public virtual std::runtime_error
{
public:
	
	/// @brief Construct a unrecoverable_session_error exception.
	///
	/// @param[in] message A string describing the error.
	unrecoverable_session_error(const std::string & message) : 
		std::runtime_error(message)
	{};

}; // class unrecoverable_session_error

} // namespace model
} // namespace foofxp

#endif // FOOFXP_UNRECOVERABLE_SESSION_ERROR_HPP_INCLUDED
