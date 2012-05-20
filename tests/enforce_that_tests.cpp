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

#include <string>
#include <stdexcept>
#include "../foofxp/utility/enforce_that.hpp"
#include <boost/test/unit_test.hpp>

using std::string;
using std::runtime_error;
using std::out_of_range;
using namespace foofxp::utility;

// Predicate to tell whether or not the exception's what() property returns
// "bar".
template<class exception_type>
bool ex_what_equals_bar(const exception_type & ex)
{
	return string(ex.what()) == "bar";
}

BOOST_AUTO_TEST_SUITE(enforce_tests)

BOOST_AUTO_TEST_CASE(enforce_test)
{
	BOOST_CHECK_NO_THROW(enforce_that(true, out_of_range, "foo"));
	
	BOOST_CHECK_THROW(enforce_that(false, out_of_range, "foo"), out_of_range);
	
	BOOST_CHECK_EXCEPTION(enforce_that(false, runtime_error, "bar"), 
	                      runtime_error, ex_what_equals_bar);
}

BOOST_AUTO_TEST_SUITE_END()
