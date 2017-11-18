#ifndef _WARC_HH
#define _WARC_HH

#include <string>
#include <istream>
#include <list>

namespace warc { inline namespace v1 { 

// forward declaration
class WARCRecord;

template<typename T>
class WARCField
{
	private:
		std::string name;
		T value;
	public:
		explicit WARCField() {};

	template<typename P>
	friend std::ostream& operator<< (std::ostream& os, const WARCField<P>& field);
	friend std::istream& operator>> (std::istream& is, struct WARCFieldTemp& field);
	friend std::istream& operator>> (std::istream& is, WARCRecord& record);
};


/// WARC record object. 
/// Store all field from the record header and its content
class WARCRecord
{
	private:
		std::string version;
		std::list<WARCField<std::string>> fields;
	public:
		explicit WARCRecord() {};

	friend std::ostream& operator<<(std::ostream& os, const WARCRecord& record);
	friend std::istream& operator>> (std::istream& is, WARCRecord& record);
};

	
WARCRecord parse_warc_record(std::istream& stream);

} };

#endif
