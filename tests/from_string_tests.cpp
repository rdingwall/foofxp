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

#include <stdexcept>
#include "../foofxp/utility/lexical_cast/from_string.hpp"
#include <boost/test/unit_test.hpp>
#include <boost/test/floating_point_comparison.hpp>

using std::string;
using namespace foofxp::utility;

#define BOOST_TEST_MODULE foofxp tests

BOOST_AUTO_TEST_SUITE(lexical_cast_from_string_tests)

BOOST_AUTO_TEST_CASE(lexical_cast_string_from_string_test)
{
	string a("hello");
	BOOST_CHECK_EQUAL(lexical_cast::from_string<string>(a), a);
	
	string b("");
	BOOST_CHECK_EQUAL(lexical_cast::from_string<string>(b), b);
}

BOOST_AUTO_TEST_CASE(lexical_cast_int_from_string_test)
{
	string a("123");
	BOOST_CHECK_EQUAL(lexical_cast::from_string<int>(a), 123);
	
	string b("-1");
	BOOST_CHECK_EQUAL(lexical_cast::from_string<int>(b), -1);
	
	string c ("1");
	BOOST_CHECK_EQUAL(lexical_cast::from_string<int>(c), 1);
	
	string d("0");
	BOOST_CHECK_EQUAL(lexical_cast::from_string<int>(d), 0);
	
	string e("asdf");
	BOOST_CHECK_THROW(lexical_cast::from_string<int>(e), 
	                  std::invalid_argument);
	string f("999999999999");
	BOOST_CHECK_THROW(lexical_cast::from_string<int>(f),
	                  std::out_of_range);
}



BOOST_AUTO_TEST_CASE(lexical_cast_short_from_string_test)
{
	string a("123");
	BOOST_CHECK_EQUAL(lexical_cast::from_string<short>(a), 123);
	
	string b("-1");
	BOOST_CHECK_EQUAL(lexical_cast::from_string<short>(b), -1);
	
	string c ("1");
	BOOST_CHECK_EQUAL(lexical_cast::from_string<short>(c), 1);
	
	string d("0");
	BOOST_CHECK_EQUAL(lexical_cast::from_string<short>(d), 0);
	
	string e("asdf");
	BOOST_CHECK_THROW(lexical_cast::from_string<short>(e), 
	                  std::invalid_argument);
		
	string f("-99999");
	BOOST_CHECK_THROW(lexical_cast::from_string<short>(f),
	                  std::out_of_range);
}

BOOST_AUTO_TEST_CASE(lexical_cast_long_from_string_test)
{
	string a("123");
	BOOST_CHECK_EQUAL(lexical_cast::from_string<long>(a), 123L);
	
	string b("-1");
	BOOST_CHECK_EQUAL(lexical_cast::from_string<long>(b), -1L);
	
	string c ("1");
	BOOST_CHECK_EQUAL(lexical_cast::from_string<long>(c), 1L);
	
	string d("0");
	BOOST_CHECK_EQUAL(lexical_cast::from_string<long>(d), 0L);
	
	string e("asdf");
	BOOST_CHECK_THROW(lexical_cast::from_string<long>(e), 
	                  std::invalid_argument);
		
	string f("999999999999");
	BOOST_CHECK_THROW(lexical_cast::from_string<long>(f),
	                  std::out_of_range);
}

BOOST_AUTO_TEST_CASE(lexical_cast_unsigned_int_from_string_test)
{
	string a("123");
	BOOST_CHECK_EQUAL(lexical_cast::from_string<unsigned int>(a), 123U);
	
	string c ("1");
	BOOST_CHECK_EQUAL(lexical_cast::from_string<unsigned int>(c), 1U);
	
	string d("0");
	BOOST_CHECK_EQUAL(lexical_cast::from_string<unsigned int>(d), 0U);
	
	string e("asdf");
	BOOST_CHECK_THROW(lexical_cast::from_string<unsigned int>(e), 
	                  std::invalid_argument);
	
	string f("999999999999");
	BOOST_CHECK_THROW(lexical_cast::from_string<unsigned int>(f),
	                  std::out_of_range);
	
	string g("-1");
	BOOST_CHECK_THROW(lexical_cast::from_string<unsigned int>(g),
	                  std::out_of_range);
}

BOOST_AUTO_TEST_CASE(lexical_cast_unsigned_short_from_string_test)
{
	string a("123");
	BOOST_CHECK_EQUAL(lexical_cast::from_string<unsigned short>(a), 123U);
	
	string b("1");
	BOOST_CHECK_EQUAL(lexical_cast::from_string<unsigned short>(b), 1U);
	
	string d("0");
	BOOST_CHECK_EQUAL(lexical_cast::from_string<unsigned short>(d), 0U);
	
	string e("asdf");
	BOOST_CHECK_THROW(lexical_cast::from_string<unsigned short>(e), 
	                  std::invalid_argument);
	
	string f("99999");
	BOOST_CHECK_THROW(lexical_cast::from_string<unsigned short>(f),
	                  std::out_of_range);
}

BOOST_AUTO_TEST_CASE(lexical_cast_unsigned_long_from_string_test)
{
	string a("123");
	BOOST_CHECK_EQUAL(lexical_cast::from_string<unsigned long>(a), 123UL);
	
	string c ("1");
	BOOST_CHECK_EQUAL(lexical_cast::from_string<unsigned long>(c), 1UL);
	
	string d("0");
	BOOST_CHECK_EQUAL(lexical_cast::from_string<unsigned long>(d), 0UL);
	
	string e("asdf");
	BOOST_CHECK_THROW(lexical_cast::from_string<unsigned long>(e), 
	                  std::invalid_argument);
	
	string f("99999999999999999999");
	BOOST_CHECK_THROW(lexical_cast::from_string<unsigned long>(f),
	                  std::out_of_range);
	
	string g("-1");
	BOOST_CHECK_THROW(lexical_cast::from_string<unsigned int>(g),
	                  std::out_of_range);
}

BOOST_AUTO_TEST_CASE(lexical_cast_float_from_string_test)
{
	string a("3.14159");
	BOOST_CHECK_CLOSE(lexical_cast::from_string<float>(a), 
	                  static_cast<float>(3.14159), 0.001);
	
	string b("asdf");
	BOOST_CHECK_THROW(lexical_cast::from_string<float>(b), 
	                  std::invalid_argument);
	
	string c("9.9999E99");
	BOOST_CHECK_THROW(lexical_cast::from_string<float>(c), 
	                  std::out_of_range);
}

BOOST_AUTO_TEST_SUITE_END()
