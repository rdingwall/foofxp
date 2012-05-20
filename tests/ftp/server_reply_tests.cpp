#include <stdexcept>
#include <string>
#include <boost/test/unit_test.hpp>
#include "../../foofxp/model/ftp/server_reply.hpp"

using namespace std;
using foofxp::model::ftp::server_reply;

BOOST_AUTO_TEST_SUITE(server_reply_tests)

BOOST_AUTO_TEST_CASE(get_pwd_path)
{
	BOOST_CHECK_EQUAL(
		server_reply("257 \"/\" is current directory.").get_pwd_path(), "/");
	BOOST_CHECK_EQUAL(
		server_reply("257 \"/foo/bar/what/\" is current "
			"directory.").get_pwd_path(), "/foo/bar/what/");
	BOOST_CHECK_EQUAL(server_reply("257 \"/a/long/path/with spaces/in/"
		"it\" is current directory.").get_pwd_path(), 
		"/a/long/path/with spaces/in/it");
	BOOST_CHECK_EQUAL(server_reply("257 \"\"").get_pwd_path(), "");
	
	BOOST_CHECK_THROW(
		server_reply("257 \"/ is current directory").get_pwd_path(), 
		invalid_argument);
}

BOOST_AUTO_TEST_CASE(is_end_of_reply)
{
	BOOST_CHECK_EQUAL(
		server_reply("257 \"/\" is current directory.").is_end_of_reply(),
		true);
	BOOST_CHECK_EQUAL(
		server_reply("257- \"/foo/bar/what/\" is current "
			"directory.").is_end_of_reply(), false);
	BOOST_CHECK_EQUAL(server_reply("total 64").is_end_of_reply(), false);
	BOOST_CHECK_EQUAL(server_reply(string()).is_end_of_reply(), false);
	BOOST_CHECK_EQUAL(server_reply("XXX ").is_end_of_reply(), false);
	
	// These are invalid status codes, but the line is complete.
	BOOST_CHECK_EQUAL(server_reply("999 ").is_end_of_reply(), true);
	BOOST_CHECK_EQUAL(server_reply("000 ").is_end_of_reply(), true);
}

BOOST_AUTO_TEST_CASE(is_valid_format)
{
	BOOST_CHECK_EQUAL(
		server_reply("257 \"/\" is current directory.").is_valid_format(),
		true);
	BOOST_CHECK_EQUAL(
		server_reply("257- \"/foo/bar/what/\" is current "
			"directory.").is_valid_format(), true);
	BOOST_CHECK_EQUAL(server_reply("total 64").is_valid_format(), false);
	BOOST_CHECK_EQUAL(server_reply(string()).is_valid_format(), false);
	BOOST_CHECK_EQUAL(server_reply("XXX ").is_valid_format(), false);
	BOOST_CHECK_EQUAL(server_reply("000 ").is_valid_format(), true);
	BOOST_CHECK_EQUAL(server_reply("000").is_valid_format(), false);
}

BOOST_AUTO_TEST_CASE(is_transient_negative_reply)
{
	BOOST_CHECK_EQUAL(server_reply("421 blah").is_transient_negative_reply(),
		true);
	BOOST_CHECK_EQUAL(server_reply("421- blah").is_transient_negative_reply(), 
		true);
	BOOST_CHECK_EQUAL(server_reply("000 ").is_transient_negative_reply(),
		false);
	BOOST_CHECK_EQUAL(server_reply("100 ").is_transient_negative_reply(),
		false);
	BOOST_CHECK_EQUAL(server_reply("200 ").is_transient_negative_reply(),
		false);
	BOOST_CHECK_EQUAL(server_reply("300 ").is_transient_negative_reply(), 
		false);
	BOOST_CHECK_EQUAL(server_reply("500 ").is_transient_negative_reply(),
		false);
	BOOST_CHECK_EQUAL(server_reply("900 ").is_transient_negative_reply(),
		false);
	
	BOOST_CHECK_THROW(server_reply(string()).get_pwd_path(), invalid_argument);
	BOOST_CHECK_THROW(server_reply(" ").get_pwd_path(), invalid_argument);
	BOOST_CHECK_THROW(server_reply("    Blah").get_pwd_path(),
		invalid_argument);
	BOOST_CHECK_THROW(server_reply("   - Blah").get_pwd_path(),
		invalid_argument);
	BOOST_CHECK_THROW(server_reply("XXX Blah").get_pwd_path(),
		invalid_argument);
	BOOST_CHECK_THROW(server_reply("XXX- Blah").get_pwd_path(),
		invalid_argument);
	BOOST_CHECK_THROW(server_reply("000Blah").get_pwd_path(), invalid_argument);
	BOOST_CHECK_THROW(server_reply("000-Blah").get_pwd_path(),
		invalid_argument);
}

