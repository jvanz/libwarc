#pragma once

#include <string>
#include <istream>

using namespace std;

namespace warc { inline namespace v1 { 

template <typename T>
class WARCField
{
	private:
		string name;
		T value;
	public:
		explicit WARCField(string name, T value): name{name}, value{value} {};
		inline string get_name() const { return this->name; };
		inline T get_value() const { return this->value; };
};

} }
