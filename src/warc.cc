#include <iostream>
#include <algorithm>
#include <cctype>

#include "warc.hh"
#include "constants.hh"

namespace warc { inline namespace v1 { 
	
static const char CR = 0x0d;
static const char LF = 0x0a;

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
std::istream& operator>> (std::istream& is, WARCField& field)
{
	std::istream::sentry s(is);
	if (s) {
		std::string line;
		is >> line; 
		if (line.empty()){
			is.setstate(std::ios_base::failbit);
			return is;
		}
		auto p = std::find(line.begin(), line.end(), ':');
		std::move(line.begin(), p, std::back_inserter(field.name));
		// XXX throw an exception or invalid the stream?
		if (!is_warc_field_name(field.name))
			throw "Unexpected field";
		p++; // skip ":"
		// remove white space after ":" char if exits
		while (isspace(*p))
			p++;
		std::move(p, line.end(), std::back_inserter(field.value));
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
			WARCField field;
			is >> field;
			// empty line (end of the header)
			if (is.fail())
				break;
			record.fields.push_back(std::move(field));
		}
		// reset fail bit
		is.clear();
		// get the content length.
		auto it = find(record.fields.begin(), record.fields.end(), CONTENT_LENGTH);
		if (it != record.fields.end()){
			auto length = stoul(it->value);
			char buffer[length];
			if (is.read(buffer, length))
				record.content = std::move(std::string(buffer, length));
		}
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

std::ostream& operator<<(std::ostream& os, const WARCField& field)
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
