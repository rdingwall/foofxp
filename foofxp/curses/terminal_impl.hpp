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

/// @file terminal_impl.hpp
///
/// @brief Header file for the curses terminal_impl class definition.

#ifndef CURSES_APPLICATION_IMPL_HPP_INCLUDED
#define CURSES_APPLICATION_IMPL_HPP_INCLUDED

#include <stdexcept>
#include <termios.h>
#include "window.hpp"
#include "cursor_mode.hpp"

namespace foofxp
{

namespace curses
{

/// @brief Curses terminal_impl class.
///
/// Carries terminal implementation.
class terminal_impl: public window
{
public:
	
	/// @brief Construct a terminal.
	terminal_impl();
	
	/// @brief Enter fullscreen mode.
	///
	/// @exception std::runtime_error Thrown if the terminal could not be
	/// started.
	void enter_fullscreen_mode() throw(std::runtime_error);
	
	/// @brief Exit fullscreen mode.
	void exit_fullscreen_mode();
	
	void cursor(cursor_mode mode);
	
	void render() const;
	
	void visit() const;
	
	/// @brief A pointer to a window.
	typedef boost::shared_ptr<window> window_pointer;
	
	/// @brief A collection of sub windows.
	typedef std::deque<window_pointer> window_collection;
	
	/// @brief Get the window's child windows.
	///
	/// @returns A const reference to the child window collection.
	const window_collection & windows() const
	{
		return windows_;
	};
	
	/// @brief Get the window's child windows.
	///
	/// @returns A reference to the child window collection.
	window_collection & windows() { return windows_; };
	
private:
	
	/// @brief Render the window's child windows.
	void render_children()
	{
		std::for_each(windows_.end(), windows_.begin(),
			boost::bind(&window::render, _1));
	};
	
	window_collection windows_;
	
	/// @brief Disable unwanted keyboard keys.
	///
	/// Disables @c INTR, @c QUIT, @c VDSUSP and @c SUSP keys.
	void disable_keys();
	
	/// @brief The termios settings that were used before.
	struct termios old_termios_;
	
}; // class terminal_impl

} // namespace curses

} // namespace foofxp

#endif // CURSES_APPLICATION_IMPL_HPP_INCLUDED