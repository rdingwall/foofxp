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

#ifndef FOOFXP_REPLY_CODES_HPP_INCLUDED
#define FOOFXP_REPLY_CODES_HPP_INCLUDED

/// @file reply_codes.hpp
///
/// @brief Header file containing a list of FTP reply codes.

namespace foofxp {
namespace model {
namespace ftp {

/// @namespace foofxp::utility::ftp::reply_codes
///
/// @brief 3-digit FTP reply codes.
///
/// @par References:
/// 
/// @li Postel J, Reynolds M. (1985). Reply Codes by Function Groups. In: 
/// <em>File Transfer Protocol (FTP)</em>, <a
/// href="http://www.faqs.org/rfcs/rfc959.html">RFC 959</a>. ISI.
/// @li Horowitz, M. (1997). New FTP Replies. In: <em>FTP Security Extensions
/// </em>, <a href="http://www.faqs.org/rfcs/rfc2228.html">RFC 2228</a>. Cygnus
/// Solutions.
/// @li Allman, M. (1998). The EPRT Command, The EPSV Command. In: <em>FTP
/// Extensions for IPv6 and NATs</em>, <a
/// href="http://www.faqs.org/rfcs/rfc2428.html">RFC 2428</a>. Ohio University. 
///
/// @ingroup ftp
namespace reply_codes
{

// -------------------------------------------------------------------------- //
/// @name Positive Preliminary replies (100-199)
///
/// The requested action is being initiated; expect another reply before
/// proceeding with a new command.
// -------------------------------------------------------------------------- //
/// @{

/// @brief Data connection already open, transfer starting.
const short data_connect_exists = 125;

/// @brief File status okay; about to open data connection.
const short opening_data_connection = 150;

/// @}

// -------------------------------------------------------------------------- //
/// @name Positive Completion replies (200-299)
///
/// The requested action has been successfully completed.
// -------------------------------------------------------------------------- //
/// @{

/// @brief Command okay.
const short noop_okay = 200;

/// @brief Command okay.
const short type_okay = 200;

/// @brief Command okay.
const short port_okay = 200;

/// @brief Command okay.
const short eprt_okay = 200;

/// @brief Command okay.
const short umask_okay = 200;

/// @brief Command okay.
const short chmod_okay = 200;

/// @brief Command okay.
const short pbsz_okay = 200;

/// @brief Command okay.
const short prot_okay = 200;

/// @brief Command okay.
const short command = 200;

/// @brief Command not implemented, superfluous at this site.
const short superfluous_command_not_implemented = 202;

/// @brief System status, or system help reply.
const short feat_okay = 211;

/// @brief System status, or system help reply.
const short stat_okay = 211;

/// @brief File status.
const short size_okay = 213;

/// @brief File status.
const short mdtm_okay = 213;

/// @brief File status.
const short statl_okay = 213;

/// @brief Help message on how to use the server or the meaning of a particular
/// non-standard command.
const short help_okay = 214;

/// @brief SYST okay.
const short syst_okay = 215;

/// @brief Service ready for new user.
const short welcome = 220;

/// @brief Service closing TELNET connection (logged off if appropriate).
const short goodbye = 221;

/// @brief Data connection open; no transfer in progress.
const short abor_no_connection = 225;

/// @brief Closing data connection; requested file action successful (file 
/// transfer okay.)
const short transfer_okay = 226;

/// @brief Closing data connection; requested file action successful (file abort
/// okay.)
const short abor_okay = 226;

/// @brief Entering [passive, active] mode.
const short pasv_okay = 227;

/// @brief Entering extended passive mode.
const short epsv_okay = 229;

/// @brief User logged on, proceed.
const short login_okay = 230;

/// @brief Security data exchange complete.
const short auth_okay = 234;

/// @brief Requested file action okay, completed.
const short cwd_okay = 250;

/// @brief Requested file action okay, completed.
const short rmd_okay = 250;

/// @brief Requested file action okay, completed.
const short dele_okay = 250;

/// @brief Requested file action okay, completed.
const short rnto_okay = 250;

/// @brief "PATHNAME" created.
const short mkdir_okay = 257;

/// @brief "PATHNAME" is current directory.
const short pwd_okay = 257;

/// @}

// -------------------------------------------------------------------------- //
/// @name Positive Intermediate replies (300-399)
///
/// The command has been accepted, but the requested action is being held in
/// abeyance, pending receipt of further information.
// -------------------------------------------------------------------------- //
/// @{

/// @brief User name okay, need password.
const short user_okay = 331;

/// @brief Requested file action pending further information.
const short rest_okay = 350;

/// @brief Requested file action pending further information.
const short rnfr_okay = 350;

/// @}

// -------------------------------------------------------------------------- //
/// @name Transient Negative Completion replies (400-499)
///
/// The command was not accepted and the requested action did not take place, 
/// but the error condition is temporary and the action may be requested again.
// -------------------------------------------------------------------------- //
/// @{

/// @brief Service not available, closing control connection.
const short idle_timeout = 421;

/// @brief Service not available, closing control connection.
const short data_timeout = 421;

/// @brief Service not available, closing control connection.
const short too_many_users = 421;

/// @brief Service not available, closing control connection.
const short ip_limit = 421;

/// @brief Service not available, closing control connection.
const short ip_deny = 421;

/// @brief Service not available, closing control connection.
const short tls_fail = 421;

/// @brief Can't open data connection.
const short data_connection_failed = 425;

/// @brief Connection closed; transfer aborted.
const short data_connection_closed = 426;

/// @brief Requested action aborted. Local error in processing.
const short local_file_error = 426;

/// @}

// -------------------------------------------------------------------------- //
/// @name Permanent Negative Completion reply (500-599)
///
/// The command was not accepted and the requested action did not take place.
// -------------------------------------------------------------------------- //
/// @{

/// @brief Syntax error, command unrecognized.
const short bad_command = 500;

/// @brief Syntax error in parameters or arguments.
const short bad_arguments = 501;

/// @brief Command not implemented.
const short command_not_implemented = 502;

/// @brief Bad sequence of commands.
const short bad_command_sequence = 503;

/// @brief Bad sequence of commands.
const short need_user = 503;

/// @brief Bad sequence of commands.
const short need_pass = 503;

/// @brief Bad sequence of commands.
const short bad_pbsz = 503;

/// @brief Bad sequence of commands.
const short bad_prot = 503;

/// @brief Command not implemented for that parameter.
const short bad_auth = 504;

/// @brief Protocol not supported.
const short protocol_not_supported = 522;

/// @brief Not logged in.
const short not_logged_in = 530;

/// @brief Requested PROT level not supported by mechanism.
const short bad_prot_level = 536;

/// @brief Requested action not taken. File unavailable (e.g., file not found,
/// no access).
const short file_unavailable = 550;

/// @brief Requested action not taken. File name not allowed.
const short bad_filename = 553;

/// @brief Requested action not taken: invalid REST parameter.
const short bad_rest = 554;

/// @}

} // namespace reply_codes

} // namespace ftp
} // namespace model
} // namespace foofxp

#endif // FOOFXP_REPLY_CODES_HPP_INCLUDED
