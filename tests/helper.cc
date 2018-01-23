#include <gtest/gtest.h>
#include <sstream>

#include "helper.hh"

using namespace warc;

std::stringstream get_invalid_field_name_record()
{
	std::stringstream ss;
	ss << "WARC/1.0" << CR << LF;
	ss << "WARC-Type: warcinfo" << CR << LF;
	ss << "WARC-Date: 2017-10-24T10:57:36Z" << CR << LF;
	ss << "WARC-Record-ID: <urn:uuid:e98258fc-8fcf-4800-bdb7-e02e19275f27>" << CR << LF;
	ss << "Content-Length: 329" << CR << LF;
	ss << "Content-Type: application/warc-fields" << CR << LF;
	ss << "Invalid-Field: CC-MAIN-20171024105736-20171024125736-00899.warc.gz" << CR << LF;
	ss << CR << LF;
	ss << "robots: classic" << CR << LF;
	ss << "hostname: ip-10-203-171-252.ec2.internal" << CR << LF;
	ss << "software: Nutch 1.6 (CC)" << CR << LF;
	ss << "isPartOf: CC-MAIN-2017-43" << CR << LF;
	ss << "operator: Common Crawl Admin" << CR << LF;
	ss << "description: Wide crawl of the web for October 2017" << CR << LF;
	ss << "publisher: Common Crawl" << CR << LF;
	ss << "format: WARC File Format 1.0" << CR << LF;
	ss << "conformsTo: http://bibnum.bnf.fr/WARC/WARC_ISO_28500_version1_latestdraft.pdf" << CR << LF;
	ss << CR << LF;
	ss << CR << LF;
	return ss;
}

std::stringstream get_record()
{
	std::stringstream ss;
	ss << "WARC/1.0" << CR << LF;
	ss << "WARC-Type: warcinfo" << CR << LF;
	ss << "WARC-Date: 2017-10-24T10:57:36Z" << CR << LF;
	ss << "WARC-Record-ID: <urn:uuid:e98258fc-8fcf-4800-bdb7-e02e19275f27>" << CR << LF;
	ss << "Content-Length: 329" << CR << LF;
	ss << "Content-Type: application/warc-fields" << CR << LF;
	ss << "WARC-Filename: CC-MAIN-20171024105736-20171024125736-00899.warc.gz" << CR << LF;
	ss << CR << LF;
	ss << get_record_content().str();
	ss << CR << LF;
	ss << CR << LF;
	return ss;
}

std::stringstream get_record_content()
{
	std::stringstream ss;
	ss << "robots: classic" << CR << LF;
	ss << "hostname: ip-10-203-171-252.ec2.internal" << CR << LF;
	ss << "software: Nutch 1.6 (CC)" << CR << LF;
	ss << "isPartOf: CC-MAIN-2017-43" << CR << LF;
	ss << "operator: Common Crawl Admin" << CR << LF;
	ss << "description: Wide crawl of the web for October 2017" << CR << LF;
	ss << "publisher: Common Crawl" << CR << LF;
	ss << "format: WARC File Format 1.0" << CR << LF;
	ss << "conformsTo: http://bibnum.bnf.fr/WARC/WARC_ISO_28500_version1_latestdraft.pdf" << CR << LF;
	return ss;
}

void assert_record(const WARCRecord& record)
{
	ASSERT_EQ(6, record.get_fields().size())
		<< "There are more fields than expected";
	for (auto field : record.get_fields()){
		if (field.get_name() == "WARC-Type")
			ASSERT_EQ("warcinfo", field.get_value())
				<< "Invalid WARC-Type value";
		else if (field.get_name() == "WARC-Date")
			ASSERT_EQ("2017-10-24T10:57:36Z", field.get_value())
				<< "Invalid WARC-Date value";
		else if (field.get_name() == "WARC-Record-ID")
			ASSERT_EQ("<urn:uuid:e98258fc-8fcf-4800-bdb7-e02e19275f27>", field.get_value())
				<< "Invalid WARC-Record-ID value";
		else if (field.get_name() == "Content-Length")
			ASSERT_EQ("329", field.get_value())
				<< "Invalid Contet-Length value";
		else if (field.get_name() == "Content-Type")
			ASSERT_EQ("application/warc-fields", field.get_value())
				<< "Invalid Content-Type value";
		else if (field.get_name() == "WARC-Filename")
			ASSERT_EQ("CC-MAIN-20171024105736-20171024125736-00899.warc.gz", field.get_value())
				<< "Invalid WARC-Filename value";
		else
			FAIL() << "Unknown field: " << field.get_name() << ": "
				<< field.get_value();
	}
	ASSERT_EQ(get_record_content().str().size(), record.get_content().size());
	ASSERT_EQ(get_record_content().str(), record.get_content());
}

