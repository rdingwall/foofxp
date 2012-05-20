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
#include "pen.hpp"
#include "detail/attributes.hpp"

namespace foofxp
{

namespace curses
{

pen::pen(window & window) : 
	window_(window)
{
	derive_style();
}

void pen::commit()
{
	::wnoutrefresh(window_.underlying_window());
}

void pen::apply_style()
{
	wattrset(window_.underlying_window(), 
		detail::make_attr_t(background_color_, foreground_color_, 
			weight_));
}

void pen::derive_style()
{
	attr_t attributes;
	short color_pair;
	
	wattr_get(window_.underlying_window(), &attributes, &color_pair, 0);
	
	weight_ = detail::get_weight(attributes);
	
	background_color_ = detail::get_background_color(color_pair);
	foreground_color_ = detail::get_foreground_color(color_pair);
}

// -------------------------------------------------------------------------- //
// Draw commands
// -------------------------------------------------------------------------- //

void pen::write(const std::string & str)
{
	apply_style();
	
	write(str, str.length());
}

void pen::write(const std::string & str, size_type length)
{
	if (str.length() < 1 || length < 0)
		return;
	
	apply_style();
	
	::waddnstr(window_.underlying_window(), str.c_str(), length);
}

void pen::write(char c)
{
	apply_style();
	
	::waddch(window_.underlying_window(), c);
}

void pen::draw_frame()
{
	apply_style();
	::box(window_.underlying_window(), ACS_VLINE, ACS_HLINE);
}

void pen::draw_horizontal_line(size_type length)
{
	apply_style();
	draw_horizontal_line(length, ACS_HLINE);
}

void pen::draw_horizontal_line(size_type length, char pattern)
{
	apply_style();
	::whline(window_.underlying_window(), pattern, length);
}

void pen::draw_vertical_line(size_type length)
{
	apply_style();
	draw_vertical_line(length, ACS_VLINE);
}

void pen::draw_vertical_line(size_type length, char pattern)
{
	apply_style();
	::wvline(window_.underlying_window(), pattern, length);
}

void pen::erase()
{
	apply_style();
	::werase(window_.underlying_window());
}

void pen::fill(color_type color)
{
	apply_style();
	::wbkgd(window_.underlying_window(), 1 /* color pair */);
}

// -------------------------------------------------------------------------- //
// Pen positioning
// -------------------------------------------------------------------------- //

pen::size_type pen::x() const
{
	size_type width, height;
	getyx(window_.underlying_window(), height, width);
	
	return width;	
}

pen::size_type pen::y() const
{
	size_type width, height;
	getyx(window_.underlying_window(), height, width);
	
	return height;
}

void pen::move(pen::size_type x, pen::size_type y) throw(std::out_of_range)
{
	apply_style();
	
	if (x > window_.width())
		throw std::invalid_argument("X coordinate exceeds window "
			"bounds.");
	
	if (y > window_.height())
		throw std::invalid_argument("Y coordinate exceeds window "
			"bounds.");
	
	::wmove(window_.underlying_window(), y, x);
}

} // namespace curses

} // namespace foofxp
