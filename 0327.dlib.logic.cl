infos {
  edit_type: SET
  proj {
    proj_name: "rotbot-engine-project"
    proj_uuid: "{cc76fabd-652a-4531-a342-7df3e7c0d35b}"
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
  element: EV
  edit_type: ADD
  ev {
    ev_id: 7
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
  cmd_id: 8
  element: EV
  edit_type: ADD
  ev {
    ev_id: 8
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
  cmd_id: 9
  element: EV
  edit_type: ADD
  ev {
    ev_id: 9
    ev_name: "DEV_SIM"
    ev_type: 9
    ev_desc: "Desc"
    init_val {
      v {
        t: T_STRING
        str: "SIM"
      }
      tm: 1679991743011395990
    }
  }
}
infos {
  cmd_id: 10
  element: EV
  edit_type: ADD
  ev {
    ev_id: 10
    ev_name: "FSM_V"
    ev_type: 2
    ev_desc: "Desc"
    init_val {
      v {
        t: T_INT32
        i: 0
      }
      tm: 1680008304915854730
    }
  }
}
infos {
  cmd_id: 11
  element: MOD
  edit_type: ADD
  mod {
    mod_id: 11
    mod_name: "M1"
  }
}
infos {
  cmd_id: 12
  element: TASK
  edit_type: ADD
  task {
    mod_id: 11
    task_id: 12
    task_name: "P1"
    interval: 1000
  }
}
infos {
  cmd_id: 13
  element: FB
  edit_type: ADD
  fb {
    mod_id: 11
    task_id: 12
    fb_id: 13
    flib_name: "Devices"
    fc_name: "CAMERA"
  }
  pos {
    x: 43
    y: 55
  }
}
infos {
  cmd_id: 14
  element: FB
  edit_type: ADD
  fb {
    mod_id: 11
    task_id: 12
    fb_id: 14
    flib_name: "AI"
    fc_name: "DLIB_FACE_DETECT"
  }
  pos {
    x: 130
    y: 81
  }
}
infos {
  cmd_id: 15
  element: FB
  edit_type: ADD
  fb {
    mod_id: 11
    task_id: 12
    fb_id: 15
    flib_name: "System"
    fc_name: "SYSSTATE"
  }
  pos {
    x: 28
    y: 39
  }
}
infos {
  cmd_id: 16
  element: LK
  edit_type: ADD
  lk {
    mod_id: 11
    task_id: 12
    lk_id: 16
    src_fb_id: 13
    src_pin_index: 1
    target_fb_id: 14
    target_pin_index: 1
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
  cmd_id: 17
  element: LK
  edit_type: ADD
  lk {
    mod_id: 11
    task_id: 12
    lk_id: 17
    src_fb_id: 13
    src_pin_index: 2
    target_fb_id: 14
    target_pin_index: 3
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
  cmd_id: 18
  element: LK
  edit_type: ADD
  lk {
    mod_id: 11
    task_id: 12
    lk_id: 18
    src_fb_id: 13
    src_pin_index: 3
    target_fb_id: 14
    target_pin_index: 2
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
  cmd_id: 19
  element: VI
  edit_type: ADD
  vi {
    mod_id: 11
    task_id: 12
    fb_id: 13
    pin_index: 1
    ev_id: 3
    vi_id: 19
  }
}
infos {
  cmd_id: 20
  element: VI
  edit_type: ADD
  vi {
    mod_id: 11
    task_id: 12
    fb_id: 14
    pin_index: 4
    ev_id: 1
    vi_id: 20
  }
}
infos {
  cmd_id: 21
  element: VI
  edit_type: ADD
  vi {
    mod_id: 11
    task_id: 12
    fb_id: 14
    pin_index: 5
    ev_id: 2
    vi_id: 21
  }
}
infos {
  cmd_id: 22
  element: VO
  edit_type: ADD
  vo {
    mod_id: 11
    task_id: 12
    fb_id: 13
    pin_index: 1
    ev_id: 4
    vo_id: 22
  }
}
infos {
  cmd_id: 23
  element: VO
  edit_type: ADD
  vo {
    mod_id: 11
    task_id: 12
    fb_id: 13
    pin_index: 2
    ev_id: 5
    vo_id: 23
  }
}
infos {
  cmd_id: 24
  element: VO
  edit_type: ADD
  vo {
    mod_id: 11
    task_id: 12
    fb_id: 13
    pin_index: 3
    ev_id: 6
    vo_id: 24
  }
}
infos {
  cmd_id: 25
  element: TASK
  edit_type: ADD
  task {
    mod_id: 11
    task_id: 25
    task_name: "P2"
    interval: 1000
  }
}
infos {
  cmd_id: 26
  element: FB
  edit_type: ADD
  fb {
    mod_id: 11
    task_id: 25
    fb_id: 26
    flib_name: "System"
    fc_name: "SYSSTATE"
  }
  pos {
    x: 25
    y: 103
  }
}
infos {
  cmd_id: 27
  element: FB
  edit_type: ADD
  fb {
    mod_id: 11
    task_id: 25
    fb_id: 27
    flib_name: "Arithmetic"
    fc_name: "ADD_FLOAT"
  }
  pos {
    x: 35
    y: 69
  }
}
infos {
  cmd_id: 28
  element: FB
  edit_type: ADD
  fb {
    mod_id: 11
    task_id: 25
    fb_id: 28
    flib_name: "Arithmetic"
    fc_name: "SUB_INT"
  }
  pos {
    x: 123
    y: 84
  }
}
infos {
  cmd_id: 29
  element: FB
  edit_type: ADD
  fb {
    mod_id: 11
    task_id: 25
    fb_id: 29
    flib_name: "Arithmetic"
    fc_name: "SUB_FLOAT"
  }
  pos {
    x: 112
    y: 69
  }
}
infos {
  cmd_id: 30
  element: FB
  edit_type: ADD
  fb {
    mod_id: 11
    task_id: 25
    fb_id: 30
    flib_name: "String"
    fc_name: "STR_APPEND"
  }
  pos {
    x: 61
    y: 45
  }
}
infos {
  cmd_id: 31
  element: FB
  edit_type: ADD
  fb {
    mod_id: 11
    task_id: 25
    fb_id: 31
    flib_name: "Converter"
    fc_name: "F2I"
  }
  pos {
    x: 74
    y: 83
  }
}
infos {
  cmd_id: 32
  element: FB
  edit_type: ADD
  fb {
    mod_id: 11
    task_id: 25
    fb_id: 32
    flib_name: "Converter"
    fc_name: "UI2I"
  }
  pos {
    x: 74
    y: 104
  }
}
infos {
  cmd_id: 33
  element: FB
  edit_type: ADD
  fb {
    mod_id: 11
    task_id: 25
    fb_id: 33
    flib_name: "Devices"
    fc_name: "SIM_READ"
  }
  pos {
    x: 92
    y: 23
  }
}
infos {
  cmd_id: 34
  element: FB
  edit_type: ADD
  fb {
    mod_id: 11
    task_id: 25
    fb_id: 34
    flib_name: "Converter"
    fc_name: "D2I"
  }
  pos {
    x: 46
    y: 130
  }
}
infos {
  cmd_id: 35
  element: FB
  edit_type: ADD
  fb {
    mod_id: 11
    task_id: 25
    fb_id: 35
    flib_name: "Converter"
    fc_name: "TM2I"
  }
  pos {
    x: 62
    y: 122
  }
}
infos {
  cmd_id: 36
  element: FB
  edit_type: ADD
  fb {
    mod_id: 11
    task_id: 25
    fb_id: 36
    flib_name: "Converter"
    fc_name: "F2I"
  }
  pos {
    x: 149
    y: 115
  }
}
infos {
  cmd_id: 37
  element: FB
  edit_type: ADD
  fb {
    mod_id: 11
    task_id: 25
    fb_id: 37
    flib_name: "Logic"
    fc_name: "AND4"
  }
  pos {
    x: 137
    y: 57
  }
}
infos {
  cmd_id: 38
  element: FB
  edit_type: ADD
  fb {
    mod_id: 11
    task_id: 25
    fb_id: 38
    flib_name: "Logic"
    fc_name: "XOR"
  }
  pos {
    x: 178
    y: 81
  }
}
infos {
  cmd_id: 39
  element: FB
  edit_type: ADD
  fb {
    mod_id: 11
    task_id: 25
    fb_id: 39
    flib_name: "Logic"
    fc_name: "RS"
  }
  pos {
    x: 143
    y: 96
  }
}
infos {
  cmd_id: 40
  element: FB
  edit_type: ADD
  fb {
    mod_id: 11
    task_id: 25
    fb_id: 40
    flib_name: "Logic"
    fc_name: "OR4"
  }
  pos {
    x: 197
    y: 41
  }
}
infos {
  cmd_id: 41
  element: FB
  edit_type: ADD
  fb {
    mod_id: 11
    task_id: 25
    fb_id: 41
    flib_name: "Logic"
    fc_name: "OR"
  }
  pos {
    x: 169
    y: 66
  }
}
infos {
  cmd_id: 42
  element: LK
  edit_type: ADD
  lk {
    mod_id: 11
    task_id: 25
    lk_id: 42
    src_fb_id: 27
    src_pin_index: 1
    target_fb_id: 29
    target_pin_index: 1
  }
  pos {
    x: 50
    y: 76
  }
  pos {
    x: 112
    y: 76
  }
}
infos {
  cmd_id: 43
  element: LK
  edit_type: ADD
  lk {
    mod_id: 11
    task_id: 25
    lk_id: 43
    src_fb_id: 27
    src_pin_index: 1
    target_fb_id: 31
    target_pin_index: 1
  }
  pos {
    x: 50
    y: 76
  }
  pos {
    x: 49
    y: 76
  }
  pos {
    x: 49
    y: 90
  }
  pos {
    x: 74
    y: 90
  }
}
infos {
  cmd_id: 44
  element: LK
  edit_type: ADD
  lk {
    mod_id: 11
    task_id: 25
    lk_id: 44
    src_fb_id: 31
    src_pin_index: 1
    target_fb_id: 28
    target_pin_index: 1
  }
  pos {
    x: 88
    y: 90
  }
  pos {
    x: 101
    y: 90
  }
  pos {
    x: 101
    y: 91
  }
  pos {
    x: 123
    y: 91
  }
}
infos {
  cmd_id: 45
  element: LK
  edit_type: ADD
  lk {
    mod_id: 11
    task_id: 25
    lk_id: 45
    src_fb_id: 26
    src_pin_index: 1
    target_fb_id: 32
    target_pin_index: 1
  }
  pos {
    x: 39
    y: 110
  }
  pos {
    x: 62
    y: 110
  }
  pos {
    x: 62
    y: 111
  }
  pos {
    x: 74
    y: 111
  }
}
infos {
  cmd_id: 46
  element: LK
  edit_type: ADD
  lk {
    mod_id: 11
    task_id: 25
    lk_id: 46
    src_fb_id: 32
    src_pin_index: 1
    target_fb_id: 28
    target_pin_index: 2
  }
  pos {
    x: 88
    y: 111
  }
  pos {
    x: 109
    y: 111
  }
  pos {
    x: 109
    y: 93
  }
  pos {
    x: 123
    y: 93
  }
}
infos {
  cmd_id: 47
  element: LK
  edit_type: ADD
  lk {
    mod_id: 11
    task_id: 25
    lk_id: 47
    src_fb_id: 26
    src_pin_index: 2
    target_fb_id: 35
    target_pin_index: 1
  }
  pos {
    x: 39
    y: 112
  }
  pos {
    x: 50
    y: 112
  }
  pos {
    x: 50
    y: 129
  }
  pos {
    x: 62
    y: 129
  }
}
infos {
  cmd_id: 48
  element: LK
  edit_type: ADD
  lk {
    mod_id: 11
    task_id: 25
    lk_id: 48
    src_fb_id: 41
    src_pin_index: 1
    target_fb_id: 40
    target_pin_index: 4
  }
  pos {
    x: 184
    y: 73
  }
  pos {
    x: 190
    y: 73
  }
  pos {
    x: 190
    y: 54
  }
  pos {
    x: 197
    y: 54
  }
}
infos {
  cmd_id: 49
  element: VI
  edit_type: ADD
  vi {
    mod_id: 11
    task_id: 25
    fb_id: 30
    pin_index: 1
    ev_id: 7
    vi_id: 49
  }
}
infos {
  cmd_id: 50
  element: VI
  edit_type: ADD
  vi {
    mod_id: 11
    task_id: 25
    fb_id: 30
    pin_index: 2
    ev_id: 8
    vi_id: 50
  }
}
infos {
  cmd_id: 51
  element: VI
  edit_type: ADD
  vi {
    mod_id: 11
    task_id: 25
    fb_id: 33
    pin_index: 1
    ev_id: 9
    vi_id: 51
  }
}
infos {
  cmd_id: 52
  element: TASK
  edit_type: ADD
  task {
    mod_id: 11
    task_id: 52
    task_name: "P3"
    interval: 1000
  }
}
infos {
  cmd_id: 53
  element: FB
  edit_type: ADD
  fb {
    mod_id: 11
    task_id: 52
    fb_id: 53
    flib_name: "Fsm"
    fc_name: "FSM"
  }
  pos {
    x: 75
    y: 88
  }
}
infos {
  cmd_id: 54
  element: FB
  edit_type: ADD
  fb {
    mod_id: 11
    task_id: 52
    fb_id: 54
    flib_name: "Fsm"
    fc_name: "FSM"
  }
  pos {
    x: 125
    y: 86
  }
}
infos {
  cmd_id: 55
  element: FB
  edit_type: ADD
  fb {
    mod_id: 11
    task_id: 52
    fb_id: 55
    flib_name: "Fsm"
    fc_name: "FSM"
  }
  pos {
    x: 193
    y: 84
  }
}
infos {
  cmd_id: 56
  element: FB
  edit_type: ADD
  fb {
    mod_id: 11
    task_id: 52
    fb_id: 56
    flib_name: "System"
    fc_name: "SYSSTATE"
  }
  pos {
    x: 12
    y: 70
  }
}
infos {
  cmd_id: 57
  element: FB
  edit_type: ADD
  fb {
    mod_id: 11
    task_id: 52
    fb_id: 57
    flib_name: "Comparison"
    fc_name: "EQ_UINT"
  }
  pos {
    x: 42
    y: 54
  }
}
infos {
  cmd_id: 58
  element: FB
  edit_type: ADD
  fb {
    mod_id: 11
    task_id: 52
    fb_id: 58
    flib_name: "Comparison"
    fc_name: "EQ_UINT"
  }
  pos {
    x: 101
    y: 57
  }
}
infos {
  cmd_id: 59
  element: FB
  edit_type: ADD
  fb {
    mod_id: 11
    task_id: 52
    fb_id: 59
    flib_name: "Comparison"
    fc_name: "EQ_UINT"
  }
  pos {
    x: 160
    y: 57
  }
}
infos {
  cmd_id: 60
  element: FB
  edit_type: ADD
  fb {
    mod_id: 11
    task_id: 52
    fb_id: 60
    flib_name: "Arithmetic"
    fc_name: "SUB_INT"
  }
  pos {
    x: 33
    y: 125
  }
}
infos {
  cmd_id: 61
  element: FB
  edit_type: ADD
  fb {
    mod_id: 11
    task_id: 52
    fb_id: 61
    flib_name: "Arithmetic"
    fc_name: "SUB_UINT"
  }
  pos {
    x: 72
    y: 130
  }
}
infos {
  cmd_id: 62
  element: FB
  edit_type: ADD
  fb {
    mod_id: 11
    task_id: 52
    fb_id: 62
    flib_name: "AI"
    fc_name: "DLIB_FACE_DETECT"
  }
  pos {
    x: 53
    y: 32
  }
}
infos {
  cmd_id: 63
  element: LK
  edit_type: ADD
  lk {
    mod_id: 11
    task_id: 52
    lk_id: 63
    src_fb_id: 56
    src_pin_index: 1
    target_fb_id: 57
    target_pin_index: 1
  }
  pos {
    x: 26
    y: 77
  }
  pos {
    x: 36
    y: 77
  }
  pos {
    x: 36
    y: 61
  }
  pos {
    x: 42
    y: 61
  }
}
infos {
  cmd_id: 64
  element: LK
  edit_type: ADD
  lk {
    mod_id: 11
    task_id: 52
    lk_id: 64
    src_fb_id: 56
    src_pin_index: 1
    target_fb_id: 58
    target_pin_index: 1
  }
  pos {
    x: 26
    y: 77
  }
  pos {
    x: 63
    y: 77
  }
  pos {
    x: 63
    y: 64
  }
  pos {
    x: 101
    y: 64
  }
}
infos {
  cmd_id: 65
  element: LK
  edit_type: ADD
  lk {
    mod_id: 11
    task_id: 52
    lk_id: 65
    src_fb_id: 56
    src_pin_index: 1
    target_fb_id: 59
    target_pin_index: 1
  }
  pos {
    x: 26
    y: 77
  }
  pos {
    x: 144
    y: 77
  }
  pos {
    x: 144
    y: 64
  }
  pos {
    x: 160
    y: 64
  }
}
infos {
  cmd_id: 66
  element: LK
  edit_type: ADD
  lk {
    mod_id: 11
    task_id: 52
    lk_id: 66
    src_fb_id: 57
    src_pin_index: 1
    target_fb_id: 53
    target_pin_index: 1
  }
  pos {
    x: 57
    y: 61
  }
  pos {
    x: 66
    y: 61
  }
  pos {
    x: 66
    y: 95
  }
  pos {
    x: 75
    y: 95
  }
}
infos {
  cmd_id: 67
  element: LK
  edit_type: ADD
  lk {
    mod_id: 11
    task_id: 52
    lk_id: 67
    src_fb_id: 58
    src_pin_index: 1
    target_fb_id: 54
    target_pin_index: 1
  }
  pos {
    x: 116
    y: 64
  }
  pos {
    x: 120
    y: 64
  }
  pos {
    x: 120
    y: 93
  }
  pos {
    x: 125
    y: 93
  }
}
infos {
  cmd_id: 68
  element: LK
  edit_type: ADD
  lk {
    mod_id: 11
    task_id: 52
    lk_id: 68
    src_fb_id: 59
    src_pin_index: 1
    target_fb_id: 55
    target_pin_index: 1
  }
  pos {
    x: 175
    y: 64
  }
  pos {
    x: 183
    y: 64
  }
  pos {
    x: 183
    y: 91
  }
  pos {
    x: 193
    y: 91
  }
}
infos {
  cmd_id: 69
  element: LK
  edit_type: ADD
  lk {
    mod_id: 11
    task_id: 52
    lk_id: 69
    src_fb_id: 53
    src_pin_index: 1
    target_fb_id: 54
    target_pin_index: 2
  }
  pos {
    x: 92
    y: 95
  }
  pos {
    x: 125
    y: 95
  }
}
infos {
  cmd_id: 70
  element: LK
  edit_type: ADD
  lk {
    mod_id: 11
    task_id: 52
    lk_id: 70
    src_fb_id: 54
    src_pin_index: 1
    target_fb_id: 55
    target_pin_index: 2
  }
  pos {
    x: 142
    y: 93
  }
  pos {
    x: 193
    y: 93
  }
}
infos {
  cmd_id: 71
  element: VI
  edit_type: ADD
  vi {
    mod_id: 11
    task_id: 52
    fb_id: 53
    pin_index: 3
    ev_id: 10
    vi_id: 71
  }
}
infos {
  cmd_id: 72
  element: VI
  edit_type: ADD
  vi {
    mod_id: 11
    task_id: 52
    fb_id: 54
    pin_index: 3
    ev_id: 10
    vi_id: 72
  }
}
infos {
  cmd_id: 73
  element: VI
  edit_type: ADD
  vi {
    mod_id: 11
    task_id: 52
    fb_id: 55
    pin_index: 3
    ev_id: 10
    vi_id: 73
  }
}
infos {
  cmd_id: 74
  element: VI
  edit_type: ADD
  vi {
    mod_id: 11
    task_id: 52
    fb_id: 62
    pin_index: 1
    ev_id: 4
    vi_id: 74
  }
}
infos {
  cmd_id: 75
  element: VI
  edit_type: ADD
  vi {
    mod_id: 11
    task_id: 52
    fb_id: 62
    pin_index: 4
    ev_id: 1
    vi_id: 75
  }
}
infos {
  cmd_id: 76
  element: VI
  edit_type: ADD
  vi {
    mod_id: 11
    task_id: 52
    fb_id: 62
    pin_index: 5
    ev_id: 2
    vi_id: 76
  }
}
infos {
  cmd_id: 77
  element: PIN
  edit_type: SET
  pin {
    mod_id: 11
    task_id: 25
    fb_id: 27
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
  cmd_id: 78
  element: PIN
  edit_type: SET
  pin {
    mod_id: 11
    task_id: 25
    fb_id: 27
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
  cmd_id: 79
  element: PIN
  edit_type: SET
  pin {
    mod_id: 11
    task_id: 25
    fb_id: 29
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
  cmd_id: 80
  element: PIN
  edit_type: SET
  pin {
    mod_id: 11
    task_id: 25
    fb_id: 30
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
  cmd_id: 81
  element: PIN
  edit_type: SET
  pin {
    mod_id: 11
    task_id: 25
    fb_id: 30
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
infos {
  cmd_id: 82
  element: PIN
  edit_type: SET
  pin {
    mod_id: 11
    task_id: 25
    fb_id: 28
    pin_index: 2
    pin_val {
      v {
        t: T_INT32
        i: 189
      }
      tm: 1679975723560690248
    }
  }
}
infos {
  cmd_id: 83
  element: PIN
  edit_type: SET
  pin {
    mod_id: 11
    task_id: 52
    fb_id: 57
    pin_index: 2
    pin_val {
      v {
        t: T_UINT32
        ui: 10
      }
      tm: 1680008164758751359
    }
  }
}
infos {
  cmd_id: 84
  element: PIN
  edit_type: SET
  pin {
    mod_id: 11
    task_id: 52
    fb_id: 58
    pin_index: 2
    pin_val {
      v {
        t: T_UINT32
        ui: 20
      }
      tm: 1680008197894277845
    }
  }
}
infos {
  cmd_id: 85
  element: PIN
  edit_type: SET
  pin {
    mod_id: 11
    task_id: 52
    fb_id: 59
    pin_index: 2
    pin_val {
      v {
        t: T_UINT32
        ui: 30
      }
      tm: 1680008212518670899
    }
  }
}
infos {
  cmd_id: 86
  element: PIN
  edit_type: SET
  pin {
    mod_id: 11
    task_id: 52
    fb_id: 53
    pin_index: 4
    pin_val {
      v {
        t: T_INT32
        i: 2
      }
      tm: 1680008419444201064
    }
  }
}
infos {
  cmd_id: 87
  element: PIN
  edit_type: SET
  pin {
    mod_id: 11
    task_id: 52
    fb_id: 54
    pin_index: 4
    pin_val {
      v {
        t: T_INT32
        i: 4
      }
      tm: 1680008425348858925
    }
  }
}
infos {
  cmd_id: 88
  element: PIN
  edit_type: SET
  pin {
    mod_id: 11
    task_id: 52
    fb_id: 55
    pin_index: 4
    pin_val {
      v {
        t: T_INT32
        i: 8
      }
      tm: 1680008430796467181
    }
  }
}
infos {
  cmd_id: 89
  element: PIN
  edit_type: SET
  pin {
    mod_id: 11
    task_id: 25
    fb_id: 30
    pin_index: 4
    pin_val {
      v {
        t: T_UINT32
        ui: 10
      }
      tm: 1680008560766643271
    }
  }
}
infos {
  cmd_id: 90
  element: PIN
  edit_type: SET
  pin {
    mod_id: 11
    task_id: 25
    fb_id: 30
    pin_index: 4
    pin_val {
      v {
        t: T_UINT32
        ui: 12
      }
      tm: 1680009933222923479
    }
  }
}
infos {
  cmd_id: 91
  element: PIN
  edit_type: SET
  pin {
    mod_id: 11
    task_id: 25
    fb_id: 36
    pin_index: 1
    pin_val {
      v {
        t: T_FLOAT32
        f: 1e+10
      }
      tm: 1680010113744107570
    }
  }
}
infos {
  cmd_id: 92
  element: PIN
  edit_type: SET
  pin {
    mod_id: 11
    task_id: 25
    fb_id: 41
    pin_index: 2
    pin_val {
      v {
        t: T_BOOL
        b: true
      }
      tm: 1680010240173941846
    }
  }
}
infos {
  cmd_id: 93
  element: PIN
  edit_type: SET
  pin {
    mod_id: 11
    task_id: 25
    fb_id: 41
    pin_index: 1
    pin_val {
      v {
        t: T_BOOL
        b: false
      }
      tm: 1680010244541722362
    }
  }
}
infos {
  cmd_id: 94
  element: PIN
  edit_type: SET
  pin {
    mod_id: 11
    task_id: 25
    fb_id: 40
    pin_index: 3
    pin_val {
      v {
        t: T_BOOL
        b: true
      }
      tm: 1680010250324999742
    }
  }
}
infos {
  cmd_id: 95
  element: PIN
  edit_type: SET
  pin {
    mod_id: 11
    task_id: 52
    fb_id: 62
    pin_index: 2
    pin_val {
      v {
        t: T_UINT32
        ui: 640
      }
      tm: 1680011131016749775
    }
  }
}
infos {
  cmd_id: 96
  element: PIN
  edit_type: SET
  pin {
    mod_id: 11
    task_id: 52
    fb_id: 62
    pin_index: 3
    pin_val {
      v {
        t: T_UINT32
        ui: 480
      }
      tm: 1680011137593218343
    }
  }
}
infos {
  cmd_id: 97
  element: FB
  edit_type: ADD
  fb {
    mod_id: 11
    task_id: 25
    fb_id: 77
    flib_name: "Arithmetic"
    fc_name: "DIV_INT"
  }
  pos {
    x: 154
    y: 131
  }
}
infos {
  cmd_id: 98
  element: PIN
  edit_type: SET
  pin {
    mod_id: 11
    task_id: 25
    fb_id: 77
    pin_index: 1
    pin_val {
      v {
        t: T_INT32
        i: 123
      }
      tm: 1680011672621565440
    }
  }
}
infos {
  cmd_id: 99
  element: PIN
  edit_type: SET
  pin {
    mod_id: 11
    task_id: 25
    fb_id: 77
    pin_index: 2
    pin_val {
      v {
        t: T_INT32
        i: 0
      }
      tm: 1680011675285338579
    }
  }
}
infos {
  cmd_id: 102
  element: FB
  edit_type: MV
  fb {
    mod_id: 11
    task_id: 25
    fb_id: 36
  }
  pos {
    x: 148
    y: 110
  }
}
infos {
  cmd_id: 103
  element: FB
  edit_type: MV
  fb {
    mod_id: 11
    task_id: 25
    fb_id: 77
  }
  pos {
    x: 108
    y: 118
  }
}
infos {
  cmd_id: 104
  element: FB
  edit_type: ADD
  fb {
    mod_id: 11
    task_id: 25
    fb_id: 78
    flib_name: "Arithmetic"
    fc_name: "ADD_INT"
  }
  pos {
    x: 153
    y: 129
  }
}
infos {
  cmd_id: 105
  element: LK
  edit_type: ADD
  lk {
    mod_id: 11
    task_id: 25
    lk_id: 79
    src_fb_id: 77
    src_pin_index: 1
    target_fb_id: 78
    target_pin_index: 1
  }
  pos {
    x: 123
    y: 125
  }
  pos {
    x: 138
    y: 125
  }
  pos {
    x: 138
    y: 136
  }
  pos {
    x: 153
    y: 136
  }
}
infos {
  cmd_id: 106
  element: FB
  edit_type: ADD
  fb {
    mod_id: 11
    task_id: 25
    fb_id: 80
    flib_name: "Geometry"
    fc_name: "PATH_SPLIT"
  }
  pos {
    x: 93
    y: 53
  }
}
infos {
  cmd_id: 108
  element: FB
  edit_type: ADD
  fb {
    mod_id: 11
    task_id: 25
    fb_id: 81
    flib_name: "Geometry"
    fc_name: "PATH_MERGE"
  }
  pos {
    x: 118
    y: 147
  }
}
infos {
  cmd_id: 113
  element: FB
  edit_type: MV
  fb {
    mod_id: 11
    task_id: 25
    fb_id: 81
  }
  pos {
    x: 106
    y: 141
  }
}
infos {
  cmd_id: 115
  element: FB
  edit_type: MV
  fb {
    mod_id: 11
    task_id: 25
    fb_id: 80
  }
  pos {
    x: 43
    y: 145
  }
}
infos {
  cmd_id: 116
  element: FB
  edit_type: ADD
  fb {
    mod_id: 11
    task_id: 25
    fb_id: 82
    flib_name: "Geometry"
    fc_name: "PATH_SPLIT"
  }
  pos {
    x: 78
    y: 161
  }
}
infos {
  cmd_id: 117
  element: PIN
  edit_type: SET
  pin {
    mod_id: 11
    task_id: 25
    fb_id: 30
    pin_index: 4
    pin_val {
      v {
        t: T_UINT32
        ui: 5
      }
      tm: 1680261537714398961
    }
  }
}
