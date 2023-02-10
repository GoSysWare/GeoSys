#include "modules/calc/include/k_functionblock.h"
#include "modules/calc/include/k_evdata.h"
#include "modules/calc/include/k_util.h"
#include <stddef.h>
#include <stdio.h>
#include <string.h>


static void fb_init_pin(pin_t *pin) {
  pin->s = PIN_NO_LINK;
  vam_init(&pin->v,pin->t);
}

// static void fb_init_pin(pin_t *pin) {
//   pin->s = PIN_NO_LINK;

//   pin->v.reset( new value_tm );
//   pin->v->set_tm(apollo::cyber::Time::Now().ToNanosecond());

//   pin->v->mutable_v()->set_t(pin->t);
//   value_t *vt = pin->v->mutable_v();
//   switch (pin->t) {
//   case T_NONE:
//     break;
//   case T_BOOL:
//     vt->set_b(false);
//     break;
//   case T_INT32:
//     vt->set_i(0);
//     break;
//   case T_UINT32:
//     vt->set_ui(0);
//     break;
//   case T_INT64:
//     vt->set_ll(0);
//     break;
//   case T_UINT64:
//     vt->set_ull(0);
//     break;
//   case T_FLOAT32:
//     vt->set_i(0.0);
//     break;
//   case T_FLOAT64:
//     vt->set_d(0.0);
//     break;
//   case T_TIME:
//     vt->set_tm(0);
//     break;
//   case T_STRING:
//     vt->set_str("");
//     break;
//   case T_BYTES:
//     vt->set_blob("");
//     break;
//   case T_IMAGE:
//     vt->set_img("");
//     break;
//   case T_LIDAR:
//     vt->set_lidar("");
//     break;
//   case T_SONAR:
//     vt->set_sonar("");
//     break;
//   case T_FILE:
//     vt->set_file("");
//     break;
//   default:
//     break;
//   }
// }
// static void fb_init_pin(pin_t *pin) {
//   if(pin->v != nullptr) 
//     pin->v.reset(); 
// }
void fb_reset(fb_t *p_fb) {
  if (p_fb) {
    for (auto &pin : p_fb->ins) {
      fb_init_pin(&pin);
    }
    for (auto &pin : p_fb->outs) {
      fb_init_pin(&pin);
    }
    for (auto &pin : p_fb->props) {
      fb_init_pin(&pin);
    }
  }
}

fb_t *fb_new(fb_t *p_source) {
  fb_t *p_dst = 0;
  p_dst = new fb_t;
  if (p_dst) {
    p_dst->h = p_source->h;
    p_dst->ins = p_source->ins;
    for (auto &&pin : p_dst->ins) {
      fb_init_pin(&pin);
    }
    p_dst->outs = p_source->outs;
    for (auto &&pin : p_dst->outs) {
      fb_init_pin(&pin);
    }
    p_dst->props = p_source->props;
    for (auto &&pin : p_dst->props) {
      fb_init_pin(&pin);
    }
  }
  return p_dst;
}

void fb_delete(fb_t *p_fb) {
  for (auto &&pin : p_fb->ins) {
    pin.v.reset();
  }
  for (auto &&pin : p_fb->outs) {
    pin.v.reset();
  }
  for (auto &&pin : p_fb->props) {
    pin.v.reset();
  }
  delete p_fb;
}
//管脚从1开始计数
pin_t *fb_getpin(fb_t *p_fb, int pintype, unsigned int n) {
  pin_t *p_pin;

  if (pintype == PININPUT) {
    if (n >= p_fb->ins.size()) {
      return 0;
    }
    p_pin = &p_fb->ins[n];
  } else if (pintype == PINOUTPUT) {
    if (n >= p_fb->outs.size()) {
      return 0;
    }
    p_pin = &p_fb->outs[n];
  } else if (pintype == PINPROPERTY) {
    if (n >= p_fb->props.size()) {
      return 0;
    }
    p_pin = &p_fb->props[n];
  } else {
    return 0;
  }
  return p_pin;
}

