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

#include <curses.h>
#include "terminal_impl.hpp"
#include "detail/color.hpp"

#ifndef COLOR_PAIRS
#  define COLOR_PAIRS 64
#endif

namespace foofxp
{

namespace curses
{

terminal_impl::terminal_impl() :
	window(stdscr)
{
}

// -------------------------------------------------------------------------- //
// Start/stop
// -------------------------------------------------------------------------- //

void terminal_impl::enter_fullscreen_mode() throw(std::runtime_error)
{
	if(!initscr())
		throw std::runtime_error("Could not initialize terminal_impl.");
	
	// Handle keystrokes as soon as they are entered, except
	// control characters like CTRL-Z etc.
	cbreak();
	
	// Don't echo key strokes to the screen.
	noecho();
	
	// Enable Fn, arrow keys etc.
	keypad(stdscr, TRUE);
	
	idlok(stdscr, FALSE);

	// Enable non-blocking keyboard polling.
	timeout(0);
	
	if (has_colors())
		detail::initialize_color_pairs();
	
	disable_keys();
}

void terminal_impl::exit_fullscreen_mode()
{
	endwin();
}


void terminal_impl::cursor(cursor_mode mode)
{
	::curs_set(mode);
}

// -------------------------------------------------------------------------- //
// Initialization
// -------------------------------------------------------------------------- //

void terminal_impl::disable_keys()
{
	intrflush(stdscr, FALSE); nodelay(stdscr, TRUE);

	// Disable INTR, QUIT, VDSUSP and SUSP keys
	if (tcgetattr(0, &old_termios_) == 0)
	{
		struct termios tio;
		
		std::memcpy(&tio, &old_termios_, sizeof(tio));
		tio.c_cc[VINTR] = _POSIX_VDISABLE;
		tio.c_cc[VQUIT] = _POSIX_VDISABLE;
#ifdef VDSUSP
		tio.c_cc[VDSUSP] = _POSIX_VDISABLE;
#endif
#ifdef VSUSP
		tio.c_cc[VSUSP] = _POSIX_VDISABLE;
#endif
		tcsetattr(0, TCSADRAIN, &tio);
	}
}

static inline void 
render_window(const boost::shared_ptr<window> & w) { w->render(); }

static inline void 
visit_window(const boost::shared_ptr<window> & w) { w->visit(); }

void terminal_impl::render() const
{	
	std::for_each(windows_.begin(), windows_.end(), render_window);
}

void terminal_impl::visit() const
{
	std::for_each(windows_.begin(), windows_.end(), visit_window);
}


} // namespace curses

} // namespace foofxp
