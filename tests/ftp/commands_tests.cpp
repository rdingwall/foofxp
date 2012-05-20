#include <stdexcept>
#include <string>
#include <boost/test/unit_test.hpp>
#include "../../foofxp/model/ftp/commands.hpp"

using std::invalid_argument;
using std::string;
using namespace foofxp::model::ftp;

BOOST_AUTO_TEST_SUITE(commands_tests)

BOOST_AUTO_TEST_CASE(auth_tls)
{
	BOOST_REQUIRE_EQUAL(commands::auth_tls(), "AUTH TLS");
}

BOOST_AUTO_TEST_CASE(cwd)
{
	BOOST_REQUIRE_EQUAL(commands::cwd("aaa"), "CWD aaa");
	BOOST_REQUIRE_EQUAL(commands::cwd("aaa/bbb"), "CWD aaa/bbb");
	BOOST_REQUIRE_EQUAL(commands::cwd("aaa/bbb/"), "CWD aaa/bbb/");
}

BOOST_AUTO_TEST_CASE(dele)
{
	BOOST_REQUIRE_EQUAL(commands::dele("aaa"), "DELE aaa");
	BOOST_REQUIRE_EQUAL(commands::dele("aaa/bbb"), "DELE aaa/bbb");
	BOOST_CHECK_THROW(commands::dele(string()), invalid_argument);
}

BOOST_AUTO_TEST_CASE(feat)
{
	BOOST_REQUIRE_EQUAL(commands::feat(), "FEAT");
}

BOOST_AUTO_TEST_CASE(mdkir)
{
	BOOST_REQUIRE_EQUAL(commands::mkdir("aaa"), "MKD aaa");
	BOOST_REQUIRE_EQUAL(commands::mkdir("aaa/bbb"), "MKD aaa/bbb");
	BOOST_REQUIRE_EQUAL(commands::mkdir("aaa/bbb/"), "MKD aaa/bbb/");
	BOOST_CHECK_THROW(commands::mkdir(string()), invalid_argument);
}

BOOST_AUTO_TEST_CASE(pass)
{
	BOOST_REQUIRE_EQUAL(commands::pass("aaa"), "PASS aaa");
	BOOST_CHECK_THROW(commands::pass(string()), invalid_argument);
}

BOOST_AUTO_TEST_CASE(pasv)
{
	BOOST_REQUIRE_EQUAL(commands::pasv(), "PASV");
}

BOOST_AUTO_TEST_CASE(pbsz)
{
	BOOST_REQUIRE_EQUAL(commands::pbsz(), "PBSZ 0");
}

BOOST_AUTO_TEST_CASE(pwd)
{
	BOOST_REQUIRE_EQUAL(commands::pwd(), "PWD");
}

BOOST_AUTO_TEST_CASE(site)
{
	BOOST_REQUIRE_EQUAL(commands::site("aaa"), "SITE aaa");
	BOOST_REQUIRE_EQUAL(commands::site("aaa bbb"), "SITE aaa bbb");
	BOOST_CHECK_THROW(commands::site(string()), invalid_argument);
}


BOOST_AUTO_TEST_SUITE_END()
