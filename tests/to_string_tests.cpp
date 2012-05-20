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

#include "../foofxp/utility/lexical_cast/to_string.hpp"
#include <boost/test/auto_unit_test.hpp>

using std::string;
using namespace foofxp::utility;

BOOST_AUTO_TEST_SUITE(lexical_cast_to_string_tests)

BOOST_AUTO_TEST_CASE(lexical_cast_string_to_string_test)
{
	string a("hello");
	BOOST_CHECK_EQUAL(lexical_cast::to_string(a), a);
	
	string b("");
	BOOST_CHECK_EQUAL(lexical_cast::to_string(b), b);
}

BOOST_AUTO_TEST_CASE(lexical_cast_int_to_string_test)
{
	int a = 123;
	BOOST_CHECK_EQUAL(lexical_cast::to_string(a), "123");
	
	int b = -1;
	BOOST_CHECK_EQUAL(lexical_cast::to_string(b), "-1");
	
	int c = 1;
	BOOST_CHECK_EQUAL(lexical_cast::to_string(c), "1");
	
	int d = 0;
	BOOST_CHECK_EQUAL(lexical_cast::to_string(d), "0");
}

BOOST_AUTO_TEST_CASE(lexical_cast_short_to_string_test)
{
	short a = 123;
	BOOST_CHECK_EQUAL(lexical_cast::to_string(a), "123");
	
	short b = -1;
	BOOST_CHECK_EQUAL(lexical_cast::to_string(b), "-1");
	
	short c = 1;
	BOOST_CHECK_EQUAL(lexical_cast::to_string(c), "1");
	
	short d = 0;
	BOOST_CHECK_EQUAL(lexical_cast::to_string(d), "0");
}

BOOST_AUTO_TEST_CASE(lexical_cast_long_to_string_test)
{
	long a = 123;
	BOOST_CHECK_EQUAL(lexical_cast::to_string(a), "123");
	
	long b = -1;
	BOOST_CHECK_EQUAL(lexical_cast::to_string(b), "-1");
	
	long c = 1;
	BOOST_CHECK_EQUAL(lexical_cast::to_string(c), "1");
	
	long d = 0;
	BOOST_CHECK_EQUAL(lexical_cast::to_string(d), "0");	
}

BOOST_AUTO_TEST_CASE(lexical_cast_unsigned_int_to_string_test)
{
	unsigned int a = 123;
	BOOST_CHECK_EQUAL(lexical_cast::to_string(a), "123");
	
	unsigned int c = 1;
	BOOST_CHECK_EQUAL(lexical_cast::to_string(c), "1");
	
	unsigned int d = 0;
	BOOST_CHECK_EQUAL(lexical_cast::to_string(d), "0");
}

BOOST_AUTO_TEST_CASE(lexical_cast_unsigned_short_to_string_test)
{
	unsigned short a = 123;
	BOOST_CHECK_EQUAL(lexical_cast::to_string(a), "123");
	
	unsigned short c = 1;
	BOOST_CHECK_EQUAL(lexical_cast::to_string(c), "1");
	
	unsigned short d = 0;
	BOOST_CHECK_EQUAL(lexical_cast::to_string(d), "0");
}

BOOST_AUTO_TEST_CASE(lexical_cast_unsigned_long_to_string_test)
{
	unsigned long a = 123;
	BOOST_CHECK_EQUAL(lexical_cast::to_string(a), "123");
	
	unsigned long c = 1;
	BOOST_CHECK_EQUAL(lexical_cast::to_string(c), "1");
	
	unsigned long d = 0;
	BOOST_CHECK_EQUAL(lexical_cast::to_string(d), "0");	
}

BOOST_AUTO_TEST_CASE(lexical_cast_bool_to_string_test)
{
	BOOST_CHECK_EQUAL(lexical_cast::to_string(false), "false");
	BOOST_CHECK_EQUAL(lexical_cast::to_string(true), "true");
}

BOOST_AUTO_TEST_SUITE_END()
