#include <gtest/gtest.h>

#include "warc.hh"

using namespace warc;
using namespace std;

static const char CR= 0x0D;
static const char LF= 0x0A;
	
static std::stringstream get_invalid_field_name_record()
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
	ss << CR << LF;
	return ss;
}

static std::stringstream get_record_content()
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

static std::stringstream get_record()
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
	return ss;
}


TEST(WARCRecord, parse_warc_record) 
{
	auto rstream = get_record();
	auto record = parse_warc_record(rstream);
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

TEST(WARCRecord, invalid_field_name) 
{
	auto rstream = get_invalid_field_name_record();
	ASSERT_ANY_THROW(parse_warc_record(rstream));
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
