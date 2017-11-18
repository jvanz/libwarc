#include <iostream>
#include <sstream>
#include <algorithm>
#include <iterator>

#include "warc.hh"

namespace warc { inline namespace v1 { 
	
static const char CR = 0x0d;
static const char LF = 0x0a;

struct WARCFieldTemp
{
	std::string name;
	std::string value;
};

// when we read data from the warc file to a string always read until
// CRLF chars found
std::istream& operator>> (std::istream& is, std::string& str)
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
std::istream& operator>> (std::istream& is, struct WARCFieldTemp& field)
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

/// parse the new WARCRecord from the istream
std::istream& operator>>(std::istream& is, WARCRecord& record)
{
	std::istream::sentry s(is);
	if (s) {
		// get the record version
		std::string version;
		is >> version;
		record.version = version;
		// read the header data
		while(is.good()) {
			struct WARCFieldTemp f;
			is >> f;
			// empty line (end of the header)
			if (is.eof())
				break;
			WARCField<std::string> field;
			field.name = f.name;
			field.value = f.value;
			record.fields.push_back(std::move(field));
		}
		// read record content
		// TODO
	}
	return is;
}

std::ostream& operator<<(std::ostream& os, const WARCRecord& record)
{
	std::ostream::sentry s(os);
	if (s) {
		for (auto field : record.fields)
			os << field << std::endl;
	}
	return os;
};

template<typename T>
std::ostream& operator<<(std::ostream& os, const WARCField<T>& field)
{
	std::ostream::sentry s(os);
	if (s) 
		os << field.name << ": " << field.value;
	return os;
};

WARCRecord parse_warc_record(std::istream& is)
{
	WARCRecord record;
	is >> record;
	return record;
}

} };
