#ifndef _CONSTANTS_HH
#define _CONSTANTS_HH

#include <string>

// defined WARC fields
const auto WARC_TYPE = "WARC-Type";
const auto WARC_RECORD_ID = "WARC-Record-ID";
const auto WARC_DATE = "WARC-Date";
const auto CONTENT_LENGTH = "Content-Length";
const auto CONTENT_TYPE = "Content-Type";
const auto WARC_CONCURRENT_TO = "WARC-Concurrent-To";
const auto WARC_BLOCK_DIGEST = "WARC-Block-Digest";
const auto WARC_PAYLOAD_DIGEST = "WARC-Payload-Digest";
const auto WARC_IP_ADDRESS = "WARC-IP-Address";
const auto WARC_REFERS_TO = "WARC-Refers-To";
const auto WARC_TARGET_URI = "WARC-Target-URI";
const auto WARC_TRUNCATED = "WARC-Truncated";
const auto WARC_WARCINFO_ID = "WARC-Warcinfo-ID";
const auto WARC_FILENAME = "WARC-Filename";
const auto WARC_PROFILE = "WARC-Profile";
const auto WARC_IDENTIFIED_PAYLOAD_TYPE = "WARC-Identified-Payload-Type";
const auto WARC_SEGMENT_ORIGIN_ID = "WARC-Segment-Origin-ID";
const auto WARC_SEGMENT_NUMBER = "WARC-Segment-Number";
const auto WARC_SEGMENT_TOTAL_LENGTH = "WARC-Segment-Total-Length";

bool is_warc_field_name(std::string name);

#endif