int fb_setpin(fb_t *p_fb, int pintype, unsigned int n, value_tm v) {
  pin_t *p_pin;
  if (pintype == PININPUT) {
    if (n >= p_fb->ins.size()) {
      return -1;
    }
    p_pin = &p_fb->ins[n];

  } else if (pintype == PINOUTPUT) {
    if (n >= p_fb->outs.size()) {
      return 0;
    }
    p_pin = &p_fb->outs[n];
    return -1;
  } else if (pintype == PINPROPERTY) {
    if (n >= p_fb->props.size()) {
      return -1;
    }
    p_pin = &p_fb->props[n];
  } else {
    return -1;
  }
  p_pin->s = PIN_IS_LINK;
  p_pin->v = std::make_shared<value_tm>(v);
  return 0;
}

int fb_setpin(fb_t *p_fb, int pintype, unsigned int n, vam_t v) {
  pin_t *p_pin;
  if (pintype == PININPUT) {
    if (n >= p_fb->ins.size()) {
      return -1;
    }
    p_pin = &p_fb->ins[n];

  } else if (pintype == PINOUTPUT) {
    if (n >= p_fb->outs.size()) {
      return -1;
    }
    p_pin = &p_fb->outs[n];
  } else if (pintype == PINPROPERTY) {
    if (n >= p_fb->props.size()) {
      return -1;
    }
    p_pin = &p_fb->props[n];
  } else {
    return -1;
  }
  p_pin->s = PIN_IS_LINK;
  p_pin->v = v;
  return 0;
}

void fb_dump(fb_t *p_fb) {
  unsigned int i;
  std::cout << "\t\t\tfc: " << p_fb->h.fcname << std::endl;
  std::cout << "\t\t\tinput: " << std::endl;
  for (i = 0; i < p_fb->ins.size(); i++) {
    std::cout << "\t\t\t\tfb: " << p_fb->ins[i].pinname << "- "
              << type2str(p_fb->ins[i].t) << ": "
              << p_fb->ins[i].v->ShortDebugString() << std::endl;
  }
  std::cout << "\t\t\toutput: " << std::endl;
  for (i = 0; i < p_fb->outs.size(); i++) {
    std::cout << "\t\t\t\tfb: " << p_fb->outs[i].pinname << "- "
              << type2str(p_fb->outs[i].t) << ": "
              << p_fb->outs[i].v->ShortDebugString() << std::endl;
  }
  std::cout << "\t\t\tproperty: " << std::endl;
  for (i = 0; i < p_fb->props.size(); i++) {
    std::cout << "\t\t\t\tfb: " << p_fb->props[i].pinname << "- "
              << type2str(p_fb->props[i].t) << ": "
              << p_fb->props[i].v->ShortDebugString() << std::endl;
  }
  std::cout << std::endl;
}

std::string fb_pins_to_string(fb_t *p_fb) {
  unsigned int i;
  std::string fb_string;
  /* input */
  for (i = 0; i < p_fb->ins.size(); i++) {
    fb_string += p_fb->ins[i].pinname + "/" + type2str(p_fb->ins[i].t) + "/" +
                 p_fb->ins[i].v->ShortDebugString() + ",";
  }
  fb_string += ",;";

  /* output */
  for (i = 0; i < p_fb->outs.size(); i++) {
    fb_string += p_fb->outs[i].pinname + "/" + type2str(p_fb->outs[i].t) + "/" +
                 p_fb->ins[i].v->ShortDebugString() + ",";
  }
  fb_string += ",;";

  /* property */
  for (i = 0; i < p_fb->props.size(); i++) {
    fb_string += p_fb->props[i].pinname + "/" + type2str(p_fb->props[i].t) +
                 "/" + p_fb->ins[i].v->ShortDebugString() + ",";
  }
  fb_string += ";";
  return fb_string;
}

std::string fb_vars_to_string(fb_t *p_fb) {
  unsigned int i;

  std::string var_string;
  for (i = 0; i < p_fb->ins.size(); i++) {
    var_string += p_fb->ins[i].v->ShortDebugString();
    var_string += ",";
  }

  /* output */
  for (i = 0; i < p_fb->outs.size(); i++) {
    var_string += p_fb->ins[i].v->ShortDebugString();
    var_string += ",";
  }

  /* property */
  for (i = 0; i < p_fb->props.size(); i++) {
    var_string += p_fb->ins[i].v->ShortDebugString();
    var_string += ",";
  }
  return var_string;
}
