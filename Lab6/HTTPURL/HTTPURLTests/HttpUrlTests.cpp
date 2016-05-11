#include "stdafx.h"
#include "../HTTPURL/HttpUrl.h"

using namespace std;

void VerifyDataUrl(CHttpUrl const & httpUrl, string const & domain, string const & document, 
				Protocol protocol = HTTP, unsigned short port = 80)
{
	BOOST_CHECK_EQUAL(httpUrl.GetDomain(), domain);
	BOOST_CHECK_EQUAL(httpUrl.GetDocument(), document);
	BOOST_CHECK_EQUAL(httpUrl.GetPort(), port);
	BOOST_CHECK_EQUAL(httpUrl.GetProtocol(), protocol);
}

BOOST_AUTO_TEST_CASE(can_transfer_the_data_url)
{
	CHttpUrl httpUrl("github.com", "/document/image.jpeg", HTTPS, 404);
	VerifyDataUrl(httpUrl, "github.com", "/document/image.jpeg", HTTPS, 404);
}

BOOST_AUTO_TEST_CASE(can_transfer_only_transfer_the_domain_and_the_document)
{
	CHttpUrl httpUrl("github.com", "/image.jpeg");
	VerifyDataUrl(httpUrl, "github.com", "/image.jpeg");
}

BOOST_AUTO_TEST_CASE(an_exception_is_thrown_with_the_incorrect_domain)
{
	BOOST_REQUIRE_THROW(CHttpUrl("gith ub.com", "/image.jpeg"), invalid_argument);
	BOOST_REQUIRE_THROW(CHttpUrl("gi/thub.com", "/image.jpeg"), invalid_argument);
}

BOOST_AUTO_TEST_CASE(an_exception_is_thrown_with_the_incorrect_document)
{
	BOOST_REQUIRE_THROW(CHttpUrl("github.com", "/ima ge.jpeg"), invalid_argument);
	BOOST_REQUIRE_THROW(CHttpUrl("github.com", "/image.		jpeg"), invalid_argument);
}