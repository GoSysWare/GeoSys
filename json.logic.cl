infos {
  cmd_id: 49
  edit_type: SET
  proj {
    proj_name: "rotbot-engine-project"
    proj_uuid: "{73260418-ac3a-4a33-8cea-5685b07f4ebc}"
  }
}
infos {
  cmd_id: 1
  element: MOD
  edit_type: ADD
  mod {
    mod_id: 1
    mod_name: "M1"
  }
}
infos {
  cmd_id: 2
  element: TASK
  edit_type: ADD
  task {
    mod_id: 1
    task_id: 2
    task_name: "P1"
    interval: 1000
  }
}
infos {
  cmd_id: 3
  element: FB
  edit_type: ADD
  fb {
    mod_id: 1
    task_id: 2
    fb_id: 3
    flib_name: "Value"
    fc_name: "JSON_SERIAL_OBJ"
  }
  pos {
    x: 19
    y: 9
  }
}
infos {
  cmd_id: 4
  element: PIN
  edit_type: SET
  pin {
    mod_id: 1
    task_id: 2
    fb_id: 3
    pin_index: 2
    pin_val {
      t: T_STRING
      v {
        str: "str1"
      }
      tm: 1685675686329280803
    }
  }
}
infos {
  cmd_id: 5
  element: PIN
  edit_type: SET
  pin {
    mod_id: 1
    task_id: 2
    fb_id: 3
    pin_index: 3
    pin_val {
      t: T_STRING
      v {
        str: "val1"
      }
      tm: 1685675692185432169
    }
  }
}
infos {
  cmd_id: 6
  element: PIN
  edit_type: SET
  pin {
    mod_id: 1
    task_id: 2
    fb_id: 3
    pin_index: 7
    pin_val {
      t: T_STRING
      v {
        str: "str3"
      }
      tm: 1685675699576796375
    }
  }
}
infos {
  cmd_id: 7
  element: PIN
  edit_type: SET
  pin {
    mod_id: 1
    task_id: 2
    fb_id: 3
    pin_index: 7
    pin_val {
      t: T_STRING
      v {
        str: "val3"
      }
      tm: 1685675709008195398
    }
  }
}
infos {
  cmd_id: 8
  element: PIN
  edit_type: SET
  pin {
    mod_id: 1
    task_id: 2
    fb_id: 3
    pin_index: 6
    pin_val {
      t: T_STRING
      v {
        str: "str3"
      }
      tm: 1685675714544041862
    }
  }
}
infos {
  cmd_id: 9
  element: EV
  edit_type: ADD
  ev {
    ev_id: 4
    ev_name: "Json_str_1"
    ev_type: 9
    ev_desc: "Desc"
    init_val {
      t: T_STRING
      v {
        str: ""
      }
      tm: 1685675897649431433
    }
  }
}
infos {
  cmd_id: 10
  element: VO
  edit_type: ADD
  vo {
    mod_id: 1
    task_id: 2
    fb_id: 3
    pin_index: 1
    ev_id: 4
    vo_id: 5
  }
}
infos {
  cmd_id: 11
  element: PIN
  edit_type: SET
  pin {
    mod_id: 1
    task_id: 2
    fb_id: 3
    pin_index: 8
    pin_val {
      t: T_STRING
      v {
        str: "afg"
      }
      tm: 1685686292504512255
    }
  }
}
infos {
  cmd_id: 12
  element: PIN
  edit_type: SET
  pin {
    mod_id: 1
    task_id: 2
    fb_id: 3
    pin_index: 9
    pin_val {
      t: T_STRING
      v {
        str: "rtt111"
      }
      tm: 1685686297216570870
    }
  }
}
infos {
  cmd_id: 13
  element: PIN
  edit_type: SET
  pin {
    mod_id: 1
    task_id: 2
    fb_id: 3
    pin_index: 10
    pin_val {
      t: T_STRING
      v {
        str: "3445"
      }
      tm: 1685686302888110092
    }
  }
}
infos {
  cmd_id: 14
  element: PIN
  edit_type: SET
  pin {
    mod_id: 1
    task_id: 2
    fb_id: 3
    pin_index: 11
    pin_val {
      t: T_STRING
      v {
        str: "13hy"
      }
      tm: 1685686309447862581
    }
  }
}
infos {
  cmd_id: 15
  element: FB
  edit_type: ADD
  fb {
    mod_id: 1
    task_id: 2
    fb_id: 6
    flib_name: "Value"
    fc_name: "JSON_SERIAL_OBJ"
  }
  pos {
    x: 19
    y: 9
  }
}
infos {
  cmd_id: 16
  element: FB
  edit_type: MV
  fb {
    mod_id: 1
    task_id: 2
    fb_id: 6
  }
  pos {
    x: 20
    y: 41
  }
}
infos {
  cmd_id: 17
  element: PIN
  edit_type: SET
  pin {
    mod_id: 1
    task_id: 2
    fb_id: 6
    pin_index: 2
    pin_val {
      t: T_STRING
      v {
        str: "vstr1"
      }
      tm: 1685689578451026265
    }
  }
}
infos {
  cmd_id: 18
  element: PIN
  edit_type: SET
  pin {
    mod_id: 1
    task_id: 2
    fb_id: 6
    pin_index: 3
    pin_val {
      t: T_STRING
      v {
        str: "gty"
      }
      tm: 1685689582346929174
    }
  }
}
infos {
  cmd_id: 19
  element: PIN
  edit_type: SET
  pin {
    mod_id: 1
    task_id: 2
    fb_id: 6
    pin_index: 4
    pin_val {
      t: T_STRING
      v {
        str: "fda"
      }
      tm: 1685689586002668048
    }
  }
}
infos {
  cmd_id: 20
  element: PIN
  edit_type: SET
  pin {
    mod_id: 1
    task_id: 2
    fb_id: 6
    pin_index: 5
    pin_val {
      t: T_STRING
      v {
        str: "erqew"
      }
      tm: 1685689588715205828
    }
  }
}
infos {
  cmd_id: 21
  element: FB
  edit_type: ADD
  fb {
    mod_id: 1
    task_id: 2
    fb_id: 7
    flib_name: "Value"
    fc_name: "JSON_OBJ_MERGE"
  }
  pos {
    x: 70
    y: 36
  }
}
infos {
  cmd_id: 22
  element: LK
  edit_type: ADD
  lk {
    mod_id: 1
    task_id: 2
    lk_id: 8
    src_fb_id: 3
    src_pin_index: 1
    target_fb_id: 7
    target_pin_index: 2
  }
  pos {
    x: 40
    y: 16
  }
  pos {
    x: 55
    y: 16
  }
  pos {
    x: 55
    y: 45
  }
  pos {
    x: 70
    y: 45
  }
}
infos {
  cmd_id: 23
  element: LK
  edit_type: ADD
  lk {
    mod_id: 1
    task_id: 2
    lk_id: 9
    src_fb_id: 6
    src_pin_index: 1
    target_fb_id: 7
    target_pin_index: 3
  }
  pos {
    x: 41
    y: 48
  }
  pos {
    x: 55
    y: 48
  }
  pos {
    x: 55
    y: 47
  }
  pos {
    x: 70
    y: 47
  }
}
infos {
  cmd_id: 24
  element: EV
  edit_type: ADD
  ev {
    ev_id: 10
    ev_name: "Json_str_2"
    ev_type: 9
    ev_desc: "Desc"
    init_val {
      t: T_STRING
      v {
        str: ""
      }
      tm: 1685689624403734086
    }
  }
}
infos {
  cmd_id: 25
  element: VO
  edit_type: ADD
  vo {
    mod_id: 1
    task_id: 2
    fb_id: 7
    pin_index: 1
    ev_id: 10
    vo_id: 11
  }
}
infos {
  cmd_id: 26
  element: PIN
  edit_type: SET
  pin {
    mod_id: 1
    task_id: 2
    fb_id: 6
    pin_index: 8
    pin_val {
      t: T_STRING
      v {
        str: "gty"
      }
      tm: 1685698378060000934
    }
  }
}
infos {
  cmd_id: 27
  element: PIN
  edit_type: SET
  pin {
    mod_id: 1
    task_id: 2
    fb_id: 6
    pin_index: 9
    pin_val {
      t: T_STRING
      v {
        str: "123456"
      }
      tm: 1685698383767956436
    }
  }
}
infos {
  cmd_id: 28
  element: FB
  edit_type: ADD
  fb {
    mod_id: 1
    task_id: 2
    fb_id: 12
    flib_name: "Value"
    fc_name: "JSON_SERIAL_OBJ"
  }
  pos {
    x: 74
    y: 64
  }
}
infos {
  cmd_id: 29
  element: LK
  edit_type: ADD
  lk {
    mod_id: 1
    task_id: 2
    lk_id: 13
    src_fb_id: 6
    src_pin_index: 1
    target_fb_id: 12
    target_pin_index: 3
  }
  pos {
    x: 41
    y: 48
  }
  pos {
    x: 57
    y: 48
  }
  pos {
    x: 57
    y: 75
  }
  pos {
    x: 74
    y: 75
  }
}
infos {
  cmd_id: 30
  element: PIN
  edit_type: SET
  pin {
    mod_id: 1
    task_id: 2
    fb_id: 12
    pin_index: 2
    pin_val {
      t: T_STRING
      v {
        str: "gooe"
      }
      tm: 1685698478180950035
    }
  }
}
infos {
  cmd_id: 31
  element: PIN
  edit_type: SET
  pin {
    mod_id: 1
    task_id: 2
    fb_id: 12
    pin_index: 4
    pin_val {
      t: T_STRING
      v {
        str: "hei"
      }
      tm: 1685698483909159846
    }
  }
}
infos {
  cmd_id: 32
  element: PIN
  edit_type: SET
  pin {
    mod_id: 1
    task_id: 2
    fb_id: 12
    pin_index: 5
    pin_val {
      t: T_STRING
      v {
        str: "7899"
      }
      tm: 1685698489565111848
    }
  }
}
infos {
  cmd_id: 33
  element: FB
  edit_type: ADD
  fb {
    mod_id: 1
    task_id: 2
    fb_id: 14
    flib_name: "Value"
    fc_name: "JSON_SERIAL_OBJ"
  }
  pos {
    x: 32
    y: 97
  }
}
infos {
  cmd_id: 34
  element: PIN
  edit_type: SET
  pin {
    mod_id: 1
    task_id: 2
    fb_id: 14
    pin_index: 3
    pin_val {
      t: T_STRING
      v {
        str: "23"
      }
      tm: 1685700464522731774
    }
  }
}
infos {
  cmd_id: 35
  element: PIN
  edit_type: SET
  pin {
    mod_id: 1
    task_id: 2
    fb_id: 14
    pin_index: 5
    pin_val {
      t: T_STRING
      v {
        str: "34"
      }
      tm: 1685700467354255821
    }
  }
}
infos {
  cmd_id: 36
  element: PIN
  edit_type: SET
  pin {
    mod_id: 1
    task_id: 2
    fb_id: 14
    pin_index: 7
    pin_val {
      t: T_STRING
      v {
        str: "55"
      }
      tm: 1685700469882034008
    }
  }
}
infos {
  cmd_id: 37
  element: PIN
  edit_type: SET
  pin {
    mod_id: 1
    task_id: 2
    fb_id: 14
    pin_index: 9
    pin_val {
      t: T_STRING
      v {
        str: "fghh"
      }
      tm: 1685700473370245103
    }
  }
}
infos {
  cmd_id: 38
  element: PIN
  edit_type: SET
  pin {
    mod_id: 1
    task_id: 2
    fb_id: 14
    pin_index: 11
    pin_val {
      t: T_STRING
      v {
        str: "67u"
      }
      tm: 1685700479401740555
    }
  }
}
infos {
  cmd_id: 39
  element: LK
  edit_type: ADD
  lk {
    mod_id: 1
    task_id: 2
    lk_id: 15
    src_fb_id: 14
    src_pin_index: 1
    target_fb_id: 12
    target_pin_index: 8
  }
  pos {
    x: 53
    y: 104
  }
  pos {
    x: 63
    y: 104
  }
  pos {
    x: 63
    y: 85
  }
  pos {
    x: 74
    y: 85
  }
}
infos {
  cmd_id: 40
  element: PIN
  edit_type: SET
  pin {
    mod_id: 1
    task_id: 2
    fb_id: 12
    pin_index: 7
    pin_val {
      t: T_STRING
      v {
        str: "ceshi"
      }
      tm: 1685703973360777323
    }
  }
}
infos {
  cmd_id: 41
  element: PIN
  edit_type: SET
  pin {
    mod_id: 1
    task_id: 2
    fb_id: 12
    pin_index: 7
    pin_val {
      t: T_STRING
      tm: 1685704606959918864
    }
  }
}
infos {
  cmd_id: 46
  element: LK
  edit_type: RM
  lk {
    mod_id: 1
    task_id: 2
    lk_id: 15
  }
}
infos {
  cmd_id: 47
  element: LK
  edit_type: ADD
  lk {
    mod_id: 1
    task_id: 2
    lk_id: 16
    src_fb_id: 14
    src_pin_index: 1
    target_fb_id: 12
    target_pin_index: 9
  }
  pos {
    x: 53
    y: 104
  }
  pos {
    x: 63
    y: 104
  }
  pos {
    x: 63
    y: 87
  }
  pos {
    x: 74
    y: 87
  }
}
infos {
  cmd_id: 48
  element: PIN
  edit_type: SET
  pin {
    mod_id: 1
    task_id: 2
    fb_id: 12
    pin_index: 8
    pin_val {
      t: T_STRING
      v {
        str: "fdsa"
      }
      tm: 1685704638484489049
    }
  }
}
infos {
  cmd_id: 49
  element: PIN
  edit_type: SET
  pin {
    mod_id: 1
    task_id: 2
    fb_id: 14
    pin_index: 1
    pin_val {
      t: T_BOOL
      v {
        b: true
      }
      tm: 1685704849260556928
    }
  }
}
