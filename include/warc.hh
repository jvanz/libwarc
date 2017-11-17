#ifndef _WARC_HH
#define _WARC_HH

#include <string>
#include <istream>

using namespace std;

namespace warc { inline namespace v1 { 

template<typename T>
class WARCField
{
	std::string name;
	T value;
	public:
		explicit WARCField(string _name, T _value) : name{_name}, 
			 value{_value} { }
		// move constructor
		WARCField(WARCField&& r) : name(std::move(r.name)), 
			value(std::move(r.value)) { };
	template<typename P>
	friend std::ostream& operator<<(std::ostream& os, const WARCField<P>& field);
};

template<typename T>
std::ostream& operator<<(std::ostream& os, const WARCField<T>& field)
{
	std::ostream::sentry s(os);
	if (s) 
		os << field.name << ": " << field.value;
	return os;
};

class WARCRecord
{
	private:
		string version;
	public:
		explicit WARCRecord(string version): version{version} {};
};
	
void parse_warc_record(istream& stream);

} };

#endif