std::stringstream get_record2()
{
	std::stringstream ss;
	ss << "WARC/1.0" << CR << LF;
	ss << "WARC-Type: request" << CR << LF;
	ss << "WARC-Date: 2017-10-24T11:29:43Z" << CR << LF;
	ss << "WARC-Record-ID: <urn:uuid:5c576cdd-5402-446a-b3c1-03f25b4c45b4>" << CR << LF;
	ss << "Content-Length: 287" << CR << LF;
	ss << "Content-Type: application/http; msgtype=request" << CR << LF;
	ss << "WARC-Warcinfo-ID: <urn:uuid:e98258fc-8fcf-4800-bdb7-e02e19275f27>" << CR << LF;
	ss << "WARC-IP-Address: 104.244.98.65" << CR << LF;
	ss << "WARC-Target-URI: http://00iamgundam00.blog.fc2.com/blog-entry-935.html" << CR << LF;
	ss << CR << LF;
	ss << get_record2_content().str();
	ss << CR << LF;
	ss << CR << LF;
	return ss;
}

std::stringstream get_record2_content()
{
	std::stringstream ss;
	ss << "GET /blog-entry-935.html HTTP/1.0" << CR << LF;
	ss << "Host: 00iamgundam00.blog.fc2.com" << CR << LF;
	ss << "Accept-Encoding: x-gzip, gzip, deflate" << CR << LF;
	ss << "User-Agent: CCBot/2.0 (http://commoncrawl.org/faq/)" << CR << LF;
	ss << "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8" << CR << LF;
	ss << "If-Modified-Since: Sat, 19 Aug 2017 09:15:44 GMT" << CR << LF;
	ss << CR << LF;
	return ss;
}

void assert_record2(const WARCRecord& record)
{
	ASSERT_EQ(9, record.get_fields().size())
		<< "There are more fields than expected";
	for (auto field : record.get_fields()){
		if (field.get_name() == "WARC-Type")
			ASSERT_EQ("request", field.get_value())
				<< "Invalid WARC-Type value";
		else if (field.get_name() == "WARC-Date")
			ASSERT_EQ("2017-10-24T11:29:43Z", field.get_value())
				<< "Invalid WARC-Date value";
		else if (field.get_name() == "WARC-Record-ID")
			ASSERT_EQ("<urn:uuid:5c576cdd-5402-446a-b3c1-03f25b4c45b4>", field.get_value())
				<< "Invalid WARC-Record-ID value";
		else if (field.get_name() == "Content-Length")
			ASSERT_EQ("287", field.get_value())
				<< "Invalid Contet-Length value";
		else if (field.get_name() == "Content-Type")
			ASSERT_EQ("application/http; msgtype=request", field.get_value())
				<< "Invalid Content-Type value";
		else if (field.get_name() == "WARC-Warcinfo-ID")
			ASSERT_EQ("<urn:uuid:e98258fc-8fcf-4800-bdb7-e02e19275f27>", field.get_value())
				<< "Invalid WARC-Warcinfo-ID value";
		else if (field.get_name() == "WARC-IP-Address")
			ASSERT_EQ("104.244.98.65", field.get_value())
				<< "Invalid WARC-IP-Address value";
		else if (field.get_name() == "WARC-Target-URI")
			ASSERT_EQ("http://00iamgundam00.blog.fc2.com/blog-entry-935.html", field.get_value())
				<< "Invalid WARC-Target-URI value";
		else
			FAIL() << "Unknown field: " << field.get_name() << ": "
				<< field.get_value();
	}
	ASSERT_EQ(get_record2_content().str().size(), record.get_content().size());
	ASSERT_EQ(get_record2_content().str(), record.get_content());
}

