infos {
  edit_type: SET
  proj {
    proj_name: "rotbot-engine-project"
    proj_uuid: "{d3f0189b-ebe0-4af8-aad2-15a7c25c859a}"
  }
}
infos {
  cmd_id: 1
  element: EV
  edit_type: ADD
  ev {
    ev_id: 1
    ev_name: "SP_FILE_NAME"
    ev_type: 9
    ev_desc: "Desc"
    init_val {
      v {
        t: T_STRING
        str: "/home/shuimujie/Works/bamboo_ws/bin/debug/shape_predictor_5_face_landmarks.dat"
      }
      tm: 1679902220638820161
    }
  }
}
infos {
  cmd_id: 2
  element: EV
  edit_type: ADD
  ev {
    ev_id: 2
    ev_name: "ANET_FILE_NAME"
    ev_type: 9
    ev_desc: "Desc"
    init_val {
      v {
        t: T_STRING
        str: "/home/shuimujie/Works/bamboo_ws/bin/debug/dlib_face_recognition_resnet_model_v1.dat"
      }
      tm: 1679902285886066016
    }
  }
}
infos {
  cmd_id: 3
  element: EV
  edit_type: ADD
  ev {
    ev_id: 3
    ev_name: "CAM_1"
    ev_type: 9
    ev_desc: "Desc"
    init_val {
      v {
        t: T_STRING
        str: "front camera"
      }
      tm: 1679902426383290942
    }
  }
}
infos {
  cmd_id: 4
  element: EV
  edit_type: ADD
  ev {
    ev_id: 4
    ev_name: "IMG_1"
    ev_type: 2
    ev_desc: "Desc"
    init_val {
      v {
        t: T_IMAGE
        img: "front camera"
      }
      tm: 1679902478647213095
    }
  }
}
infos {
  cmd_id: 5
  element: EV
  edit_type: ADD
  ev {
    ev_id: 5
    ev_name: "h"
    ev_type: 3
    ev_desc: "Desc"
    init_val {
      v {
        t: T_UINT32
        ui: 0
      }
      tm: 1679903081990699883
    }
  }
}
infos {
  cmd_id: 6
  element: EV
  edit_type: ADD
  ev {
    ev_id: 6
    ev_name: "w"
    ev_type: 3
    ev_desc: "Desc"
    init_val {
      v {
        t: T_UINT32
        ui: 0
      }
      tm: 1679903087957670986
    }
  }
}
infos {
  cmd_id: 7
  element: MOD
  edit_type: ADD
  mod {
    mod_id: 7
    mod_name: "M1"
  }
}
infos {
  cmd_id: 8
  element: TASK
  edit_type: ADD
  task {
    mod_id: 7
    task_id: 8
    task_name: "P1"
    interval: 1000
  }
}
infos {
  cmd_id: 9
  element: FB
  edit_type: ADD
  fb {
    mod_id: 7
    task_id: 8
    fb_id: 9
    flib_name: "Devices"
    fc_name: "CAMERA"
  }
  pos {
    x: 62
    y: 61
  }
}
infos {
  cmd_id: 10
  element: FB
  edit_type: ADD
  fb {
    mod_id: 7
    task_id: 8
    fb_id: 10
    flib_name: "AI"
    fc_name: "DLIB_FACE_DETECT"
  }
  pos {
    x: 130
    y: 81
  }
}
infos {
  cmd_id: 11
  element: LK
  edit_type: ADD
  lk {
    mod_id: 7
    task_id: 8
    lk_id: 11
    src_fb_id: 9
    src_pin_index: 1
    target_fb_id: 10
    target_pin_index: 1
  }
  pos {
    x: 78
    y: 68
  }
  pos {
    x: 104
    y: 68
  }
  pos {
    x: 104
    y: 88
  }
  pos {
    x: 130
    y: 88
  }
}
infos {
  cmd_id: 12
  element: LK
  edit_type: ADD
  lk {
    mod_id: 7
    task_id: 8
    lk_id: 12
    src_fb_id: 9
    src_pin_index: 2
    target_fb_id: 10
    target_pin_index: 3
  }
  pos {
    x: 78
    y: 70
  }
  pos {
    x: 104
    y: 70
  }
  pos {
    x: 104
    y: 92
  }
  pos {
    x: 130
    y: 92
  }
}
infos {
  cmd_id: 13
  element: LK
  edit_type: ADD
  lk {
    mod_id: 7
    task_id: 8
    lk_id: 13
    src_fb_id: 9
    src_pin_index: 3
    target_fb_id: 10
    target_pin_index: 2
  }
  pos {
    x: 78
    y: 72
  }
  pos {
    x: 104
    y: 72
  }
  pos {
    x: 104
    y: 90
  }
  pos {
    x: 130
    y: 90
  }
}
infos {
  cmd_id: 14
  element: VI
  edit_type: ADD
  vi {
    mod_id: 7
    task_id: 8
    fb_id: 9
    pin_index: 1
    ev_id: 3
    vi_id: 14
  }
}
infos {
  cmd_id: 15
  element: VI
  edit_type: ADD
  vi {
    mod_id: 7
    task_id: 8
    fb_id: 10
    pin_index: 4
    ev_id: 1
    vi_id: 15
  }
}
infos {
  cmd_id: 16
  element: VI
  edit_type: ADD
  vi {
    mod_id: 7
    task_id: 8
    fb_id: 10
    pin_index: 5
    ev_id: 2
    vi_id: 16
  }
}
infos {
  cmd_id: 17
  element: VO
  edit_type: ADD
  vo {
    mod_id: 7
    task_id: 8
    fb_id: 9
    pin_index: 1
    ev_id: 4
    vo_id: 17
  }
}
infos {
  cmd_id: 18
  element: VO
  edit_type: ADD
  vo {
    mod_id: 7
    task_id: 8
    fb_id: 9
    pin_index: 2
    ev_id: 5
    vo_id: 18
  }
}
infos {
  cmd_id: 19
  element: VO
  edit_type: ADD
  vo {
    mod_id: 7
    task_id: 8
    fb_id: 9
    pin_index: 3
    ev_id: 6
    vo_id: 19
  }
}
infos {
  cmd_id: 20
  element: FB
  edit_type: MV
  fb {
    mod_id: 7
    task_id: 8
    fb_id: 9
  }
  pos {
    x: 43
    y: 55
  }
}
infos {
  cmd_id: 21
  element: LK
  edit_type: MV
  lk {
    mod_id: 7
    task_id: 8
    lk_id: 11
  }
  pos {
    x: 59
    y: 62
  }
  pos {
    x: 104
    y: 62
  }
  pos {
    x: 104
    y: 88
  }
  pos {
    x: 130
    y: 88
  }
}
infos {
  cmd_id: 25
  element: LK
  edit_type: MV
  lk {
    mod_id: 7
    task_id: 8
    lk_id: 13
  }
  pos {
    x: 59
    y: 66
  }
  pos {
    x: 88
    y: 66
  }
  pos {
    x: 88
    y: 90
  }
  pos {
    x: 130
    y: 90
  }
}
infos {
  cmd_id: 26
  element: LK
  edit_type: MV
  lk {
    mod_id: 7
    task_id: 8
    lk_id: 12
  }
  pos {
    x: 59
    y: 64
  }
  pos {
    x: 94
    y: 64
  }
  pos {
    x: 94
    y: 92
  }
  pos {
    x: 130
    y: 92
  }
}
infos {
  cmd_id: 27
  element: TASK
  edit_type: ADD
  task {
    mod_id: 7
    task_id: 20
    task_name: "P2"
    interval: 1000
  }
}
infos {
  cmd_id: 28
  element: FB
  edit_type: ADD
  fb {
    mod_id: 7
    task_id: 20
    fb_id: 21
    flib_name: "System"
    fc_name: "SYSSTATE"
  }
  pos {
    x: 31
    y: 49
  }
}
infos {
  cmd_id: 29
  element: FB
  edit_type: ADD
  fb {
    mod_id: 7
    task_id: 20
    fb_id: 22
    flib_name: "Arithmetic"
    fc_name: "ADD_FLOAT"
  }
  pos {
    x: 44
    y: 83
  }
}
infos {
  cmd_id: 30
  element: FB
  edit_type: ADD
  fb {
    mod_id: 7
    task_id: 20
    fb_id: 23
    flib_name: "Arithmetic"
    fc_name: "SUB_INT"
  }
  pos {
    x: 82
    y: 92
  }
}
infos {
  cmd_id: 31
  element: FB
  edit_type: ADD
  fb {
    mod_id: 7
    task_id: 20
    fb_id: 24
    flib_name: "Arithmetic"
    fc_name: "SUB_FLOAT"
  }
  pos {
    x: 83
    y: 74
  }
}
infos {
  cmd_id: 32
  element: LK
  edit_type: ADD
  lk {
    mod_id: 7
    task_id: 20
    lk_id: 25
    src_fb_id: 22
    src_pin_index: 1
    target_fb_id: 24
    target_pin_index: 1
  }
  pos {
    x: 59
    y: 90
  }
  pos {
    x: 71
    y: 90
  }
  pos {
    x: 71
    y: 81
  }
  pos {
    x: 83
    y: 81
  }
}
infos {
  cmd_id: 33
  element: PIN
  edit_type: SET
  pin {
    mod_id: 7
    task_id: 20
    fb_id: 22
    pin_index: 1
    pin_val {
      v {
        t: T_FLOAT32
        f: 3.6
      }
      tm: 1679923255769582114
    }
  }
}
infos {
  cmd_id: 34
  element: PIN
  edit_type: SET
  pin {
    mod_id: 7
    task_id: 20
    fb_id: 22
    pin_index: 2
    pin_val {
      v {
        t: T_FLOAT32
        f: 5.6
      }
      tm: 1679923263200557732
    }
  }
}
infos {
  cmd_id: 35
  element: PIN
  edit_type: SET
  pin {
    mod_id: 7
    task_id: 20
    fb_id: 24
    pin_index: 2
    pin_val {
      v {
        t: T_FLOAT32
        f: 1.8
      }
      tm: 1679923269848106615
    }
  }
}
infos {
  cmd_id: 38
  element: FB
  edit_type: ADD
  fb {
    mod_id: 7
    task_id: 20
    fb_id: 26
    flib_name: "String"
    fc_name: "STR_APPEND"
  }
  pos {
    x: 57
    y: 38
  }
}
infos {
  cmd_id: 39
  element: FB
  edit_type: MV
  fb {
    mod_id: 7
    task_id: 20
    fb_id: 22
  }
  pos {
    x: 42
    y: 69
  }
}
infos {
  cmd_id: 40
  element: FB
  edit_type: MV
  fb {
    mod_id: 7
    task_id: 20
    fb_id: 26
  }
  pos {
    x: 66
    y: 34
  }
}
infos {
  cmd_id: 41
  element: LK
  edit_type: MV
  lk {
    mod_id: 7
    task_id: 20
    lk_id: 25
  }
  pos {
    x: 57
    y: 76
  }
  pos {
    x: 71
    y: 76
  }
  pos {
    x: 71
    y: 81
  }
  pos {
    x: 83
    y: 81
  }
}
infos {
  cmd_id: 42
  element: EV
  edit_type: ADD
  ev {
    ev_id: 27
    ev_name: "STR_1"
    ev_type: 9
    ev_desc: "Desc"
    init_val {
      v {
        t: T_STRING
        str: "zheshi wode ceshi zifuchuan"
      }
      tm: 1679923350128919039
    }
  }
}
infos {
  cmd_id: 43
  element: VI
  edit_type: ADD
  vi {
    mod_id: 7
    task_id: 20
    fb_id: 26
    pin_index: 1
    ev_id: 27
    vi_id: 28
  }
}
infos {
  cmd_id: 44
  element: EV
  edit_type: ADD
  ev {
    ev_id: 29
    ev_name: "STR_2"
    ev_type: 9
    ev_desc: "Desc"
    init_val {
      v {
        t: T_STRING
        str: "ni bu zhi dao"
      }
      tm: 1679923385613666573
    }
  }
}
infos {
  cmd_id: 45
  element: VI
  edit_type: ADD
  vi {
    mod_id: 7
    task_id: 20
    fb_id: 26
    pin_index: 2
    ev_id: 29
    vi_id: 30
  }
}
infos {
  cmd_id: 46
  element: PIN
  edit_type: SET
  pin {
    mod_id: 7
    task_id: 20
    fb_id: 26
    pin_index: 3
    pin_val {
      v {
        t: T_UINT32
        ui: 0
      }
      tm: 1679923632602015365
    }
  }
}
infos {
  cmd_id: 47
  element: PIN
  edit_type: SET
  pin {
    mod_id: 7
    task_id: 20
    fb_id: 26
    pin_index: 4
    pin_val {
      v {
        t: T_UINT32
        ui: 5
      }
      tm: 1679923642673344101
    }
  }
}
