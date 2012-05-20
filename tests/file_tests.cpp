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
//       documentation and/or file::other materials provided with the distribution.
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

#include "../foofxp/model/file.hpp"
#include <boost/test/unit_test.hpp>

using foofxp::model::file;
using namespace boost::posix_time;

BOOST_AUTO_TEST_SUITE(file_tests)

// -------------------------------------------------------------------------- //
// Constructor tests
// -------------------------------------------------------------------------- //

// Test file constructor.
BOOST_AUTO_TEST_CASE(file_one_arg_constructor_test)
{
	file a("file_name.ext");
	BOOST_CHECK_EQUAL(a.name(), "file_name.ext");
}

// Test file copy constructor.
BOOST_AUTO_TEST_CASE(file_copy_constructor_test)
{
	file a("file_name.ext");
	BOOST_REQUIRE_EQUAL(a.name(), "file_name.ext");
	
	a.type(file::other);
	BOOST_REQUIRE_EQUAL(a.type(), file::other);
	
	a.size(999UL);
	BOOST_REQUIRE_EQUAL(a.size(), 999UL);
	
	ptime t = second_clock::local_time();
	
	a.time(t);
	BOOST_REQUIRE_EQUAL(a.time(), t);

	file b(a);
	
	BOOST_CHECK_EQUAL(a.name(), b.name());
	BOOST_CHECK_EQUAL(a.type(), b.type());
	BOOST_CHECK_EQUAL(a.size(), b.size());
	BOOST_CHECK_EQUAL(a.time(), b.time());
}

// -------------------------------------------------------------------------- //
// Operator tests
// -------------------------------------------------------------------------- //

// Test file::operator=().
BOOST_AUTO_TEST_CASE(file_assignment_constructor_test)
{
	file a("file_name.ext");
	BOOST_REQUIRE_EQUAL(a.name(), "file_name.ext");
	
	a.type(file::other);
	BOOST_REQUIRE_EQUAL(a.type(), file::other);
	
	a.size(999UL);
	BOOST_REQUIRE_EQUAL(a.size(), 999UL);
	
	ptime t = second_clock::local_time();
	
	a.time(t);
	BOOST_REQUIRE_EQUAL(a.time(), t);
	
	file b;
	b = a;
	
	BOOST_CHECK_EQUAL(a.name(), b.name());
	BOOST_CHECK_EQUAL(a.type(), b.type());
	BOOST_CHECK_EQUAL(a.size(), b.size());
	BOOST_CHECK_EQUAL(a.time(), b.time());
}

// Test file::operator==().
BOOST_AUTO_TEST_CASE(file_equality_operator_test)
{
	ptime t = second_clock::local_time();
	
	file a("file_name.ext");
	BOOST_REQUIRE_EQUAL(a.name(), "file_name.ext");
	a.type(file::other);
	BOOST_REQUIRE_EQUAL(a.type(), file::other);
	a.size(999UL);
	BOOST_REQUIRE_EQUAL(a.size(), 999UL);
	a.time(t);
	BOOST_REQUIRE_EQUAL(a.time(), t);
	
	file b("file_name.ext");
	BOOST_REQUIRE_EQUAL(b.name(), "file_name.ext");
	b.type(file::other);
	BOOST_REQUIRE_EQUAL(b.type(), file::other);
	b.size(999UL);
	BOOST_REQUIRE_EQUAL(b.size(), 999UL);
	b.time(t);
	BOOST_REQUIRE_EQUAL(b.time(), t);
	
	file c("ungh.ext");
	BOOST_REQUIRE_EQUAL(c.name(), "ungh.ext");
	c.type(file::plain_old_file);
	BOOST_REQUIRE_EQUAL(c.type(), file::plain_old_file);
	c.size(999UL);
	BOOST_REQUIRE_EQUAL(c.size(), 999UL);
	c.time(t);
	BOOST_REQUIRE_EQUAL(c.time(), t);
	
	// Test if same.
	BOOST_CHECK_EQUAL(a.operator==(b), true);
	
	// Test if not same.
	BOOST_CHECK_EQUAL(a.operator==(c), false);
}

// Test file::operator!=().
BOOST_AUTO_TEST_CASE(file_inequality_operator_test)
{
	ptime t = second_clock::local_time();
	
	file a("file_name.ext");
	BOOST_REQUIRE_EQUAL(a.name(), "file_name.ext");
	a.type(file::other);
	BOOST_REQUIRE_EQUAL(a.type(), file::other);
	a.size(999UL);
	BOOST_REQUIRE_EQUAL(a.size(), 999UL);
	a.time(t);
	BOOST_REQUIRE_EQUAL(a.time(), t);
	
	file b("file_name.ext");
	BOOST_REQUIRE_EQUAL(b.name(), "file_name.ext");
	b.type(file::other);
	BOOST_REQUIRE_EQUAL(b.type(), file::other);
	b.size(999UL);
	BOOST_REQUIRE_EQUAL(b.size(), 999UL);
	b.time(t);
	BOOST_REQUIRE_EQUAL(b.time(), t);
	
	file c("ungh.ext");
	BOOST_REQUIRE_EQUAL(c.name(), "ungh.ext");
	c.type(file::plain_old_file);
	BOOST_REQUIRE_EQUAL(c.type(), file::plain_old_file);
	c.size(999UL);
	BOOST_REQUIRE_EQUAL(c.size(), 999UL);
	c.time(t);
	BOOST_REQUIRE_EQUAL(c.time(), t);
	
	// Test if same.
	BOOST_CHECK_EQUAL(a.operator!=(b), false);
	
	// Test if not same.
	BOOST_CHECK_EQUAL(a.operator!=(c), true);
}

// -------------------------------------------------------------------------- //
// Property tests
// -------------------------------------------------------------------------- //

// Test file::name().
BOOST_AUTO_TEST_CASE(file_name_property_operator_test)
{
	file a;
	
	a.name("test_file_name.ext");
	BOOST_CHECK_EQUAL(a.name(), "test_file_name.ext");
	
	a.name("ungh.ext");
	BOOST_CHECK_EQUAL(a.name(), "ungh.ext");
}

// Test file::size().
BOOST_AUTO_TEST_CASE(file_size_property_operator_test)
{
	file a;
	
	a.size(999UL);
	BOOST_CHECK_EQUAL(a.size(), 999UL);
	
	a.size(42UL);
	BOOST_CHECK_EQUAL(a.size(), 42UL);
}

// Test file::time().
BOOST_AUTO_TEST_CASE(file_time_property_operator_test)
{
	file a;
	
	ptime t = second_clock::local_time();
	
	a.time(t);
	BOOST_REQUIRE_EQUAL(a.time(), t);
}

BOOST_AUTO_TEST_SUITE_END()
