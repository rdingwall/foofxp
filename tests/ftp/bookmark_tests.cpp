#include "../../foofxp/model/ftp/bookmark.hpp"
#include <boost/ref.hpp>
#include <boost/test/unit_test.hpp>

using boost::ref;
using foofxp::model::ftp::bookmark;

struct modified_handler
{
	modified_handler(const bookmark & expected) : 
		has_been_called_(false), expected_(expected) {};
	
	void operator()(const bookmark & actual)
	{
		has_been_called_ = true;
		BOOST_CHECK_EQUAL(&expected_ == &actual, true);
	};
	
	~modified_handler()
	{
		BOOST_CHECK_MESSAGE(has_been_called_ == true,
			"signal handler was not called");
	};

private:	
	bool has_been_called_;
	const bookmark & expected_;
};

struct bookmark_fixture
{
	bookmark_fixture() : instance()
	{
		// Make sure that setter values get persisted.
		instance.name("FOO");
		instance.auth_tls(true);
		instance.tls_data(true);
		instance.host("localhost");
		instance.port(666);
		instance.ipv6(true);
		instance.username("root");
		instance.password("pass");
		instance.path("/incoming/");
		
		BOOST_REQUIRE_EQUAL(instance.name(), "FOO");
		BOOST_REQUIRE_EQUAL(instance.auth_tls(), true);
		BOOST_REQUIRE_EQUAL(instance.tls_data(), true);
		BOOST_REQUIRE_EQUAL(instance.host(), "localhost");
		BOOST_REQUIRE_EQUAL(instance.port(), 666);
		BOOST_REQUIRE_EQUAL(instance.ipv6(), true);
		BOOST_REQUIRE_EQUAL(instance.username(), "root");
		BOOST_REQUIRE_EQUAL(instance.password(), "pass");
		BOOST_REQUIRE_EQUAL(instance.path(), "/incoming/");
	};
	
	bookmark instance;
};

BOOST_AUTO_TEST_SUITE(bookmark_tests)

// ----------------------------------------------------------------------------
// Make sure that the 'modified' event gets triggered when updating bookmark
// details.
// ----------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(setting_name_triggers_modified_event)
{
	bookmark_fixture fixture;
	modified_handler handler(fixture.instance);
	fixture.instance.modified.connect(ref(handler));
	fixture.instance.name("aaa");
}

BOOST_AUTO_TEST_CASE(setting_auth_tls_triggers_modified_event)
{
	bookmark_fixture fixture;
	modified_handler handler(fixture.instance);
	fixture.instance.modified.connect(ref(handler));
	fixture.instance.auth_tls(true);
}

BOOST_AUTO_TEST_CASE(setting_tls_data_triggers_modified_event)
{
	bookmark_fixture fixture;
	modified_handler handler(fixture.instance);
	fixture.instance.modified.connect(ref(handler));
	fixture.instance.tls_data(true);
}

BOOST_AUTO_TEST_CASE(setting_host_triggers_modified_event)
{
	bookmark_fixture fixture;
	modified_handler handler(fixture.instance);
	fixture.instance.modified.connect(ref(handler));
	fixture.instance.host("192.168.0.1");
}

BOOST_AUTO_TEST_CASE(setting_port_triggers_modified_event)
{
	bookmark_fixture fixture;
	modified_handler handler(fixture.instance);
	fixture.instance.modified.connect(ref(handler));
	fixture.instance.port(666);
}

BOOST_AUTO_TEST_CASE(setting_ipv6_triggers_modified_event)
{
	bookmark_fixture fixture;
	modified_handler handler(fixture.instance);
	fixture.instance.modified.connect(ref(handler));
	fixture.instance.ipv6(true);
}

BOOST_AUTO_TEST_CASE(setting_username_triggers_modified_event)
{
	bookmark_fixture fixture;
	modified_handler handler(fixture.instance);
	fixture.instance.modified.connect(ref(handler));
	fixture.instance.username("richard");
}

BOOST_AUTO_TEST_CASE(setting_password_triggers_modified_event)
{
	bookmark_fixture fixture;
	modified_handler handler(fixture.instance);
	fixture.instance.modified.connect(ref(handler));
	fixture.instance.password("password");
}

BOOST_AUTO_TEST_CASE(setting_path_triggers_modified_event)
{
	bookmark_fixture fixture;
	modified_handler handler(fixture.instance);
	fixture.instance.modified.connect(ref(handler));
	fixture.instance.path("/incoming/");
}

BOOST_AUTO_TEST_CASE(assignment_operator_triggers_modified_event)
{
	bookmark_fixture fixture;
	bookmark copy;
	
	modified_handler handler(copy);
	copy.modified.connect(ref(handler));
	
	copy = fixture.instance;
}

// ----------------------------------------------------------------------------
// Check the copy constructor and assignment operators works properly.
// ----------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(copy_constructor_copies)
{
	bookmark_fixture fixture;
	
	bookmark copy(fixture.instance);
	
	BOOST_CHECK_EQUAL(copy.name(), fixture.instance.name());
	BOOST_CHECK_EQUAL(copy.auth_tls(), fixture.instance.auth_tls());
	BOOST_CHECK_EQUAL(copy.tls_data(), fixture.instance.tls_data());
	BOOST_CHECK_EQUAL(copy.host(), fixture.instance.host());
	BOOST_CHECK_EQUAL(copy.port(), fixture.instance.port());
	BOOST_CHECK_EQUAL(copy.ipv6(), fixture.instance.ipv6());
	BOOST_CHECK_EQUAL(copy.username(), fixture.instance.username());
	BOOST_CHECK_EQUAL(copy.password(), fixture.instance.password());
	BOOST_CHECK_EQUAL(copy.path(), fixture.instance.path());
}

BOOST_AUTO_TEST_CASE(assignment_operator_assigns)
{
	bookmark_fixture fixture;
	bookmark copy;
	
	copy = fixture.instance;
	
	BOOST_CHECK_EQUAL(copy.name(), fixture.instance.name());
	BOOST_CHECK_EQUAL(copy.auth_tls(), fixture.instance.auth_tls());
	BOOST_CHECK_EQUAL(copy.tls_data(), fixture.instance.tls_data());
	BOOST_CHECK_EQUAL(copy.host(), fixture.instance.host());
	BOOST_CHECK_EQUAL(copy.port(), fixture.instance.port());
	BOOST_CHECK_EQUAL(copy.ipv6(), fixture.instance.ipv6());
	BOOST_CHECK_EQUAL(copy.username(), fixture.instance.username());
	BOOST_CHECK_EQUAL(copy.password(), fixture.instance.password());
	BOOST_CHECK_EQUAL(copy.path(), fixture.instance.path());
}

// ----------------------------------------------------------------------------
// Check the comparison operators.
// ----------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(equality_operator)
{
	bookmark_fixture aa;
	bookmark_fixture bb;
	
	BOOST_CHECK_EQUAL(aa.instance == bb.instance, true);
}

BOOST_AUTO_TEST_CASE(inequality_operator)
{
	bookmark_fixture aa;
	aa.instance.name("BAR");
	bookmark_fixture bb;
	
	BOOST_CHECK_EQUAL(aa.instance != bb.instance, true);
}

BOOST_AUTO_TEST_SUITE_END()
