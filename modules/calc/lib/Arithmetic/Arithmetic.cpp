#include <float.h>
#include <limits.h>
#include <stddef.h>

#include "modules/calc/include/k_functionblock.h"

#include "ADD_DOUBLE"
#include "ADD_FLOAT"
#include "ADD_INT"
#include "ADD_INT64"
#include "ADD_TIME"
#include "ADD_UINT"
#include "ADD_UINT64"

#include "DIV_DOUBLE"
#include "DIV_FLOAT"
#include "DIV_INT"
#include "DIV_INT64"
#include "DIV_UINT"
#include "DIV_UINT64"

#include "MOVE_BOOL"
#include "MOVE_DOUBLE"
#include "MOVE_FLOAT"
#include "MOVE_INT"
#include "MOVE_INT64"
#include "MOVE_UINT"
#include "MOVE_UINT64"

#include "MUL_DOUBLE"
#include "MUL_FLOAT"
#include "MUL_INT"
#include "MUL_INT64"
#include "MUL_UINT"
#include "MUL_UINT64"

#include "SUB_DOUBLE"
#include "SUB_FLOAT"
#include "SUB_INT"
#include "SUB_INT64"
#include "SUB_TIME"
#include "SUB_UINT"
#include "SUB_UINT64"

static void *fb_table[] = {
    &fb_ADD_DOUBLE, &fb_ADD_FLOAT,  &fb_ADD_INT,     &fb_ADD_INT64,
    &fb_ADD_TIME,   &fb_ADD_UINT,   &fb_ADD_UINT64,  &fb_DIV_DOUBLE,
    &fb_DIV_FLOAT,  &fb_DIV_INT,    &fb_DIV_INT64,   &fb_DIV_UINT,
    &fb_DIV_UINT64, &fb_MOVE_BOOL,  &fb_MOVE_DOUBLE, &fb_MOVE_FLOAT,
    &fb_MOVE_INT,   &fb_MOVE_INT64, &fb_MOVE_UINT,   &fb_MOVE_UINT64,
    &fb_MUL_DOUBLE, &fb_MUL_FLOAT,  &fb_MUL_INT,     &fb_MUL_INT64,
    &fb_MUL_UINT,   &fb_MUL_UINT64, &fb_SUB_DOUBLE,  &fb_SUB_FLOAT,
    &fb_SUB_INT,    &fb_SUB_INT64,  &fb_SUB_TIME,    &fb_SUB_UINT,
    &fb_SUB_UINT64,
};

static size_t cursor;

void *arithmetic_first() {
  cursor = 0;
  return fb_table[0];
}

void *arithmetic_next() {
  cursor++;
  if (cursor < sizeof(fb_table) / sizeof(void *)) {
    return fb_table[cursor];
  } else {
    return 0; // NULL
  }
}
