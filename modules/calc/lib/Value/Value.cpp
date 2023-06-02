#include <stddef.h>
#include <regex>
#include "modules/calc/include/k_functionblock.h"
#include <nlohmann/json.hpp>
#include <google/protobuf/util/json_util.h>


void split(const std::string &s, std::vector<std::string> &tokens,
           const std::string &delimiters = " ") {
  std::string::size_type lastPos = s.find_first_not_of(delimiters, 0);
  std::string::size_type pos = s.find_first_of(delimiters, lastPos);
  while (std::string::npos != pos || std::string::npos != lastPos) {
    tokens.emplace_back(s.substr(lastPos, pos - lastPos));
    lastPos = s.find_first_not_of(delimiters, pos);
    pos = s.find_first_of(delimiters, lastPos);
  }
}
using namespace google::protobuf;

using namespace google::protobuf::util;


#include "JSON_OBJ_MERGE"
#include "JSON_SERIAL"

#include "JSON2PB"
#include "PB2JSON"
#include "V_GET_ANY"
#include "V_GET_DOUBLE"
#include "V_SET_ANY"
#include "V_SET_DOUBLE"

static void *fb_table[] = {
	&fb_JSON_OBJ_MERGE,
	&fb_JSON_SERIAL,
    &fb_JSON2PB,      &fb_PB2JSON,   &fb_V_GET_ANY,
    &fb_V_GET_DOUBLE, &fb_V_SET_ANY, &fb_V_SET_DOUBLE,

};

static size_t cursor;

void *value_first() {
  cursor = 0;
  return fb_table[0];
}

void *value_next() {
  cursor++;
  if (cursor < sizeof(fb_table) / sizeof(void *)) {
    return fb_table[cursor];
  } else {
    return 0;  // NULL
  }
}
