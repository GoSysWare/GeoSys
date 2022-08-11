#include "modules/calc/include/k_functionblock.h"
#include "modules/calc/include/k_evdata.h"
#include "modules/calc/include/k_util.h"
#include <stddef.h>
#include <stdio.h>
#include <string.h>

fb_t *fb_new(fb_t *p_source) {
  fb_t *p_dst = 0;
  p_dst = new fb_t;
  if (p_dst) {
    p_dst->h = p_source->h;
    p_dst->ins = p_source->ins;
    for (auto &&pin : p_dst->ins) {
      pin.v = new vam_t(std::make_shared<value_tm>());
      (*(pin.v))->mutable_v()->set_t(pin.t);
    }
    p_dst->outs = p_source->outs;
    for (auto &&pin : p_dst->outs) {
      pin.v = new vam_t(std::make_shared<value_tm>());
      (*(pin.v))->mutable_v()->set_t(pin.t);
    }
    p_dst->props = p_source->props;
    for (auto &&pin : p_dst->props) {
      pin.v = new vam_t(std::make_shared<value_tm>());
      (*(pin.v))->mutable_v()->set_t(pin.t);
    }
  }
  return p_dst;
}

void fb_delete(fb_t *p_fb) {
  for (auto &&pin : p_fb->ins) {
    pin.v->reset();
    delete pin.v;
  }
  for (auto &&pin : p_fb->outs) {
    pin.v->reset();
    delete pin.v;
  }
  for (auto &&pin : p_fb->props) {
    pin.v->reset();
    delete pin.v;
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
  // 对共享指针所指的内容进行值拷贝，计数器不动
  return setvar(*(p_pin->v), p_pin->t, v);
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
  if (p_pin->v) {
    p_pin->v->reset();
  }
  //此时计数器会+1，指向新值
  *(p_pin->v) = v;
  //等函数执行完 局部变量v的计数器-1,管脚的v计数器依然为1
  return 0;
}

void fb_dump(fb_t *p_fb) {
  unsigned int i;
  std::cout << "fc: " << p_fb->h.fcname << std::endl;
  std::cout << "input: " << std::endl;
  for (i = 0; i < p_fb->ins.size(); i++) {
    std::cout << "fb: " << p_fb->ins[i].pinname << "- "
              << type2str(p_fb->ins[i].t) << ": "
              << (*(p_fb->ins[i].v))->ShortDebugString() << std::endl;
  }
  std::cout << "output: " << std::endl;
  for (i = 0; i < p_fb->outs.size(); i++) {
    std::cout << "fb: " << p_fb->outs[i].pinname << "- "
              << type2str(p_fb->outs[i].t) << ": "
              << (*(p_fb->outs[i].v))->ShortDebugString() << std::endl;
  }
  std::cout << "property: " << std::endl;
  for (i = 0; i < p_fb->props.size(); i++) {
    std::cout << "fb: " << p_fb->props[i].pinname << "- "
              << type2str(p_fb->props[i].t) << ": "
              << (*(p_fb->props[i].v))->ShortDebugString() << std::endl;
  }
  std::cout << std::endl;
}

std::string fb_pins_to_string(fb_t *p_fb) {
  unsigned int i;
  std::string fb_string;
  /* input */
  for (i = 0; i < p_fb->ins.size(); i++) {
    fb_string += p_fb->ins[i].pinname + "/" + type2str(p_fb->ins[i].t) + "/" +
                 (*(p_fb->ins[i].v))->ShortDebugString() + ",";
  }
  fb_string += ",;";

  /* output */
  for (i = 0; i < p_fb->outs.size(); i++) {
    fb_string += p_fb->outs[i].pinname + "/" + type2str(p_fb->outs[i].t) + "/" +
                 (*(p_fb->outs[i].v))->ShortDebugString() + ",";
  }
  fb_string += ",;";

  /* property */
  for (i = 0; i < p_fb->props.size(); i++) {
    fb_string += p_fb->props[i].pinname + "/" + type2str(p_fb->props[i].t) +
                 "/" + (*(p_fb->props[i].v))->ShortDebugString() + ",";
  }
  fb_string += ";";
  return fb_string;
}

std::string fb_vars_to_string(fb_t *p_fb) {
  unsigned int i;

  std::string var_string;
  for (i = 0; i < p_fb->ins.size(); i++) {
    var_string += (*(p_fb->ins[i].v))->ShortDebugString();
    var_string += ",";
  }

  /* output */
  for (i = 0; i < p_fb->outs.size(); i++) {
    var_string += (*(p_fb->outs[i].v))->ShortDebugString();
    var_string += ",";
  }

  /* property */
  for (i = 0; i < p_fb->props.size(); i++) {
    var_string += (*(p_fb->props[i].v))->ShortDebugString();
    var_string += ",";
  }
  return var_string;
}
