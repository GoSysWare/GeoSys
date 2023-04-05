infos {
  edit_type: SET
  proj {
    proj_name: "rotbot-engine-project"
    proj_uuid: "{0c161cf6-4513-45b8-8cba-5511391e638f}"
  }
}
infos {
  cmd_id: 1
  element: EV
  edit_type: ADD
  ev {
    ev_id: 1
    ev_name: "F1"
    ev_type: 9
    ev_desc: "Desc"
    init_val {
      v {
        t: T_STRING
        str: "/home/shuimujie/Works/bamboo_ws/bin/debug/shape_predictor_5_face_landmarks.dat"
      }
      tm: 1680144945831915783
    }
  }
}
infos {
  cmd_id: 2
  element: EV
  edit_type: ADD
  ev {
    ev_id: 2
    ev_name: "F2"
    ev_type: 9
    ev_desc: "Desc"
    init_val {
      v {
        t: T_STRING
        str: "/home/shuimujie/Works/bamboo_ws/bin/debug/dlib_face_recognition_resnet_model_v1.dat"
      }
      tm: 1680144958426889105
    }
  }
}
infos {
  cmd_id: 3
  element: EV
  edit_type: ADD
  ev {
    ev_id: 3
    ev_name: "cam1"
    ev_type: 2
    ev_desc: "Desc"
    init_val {
      v {
        t: T_IMAGE
        img: "0"
      }
      tm: 1680260381368684012
    }
  }
}
infos {
  cmd_id: 4
  element: MOD
  edit_type: ADD
  mod {
    mod_id: 4
    mod_name: "M1"
  }
}
infos {
  cmd_id: 5
  element: TASK
  edit_type: ADD
  task {
    mod_id: 4
    task_id: 5
    task_name: "P1"
    interval: 1000
  }
}
infos {
  cmd_id: 6
  element: FB
  edit_type: ADD
  fb {
    mod_id: 4
    task_id: 5
    fb_id: 6
    flib_name: "AI"
    fc_name: "DLIB_FACE_DETECT"
  }
  pos {
    x: 131
    y: 68
  }
}
infos {
  cmd_id: 7
  element: FB
  edit_type: ADD
  fb {
    mod_id: 4
    task_id: 5
    fb_id: 7
    flib_name: "Devices"
    fc_name: "CAMERA"
  }
  pos {
    x: 76
    y: 61
  }
}
infos {
  cmd_id: 8
  element: FB
  edit_type: ADD
  fb {
    mod_id: 4
    task_id: 5
    fb_id: 8
    flib_name: "System"
    fc_name: "FILE_OPEN_ONCE"
  }
  pos {
    x: 65
    y: 86
  }
}
infos {
  cmd_id: 9
  element: FB
  edit_type: ADD
  fb {
    mod_id: 4
    task_id: 5
    fb_id: 9
    flib_name: "System"
    fc_name: "FILE_OPEN_ONCE"
  }
  pos {
    x: 75
    y: 112
  }
}
infos {
  cmd_id: 10
  element: FB
  edit_type: ADD
  fb {
    mod_id: 4
    task_id: 5
    fb_id: 10
    flib_name: "System"
    fc_name: "SYSSTATE"
  }
  pos {
    x: 29
    y: 41
  }
}
infos {
  cmd_id: 11
  element: FB
  edit_type: ADD
  fb {
    mod_id: 4
    task_id: 5
    fb_id: 11
    flib_name: "Fsm"
    fc_name: "FSM"
  }
  pos {
    x: 83
    y: 38
  }
}
infos {
  cmd_id: 12
  element: LK
  edit_type: ADD
  lk {
    mod_id: 4
    task_id: 5
    lk_id: 12
    src_fb_id: 7
    src_pin_index: 1
    target_fb_id: 6
    target_pin_index: 1
  }
  pos {
    x: 92
    y: 68
  }
  pos {
    x: 111
    y: 68
  }
  pos {
    x: 111
    y: 75
  }
  pos {
    x: 131
    y: 75
  }
}
infos {
  cmd_id: 13
  element: LK
  edit_type: ADD
  lk {
    mod_id: 4
    task_id: 5
    lk_id: 13
    src_fb_id: 8
    src_pin_index: 1
    target_fb_id: 6
    target_pin_index: 4
  }
  pos {
    x: 84
    y: 93
  }
  pos {
    x: 107
    y: 93
  }
  pos {
    x: 107
    y: 81
  }
  pos {
    x: 131
    y: 81
  }
}
infos {
  cmd_id: 14
  element: LK
  edit_type: ADD
  lk {
    mod_id: 4
    task_id: 5
    lk_id: 14
    src_fb_id: 9
    src_pin_index: 1
    target_fb_id: 6
    target_pin_index: 5
  }
  pos {
    x: 94
    y: 119
  }
  pos {
    x: 112
    y: 119
  }
  pos {
    x: 112
    y: 83
  }
  pos {
    x: 131
    y: 83
  }
}
infos {
  cmd_id: 15
  element: LK
  edit_type: ADD
  lk {
    mod_id: 4
    task_id: 5
    lk_id: 15
    src_fb_id: 7
    src_pin_index: 3
    target_fb_id: 6
    target_pin_index: 2
  }
  pos {
    x: 92
    y: 72
  }
  pos {
    x: 108
    y: 72
  }
  pos {
    x: 108
    y: 77
  }
  pos {
    x: 131
    y: 77
  }
}
infos {
  cmd_id: 16
  element: LK
  edit_type: ADD
  lk {
    mod_id: 4
    task_id: 5
    lk_id: 16
    src_fb_id: 7
    src_pin_index: 2
    target_fb_id: 6
    target_pin_index: 3
  }
  pos {
    x: 92
    y: 70
  }
  pos {
    x: 105
    y: 70
  }
  pos {
    x: 105
    y: 79
  }
  pos {
    x: 131
    y: 79
  }
}
infos {
  cmd_id: 17
  element: LK
  edit_type: ADD
  lk {
    mod_id: 4
    task_id: 5
    lk_id: 17
    src_fb_id: 7
    src_pin_index: 4
    target_fb_id: 6
  }
  pos {
    x: 92
    y: 74
  }
  pos {
    x: 111
    y: 74
  }
  pos {
    x: 111
    y: 73
  }
  pos {
    x: 131
    y: 73
  }
}
infos {
  cmd_id: 18
  element: VI
  edit_type: ADD
  vi {
    mod_id: 4
    task_id: 5
    fb_id: 8
    pin_index: 1
    ev_id: 1
    vi_id: 18
  }
}
infos {
  cmd_id: 19
  element: VI
  edit_type: ADD
  vi {
    mod_id: 4
    task_id: 5
    fb_id: 9
    pin_index: 1
    ev_id: 2
    vi_id: 19
  }
}
infos {
  cmd_id: 20
  element: VO
  edit_type: ADD
  vo {
    mod_id: 4
    task_id: 5
    fb_id: 7
    pin_index: 1
    ev_id: 3
    vo_id: 20
  }
}
infos {
  cmd_id: 21
  element: PIN
  edit_type: SET
  pin {
    mod_id: 4
    task_id: 5
    fb_id: 7
    pin_index: 1
    pin_val {
      v {
        t: T_STRING
        str: "front camera"
      }
      tm: 1680144479409590892
    }
  }
}
infos {
  cmd_id: 22
  element: PIN
  edit_type: SET
  pin {
    mod_id: 4
    task_id: 5
    fb_id: 8
    pin_index: 1
    pin_val {
      v {
        t: T_STRING
        str: "/home/shuimujie/Works/bamboo_ws/"
      }
      tm: 1680144527136476830
    }
  }
}
infos {
  cmd_id: 23
  element: PIN
  edit_type: SET
  pin {
    mod_id: 4
    task_id: 5
    fb_id: 8
    pin_index: 2
    pin_val {
      v {
        t: T_UINT32
        ui: 0
      }
      tm: 1680144533199563467
    }
  }
}
infos {
  cmd_id: 24
  element: PIN
  edit_type: SET
  pin {
    mod_id: 4
    task_id: 5
    fb_id: 8
    pin_index: 3
    pin_val {
      v {
        t: T_BOOL
        b: true
      }
      tm: 1680144537728207634
    }
  }
}
infos {
  cmd_id: 25
  element: PIN
  edit_type: SET
  pin {
    mod_id: 4
    task_id: 5
    fb_id: 9
    pin_index: 1
    pin_val {
      v {
        t: T_STRING
        str: "/home/shuimujie/Works/bamboo_ws/"
      }
      tm: 1680144551170625664
    }
  }0
}
infos {
  cmd_id: 26
  element: PIN
  edit_type: SET
  pin {
    mod_id: 4
    task_id: 5
    fb_id: 9
    pin_index: 2
    pin_val {
      v {
        t: T_UINT32
        ui: 0
      }
      tm: 1680144555291036607
    }
  }
}
infos {
  cmd_id: 27
  element: PIN
  edit_type: SET
  pin {
    mod_id: 4
    task_id: 5
    fb_id: 9
    pin_index: 3
    pin_val {
      v {
        t: T_BOOL
        b: true
      }
      tm: 1680144558724588179
    }
  }
}
