
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

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