BOOST_AUTO_TEST_CASE(is_permanent_negative_reply)
{
	BOOST_CHECK_EQUAL(server_reply("501 blah").is_permanent_negative_reply(),
		true);
	BOOST_CHECK_EQUAL(server_reply("501- blah").is_permanent_negative_reply(), 
		true);
	BOOST_CHECK_EQUAL(server_reply("000 ").is_permanent_negative_reply(),
		false);
	BOOST_CHECK_EQUAL(server_reply("100 ").is_permanent_negative_reply(),
		false);
	BOOST_CHECK_EQUAL(server_reply("200 ").is_permanent_negative_reply(),
		false);
	BOOST_CHECK_EQUAL(server_reply("300 ").is_permanent_negative_reply(), 
		false);
	BOOST_CHECK_EQUAL(server_reply("400 ").is_permanent_negative_reply(),
		false);
	BOOST_CHECK_EQUAL(server_reply("900 ").is_permanent_negative_reply(),
		false);
	
	BOOST_CHECK_THROW(server_reply(string()).is_permanent_negative_reply(),
		invalid_argument);
	BOOST_CHECK_THROW(server_reply(" ").is_permanent_negative_reply(),
		invalid_argument);
	BOOST_CHECK_THROW(server_reply("    Blah").is_permanent_negative_reply(),
		invalid_argument);
	BOOST_CHECK_THROW(server_reply("   - Blah").is_permanent_negative_reply(),
		invalid_argument);
	BOOST_CHECK_THROW(server_reply("XXX Blah").is_permanent_negative_reply(),
		invalid_argument);
	BOOST_CHECK_THROW(server_reply("XXX- Blah").is_permanent_negative_reply(),
		invalid_argument);
	BOOST_CHECK_THROW(server_reply("000Blah").is_permanent_negative_reply(),
		invalid_argument);
	BOOST_CHECK_THROW(server_reply("000-Blah").is_permanent_negative_reply(),
		invalid_argument);
}

BOOST_AUTO_TEST_CASE(is_negative_reply)
{
	BOOST_CHECK_EQUAL(server_reply("501 blah").is_negative_reply(), true);
	BOOST_CHECK_EQUAL(server_reply("401 blah").is_negative_reply(), true);
	BOOST_CHECK_EQUAL(server_reply("501- blah").is_negative_reply(), true);
	BOOST_CHECK_EQUAL(server_reply("401- blah").is_negative_reply(), true);
	BOOST_CHECK_EQUAL(server_reply("000 ").is_negative_reply(), false);
	BOOST_CHECK_EQUAL(server_reply("100 ").is_negative_reply(), false);
	BOOST_CHECK_EQUAL(server_reply("200 ").is_negative_reply(), false);
	BOOST_CHECK_EQUAL(server_reply("300 ").is_negative_reply(), false);
	BOOST_CHECK_EQUAL(server_reply("900 ").is_negative_reply(), false);
	
	BOOST_CHECK_THROW(server_reply(string()).is_negative_reply(), 
		invalid_argument);
	BOOST_CHECK_THROW(server_reply(" ").is_negative_reply(), invalid_argument);
	BOOST_CHECK_THROW(server_reply("    Blah").is_negative_reply(),
		invalid_argument);
	BOOST_CHECK_THROW(server_reply("   - Blah").is_negative_reply(),
		invalid_argument);
	BOOST_CHECK_THROW(server_reply("XXX Blah").is_negative_reply(),
		invalid_argument);
	BOOST_CHECK_THROW(server_reply("XXX- Blah").is_negative_reply(),
		invalid_argument);
	BOOST_CHECK_THROW(server_reply("000Blah").is_negative_reply(),
		invalid_argument);
	BOOST_CHECK_THROW(server_reply("000-Blah").is_negative_reply(),
		invalid_argument);
}

