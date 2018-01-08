#include <gtest/gtest.h>
#include <algorithm>
#include <sstream>
#include <type_traits>

#include "warc.hh"
#include "helper.hh"

using namespace warc;
using namespace std;

TEST(WARCRecord, parse_warc_record)
{
	auto rstream = get_record();
	WARCRecord record;
	rstream >> record;
	assert_record(record);
}

TEST(WARCRecord, invalid_field_name)
{
	auto rstream = get_invalid_field_name_record();
	WARCRecord record;
	ASSERT_ANY_THROW(rstream >> record);
}

TEST(WARCRecord, warc_record_input_iterator)
{
	std::stringstream records;
	records << get_record().str();
	records << get_record2().str();
	std::istream_iterator<WARCRecord> it(records);
	ASSERT_EQ(6, it->get_fields().size())
		<< "There are more fields than expected";
	for (auto field : it->get_fields()){
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
	EXPECT_EQ(get_record_content().str().size(), it->get_content().size());
	ASSERT_EQ(get_record_content().str(), it->get_content());
	it++;
	ASSERT_EQ(8, it->get_fields().size())
		<< "There are more fields than expected";
	for (auto field : it->get_fields()){
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
	EXPECT_EQ(get_record2_content().str().size(), it->get_content().size());
	ASSERT_EQ(get_record2_content().str(), it->get_content());

}

TEST(WARCField, warcfield_cpp_concepts)
{
	ASSERT_EQ(true, std::is_copy_assignable<WARCField>::value)
		<< "WARCField is not copy assignable";
	ASSERT_EQ(true, std::is_copy_constructible<WARCField>::value)
		<< "WARCField is not copy constructible";
	ASSERT_EQ(true, std::is_default_constructible<WARCField>::value)
		<< "WARCField is not default constructible";
}

TEST(WARCRecord, warcrecord_cpp_concepts)
{
	ASSERT_EQ(true, std::is_copy_assignable<WARCRecord>::value)
		<< "WARCRecord is not copy assignable";
	ASSERT_EQ(true, std::is_copy_constructible<WARCRecord>::value)
		<< "WARCRecord is not copy constructible";
	ASSERT_EQ(true, std::is_default_constructible<WARCField>::value)
		<< "WARCRecord is not default constructible";
}

TEST(WARCRecord, warc_record_input_iterator_within_loop)
{
	std::stringstream records;
	records << get_record().str();
	records << get_record2().str();
	unsigned count = 1;
	for(std::istream_iterator<WARCRecord> it(records);
			it != std::istream_iterator<WARCRecord>(); it++)
	{
		if (count == 1) {
			ASSERT_EQ(6, it->get_fields().size())
				<< "There are more fields than expected";
			for (auto field : it->get_fields()){
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
			EXPECT_EQ(get_record_content().str().size(), it->get_content().size());
			ASSERT_EQ(get_record_content().str(), it->get_content());
		} else if (count == 2) {
			ASSERT_EQ(8, it->get_fields().size())
				<< "There are more fields than expected";
			for (auto field : it->get_fields()){
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
			EXPECT_EQ(get_record2_content().str().size(), it->get_content().size());
			ASSERT_EQ(get_record2_content().str(), it->get_content());
		}
		count++;
	}
	ASSERT_EQ(2, count);
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
