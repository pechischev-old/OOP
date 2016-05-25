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

BOOST_AUTO_TEST_SUITE(HttpUrl_initialized_with_url_string)
	BOOST_AUTO_TEST_CASE(can_pass_url_without_exceptions)
	{
		BOOST_REQUIRE_NO_THROW(CHttpUrl("http://github.com/document.txt"));
	}
	BOOST_AUTO_TEST_CASE(if_scheme_incorrect_then_class_throw_exception)
	{
		BOOST_REQUIRE_THROW(CHttpUrl("htts://github.com/document.txt"), CUrlParsingError);
	}
	BOOST_AUTO_TEST_CASE(if_there_is_an_invalid_separator_then_class_throw_exception)
	{
		BOOST_REQUIRE_THROW(CHttpUrl("http:/github.com/document.txt"), CUrlParsingError);
	}
	BOOST_AUTO_TEST_CASE(if_at_the_beginning_of_the_domain_name_contains_extra_delimiter_then_class_throw_exception)
	{
		BOOST_REQUIRE_THROW(CHttpUrl("http:///github.com/document.txt"), CUrlParsingError);
	}
	BOOST_AUTO_TEST_CASE(if_the_domain_is_empty_then_class_throw_exception)
	{
		BOOST_REQUIRE_THROW(CHttpUrl("http:///document.txt"), CUrlParsingError);
	}
	BOOST_AUTO_TEST_CASE(if_scheme_correct_but_protocol_type_not_supported_class_throw_exception)
	{
		BOOST_REQUIRE_THROW(CHttpUrl("ftp://github.com/document.txt"), CUrlParsingError);
	}
	BOOST_AUTO_TEST_CASE(if_the_domain_contains_spaces_and_tabs_then_class_throw_exception)
	{
		BOOST_REQUIRE_THROW(CHttpUrl("http://git	hub.com/document.txt"), CUrlParsingError);
		BOOST_REQUIRE_THROW(CHttpUrl("http://github .com/document.txt"), CUrlParsingError);
	}
	BOOST_AUTO_TEST_CASE(if_document_is_empty_class_do_not_throw_exception)
	{
		BOOST_REQUIRE_NO_THROW(CHttpUrl("http://github.com/"));
		BOOST_REQUIRE_NO_THROW(CHttpUrl("http://github.com"));
	}
	BOOST_AUTO_TEST_CASE(if_document_is_empty_then_get_doc_returns_empty_doc_with_slash_ch)
	{
		BOOST_CHECK_EQUAL(CHttpUrl("https://github.com/").GetDocument(), "/");
		BOOST_CHECK_EQUAL(CHttpUrl("https://github.com").GetDocument(), "/");
	}
	BOOST_AUTO_TEST_CASE(if_url_contains_non_empty_document_get_doc_returns_him)
	{
		BOOST_CHECK_EQUAL(CHttpUrl("http://github.com/document.txt").GetDocument(), "/document.txt");
	}
	
	BOOST_AUTO_TEST_CASE(if_the_URL_contains_the_correct_port_class_do_not_throw_exception)
	{
		BOOST_REQUIRE_NO_THROW(CHttpUrl("http://github.com:443/document.txt"));
	}
	BOOST_AUTO_TEST_CASE(if_the_URL_port_is_out_of_range)
	{
		BOOST_REQUIRE_THROW(CHttpUrl("http://github.com:9999999999999/document.txt"), CUrlParsingError);
	}
	BOOST_AUTO_TEST_CASE(if_the_URL_contains_the_uncorrect_port_then_class_throw_exception)
	{
		BOOST_REQUIRE_THROW(CHttpUrl("http://github.com:/document.txt"), CUrlParsingError);
		BOOST_REQUIRE_THROW(CHttpUrl("http://github.com:"), CUrlParsingError);
	}
	BOOST_AUTO_TEST_CASE(if_url_contains_port_then_port_will_be_different_from_standart)
	{
		BOOST_CHECK_EQUAL(CHttpUrl("http://github.com:14/document.txt").GetPort(), 14u);
	}
	BOOST_AUTO_TEST_CASE(port_may_be_final_element)
	{
		BOOST_CHECK_EQUAL(CHttpUrl("http://github.com:14").GetPort(), 14u);
	}
	
	BOOST_AUTO_TEST_CASE(can_get_the_full_URL_after_the_transfer_of_the_class)
	{
		CHttpUrl url("http://github.com/document.txt");
		BOOST_CHECK_EQUAL(url.GetURL(), "http://github.com/document.txt");
		CHttpUrl url1("http://github.com:458/document.txt");
		BOOST_CHECK_EQUAL(url1.GetURL(), "http://github.com:458/document.txt");
		CHttpUrl url2("http://github.com:80/document.txt");
		BOOST_CHECK_EQUAL(url2.GetURL(), "http://github.com/document.txt");
	}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(HttpUrl_initialized_with_url_components)

	BOOST_AUTO_TEST_CASE(can_not_pass_an_invalid_domain_name)
	{
		BOOST_REQUIRE_THROW(CHttpUrl("", "oop"), CUrlParsingError);
	}

	BOOST_AUTO_TEST_CASE(can_not_pass_an_invalid_document)
	{
		BOOST_REQUIRE_THROW(CHttpUrl("github.com", "	"), CUrlParsingError);
	}

	BOOST_AUTO_TEST_CASE(can_not_pass_an_domain_name_with_scheme_or_slash)
	{
		BOOST_REQUIRE_THROW(CHttpUrl("https://github.github.com", "oop"), CUrlParsingError);
	}

	BOOST_AUTO_TEST_CASE(if_document_does_not_begin_with_slash_it_will_be_added)
	{
		CHttpUrl url1("github.com", "");
		BOOST_CHECK_EQUAL(url1.GetDocument(), "/");

		CHttpUrl url2("github.com", "/document.txt");
		BOOST_CHECK_EQUAL(url2.GetDocument(), "/document.txt");
	}

	BOOST_AUTO_TEST_CASE(default_protocol_is_http_and_default_port_is_80)
	{
		CHttpUrl url("github.com", "document.txt");
		BOOST_CHECK(url.GetProtocol() == Protocol::HTTP);
		BOOST_CHECK_EQUAL(url.GetPort(), 80u);
	}

	BOOST_AUTO_TEST_CASE(can_explicitly_specify_the_protocol)
	{
		CHttpUrl url("github.com", "document.txt", Protocol::HTTPS);
		BOOST_CHECK(url.GetProtocol() == Protocol::HTTPS);
		BOOST_CHECK_EQUAL(url.GetPort(), 80u);
	}

	BOOST_AUTO_TEST_CASE(can_explicitly_specify_the_port_of_fourth_parameter)
	{
		CHttpUrl url("github.com", "document.txt", Protocol::HTTPS, 05);
		BOOST_CHECK(url.GetProtocol() == Protocol::HTTPS);
		BOOST_CHECK_EQUAL(url.GetPort(), 5u);
	}

BOOST_AUTO_TEST_SUITE_END()






