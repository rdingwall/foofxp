

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

/// @file session_log.hpp
///
/// @brief Header file for FTP session_log class definition.

#ifndef FOOFXP_SESSION_LOG_HPP_INCLUDED
#define FOOFXP_SESSION_LOG_HPP_INCLUDED

#include <string>
#include "../log.hpp"

namespace foofxp {
namespace model {
namespace ftp {

class ftp_session_log : public session_log
{
public:
	/// @brief Log an outgoing message.
	///
	/// @param[in] line The message.
	void add_outgoing(const std::string & line)
	{
		std::string entry(">>> " + line);
		lines_.push_front(entry);
		trim_size();
		updated(*this);
	};
	
	/// @brief Log an incoming message.
	///
	/// @param[in] line The message.
	void add_incoming(const std::string & line)
	{
		std::string entry("<<< " + line);
		lines_.push_front(entry);
		trim_size();
		updated(*this);
	};
	
	/// @brief Log a server reply message.
	///
	/// @param[in] line The message.
	void add_reply(const std::string & line)
	{
		lines_.push_front(line);
		trim_size();
		updated(*this);
	};
};

} // namespace ftp
} // namespace model
} // namespace foofxp

#endif // FOOFXP_SESSION_LOG_HPP_INCLUDED
