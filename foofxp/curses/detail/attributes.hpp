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

/// @file attributes.hpp
///
/// @brief Header file for the curses attributes detail methods.

#ifndef CURSES_ATTRIBUTES_HPP_INCLUDED
#define CURSES_ATTRIBUTES_HPP_INCLUDED

#include <curses.h>
#include "../color_type.hpp"
#include "../weight_type.hpp"

namespace foofxp
{

namespace curses
{

namespace detail
{

/// @brief Assemble a curses attr_t.
///
/// @param[in] background_color The background color to use.
/// @param[in] foreground_color The foreground color to use.
/// @param[in] weight The weight to use.
///
/// @returns An attr_t representing the three styles.
attr_t make_attr_t(color_type background_color, 
	color_type foreground_color, 
	weight_type weight);

/// @brief Get the weight specified in a curses attr_t.
///
/// @param[in] attributes The attributes to examine.
///
/// @returns The weight_type specified in the attributes.
weight_type get_weight(attr_t attributes);

/// @brief Get the background color specified in a curses attr_t.
///
/// @param[in] attributes The attributes to examine.
///
/// @returns The background color_type specified in the attributes.
color_type get_background_color(attr_t attributes);

/// @brief Get the foreground color specified in a curses attr_t.
///
/// @param[in] attributes The attributes to examine.
///
/// @returns The foreground color_type specified in the attributes.
color_type get_foreground_color(attr_t attributes);

} // namespace detail

} // namespace curses

} // namespace foofxp

#endif // CURSES_ATTRIBUTES_HPP_INCLUDED
