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

/// @file window.hpp
///
/// @brief Header file containing window class definition.

#ifndef CURSES_WINDOW_HPP_INCLUDED
#define CURSES_WINDOW_HPP_INCLUDED

#include <deque>
#include <utility>
#include <curses.h>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/noncopyable.hpp>

namespace foofxp
{

namespace curses
{

/// @brief Curses window class.
class window : public boost::noncopyable
{	
public:
	
	// ------------------------------------------------------------------ //
	// Type definitions
	// ------------------------------------------------------------------ //
	
	/// @brief The underlying window type.
	typedef WINDOW underlying_type;
	
	/// @brief Type used for window dimensions.
	typedef unsigned int size_type;
	
	// ------------------------------------------------------------------ //
	// Destructor
	// ------------------------------------------------------------------ //
	
	/// @brief Window destructor.
	///
	/// Destroys all child windows as well.
	virtual ~window()
	{
		::delwin(underlying_window_);
	};
	
	// ------------------------------------------------------------------ //
	/// @name Getters
	// ------------------------------------------------------------------ //
	/// @{
	
	/// @brief Get the width of the window.
	///
	/// @returns The height of the window, in columns.
	size_type width()
	{
		size_type width;
		size_type height;
		getmaxyx(underlying_window_, height, width);
		return width;
	};
	
	/// @brief Get the height of the window.
	///
	/// @returns The height of the window, in rows.
	size_type height()
	{
		size_type width;
		size_type height;
		getmaxyx(underlying_window_, height, width);
		return height;
	};
	
	/// @brief Get the window's underlying window.
	///
	/// @returns A const pointer to the underlying window.
	const underlying_type * underlying_window() const
	{
		return underlying_window_;
	};
	
	/// @brief Get the window's underlying window.
	///
	/// @returns A pointer to the underlying window.
	underlying_type * underlying_window()
	{
		return underlying_window_;
	};
	
	/// @}
	
	// ------------------------------------------------------------------ //
	/// @name Methods
	// ------------------------------------------------------------------ //
	/// @{
	
	/// @brief Render the window.
	virtual void render() const = 0;
	
	/// @brief Visit the window.
	virtual void visit() const = 0;
	
	/// @}
	
protected:
	
	/// @brief Construct a window.
	///
	/// @param[in] parent The parent window.
	/// 
	/// 
	window(window & parent, 
		size_type width, size_type height, 
		size_type x_position, size_type y_position) : 
		underlying_window_(
			::subwin(parent.underlying_window(), 
				height, width, y_position, x_position))
	{};
	
	explicit window(underlying_type * underlying_window) :
		underlying_window_(underlying_window)
	{};
	
	mutable underlying_type * underlying_window_;

}; // class window
	
} // namespace curses

} // namespace foofxp

#endif // CURSES_WINDOW_HPP_INCLUDED
