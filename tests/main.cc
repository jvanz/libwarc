
#include <gtest/gtest.h>

#include "warc.hh"

using namespace warc;
using namespace std;

TEST(WARCField, get_name) 
{
	string name("myfield");
	WARCField<string> field(name, "value");
	ASSERT_EQ(name, field.get_name());
}

TEST(WARCField, get_value) 
{
	WARCField<string> field("name", "value");
	ASSERT_EQ("name", field.get_name());
	ASSERT_EQ("value", field.get_value());
	
	WARCField<int> field2("name", 1);
	ASSERT_EQ("name", field2.get_name());
	ASSERT_EQ(1, field2.get_value());
	
	WARCField<float> field3("name", 9.9);
	ASSERT_EQ("name", field3.get_name());
	ASSERT_FLOAT_EQ(9.9, field3.get_value());
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
