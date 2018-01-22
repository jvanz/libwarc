#ifndef _WARC_HH
#define _WARC_HH

#include <fstream>
#include <istream>
#include <iterator>
#include <list>
#include <string>

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
		explicit WARCField() { };
		std::string get_name() const { return this->name; };
		std::string get_value() const { return this->value; };
		// Let's allow the user find the field by name
		bool operator== (const std::string& name){
			return this->name == name;
		};
		bool operator== (const WARCField& other) const
		{
			return this->name == other.name
				&& this->value == other.value;
		};
		bool operator!= (const WARCField& other) const
		{
			return !(*this == other);
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
		};

		bool operator== (const WARCRecord& other)
		{
			return this->version == other.version
				&& this->fields == other.fields
				&& this->content == other.content;
		};
		bool operator!= (const WARCRecord& other)
		{
			return !(*this == other);
		};

	friend std::ostream& operator<< (std::ostream& os, const WARCRecord& record);
	friend std::istream& operator>> (std::istream& is, WARCRecord& record);
};

// operator to parse/print the WARC fields and records
std::ostream& operator<< (std::ostream& os, const WARCField& field);
std::istream& operator>> (std::istream& is, WARCField& field);
std::istream& operator>> (std::istream& is, WARCRecord& record);
std::ostream& operator<< (std::ostream& os, const WARCRecord& record);

/// WARC file stream iterator
class WARCFile
{
	private:
		std::ifstream _file_stream;

	public:
		explicit WARCFile(std::string filename) : _file_stream(filename) {};

		auto begin()
		{
			return std::istream_iterator<WARCRecord>(_file_stream);
		};

		auto end()
		{
			return std::istream_iterator<WARCRecord>();
		};

};

} };

#endif
