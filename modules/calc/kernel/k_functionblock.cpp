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
    p_dst->d = p_source->d;
    for (auto &&pin : p_dst->d) {
      pin.v = new vam_t(std::make_shared<value_tm>());
    }
  }
  return p_dst;
}

void fb_delete(fb_t *p_fb) {
  for (auto &&pin : p_fb->d) {
    pin.v->reset();
    delete pin.v;
  }
  delete p_fb;
}

pin_t *fb_getpin(fb_t *p_fb, int pintype, unsigned int n) {
  int np;
  pin_t *p_pin;

  if (pintype == PININPUT) {
    if (n >= p_fb->h.ni) {
      return 0;
    }
    np = n;
  } else if (pintype == PINOUTPUT) {
    if (n >= p_fb->h.no) {
      return 0;
    }
    np = n + p_fb->h.ni;
  } else if (pintype == PINPROPERTY) {
    if (n >= p_fb->h.np) {
      return 0;
    }
    np = n + p_fb->h.ni + p_fb->h.no;
  } else {
    return 0;
  }

  p_pin = &p_fb->d[np];
  return p_pin;
}

int fb_setpin(fb_t *p_fb, int pintype, unsigned int n, value_tm v) {
  int np;
  if (pintype == PININPUT) {
    if (n >= p_fb->h.ni) {
      return -1;
    }
    np = n;
  } else if (pintype == PINOUTPUT) {
    if (n >= p_fb->h.no) {
      return 0;
    }
    np = n + p_fb->h.ni;
    return -1;
  } else if (pintype == PINPROPERTY) {
    if (n >= p_fb->h.np) {
      return -1;
    }
    np = n + p_fb->h.ni + p_fb->h.no;
  } else {
    return -1;
  }
  // 对共享指针所指的内容进行值拷贝，计数器不动
  setvar(*(p_fb->d[np].v),p_fb->d[np].t,v);
  return 0;
}

int fb_setpin(fb_t *p_fb, int pintype, unsigned int n, vam_t v) {
  int np;

  if (pintype == PININPUT) {
    if (n >= p_fb->h.ni) {
      return -1;
    }
    np = n;
  } else if (pintype == PINOUTPUT) {
    if (n >= p_fb->h.no) {
      return 0;
    }
    np = n + p_fb->h.ni;
    return -1;
  } else if (pintype == PINPROPERTY) {
    if (n >= p_fb->h.np) {
      return -1;
    }
    np = n + p_fb->h.ni + p_fb->h.no;
  } else {
    return -1;
  }
  if(p_fb->d[np].v){
    p_fb->d[np].v->reset();
  }
  //此时计数器会+1，指向新值
  *(p_fb->d[np].v) = v;
  //等函数执行完 局部变量v的计数器-1,管脚的v计数器依然为1
  return 0;
}

void fb_dump(fb_t *p_fb) {
  unsigned int i;
  std::cout << "fc: " << p_fb->h.fcname << std::endl;
  std::cout << "input: " << std::endl;
  for (i = 0; i < p_fb->h.ni; i++) {
    std::cout << "fb: " << p_fb->d[i].pinname << "- " << type2str(p_fb->d[i].t)
              << ": " << (*(p_fb->d[i].v))->ShortDebugString() << std::endl;
  }

  std::cout << "output: " << std::endl;

  for (i = 0 + p_fb->h.ni; i < (p_fb->h.no + p_fb->h.ni); i++) {
    std::cout << "fb: " << p_fb->d[i].pinname << "- " << type2str(p_fb->d[i].t)
              << ": " << (*(p_fb->d[i].v))->ShortDebugString() << std::endl;
  }
  std::cout << "property: " << std::endl;

  for (i = 0 + p_fb->h.ni + p_fb->h.no;
       i < (p_fb->h.np + p_fb->h.ni + p_fb->h.no); i++) {
    std::cout << "fb: " << p_fb->d[i].pinname << "- " << type2str(p_fb->d[i].t)
              << ": " << (*(p_fb->d[i].v))->ShortDebugString() << std::endl;
  }
}

std::string fb_pins_to_string(fb_t *p_fb) {
  unsigned int i;
  std::string fb_string;
  /* input */
  for (i = 0; i < p_fb->h.ni; i++) {
    fb_string += std::string(p_fb->d[i].pinname) + "/" +
                 type2str(p_fb->d[i].t) + "/" +
                 (*(p_fb->d[i].v))->ShortDebugString() + ",";
  }
  fb_string += ",;";

  /* output */
  for (i = 0 + p_fb->h.ni; i < (p_fb->h.no + p_fb->h.ni); i++) {
    fb_string += std::string(p_fb->d[i].pinname) + "/" +
                 type2str(p_fb->d[i].t) + "/" +
                (*(p_fb->d[i].v))->ShortDebugString() + ",";
  }
  fb_string += ",;";

  /* property */
  for (i = 0 + p_fb->h.ni + p_fb->h.no;
       i < (p_fb->h.np + p_fb->h.ni + p_fb->h.no); i++) {
    fb_string += std::string(p_fb->d[i].pinname) + "/" +
                 type2str(p_fb->d[i].t) + "/" +
                 (*(p_fb->d[i].v))->ShortDebugString() + ",";
  }
  fb_string += ";";
  return fb_string;
}

std::string fb_vars_to_string(fb_t *p_fb) {
  unsigned int i;

  std::string var_string;
  for (i = 0; i < (p_fb->h.np + p_fb->h.ni + p_fb->h.no); i++) {
    var_string += (*(p_fb->d[i].v))->ShortDebugString();
    var_string += ",";
  }
  return var_string;
}
