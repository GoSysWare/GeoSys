#include <float.h>
#include <limits.h>
#include <stddef.h>

#include "modules/calc/include/k_functionblock.h"

#include "STR_APPEND"
#include  "STR_CLEAR"
#include  "STR_COMPARE"
#include  "STR_COPY"
#include  "STR_EQ"
#include  "STR_ERASE"
#include  "STR_FIND"
#include  "STR_FIND_FIRST_OF"
#include  "STR_FIND_LAST_OF"
#include  "STR_INSERT"
#include  "STR_REPLACE"
#include  "STR_SUBSTR"

static void *fb_table[] = {
    &fb_STR_APPEND,
    &fb_STR_CLEAR,
    &fb_STR_COMPARE,
    &fb_STR_COPY,
    &fb_STR_EQ,
    &fb_STR_ERASE,
    &fb_STR_FIND,
    &fb_STR_FIND_FIRST_OF,
    &fb_STR_FIND_LAST_OF,
    &fb_STR_INSERT,
    &fb_STR_REPLACE,
    &fb_STR_SUBSTR,
};

static size_t cursor;

void *string_first() {
  cursor = 0;
  return fb_table[0];
}

void *string_next() {
  cursor++;
  if (cursor < sizeof(fb_table) / sizeof(void *)) {
    return fb_table[cursor];
  } else {
    return 0; // NULL
  }
}
