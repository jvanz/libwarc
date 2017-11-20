#include <algorithm>

#include "constants.hh"

static const auto ALL_FIELDS = {
	WARC_TYPE,
	WARC_RECORD_ID,
	WARC_DATE,
	CONTENT_LENGTH,
	CONTENT_TYPE,
	WARC_CONCURRENT_TO,
	WARC_BLOCK_DIGEST,
	WARC_PAYLOAD_DIGEST,
	WARC_IP_ADDRESS,
	WARC_REFERS_TO,
	WARC_TARGET_URI,
	WARC_TRUNCATED,
	WARC_WARCINFO_ID,
	WARC_FILENAME,
	WARC_PROFILE,
	WARC_IDENTIFIED_PAYLOAD_TYPE,
	WARC_SEGMENT_ORIGIN_ID,
	WARC_SEGMENT_NUMBER,
	WARC_SEGMENT_TOTAL_LENGTH
};

bool is_warc_field_name(std::string name)
{
	return std::any_of(ALL_FIELDS.begin(), ALL_FIELDS.end(),
		[name] (std::string n) { return n == name; });
}
