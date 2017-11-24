#ifndef _HELPER_HH
#define _HELPER_HH

#include <gtest/gtest.h>
#include <sstream>

#include "warc.hh"

static const char CR= 0x0D;
static const char LF= 0x0A;

std::stringstream get_invalid_field_name_record();
std::stringstream get_record();
std::stringstream get_record_content();
void assert_record(const warc::WARCRecord& record);


std::stringstream get_record2();
std::stringstream get_record2_content();
void assert_record2(const warc::WARCRecord& record);

#endif
