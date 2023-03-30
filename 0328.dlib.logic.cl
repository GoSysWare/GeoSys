infos {
  edit_type: SET
  proj {
    proj_name: "rotbot-engine-project"
    proj_uuid: "{821ae363-2741-4720-97b8-11e8f4c6bf4a}"
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
    flib_name: "AI"
    fc_name: "DLIB_FACE_DETECT"
  }
  pos {
    x: 88
    y: 52
  }
}
infos {
  cmd_id: 4
  element: FB
  edit_type: ADD
  fb {
    mod_id: 1
    task_id: 2
    fb_id: 4
    flib_name: "Devices"
    fc_name: "CAMERA"
  }
  pos {
    x: 33
    y: 45
  }
}
infos {
  cmd_id: 5
  element: FB
  edit_type: MV
  fb {
    mod_id: 1
    task_id: 2
    fb_id: 3
  }
  pos {
    x: 131
    y: 68
  }
}
infos {
  cmd_id: 6
  element: FB
  edit_type: MV
  fb {
    mod_id: 1
    task_id: 2
    fb_id: 4
  }
  pos {
    x: 76
    y: 61
  }
}
infos {
  cmd_id: 7
  element: LK
  edit_type: ADD
  lk {
    mod_id: 1
    task_id: 2
    lk_id: 5
    src_fb_id: 4
    src_pin_index: 1
    target_fb_id: 3
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
  cmd_id: 8
  element: FB
  edit_type: ADD
  fb {
    mod_id: 1
    task_id: 2
    fb_id: 6
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
  element: LK
  edit_type: ADD
  lk {
    mod_id: 1
    task_id: 2
    lk_id: 7
    src_fb_id: 6
    src_pin_index: 1
    target_fb_id: 3
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
  cmd_id: 10
  element: FB
  edit_type: ADD
  fb {
    mod_id: 1
    task_id: 2
    fb_id: 8
    flib_name: "System"
    fc_name: "FILE_OPEN_ONCE"
  }
  pos {
    x: 75
    y: 112
  }
}
infos {
  cmd_id: 11
  element: LK
  edit_type: ADD
  lk {
    mod_id: 1
    task_id: 2
    lk_id: 9
    src_fb_id: 8
    src_pin_index: 1
    target_fb_id: 3
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
  cmd_id: 12
  element: LK
  edit_type: ADD
  lk {
    mod_id: 1
    task_id: 2
    lk_id: 10
    src_fb_id: 4
    src_pin_index: 3
    target_fb_id: 3
    target_pin_index: 2
  }
  pos {
    x: 92
    y: 72
  }
  pos {
    x: 111
    y: 72
  }
  pos {
    x: 111
    y: 77
  }
  pos {
    x: 131
    y: 77
  }
}
infos {
  cmd_id: 13
  element: LK
  edit_type: ADD
  lk {
    mod_id: 1
    task_id: 2
    lk_id: 11
    src_fb_id: 4
    src_pin_index: 2
    target_fb_id: 3
    target_pin_index: 3
  }
  pos {
    x: 92
    y: 70
  }
  pos {
    x: 111
    y: 70
  }
  pos {
    x: 111
    y: 79
  }
  pos {
    x: 131
    y: 79
  }
}
infos {
  cmd_id: 14
  element: LK
  edit_type: MV
  lk {
    mod_id: 1
    task_id: 2
    lk_id: 11
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
  cmd_id: 15
  element: LK
  edit_type: MV
  lk {
    mod_id: 1
    task_id: 2
    lk_id: 10
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
  element: PIN
  edit_type: SET
  pin {
    mod_id: 1
    task_id: 2
    fb_id: 4
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
  cmd_id: 17
  element: PIN
  edit_type: SET
  pin {
    mod_id: 1
    task_id: 2
    fb_id: 6
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
  cmd_id: 18
  element: PIN
  edit_type: SET
  pin {
    mod_id: 1
    task_id: 2
    fb_id: 6
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
  cmd_id: 19
  element: PIN
  edit_type: SET
  pin {
    mod_id: 1
    task_id: 2
    fb_id: 6
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
  cmd_id: 20
  element: PIN
  edit_type: SET
  pin {
    mod_id: 1
    task_id: 2
    fb_id: 8
    pin_index: 1
    pin_val {
      v {
        t: T_STRING
        str: "/home/shuimujie/Works/bamboo_ws/"
      }
      tm: 1680144551170625664
    }
  }
}
infos {
  cmd_id: 21
  element: PIN
  edit_type: SET
  pin {
    mod_id: 1
    task_id: 2
    fb_id: 8
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
  cmd_id: 22
  element: PIN
  edit_type: SET
  pin {
    mod_id: 1
    task_id: 2
    fb_id: 8
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
infos {
  cmd_id: 23
  element: EV
  edit_type: ADD
  ev {
    ev_id: 12
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
  cmd_id: 24
  element: EV
  edit_type: ADD
  ev {
    ev_id: 13
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
  cmd_id: 25
  element: VI
  edit_type: ADD
  vi {
    mod_id: 1
    task_id: 2
    fb_id: 6
    pin_index: 1
    ev_id: 12
    vi_id: 14
  }
}
infos {
  cmd_id: 26
  element: VI
  edit_type: ADD
  vi {
    mod_id: 1
    task_id: 2
    fb_id: 8
    pin_index: 1
    ev_id: 13
    vi_id: 15
  }
}
infos {
  cmd_id: 27
  element: FB
  edit_type: ADD
  fb {
    mod_id: 1
    task_id: 2
    fb_id: 16
    flib_name: "System"
    fc_name: "SYSSTATE"
  }
  pos {
    x: 23
    y: 32
  }
}
infos {
  cmd_id: 28
  element: FB
  edit_type: MV
  fb {
    mod_id: 1
    task_id: 2
    fb_id: 16
  }
  pos {
    x: 21
    y: 43
  }
}
infos {
  cmd_id: 29
  element: LK
  edit_type: ADD
  lk {
    mod_id: 1
    task_id: 2
    lk_id: 17
    src_fb_id: 4
    src_pin_index: 4
    target_fb_id: 3
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
