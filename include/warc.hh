#ifndef _WARC_HH
#define _WARC_HH

#include <string>
#include <istream>
#include <list>

namespace warc { inline namespace v1 {

// forward declaration
class WARCRecord;

/// A WARC field definition found within WARC record header
class WARCField
{
	private:
		std::string name;
		std::string value;
	public:
		explicit WARCField() {};

		std::string get_name() const { return this->name; };
		std::string get_value() const { return this->value; };
		// Let's allow the user find the field by name
		bool operator== (const std::string& name){
			return this->name == name;
		};

	friend std::ostream& operator<< (std::ostream& os, const WARCField& field);
	friend std::istream& operator>> (std::istream& is, WARCField& field);
	friend std::istream& operator>> (std::istream& is, WARCRecord& record);
};


/// WARC record object. 
/// Store all field from the record header and its content
// TODO - allow the user to access a WARC field by name instead of iterator over
// all of them
class WARCRecord
{
	private:
		std::string version;
		std::list<WARCField> fields;
		std::string content;

	public:
		explicit WARCRecord() { };

		/// return all WARC records fields.
		auto get_fields() const
		{
			return this->fields;
		};

		std::string get_content() const
		{
			return this->content;
		}

	friend std::ostream& operator<< (std::ostream& os, const WARCRecord& record);
	friend std::istream& operator>> (std::istream& is, WARCRecord& record);
};

// operator to parse/print the WARC fields and records
std::ostream& operator<< (std::ostream& os, const WARCField& field);
std::istream& operator>> (std::istream& is, WARCField& field);
std::istream& operator>> (std::istream& is, WARCRecord& record);
std::ostream& operator<< (std::ostream& os, const WARCRecord& record);

} };

#endif
