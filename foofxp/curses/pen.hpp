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

/// @file pen.hpp
///
/// @brief Header file for the pen class definition.

#ifndef CURSES_PEN_HPP_INCLUDED
#define CURSES_PEN_HPP_INCLUDED

#include <stdexcept>
#include <string>
#include "window.hpp"
#include "color_type.hpp"
#include "weight_type.hpp"

namespace foofxp
{

namespace curses
{

/// @brief Curses pen class.
class pen
{
public:
	/// @brief The size type.
	typedef window::size_type size_type;
	
	/// @brief Construct a pen.
	///
	/// @param[in] window The window to write to.
	pen(window & window);
	
	// ------------------------------------------------------------------ //
	/// @name Draw commands
	// ------------------------------------------------------------------ //
	/// @{
	
	/// @brief Write a string to the window.
	///
	/// @param[in] str The string to write.
	/// @param[in] length The number of characters to write.
	void write(const std::string & str, size_type length);
	
	/// @brief Write a string to the window.
	///
	/// @param[in] str The string to write.
	void write(const std::string & str);
	
	/// @brief Write a character to the window.
	///
	/// @param[in] c The character to write.
	void write(char c);
	
	/// @brief Erase the contents of the window.
	void erase();
	
	/// @brief Fill the window.
	///
	/// @param[in] color The background color to use.
	void fill(color_type color);
	
	/// @brief Draw a horizontal line.
	///
	/// @param[in] length The length of the line.
	void draw_horizontal_line(size_type length);
	
	/// @brief Draw a horizontal line.
	///
	/// @param[in] length The length of the line.
	/// @param[in] pattern The character to use.
	void draw_horizontal_line(size_type length, char pattern);
	
	/// @brief Draw a vertical line.
	///
	/// @param[in] length The length of the line.
	void draw_vertical_line(size_type length);
	
	/// @brief Draw a vertical line.
	///
	/// @param[in] length The length of the line.
	/// @param[in] pattern The character to use.
	void draw_vertical_line(size_type length, char pattern);
	
	/// @brief Draw a frame around the window.
	void draw_frame();
	
	/// @}
	
	// ------------------------------------------------------------------ //
	/// @name Pen positioning
	// ------------------------------------------------------------------ //
	/// @{
	
	/// @brief Move the pen.
	///
	/// @param[in] x The X position to move to.
	/// @param[in] y The Y position to move to.
	///
	/// @exception std::out_of_range Thrown if either of the coordinates
	/// falls outside the window area.
	void move(size_type x, size_type y) throw(std::out_of_range);
	
	/// @brief Get the pen's X position.
	///
	/// @returns The X position of the pen.
	size_type x() const;
	
	/// @brief Get the pen's Y position.
	///
	/// @returns The Y position of the pen.
	size_type y() const;
	
	/// @}
	
	/// @brief Commit changes to the window.
	void commit();
	
	// ------------------------------------------------------------------ //
	/// @name Get pen style
	// ------------------------------------------------------------------ //
	/// @{
	
	/// @brief Get the pen's current foreground color.
	///
	/// @returns A color.
	color_type foreground_color() const
	{
		return foreground_color_;
	};
	
	/// @brief Get the pen's current background color.
	///
	/// @returns A color.
	color_type background_color() const
	{
		return background_color_;
	};
	
	/// @brief Get the pen's current weight.
	///
	/// @returns A weight.
	weight_type weight() const { return weight_; };
	
	/// @}
	
	// ------------------------------------------------------------------ //
	/// @name Set pen style
	// ------------------------------------------------------------------ //
	/// @{
	
	/// @brief Set the pen's foreground color.
	///
	/// @param[in] color The new foreground color.
	void foreground_color(color_type color)
	{
		foreground_color_ = color;
	};
	
	/// @brief Set the pen's background color.
	///
	/// @param[in] color The new background color.
	void background_color(color_type color)
	{
		background_color_ = color;
	};
	
	/// @brief Set the pen's weight.
	///
	/// @param[in] weight The new weight.
	void weight(weight_type weight) { weight_ = weight; };
	
	/// @}
	
private:
	
	/// @brief Apply the current style to the pen.
	void apply_style();
	
	/// @brief Derive the current foreground color, background color and 
	/// weight from the window.
	void derive_style();
	
	/// @brief The window the pen is writing to.
	window & window_;
	
	// ------------------------------------------------------------------ //
	/// @name Pen style
	// ------------------------------------------------------------------ //
	/// @{
	
	/// @brief The pen's foreground color.
	color_type foreground_color_;
	
	/// @brief The pen's background color.
	color_type background_color_;
	
	/// @brief The pen's weight.
	weight_type weight_;
	
	/// @}
	
}; // class pen

} // namespace curses

} // namespace foofxp

#endif // CURSES_PEN_HPP_INCLUDED