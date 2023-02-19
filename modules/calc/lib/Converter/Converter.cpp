#include <stddef.h>
#include <float.h>
#include <limits.h>

#include "modules/calc/include/k_functionblock.h"


#include "B2D"
#include "B2F"
#include "B2I"
#include "B2LL"
#include "B2TM"
#include "B2UI"
#include "B2ULL"

#include "D2B"
#include "D2F"
#include "D2I"
#include "D2LL"
#include "D2TM"
#include "D2UI"
#include "D2ULL"

#include "F2B"
#include "F2D"
#include "F2I"
#include "F2LL"
#include "F2TM"
#include "F2UI"
#include "F2ULL"

#include "I2B"
#include "I2D"
#include "I2F"
#include "I2LL"
#include "I2TM"
#include "I2UI"
#include "I2ULL"

#include "LL2B"
#include "LL2D"
#include "LL2F"
#include "LL2I"
#include "LL2TM"
#include "LL2UI"
#include "LL2ULL"

#include "TM2B"
#include "TM2D"
#include "TM2F"
#include "TM2I"
#include "TM2LL"
#include "TM2UI"
#include "TM2ULL"

#include "UI2B"
#include "UI2D"
#include "UI2F"
#include "UI2I"
#include "UI2LL"
#include "UI2TM"
#include "UI2ULL"

#include "ULL2B"
#include "ULL2D"
#include "ULL2F"
#include "ULL2I"
#include "ULL2LL"
#include "ULL2TM"
#include "ULL2UI"

static void *fb_table[] = {
    &fb_B2D,    &fb_B2F,    &fb_B2I,   &fb_B2LL,  &fb_B2TM,   &fb_B2UI,
    &fb_B2ULL,  &fb_D2B,    &fb_D2F,   &fb_D2I,   &fb_D2LL,   &fb_D2TM,
    &fb_D2UI,   &fb_D2ULL,  &fb_F2B,   &fb_F2D,   &fb_F2I,    &fb_F2LL,
    &fb_F2TM,   &fb_F2UI,   &fb_F2ULL, &fb_I2B,   &fb_I2D,    &fb_I2F,
    &fb_I2LL,   &fb_I2TM,   &fb_I2UI,  &fb_I2ULL, &fb_LL2B,   &fb_LL2D,
    &fb_LL2F,   &fb_LL2I,   &fb_LL2TM, &fb_LL2UI, &fb_LL2ULL, &fb_TM2B,
    &fb_TM2D,   &fb_TM2F,   &fb_TM2I,  &fb_TM2LL, &fb_TM2UI,  &fb_TM2ULL,
    &fb_UI2B,   &fb_UI2D,   &fb_UI2F,  &fb_UI2I,  &fb_UI2LL,  &fb_UI2TM,
    &fb_UI2ULL, &fb_ULL2B,  &fb_ULL2D, &fb_ULL2F, &fb_ULL2I,  &fb_ULL2LL,
    &fb_ULL2TM, &fb_ULL2UI,
};

static size_t cursor;

void *converter_first() {
  cursor = 0;
  return fb_table[0];
}

void *converter_next() {
  cursor++;
  if (cursor < sizeof(fb_table) / sizeof(void *)) {
    return fb_table[cursor];
  } else {
    return 0; // NULL
  }
}
