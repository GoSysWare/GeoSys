infos {
  cmd_id: 46
  edit_type: SET
  proj {
    proj_name: "rotbot-engine-project"
    proj_uuid: "{1794c964-ba15-4ec4-b367-af32c77bc475}"
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
    interval: 50
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
    flib_name: "Devices"
    fc_name: "CAMERA"
  }
  pos {
    x: 16
    y: 13
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
    pin_index: 1
    pin_val {
      v {
        t: T_STRING
        str: "front camera"
      }
      tm: 1682649831746164852
    }
  }
}
infos {
  cmd_id: 5
  element: FB
  edit_type: ADD
  fb {
    mod_id: 1
    task_id: 2
    fb_id: 4
    flib_name: "Task"
    fc_name: "EVENT"
  }
  pos {
    x: 58
    y: 22
  }
}
infos {
  cmd_id: 6
  element: LK
  edit_type: ADD
  lk {
    mod_id: 1
    task_id: 2
    lk_id: 5
    src_fb_id: 3
    src_pin_index: 4
    target_fb_id: 4
    target_pin_index: 1
  }
  pos {
    x: 36
    y: 26
  }
  pos {
    x: 47
    y: 26
  }
  pos {
    x: 47
    y: 29
  }
  pos {
    x: 58
    y: 29
  }
}
infos {
  cmd_id: 7
  element: FB
  edit_type: MV
  fb {
    mod_id: 1
    task_id: 2
    fb_id: 4
  }
  pos {
    x: 57
    y: 18
  }
}
infos {
  cmd_id: 8
  element: LK
  edit_type: MV
  lk {
    mod_id: 1
    task_id: 2
    lk_id: 5
  }
  pos {
    x: 36
    y: 26
  }
  pos {
    x: 47
    y: 26
  }
  pos {
    x: 47
    y: 25
  }
  pos {
    x: 57
    y: 25
  }
}
infos {
  cmd_id: 9
  element: FB
  edit_type: ADD
  fb {
    mod_id: 1
    task_id: 2
    fb_id: 6
    flib_name: "Task"
    fc_name: "TASK"
  }
  pos {
    x: 91
    y: 25
  }
}
infos {
  cmd_id: 11
  element: LK
  edit_type: ADD
  lk {
    mod_id: 1
    task_id: 2
    lk_id: 7
    src_fb_id: 4
    src_pin_index: 1
    target_fb_id: 6
    target_pin_index: 1
  }
  pos {
    x: 79
    y: 25
  }
  pos {
    x: 84
    y: 25
  }
  pos {
    x: 84
    y: 23
  }
  pos {
    x: 89
    y: 23
  }
}
infos {
  cmd_id: 12
  element: FB
  edit_type: MV
  fb {
    mod_id: 1
    task_id: 2
    fb_id: 6
  }
  pos {
    x: 90
    y: 21
  }
}
infos {
  cmd_id: 13
  element: LK
  edit_type: MV
  lk {
    mod_id: 1
    task_id: 2
    lk_id: 7
  }
  pos {
    x: 79
    y: 25
  }
  pos {
    x: 84
    y: 25
  }
  pos {
    x: 84
    y: 28
  }
  pos {
    x: 90
    y: 28
  }
}
infos {
  cmd_id: 14
  element: PIN
  edit_type: SET
  pin {
    mod_id: 1
    task_id: 2
    fb_id: 6
    pin_index: 2
    pin_val {
      v {
        t: T_STRING
        str: "M1"
      }
      tm: 1682651779900946824
    }
  }
}
infos {
  cmd_id: 15
  element: PIN
  edit_type: SET
  pin {
    mod_id: 1
    task_id: 2
    fb_id: 6
    pin_index: 3
    pin_val {
      v {
        t: T_STRING
        str: "P2"
      }
      tm: 1682651784012623038
    }
  }
}
infos {
  cmd_id: 16
  element: PIN
  edit_type: SET
  pin {
    mod_id: 1
    task_id: 2
    fb_id: 6
    pin_index: 4
    pin_val {
      v {
        t: T_TIME
        tm: 5000
      }
      tm: 1682651789988961666
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
    pin_index: 5
    pin_val {
      v {
        t: T_BOOL
        b: true
      }
      tm: 1682651792173053046
    }
  }
}
infos {
  cmd_id: 18
  element: TASK
  edit_type: ADD
  task {
    task_type: ASYNC
    mod_id: 1
    task_id: 8
    task_name: "P2"
    interval: 1000
  }
}
infos {
  cmd_id: 19
  element: FB
  edit_type: ADD
  fb {
    mod_id: 1
    task_id: 8
    fb_id: 9
    flib_name: "System"
    fc_name: "FILE_OPEN_ONCE"
  }
  pos {
    x: 14
    y: 14
  }
}
infos {
  cmd_id: 20
  element: FB
  edit_type: ADD
  fb {
    mod_id: 1
    task_id: 8
    fb_id: 10
    flib_name: "System"
    fc_name: "FILE_OPEN_ONCE"
  }
  pos {
    x: 25
    y: 37
  }
}
infos {
  cmd_id: 21
  element: PIN
  edit_type: SET
  pin {
    mod_id: 1
    task_id: 8
    fb_id: 10
    pin_index: 2
    pin_val {
      v {
        t: T_UINT32
        ui: 0
      }
      tm: 1682651847257718607
    }
  }
}
infos {
  cmd_id: 22
  element: PIN
  edit_type: SET
  pin {
    mod_id: 1
    task_id: 8
    fb_id: 10
    pin_index: 3
    pin_val {
      v {
        t: T_BOOL
        b: true
      }
      tm: 1682651849573865492
    }
  }
}
infos {
  cmd_id: 23
  element: PIN
  edit_type: SET
  pin {
    mod_id: 1
    task_id: 8
    fb_id: 9
    pin_index: 2
    pin_val {
      v {
        t: T_UINT32
        ui: 0
      }
      tm: 1682651852353760430
    }
  }
}
infos {
  cmd_id: 24
  element: PIN
  edit_type: SET
  pin {
    mod_id: 1
    task_id: 8
    fb_id: 9
    pin_index: 3
    pin_val {
      v {
        t: T_BOOL
        b: true
      }
      tm: 1682651854577846249
    }
  }
}
infos {
  cmd_id: 25
  element: PIN
  edit_type: SET
  pin {
    mod_id: 1
    task_id: 8
    fb_id: 9
    pin_index: 1
    pin_val {
      v {
        t: T_STRING
        str: "/home/shuimujie/Works/GeoSys/dlib_face_recognition_resnet_model_v1.dat"
      }
      tm: 1682651863249993580
    }
  }
}
infos {
  cmd_id: 29
  element: PIN
  edit_type: SET
  pin {
    mod_id: 1
    task_id: 8
    fb_id: 10
    pin_index: 1
    pin_val {
      v {
        t: T_STRING
        str: "/home/shuimujie/Works/GeoSys/shape_predictor_5_face_landmarks.dat"
      }
      tm: 1682651899266665455
    }
  }
}
infos {
  cmd_id: 32
  element: FB
  edit_type: ADD
  fb {
    mod_id: 1
    task_id: 8
    fb_id: 11
    flib_name: "AI"
    fc_name: "DLIB_FACE_DETECT"
  }
  pos {
    x: 91
    y: 25
  }
}
infos {
  cmd_id: 37
  element: FB
  edit_type: MV
  fb {
    mod_id: 1
    task_id: 8
    fb_id: 9
  }
  pos {
    x: 49
    y: 35
  }
}
infos {
  cmd_id: 38
  element: FB
  edit_type: MV
  fb {
    mod_id: 1
    task_id: 8
    fb_id: 10
  }
  pos {
    x: 48
    y: 16
  }
}
infos {
  cmd_id: 39
  element: LK
  edit_type: ADD
  lk {
    mod_id: 1
    task_id: 8
    lk_id: 12
    src_fb_id: 10
    src_pin_index: 1
    target_fb_id: 11
    target_pin_index: 4
  }
  pos {
    x: 70
    y: 23
  }
  pos {
    x: 80
    y: 23
  }
  pos {
    x: 80
    y: 38
  }
  pos {
    x: 91
    y: 38
  }
}
infos {
  cmd_id: 40
  element: LK
  edit_type: ADD
  lk {
    mod_id: 1
    task_id: 8
    lk_id: 13
    src_fb_id: 9
    src_pin_index: 1
    target_fb_id: 11
    target_pin_index: 5
  }
  pos {
    x: 71
    y: 42
  }
  pos {
    x: 81
    y: 42
  }
  pos {
    x: 81
    y: 40
  }
  pos {
    x: 91
    y: 40
  }
}
infos {
  cmd_id: 41
  element: EV
  edit_type: ADD
  ev {
    ev_id: 14
    ev_name: "Imag_1"
    ev_type: 11
    ev_desc: "Desc"
    init_val {
      v {
        t: T_IMAGE
        img {
          data: "0"
        }
      }
      tm: 1682651954239672107
    }
  }
}
infos {
  cmd_id: 42
  element: VO
  edit_type: ADD
  vo {
    mod_id: 1
    task_id: 2
    fb_id: 3
    pin_index: 1
    ev_id: 14
    vo_id: 15
  }
}
infos {
  cmd_id: 43
  element: VI
  edit_type: ADD
  vi {
    mod_id: 1
    task_id: 8
    fb_id: 11
    pin_index: 1
    ev_id: 14
    vi_id: 16
  }
}
infos {
  cmd_id: 44
  element: FB
  edit_type: ADD
  fb {
    mod_id: 1
    task_id: 2
    fb_id: 17
    flib_name: "Task"
    fc_name: "TASK_STATE"
  }
  pos {
    x: 9
    y: 38
  }
}
infos {
  cmd_id: 45
  element: FB
  edit_type: ADD
  fb {
    mod_id: 1
    task_id: 8
    fb_id: 18
    flib_name: "Task"
    fc_name: "TASK_STATE"
  }
  pos {
    x: 13
    y: 57
  }
}
infos {
  cmd_id: 46
  element: FB
  edit_type: MV
  fb {
    mod_id: 1
    task_id: 8
    fb_id: 18
  }
  pos {
    y: 49
  }
}
