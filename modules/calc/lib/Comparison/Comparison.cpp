#include "modules/calc/include/k_functionblock.h"
#include <stddef.h>


#include "EQ_DOUBLE"
#include "EQ_FLOAT"
#include "EQ_INT"
#include "EQ_INT64"
#include "EQ_TIME"
#include "EQ_UINT"
#include "EQ_UINT64"
#include "GE_DOUBLE"
#include "GE_FLOAT"
#include "GE_INT"
#include "GE_INT64"
#include "GE_TIME"
#include "GE_UINT"
#include "GE_UINT64"
#include "GT_DOUBLE"
#include "GT_FLOAT"
#include "GT_INT"
#include "GT_INT64"
#include "GT_TIME"
#include "GT_UINT"
#include "GT_UINT64"
#include "LE_DOUBLE"
#include "LE_FLOAT"
#include "LE_INT"
#include "LE_INT64"
#include "LE_TIME"
#include "LE_UINT"
#include "LE_UINT64"
#include "LT_DOUBLE"
#include "LT_FLOAT"
#include "LT_INT"
#include "LT_INT64"
#include "LT_TIME"
#include "LT_UINT"
#include "LT_UINT64"
#include "NE_DOUBLE"
#include "NE_FLOAT"
#include "NE_INT"
#include "NE_INT64"
#include "NE_TIME"
#include "NE_UINT"
#include "NE_UINT64"

static void *fb_table[] = {
    &fb_EQ_DOUBLE, &fb_EQ_FLOAT,  &fb_EQ_INT,    &fb_EQ_INT64,  &fb_EQ_TIME,
    &fb_EQ_UINT,   &fb_EQ_UINT64, &fb_GE_DOUBLE, &fb_GE_FLOAT,  &fb_GE_INT,
    &fb_GE_INT64,  &fb_GE_TIME,   &fb_GE_UINT,   &fb_GE_UINT64, &fb_GT_DOUBLE,
    &fb_GT_FLOAT,  &fb_GT_INT,    &fb_GT_INT64,  &fb_GT_TIME,   &fb_GT_UINT,
    &fb_GT_UINT64, &fb_LE_DOUBLE, &fb_LE_FLOAT,  &fb_LE_INT,    &fb_LE_INT64,
    &fb_LE_TIME,   &fb_LE_UINT,   &fb_LE_UINT64, &fb_LT_DOUBLE, &fb_LT_FLOAT,
    &fb_LT_INT,    &fb_LT_INT64,  &fb_LT_TIME,   &fb_LT_UINT,   &fb_LT_UINT64,
    &fb_NE_DOUBLE, &fb_NE_FLOAT,  &fb_NE_INT,    &fb_NE_INT64,  &fb_NE_TIME,
    &fb_NE_UINT,   &fb_NE_UINT64,
};

static size_t cursor;

void *comparison_first() {
  cursor = 0;
  return fb_table[0];
}

void *comparison_next() {
  cursor++;
  if (cursor < sizeof(fb_table) / sizeof(void *)) {
    return fb_table[cursor];
  } else {
    return 0; // NULL
  }
}
