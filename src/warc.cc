#include <iostream>
#include <sstream>
#include <algorithm>
#include <iterator>

#include "warc.hh"

namespace warc { inline namespace v1 { 
	
static const char CR = 0x0d;
static const char LF = 0x0a;

struct WARCField
{
	std::string name;
	std::string value;
};

// when we read data from the warc file to a string always read until
// CRLF chars found
std::istream& operator>> (std::istream& is, string& str)
{
	std::istream::sentry s(is);
	if (s) {
		is >> std::noskipws;
		while(is.good()){
			char c = is.get();
			if (c == CR && is.get() == LF)
				break;
			str += c;
		}
	}
	return is;
}

// parse a WARCField from the istream
std::istream& operator>> (std::istream& is, struct WARCField& field)
{
	std::istream::sentry s(is);
	if (s) {
		std::string line;
		is >> line; 
		if (line.empty()){
			is.setstate(std::ios_base::eofbit);
			return is;
		}
		auto p = std::find(line.begin(), line.end(), ':');
		std::move(line.begin(), p, std::back_inserter(field.name));
		std::move(p+1, line.end(), std::back_inserter(field.value));
	}
	return is;
}

void parse_warc_record(istream& is)
{
	string version;
	is >> version;
	std::cout << "Record version: " << version << std::endl;
	while(is.good()) {
		WARCField field;
		is >> field;
		if (is.good())
			std::cout << field.name << " : " << field.value << std::endl;
	}
}

} };
