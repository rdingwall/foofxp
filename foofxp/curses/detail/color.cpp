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
#include "color.hpp"

namespace foofxp
{

namespace curses
{

namespace detail
{

void initialize_color_pairs()
{
	const char ansi_tab[8] = { 0, 4, 2, 6, 1, 5, 3, 7 };

#ifdef HAVE_NCURSES_USE_DEFAULT_COLORS

	// this lets us to use the "default" background color for colors <= 7 so
	// background pixmaps etc. show up right.
	use_default_colors();

	for (int pair = 1; pair < COLOR_PAIRS; pair++)
	{
		short foreground = ansi_tab[pair & 7];
		short background = pair <= 7 ? -1 : ansi_tab[pair >> 3];

		init_pair(pair, foreground, background);
	}


	// hm.. not THAT good idea, but probably more people want dark grey than
	// white on white..
	init_pair(63, 0, -1);

#else

	for (int pair = 1; pair < COLOR_PAIRS; pair++)
	{
		short foreground = ansi_tab[pair & 7];
		short background = ansi_tab[pair >> 3];

		init_pair(pair, foreground, background);
	}

	init_pair(63, 0, 0);

#endif
}

} // namespace detail

} // namespace curses

} // namespace foofxp