BOOST_AUTO_TEST_CASE(get_message)
{
	BOOST_CHECK_EQUAL(server_reply("501 blah").get_message(), "blah");
	BOOST_CHECK_EQUAL(server_reply("501- blah").get_message(), "blah");
	BOOST_CHECK_EQUAL(server_reply("501 ").get_message(), string());
	BOOST_CHECK_EQUAL(server_reply("501- ").get_message(), string());
	
	BOOST_CHECK_THROW(server_reply(string()).get_message(), invalid_argument);
	BOOST_CHECK_THROW(server_reply(" ").get_message(), invalid_argument);
	BOOST_CHECK_THROW(server_reply("    Blah").get_message(), invalid_argument);
	BOOST_CHECK_THROW(server_reply("   - Blah").get_message(), 
		invalid_argument);
	BOOST_CHECK_THROW(server_reply("XXX Blah").get_message(), invalid_argument);
	BOOST_CHECK_THROW(server_reply("XXX- Blah").get_message(),
		invalid_argument);
	BOOST_CHECK_THROW(server_reply("000Blah").get_message(), invalid_argument);
	BOOST_CHECK_THROW(server_reply("000-Blah").get_message(), invalid_argument);
}

BOOST_AUTO_TEST_CASE(get_reply_code)
{
	BOOST_CHECK_EQUAL(server_reply("001 blah").get_reply_code(), 1);
	BOOST_CHECK_EQUAL(server_reply("101 blah").get_reply_code(), 101);
	BOOST_CHECK_EQUAL(server_reply("201 blah").get_reply_code(), 201);
	BOOST_CHECK_EQUAL(server_reply("301 blah").get_reply_code(), 301);
	BOOST_CHECK_EQUAL(server_reply("401 blah").get_reply_code(), 401);
	BOOST_CHECK_EQUAL(server_reply("501 blah").get_reply_code(), 501);
	BOOST_CHECK_EQUAL(server_reply("601 blah").get_reply_code(), 601);
	BOOST_CHECK_EQUAL(server_reply("699 blah").get_reply_code(), 699);
	BOOST_CHECK_EQUAL(server_reply("699- blah").get_reply_code(), 699);
	BOOST_CHECK_THROW(server_reply("000 blah").get_reply_code(), out_of_range);
	BOOST_CHECK_THROW(server_reply("700 blah").get_reply_code(), out_of_range);
	BOOST_CHECK_THROW(server_reply("800 blah").get_reply_code(), out_of_range);
	BOOST_CHECK_THROW(server_reply("900 blah").get_reply_code(), out_of_range);
	
	BOOST_CHECK_THROW(server_reply(string()).get_reply_code(),
		invalid_argument);
	BOOST_CHECK_THROW(server_reply(" ").get_reply_code(), invalid_argument);
	BOOST_CHECK_THROW(server_reply("    Blah").get_reply_code(),
		invalid_argument);
	BOOST_CHECK_THROW(server_reply("   - Blah").get_reply_code(), 
		invalid_argument);
	BOOST_CHECK_THROW(server_reply("XXX Blah").get_reply_code(),
		invalid_argument);
	BOOST_CHECK_THROW(server_reply("XXX- Blah").get_reply_code(),
		invalid_argument);
	BOOST_CHECK_THROW(server_reply("000Blah").get_reply_code(),
		invalid_argument);
	BOOST_CHECK_THROW(server_reply("000-Blah").get_reply_code(),
		invalid_argument);
}

BOOST_AUTO_TEST_SUITE_END()
