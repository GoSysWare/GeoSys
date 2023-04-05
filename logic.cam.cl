infos {
  edit_type: SET
  proj {
    proj_name: "rotbot-engine-project"
    proj_uuid: "{e8938fcf-1ae5-461d-be40-5d3080c80f7d}"
  }
}
infos {
  cmd_id: 1
  element: EV
  edit_type: ADD
  ev {
    ev_id: 1
    ev_name: "IMG1"
    ev_type: 2
    ev_desc: "Desc"
    init_val {
      v {
        t: T_IMAGE
        img: "0"
      }
      tm: 1680607692935997440
    }
  }
}
infos {
  cmd_id: 2
  element: EV
  edit_type: ADD
  ev {
    ev_id: 2
    ev_name: "AF1"
    ev_type: 9
    ev_desc: "Desc"
    init_val {
      v {
        t: T_STRING
        str: "/home/shuimujie/Works/bamboo_ws/bin/debug/shape_predictor_5_face_landmarks.dat"
      }
      tm: 1680607907957121309
    }
  }
}
infos {
  cmd_id: 3
  element: EV
  edit_type: ADD
  ev {
    ev_id: 3
    ev_name: "AF2"
    ev_type: 9
    ev_desc: "Desc"
    init_val {
      v {
        t: T_STRING
        str: "/home/shuimujie/Works/bamboo_ws/bin/debug/dlib_face_recognition_resnet_model_v1.dat"
      }
      tm: 1680607946989513710
    }
  }
}
infos {
  cmd_id: 4
  element: EV
  edit_type: ADD
  ev {
    ev_id: 4
    ev_name: "SPEED"
    ev_type: 2
    ev_desc: "Desc"
    init_val {
      v {
        t: T_INT32
        i: 0
      }
      tm: 1680611411410198622
    }
  }
}
infos {
  cmd_id: 5
  element: MOD
  edit_type: ADD
  mod {
    mod_id: 5
    mod_name: "F1"
  }
}
infos {
  cmd_id: 6
  element: TASK
  edit_type: ADD
  task {
    mod_id: 5
    task_id: 6
    task_name: "comp1"
    interval: 1000
  }
}
infos {
  cmd_id: 7
  element: FB
  edit_type: ADD
  fb {
    mod_id: 5
    task_id: 6
    fb_id: 7
    flib_name: "Devices"
    fc_name: "CAMERA"
  }
  pos {
    x: 31
    y: 34
  }
}
infos {
  cmd_id: 8
  element: FB
  edit_type: ADD
  fb {
    mod_id: 5
    task_id: 6
    fb_id: 8
    flib_name: "System"
    fc_name: "FILE_OPEN_ONCE"
  }
  pos {
    x: 111
    y: 83
  }
}
infos {
  cmd_id: 9
  element: FB
  edit_type: ADD
  fb {
    mod_id: 5
    task_id: 6
    fb_id: 9
    flib_name: "System"
    fc_name: "FILE_OPEN_ONCE"
  }
  pos {
    x: 115
    y: 107
  }
}
infos {
  cmd_id: 10
  element: FB
  edit_type: ADD
  fb {
    mod_id: 5
    task_id: 6
    fb_id: 10
    flib_name: "AI"
    fc_name: "DLIB_FACE_DETECT"
  }
  pos {
    x: 109
    y: 30
  }
}
infos {
  cmd_id: 11
  element: FB
  edit_type: ADD
  fb {
    mod_id: 5
    task_id: 6
    fb_id: 11
    flib_name: "Arithmetic"
    fc_name: "ADD_INT"
  }
  pos {
    x: 43
    y: 11
  }
}
infos {
  cmd_id: 12
  element: FB
  edit_type: ADD
  fb {
    mod_id: 5
    task_id: 6
    fb_id: 12
    flib_name: "Arithmetic"
    fc_name: "ADD_FLOAT"
  }
  pos {
    x: 115
    y: 10
  }
}
infos {
  cmd_id: 13
  element: FB
  edit_type: ADD
  fb {
    mod_id: 5
    task_id: 6
    fb_id: 13
    flib_name: "Converter"
    fc_name: "I2F"
  }
  pos {
    x: 86
    y: 17
  }
}
infos {
  cmd_id: 14
  element: FB
  edit_type: ADD
  fb {
    mod_id: 5
    task_id: 6
    fb_id: 14
    flib_name: "System"
    fc_name: "SYSSTATE"
  }
  pos {
    x: 16
    y: 61
  }
}
infos {
  cmd_id: 15
  element: FB
  edit_type: ADD
  fb {
    mod_id: 5
    task_id: 6
    fb_id: 15
    flib_name: "Devices"
    fc_name: "SIM_READ"
  }
  pos {
    x: 57
    y: 54
  }
}
infos {
  cmd_id: 16
  element: FB
  edit_type: ADD
  fb {
    mod_id: 5
    task_id: 6
    fb_id: 16
    flib_name: "Converter"
    fc_name: "D2I"
  }
  pos {
    x: 94
    y: 57
  }
}
infos {
  cmd_id: 17
  element: LK
  edit_type: ADD
  lk {
    mod_id: 5
    task_id: 6
    lk_id: 17
    src_fb_id: 7
    src_pin_index: 1
    target_fb_id: 10
    target_pin_index: 1
  }
  pos {
    x: 47
    y: 41
  }
  pos {
    x: 101
    y: 41
  }
  pos {
    x: 101
    y: 37
  }
  pos {
    x: 109
    y: 37
  }
}
infos {
  cmd_id: 18
  element: LK
  edit_type: ADD
  lk {
    mod_id: 5
    task_id: 6
    lk_id: 18
    src_fb_id: 7
    src_pin_index: 2
    target_fb_id: 10
    target_pin_index: 3
  }
  pos {
    x: 47
    y: 43
  }
  pos {
    x: 101
    y: 43
  }
  pos {
    x: 101
    y: 41
  }
  pos {
    x: 109
    y: 41
  }
}
infos {
  cmd_id: 19
  element: LK
  edit_type: ADD
  lk {
    mod_id: 5
    task_id: 6
    lk_id: 19
    src_fb_id: 7
    src_pin_index: 3
    target_fb_id: 10
    target_pin_index: 2
  }
  pos {
    x: 47
    y: 45
  }
  pos {
    x: 101
    y: 45
  }
  pos {
    x: 101
    y: 39
  }
  pos {
    x: 109
    y: 39
  }
}
infos {
  cmd_id: 20
  element: LK
  edit_type: ADD
  lk {
    mod_id: 5
    task_id: 6
    lk_id: 20
    src_fb_id: 8
    src_pin_index: 1
    target_fb_id: 10
    target_pin_index: 4
  }
  pos {
    x: 130
    y: 90
  }
  pos {
    x: 142
    y: 90
  }
  pos {
    x: 142
    y: 43
  }
  pos {
    x: 109
    y: 43
  }
}
infos {
  cmd_id: 21
  element: LK
  edit_type: ADD
  lk {
    mod_id: 5
    task_id: 6
    lk_id: 21
    src_fb_id: 9
    src_pin_index: 1
    target_fb_id: 10
    target_pin_index: 5
  }
  pos {
    x: 134
    y: 114
  }
  pos {
    x: 144
    y: 114
  }
  pos {
    x: 144
    y: 45
  }
  pos {
    x: 109
    y: 45
  }
}
infos {
  cmd_id: 22
  element: LK
  edit_type: ADD
  lk {
    mod_id: 5
    task_id: 6
    lk_id: 22
    src_fb_id: 11
    src_pin_index: 1
    target_fb_id: 13
    target_pin_index: 1
  }
  pos {
    x: 58
    y: 18
  }
  pos {
    x: 72
    y: 18
  }
  pos {
    x: 72
    y: 24
  }
  pos {
    x: 86
    y: 24
  }
}
infos {
  cmd_id: 23
  element: LK
  edit_type: ADD
  lk {
    mod_id: 5
    task_id: 6
    lk_id: 23
    src_fb_id: 13
    src_pin_index: 1
    target_fb_id: 12
    target_pin_index: 1
  }
  pos {
    x: 100
    y: 24
  }
  pos {
    x: 107
    y: 24
  }
  pos {
    x: 107
    y: 17
  }
  pos {
    x: 115
    y: 17
  }
}
infos {
  cmd_id: 24
  element: LK
  edit_type: ADD
  lk {
    mod_id: 5
    task_id: 6
    lk_id: 24
    src_fb_id: 15
    src_pin_index: 6
    target_fb_id: 16
    target_pin_index: 1
  }
  pos {
    x: 73
    y: 71
  }
  pos {
    x: 83
    y: 71
  }
  pos {
    x: 83
    y: 64
  }
  pos {
    x: 94
    y: 64
  }
}
infos {
  cmd_id: 25
  element: VI
  edit_type: ADD
  vi {
    mod_id: 5
    task_id: 6
    fb_id: 8
    pin_index: 1
    ev_id: 2
    vi_id: 25
  }
}
infos {
  cmd_id: 26
  element: VI
  edit_type: ADD
  vi {
    mod_id: 5
    task_id: 6
    fb_id: 9
    pin_index: 1
    ev_id: 3
    vi_id: 26
  }
}
infos {
  cmd_id: 27
  element: VO
  edit_type: ADD
  vo {
    mod_id: 5
    task_id: 6
    fb_id: 7
    pin_index: 1
    ev_id: 1
    vo_id: 27
  }
}
infos {
  cmd_id: 28
  element: VO
  edit_type: ADD
  vo {
    mod_id: 5
    task_id: 6
    fb_id: 16
    pin_index: 1
    ev_id: 4
    vo_id: 28
  }
}
infos {
  cmd_id: 29
  element: PIN
  edit_type: SET
  pin {
    mod_id: 5
    task_id: 6
    fb_id: 7
    pin_index: 1
    pin_val {
      v {
        t: T_STRING
        str: "front camera"
      }
      tm: 1680607568159046766
    }
  }
}
infos {
  cmd_id: 30
  element: PIN
  edit_type: SET
  pin {
    mod_id: 5
    task_id: 6
    fb_id: 8
    pin_index: 3
    pin_val {
      v {
        t: T_BOOL
        b: true
      }
      tm: 1680607806459595639
    }
  }
}
infos {
  cmd_id: 31
  element: PIN
  edit_type: SET
  pin {
    mod_id: 5
    task_id: 6
    fb_id: 8
    pin_index: 2
    pin_val {
      v {
        t: T_UINT32
        ui: 0
      }
      tm: 1680607812418177647
    }
  }
}
infos {
  cmd_id: 32
  element: PIN
  edit_type: SET
  pin {
    mod_id: 5
    task_id: 6
    fb_id: 8
    pin_index: 1
    pin_val {
      v {
        t: T_STRING
        str: "/home/shuimujie/Works/bamboo_ws/"
      }
      tm: 1680607844400248765
    }
  }
}
infos {
  cmd_id: 33
  element: PIN
  edit_type: SET
  pin {
    mod_id: 5
    task_id: 6
    fb_id: 9
    pin_index: 1
    pin_val {
      v {
        t: T_STRING
        str: "/home/shuimujie/Works/bamboo_ws/"
      }
      tm: 1680607867263995649
    }
  }
}
infos {
  cmd_id: 34
  element: PIN
  edit_type: SET
  pin {
    mod_id: 5
    task_id: 6
    fb_id: 9
    pin_index: 2
    pin_val {
      v {
        t: T_UINT32
        ui: 0
      }
      tm: 1680607873379884093
    }
  }
}
infos {
  cmd_id: 35
  element: PIN
  edit_type: SET
  pin {
    mod_id: 5
    task_id: 6
    fb_id: 9
    pin_index: 3
    pin_val {
      v {
        t: T_BOOL
        b: true
      }
      tm: 1680607877567132906
    }
  }
}
infos {
  cmd_id: 36
  element: PIN
  edit_type: SET
  pin {
    mod_id: 5
    task_id: 6
    fb_id: 11
    pin_index: 1
    pin_val {
      v {
        t: T_INT32
        i: 3
      }
      tm: 1680608537292404889
    }
  }
}
infos {
  cmd_id: 37
  element: PIN
  edit_type: SET
  pin {
    mod_id: 5
    task_id: 6
    fb_id: 11
    pin_index: 2
    pin_val {
      v {
        t: T_INT32
        i: 2
      }
      tm: 1680608541450275167
    }
  }
}
infos {
  cmd_id: 38
  element: PIN
  edit_type: SET
  pin {
    mod_id: 5
    task_id: 6
    fb_id: 12
    pin_index: 2
    pin_val {
      v {
        t: T_FLOAT32
        f: 3.9
      }
      tm: 1680608548967231066
    }
  }
}
infos {
  cmd_id: 39
  element: PIN
  edit_type: SET
  pin {
    mod_id: 5
    task_id: 6
    fb_id: 15
    pin_index: 7
    pin_val {
      v {
        t: T_STRING
        str: "$SECOND"
      }
      tm: 1680611508738597246
    }
  }
}
infos {
  cmd_id: 40
  element: PIN
  edit_type: SET
  pin {
    mod_id: 5
    task_id: 6
    fb_id: 15
    pin_index: 1
    pin_val {
      v {
        t: T_STRING
        str: "SIM"
      }
      tm: 1680611658421511869
    }
  }
}
infos {
  cmd_id: 41
  element: PIN
  edit_type: SET
  pin {
    mod_id: 5
    task_id: 6
    fb_id: 15
    pin_index: 8
    pin_val {
      v {
        t: T_STRING
        str: "3+2"
      }
      tm: 1680611692082075459
    }
  }
}
