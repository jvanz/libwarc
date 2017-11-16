#ifndef _WARC_HH
#define _WARC_HH

#include <string>
#include <istream>

using namespace std;

namespace warc { inline namespace v1 { 

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
