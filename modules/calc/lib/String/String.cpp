#include <float.h>
#include <limits.h>
#include <stddef.h>

#include "modules/calc/include/k_functionblock.h"

#include "ADD_DOUBLE"


static void *fb_table[] = {
    &fb_ADD_DOUBLE,
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
