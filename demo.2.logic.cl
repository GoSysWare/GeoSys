infos {
  cmd_id: 726
  edit_type: SET
  proj {
    proj_name: "rotbot-engine-project"
    proj_uuid: "{f9ec54d3-4508-43a5-8b5e-cbffcde72ffa}"
  }
}
infos {
  cmd_id: 1
  element: MOD
  edit_type: ADD
  mod {
    mod_id: 1
    mod_name: "Base"
  }
}
infos {
  cmd_id: 2
  element: TASK
  edit_type: ADD
  task {
    mod_id: 1
    task_id: 2
    task_name: "Math"
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
    flib_name: "Task"
    fc_name: "TASK_STATE"
  }
  pos {
    x: 10
    y: 8
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
    flib_name: "Arithmetic"
    fc_name: "ADD_INT"
  }
  pos {
    x: 70
    y: 22
  }
}
infos {
  cmd_id: 5
  element: FB
  edit_type: ADD
  fb {
    mod_id: 1
    task_id: 2
    fb_id: 5
    flib_name: "Converter"
    fc_name: "D2I"
  }
  pos {
    x: 53
    y: 22
  }
}
infos {
  cmd_id: 11
  element: FB
  edit_type: ADD
  fb {
    mod_id: 1
    task_id: 2
    fb_id: 6
    flib_name: "Devices"
    fc_name: "SIM_READ"
  }
  pos {
    x: 11
    y: 39
  }
}
infos {
  cmd_id: 18
  element: LK
  edit_type: ADD
  lk {
    mod_id: 1
    task_id: 2
    lk_id: 7
    src_fb_id: 6
    src_pin_index: 1
    target_fb_id: 5
    target_pin_index: 1
  }
  pos {
    x: 27
    y: 38
  }
  pos {
    x: 36
    y: 38
  }
  pos {
    x: 36
    y: 39
  }
  pos {
    x: 46
    y: 39
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
    pin_index: 1
    pin_val {
      t: T_STRING
      v {
        str: "SIM"
      }
      tm: 1683612436338681534
    }
  }
}
infos {
  cmd_id: 23
  element: FB
  edit_type: MV
  fb {
    mod_id: 1
    task_id: 2
    fb_id: 5
  }
  pos {
    x: 55
    y: 32
  }
}
infos {
  cmd_id: 25
  element: LK
  edit_type: ADD
  lk {
    mod_id: 1
    task_id: 2
    lk_id: 8
    src_fb_id: 5
    src_pin_index: 1
    target_fb_id: 4
    target_pin_index: 1
  }
  pos {
    x: 73
    y: 39
  }
  pos {
    x: 82
    y: 39
  }
  pos {
    x: 82
    y: 40
  }
  pos {
    x: 91
    y: 40
  }
}
infos {
  cmd_id: 28
  element: FB
  edit_type: MV
  fb {
    mod_id: 1
    task_id: 2
    fb_id: 4
  }
  pos {
    x: 91
    y: 32
  }
}
infos {
  cmd_id: 29
  element: LK
  edit_type: MV
  lk {
    mod_id: 1
    task_id: 2
    lk_id: 8
  }
  pos {
    x: 73
    y: 39
  }
  pos {
    x: 91
    y: 39
  }
}
infos {
  cmd_id: 32
  element: FB
  edit_type: MV
  fb {
    mod_id: 1
    task_id: 2
    fb_id: 6
  }
  pos {
    x: 7
    y: 32
  }
}
infos {
  cmd_id: 33
  element: LK
  edit_type: MV
  lk {
    mod_id: 1
    task_id: 2
    lk_id: 7
  }
  pos {
    x: 27
    y: 39
  }
  pos {
    x: 55
    y: 39
  }
}
infos {
  cmd_id: 34
  element: FB
  edit_type: ADD
  fb {
    mod_id: 1
    task_id: 2
    fb_id: 9
    flib_name: "Arithmetic"
    fc_name: "SUB_DOUBLE"
  }
  pos {
    x: 66
    y: 54
  }
}
infos {
  cmd_id: 36
  element: LK
  edit_type: ADD
  lk {
    mod_id: 1
    task_id: 2
    lk_id: 10
    src_fb_id: 6
    src_pin_index: 1
    target_fb_id: 9
    target_pin_index: 1
  }
  pos {
    x: 27
    y: 39
  }
  pos {
    x: 41
    y: 39
  }
  pos {
    x: 41
    y: 53
  }
  pos {
    x: 55
    y: 53
  }
}
infos {
  cmd_id: 39
  element: FB
  edit_type: ADD
  fb {
    mod_id: 1
    task_id: 2
    fb_id: 11
    flib_name: "Arithmetic"
    fc_name: "MUL_INT"
  }
  pos {
    x: 100
    y: 19
  }
}
infos {
  cmd_id: 41
  element: FB
  edit_type: MV
  fb {
    mod_id: 1
    task_id: 2
    fb_id: 11
  }
  pos {
    x: 91
    y: 16
  }
}
infos {
  cmd_id: 47
  element: FB
  edit_type: ADD
  fb {
    mod_id: 1
    task_id: 2
    fb_id: 12
    flib_name: "Arithmetic"
    fc_name: "DIV_UINT"
  }
  pos {
    x: 71
    y: 22
  }
}
infos {
  cmd_id: 48
  element: FB
  edit_type: MV
  fb {
    mod_id: 1
    task_id: 2
    fb_id: 9
  }
  pos {
    x: 90
    y: 51
  }
}
infos {
  cmd_id: 54
  element: FB
  edit_type: ADD
  fb {
    mod_id: 1
    task_id: 2
    fb_id: 13
    flib_name: "Converter"
    fc_name: "D2UI"
  }
  pos {
    x: 62
    y: 68
  }
}
infos {
  cmd_id: 56
  element: FB
  edit_type: MV
  fb {
    mod_id: 1
    task_id: 2
    fb_id: 13
  }
  pos {
    x: 58
    y: 68
  }
}
infos {
  cmd_id: 58
  element: LK
  edit_type: ADD
  lk {
    mod_id: 1
    task_id: 2
    lk_id: 14
    src_fb_id: 6
    src_pin_index: 1
    target_fb_id: 13
    target_pin_index: 1
  }
  pos {
    x: 27
    y: 39
  }
  pos {
    x: 42
    y: 39
  }
  pos {
    x: 42
    y: 75
  }
  pos {
    x: 58
    y: 75
  }
}
infos {
  cmd_id: 61
  element: LK
  edit_type: ADD
  lk {
    mod_id: 1
    task_id: 2
    lk_id: 15
    src_fb_id: 13
    src_pin_index: 1
    target_fb_id: 12
    target_pin_index: 1
  }
  pos {
    x: 76
    y: 75
  }
  pos {
    x: 83
    y: 75
  }
  pos {
    x: 83
    y: 74
  }
  pos {
    x: 90
    y: 74
  }
}
infos {
  cmd_id: 62
  element: FB
  edit_type: MV
  fb {
    mod_id: 1
    task_id: 2
    fb_id: 12
  }
  pos {
    x: 90
    y: 68
  }
}
infos {
  cmd_id: 63
  element: LK
  edit_type: MV
  lk {
    mod_id: 1
    task_id: 2
    lk_id: 15
  }
  pos {
    x: 76
    y: 75
  }
  pos {
    x: 90
    y: 75
  }
}
infos {
  cmd_id: 64
  element: LK
  edit_type: ADD
  lk {
    mod_id: 1
    task_id: 2
    lk_id: 16
    src_fb_id: 5
    src_pin_index: 1
    target_fb_id: 11
    target_pin_index: 1
  }
  pos {
    x: 73
    y: 39
  }
  pos {
    x: 82
    y: 39
  }
  pos {
    x: 82
    y: 23
  }
  pos {
    x: 91
    y: 23
  }
}
infos {
  cmd_id: 65
  element: PIN
  edit_type: SET
  pin {
    mod_id: 1
    task_id: 2
    fb_id: 11
    pin_index: 2
    pin_val {
      t: T_INT32
      v {
        i: 3
      }
      tm: 1683612771660258670
    }
  }
}
infos {
  cmd_id: 66
  element: PIN
  edit_type: SET
  pin {
    mod_id: 1
    task_id: 2
    fb_id: 4
    pin_index: 2
    pin_val {
      t: T_INT32
      v {
        i: 2
      }
      tm: 1683612775800589081
    }
  }
}
infos {
  cmd_id: 67
  element: PIN
  edit_type: SET
  pin {
    mod_id: 1
    task_id: 2
    fb_id: 9
    pin_index: 2
    pin_val {
      t: T_FLOAT64
      v {
        d: 12.5
      }
      tm: 1683612786488398648
    }
  }
}
infos {
  cmd_id: 68
  element: PIN
  edit_type: SET
  pin {
    mod_id: 1
    task_id: 2
    fb_id: 12
    pin_index: 2
    pin_val {
      t: T_UINT32
      v {
        ui: 3
      }
      tm: 1683612793548623621
    }
  }
}
infos {
  cmd_id: 69
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
        str: "$SECOND"
      }
      tm: 1683612833724742370
    }
  }
}
infos {
  cmd_id: 70
  element: MOD
  edit_type: ADD
  mod {
    mod_id: 17
    mod_name: "Task"
  }
}
infos {
  cmd_id: 71
  element: TASK
  edit_type: ADD
  task {
    mod_id: 17
    task_id: 18
    task_name: "Fsm"
    interval: 1000
  }
}
infos {
  cmd_id: 72
  element: FB
  edit_type: ADD
  fb {
    mod_id: 17
    task_id: 18
    fb_id: 19
    flib_name: "Task"
    fc_name: "TASK_STATE"
  }
  pos {
    x: 12
    y: 50
  }
}
infos {
  cmd_id: 73
  element: FB
  edit_type: ADD
  fb {
    mod_id: 17
    task_id: 18
    fb_id: 20
    flib_name: "Fsm"
    fc_name: "FSM"
  }
  pos {
    x: 32
    y: 83
  }
}
infos {
  cmd_id: 74
  element: FB
  edit_type: ADD
  fb {
    mod_id: 17
    task_id: 18
    fb_id: 21
    flib_name: "Fsm"
    fc_name: "FSM"
  }
  pos {
    x: 78
    y: 90
  }
}
infos {
  cmd_id: 80
  element: FB
  edit_type: ADD
  fb {
    mod_id: 17
    task_id: 18
    fb_id: 22
    flib_name: "Fsm"
    fc_name: "FSM"
  }
  pos {
    x: 116
    y: 89
  }
}
infos {
  cmd_id: 85
  element: FB
  edit_type: ADD
  fb {
    mod_id: 17
    task_id: 18
    fb_id: 23
    flib_name: "Fsm"
    fc_name: "FSM"
  }
  pos {
    x: 129
    y: 83
  }
}
infos {
  cmd_id: 90
  element: LK
  edit_type: ADD
  lk {
    mod_id: 17
    task_id: 18
    lk_id: 24
    src_fb_id: 20
    src_pin_index: 1
    target_fb_id: 21
    target_pin_index: 2
  }
  pos {
    x: 32
    y: 88
  }
  pos {
    x: 41
    y: 88
  }
  pos {
    x: 41
    y: 90
  }
  pos {
    x: 50
    y: 90
  }
}
infos {
  cmd_id: 91
  element: LK
  edit_type: ADD
  lk {
    mod_id: 17
    task_id: 18
    lk_id: 25
    src_fb_id: 21
    src_pin_index: 1
    target_fb_id: 22
    target_pin_index: 2
  }
  pos {
    x: 71
    y: 88
  }
  pos {
    x: 81
    y: 88
  }
  pos {
    x: 81
    y: 90
  }
  pos {
    x: 92
    y: 90
  }
}
infos {
  cmd_id: 92
  element: LK
  edit_type: ADD
  lk {
    mod_id: 17
    task_id: 18
    lk_id: 26
    src_fb_id: 22
    src_pin_index: 1
    target_fb_id: 23
    target_pin_index: 2
  }
  pos {
    x: 113
    y: 88
  }
  pos {
    x: 125
    y: 88
  }
  pos {
    x: 125
    y: 90
  }
  pos {
    x: 138
    y: 90
  }
}
infos {
  cmd_id: 93
  element: FB
  edit_type: ADD
  fb {
    mod_id: 17
    task_id: 18
    fb_id: 27
    flib_name: "Fsm"
    fc_name: "FSM"
  }
  pos {
    x: 57
    y: 113
  }
}
infos {
  cmd_id: 97
  element: FB
  edit_type: ADD
  fb {
    mod_id: 17
    task_id: 18
    fb_id: 28
    flib_name: "Fsm"
    fc_name: "FSM"
  }
  pos {
    x: 103
    y: 115
  }
}
infos {
  cmd_id: 99
  element: LK
  edit_type: ADD
  lk {
    mod_id: 17
    task_id: 18
    lk_id: 29
    src_fb_id: 27
    src_pin_index: 1
    target_fb_id: 28
    target_pin_index: 2
  }
  pos {
    x: 71
    y: 115
  }
  pos {
    x: 81
    y: 115
  }
  pos {
    x: 81
    y: 119
  }
  pos {
    x: 92
    y: 119
  }
}
infos {
  cmd_id: 100
  element: LK
  edit_type: ADD
  lk {
    mod_id: 17
    task_id: 18
    lk_id: 30
    src_fb_id: 20
    src_pin_index: 1
    target_fb_id: 27
    target_pin_index: 2
  }
  pos {
    x: 32
    y: 88
  }
  pos {
    x: 41
    y: 88
  }
  pos {
    x: 41
    y: 117
  }
  pos {
    x: 50
    y: 117
  }
}
infos {
  cmd_id: 122
  element: EV
  edit_type: ADD
  ev {
    ev_id: 31
    ev_name: "Fsm_state"
    ev_type: 2
    ev_desc: "Desc"
    init_val {
      t: T_INT32
      v {
        i: 0
      }
      tm: 1683613001825857849
    }
  }
}
infos {
  cmd_id: 123
  element: VI
  edit_type: ADD
  vi {
    mod_id: 17
    task_id: 18
    fb_id: 20
    pin_index: 3
    ev_id: 31
    vi_id: 32
  }
}
infos {
  cmd_id: 124
  element: VI
  edit_type: ADD
  vi {
    mod_id: 17
    task_id: 18
    fb_id: 21
    pin_index: 3
    ev_id: 31
    vi_id: 33
  }
}
infos {
  cmd_id: 125
  element: VI
  edit_type: ADD
  vi {
    mod_id: 17
    task_id: 18
    fb_id: 22
    pin_index: 3
    ev_id: 31
    vi_id: 34
  }
}
infos {
  cmd_id: 126
  element: VI
  edit_type: ADD
  vi {
    mod_id: 17
    task_id: 18
    fb_id: 27
    pin_index: 3
    ev_id: 31
    vi_id: 35
  }
}
infos {
  cmd_id: 127
  element: VI
  edit_type: ADD
  vi {
    mod_id: 17
    task_id: 18
    fb_id: 28
    pin_index: 3
    ev_id: 31
    vi_id: 36
  }
}
infos {
  cmd_id: 128
  element: PIN
  edit_type: SET
  pin {
    mod_id: 17
    task_id: 18
    fb_id: 20
    pin_index: 4
    pin_val {
      t: T_INT32
      v {
        i: 0
      }
      tm: 1683613033469692586
    }
  }
}
infos {
  cmd_id: 129
  element: PIN
  edit_type: SET
  pin {
    mod_id: 17
    task_id: 18
    fb_id: 21
    pin_index: 4
    pin_val {
      t: T_INT32
      v {
        i: 1
      }
      tm: 1683613037693492123
    }
  }
}
infos {
  cmd_id: 130
  element: PIN
  edit_type: SET
  pin {
    mod_id: 17
    task_id: 18
    fb_id: 22
    pin_index: 4
    pin_val {
      t: T_INT32
      v {
        i: 2
      }
      tm: 1683613039925748169
    }
  }
}
infos {
  cmd_id: 131
  element: PIN
  edit_type: SET
  pin {
    mod_id: 17
    task_id: 18
    fb_id: 23
    pin_index: 4
    pin_val {
      t: T_INT32
      v {
        i: 0
      }
      tm: 1683613046117679709
    }
  }
}
infos {
  cmd_id: 132
  element: VI
  edit_type: ADD
  vi {
    mod_id: 17
    task_id: 18
    fb_id: 23
    pin_index: 3
    ev_id: 31
    vi_id: 37
  }
}
infos {
  cmd_id: 133
  element: PIN
  edit_type: SET
  pin {
    mod_id: 17
    task_id: 18
    fb_id: 27
    pin_index: 4
    pin_val {
      t: T_INT32
      v {
        i: 3
      }
      tm: 1683613074917975211
    }
  }
}
infos {
  cmd_id: 134
  element: PIN
  edit_type: SET
  pin {
    mod_id: 17
    task_id: 18
    fb_id: 28
    pin_index: 4
    pin_val {
      t: T_INT32
      v {
        i: 0
      }
      tm: 1683613079501703550
    }
  }
}
infos {
  cmd_id: 135
  element: PIN
  edit_type: SET
  pin {
    mod_id: 17
    task_id: 18
    fb_id: 28
    pin_index: 4
    pin_val {
      t: T_INT32
      v {
        i: 2
      }
      tm: 1683613092941908409
    }
  }
}
infos {
  cmd_id: 142
  element: FB
  edit_type: ADD
  fb {
    mod_id: 17
    task_id: 18
    fb_id: 38
    flib_name: "Devices"
    fc_name: "SIM_READ"
  }
  pos {
    x: 9
    y: 114
  }
}
infos {
  cmd_id: 151
  element: FB
  edit_type: MV
  fb {
    mod_id: 17
    task_id: 18
    fb_id: 20
  }
  pos {
    x: 22
    y: 81
  }
}
infos {
  cmd_id: 180
  element: EV
  edit_type: ADD
  ev {
    ev_id: 39
    ev_name: "Speed"
    ev_type: 7
    ev_desc: "Desc"
    init_val {
      t: T_FLOAT64
      v {
        d: 0
      }
      tm: 1683613199794453667
    }
  }
}
infos {
  cmd_id: 181
  element: PIN
  edit_type: SET
  pin {
    mod_id: 17
    task_id: 18
    fb_id: 38
    pin_index: 1
    pin_val {
      t: T_STRING
      v {
        str: "SIM"
      }
      tm: 1683613217058868402
    }
  }
}
infos {
  cmd_id: 182
  element: PIN
  edit_type: SET
  pin {
    mod_id: 17
    task_id: 18
    fb_id: 38
    pin_index: 4
    pin_val {
      t: T_STRING
      v {
        str: "$SECOND"
      }
      tm: 1683613224274643661
    }
  }
}
infos {
  cmd_id: 183
  element: VO
  edit_type: ADD
  vo {
    mod_id: 17
    task_id: 18
    fb_id: 38
    pin_index: 3
    ev_id: 39
    vo_id: 40
  }
}
infos {
  cmd_id: 196
  element: EV
  edit_type: ADD
  ev {
    ev_id: 41
    ev_name: "AutoMod"
    ev_type: 1
    ev_desc: "Desc"
    init_val {
      t: T_BOOL
      v {
        b: true
      }
      tm: 1683613280382995313
    }
  }
}
infos {
  cmd_id: 197
  element: EV
  edit_type: SET
  ev {
    ev_id: 41
    ev_name: "AutoMode"
    ev_type: 1
    ev_desc: "Desc"
    init_val {
      t: T_BOOL
      v {
        b: true
      }
      tm: 1683613288023001064
    }
  }
}
infos {
  cmd_id: 219
  element: FB
  edit_type: ADD
  fb {
    mod_id: 17
    task_id: 18
    fb_id: 42
    flib_name: "Comparison"
    fc_name: "GT_DOUBLE"
  }
  pos {
    x: 61
    y: 53
  }
}
infos {
  cmd_id: 222
  element: VI
  edit_type: ADD
  vi {
    mod_id: 17
    task_id: 18
    fb_id: 42
    pin_index: 1
    ev_id: 39
    vi_id: 43
  }
}
infos {
  cmd_id: 223
  element: PIN
  edit_type: SET
  pin {
    mod_id: 17
    task_id: 18
    fb_id: 42
    pin_index: 2
    pin_val {
      t: T_FLOAT64
      v {
        d: 0
      }
      tm: 1683613493827506822
    }
  }
}
infos {
  cmd_id: 225
  element: FB
  edit_type: ADD
  fb {
    mod_id: 17
    task_id: 18
    fb_id: 44
    flib_name: "Comparison"
    fc_name: "LE_DOUBLE"
  }
  pos {
    x: 54
    y: 65
  }
}
infos {
  cmd_id: 229
  element: VI
  edit_type: ADD
  vi {
    mod_id: 17
    task_id: 18
    fb_id: 44
    pin_index: 1
    ev_id: 39
    vi_id: 45
  }
}
infos {
  cmd_id: 230
  element: PIN
  edit_type: SET
  pin {
    mod_id: 17
    task_id: 18
    fb_id: 44
    pin_index: 2
    pin_val {
      t: T_FLOAT64
      v {
        d: 10
      }
      tm: 1683613515363607585
    }
  }
}
infos {
  cmd_id: 231
  element: FB
  edit_type: ADD
  fb {
    mod_id: 17
    task_id: 18
    fb_id: 46
    flib_name: "Logic"
    fc_name: "AND"
  }
  pos {
    x: 81
    y: 55
  }
}
infos {
  cmd_id: 232
  element: FB
  edit_type: MV
  fb {
    mod_id: 17
    task_id: 18
    fb_id: 46
  }
  pos {
    x: 79
    y: 52
  }
}
infos {
  cmd_id: 233
  element: FB
  edit_type: RM
  fb {
    mod_id: 17
    task_id: 18
    fb_id: 46
  }
}
infos {
  cmd_id: 234
  element: FB
  edit_type: ADD
  fb {
    mod_id: 17
    task_id: 18
    fb_id: 47
    flib_name: "Logic"
    fc_name: "AND4"
  }
  pos {
    x: 85
    y: 55
  }
}
infos {
  cmd_id: 236
  element: LK
  edit_type: ADD
  lk {
    mod_id: 17
    task_id: 18
    lk_id: 48
    src_fb_id: 42
    src_pin_index: 1
    target_fb_id: 47
    target_pin_index: 1
  }
  pos {
    x: 69
    y: 54
  }
  pos {
    x: 74
    y: 54
  }
  pos {
    x: 74
    y: 56
  }
  pos {
    x: 79
    y: 56
  }
}
infos {
  cmd_id: 237
  element: LK
  edit_type: ADD
  lk {
    mod_id: 17
    task_id: 18
    lk_id: 49
    src_fb_id: 44
    src_pin_index: 1
    target_fb_id: 47
    target_pin_index: 2
  }
  pos {
    x: 69
    y: 68
  }
  pos {
    x: 74
    y: 68
  }
  pos {
    x: 74
    y: 58
  }
  pos {
    x: 79
    y: 58
  }
}
infos {
  cmd_id: 238
  element: PIN
  edit_type: SET
  pin {
    mod_id: 17
    task_id: 18
    fb_id: 47
    pin_index: 3
    pin_val {
      t: T_BOOL
      v {
        b: true
      }
      tm: 1683613549524261631
    }
  }
}
infos {
  cmd_id: 239
  element: PIN
  edit_type: SET
  pin {
    mod_id: 17
    task_id: 18
    fb_id: 47
    pin_index: 4
    pin_val {
      t: T_BOOL
      v {
        b: true
      }
      tm: 1683613551236370760
    }
  }
}
infos {
  cmd_id: 240
  element: LK
  edit_type: ADD
  lk {
    mod_id: 17
    task_id: 18
    lk_id: 50
    src_fb_id: 47
    src_pin_index: 1
    target_fb_id: 21
    target_pin_index: 1
  }
  pos {
    x: 98
    y: 56
  }
  pos {
    x: 84
    y: 56
  }
  pos {
    x: 84
    y: 86
  }
  pos {
    x: 71
    y: 86
  }
}
infos {
  cmd_id: 254
  element: FB
  edit_type: MV
  fb {
    mod_id: 17
    task_id: 18
    fb_id: 19
  }
  pos {
    x: 11
    y: 1
  }
}
infos {
  cmd_id: 255
  element: FB
  edit_type: MV
  fb {
    mod_id: 17
    task_id: 18
    fb_id: 38
  }
  pos {
    x: 62
  }
}
infos {
  cmd_id: 300
  element: VI
  edit_type: ADD
  vi {
    mod_id: 17
    task_id: 18
    fb_id: 47
    pin_index: 3
    ev_id: 41
    vi_id: 51
  }
}
infos {
  cmd_id: 313
  element: FB
  edit_type: MV
  fb {
    mod_id: 17
    task_id: 18
    fb_id: 47
  }
  pos {
    x: 50
    y: 52
  }
}
infos {
  cmd_id: 314
  element: LK
  edit_type: MV
  lk {
    mod_id: 17
    task_id: 18
    lk_id: 48
  }
  pos {
    x: 36
    y: 49
  }
  pos {
    x: 46
    y: 49
  }
  pos {
    x: 46
    y: 59
  }
  pos {
    x: 50
    y: 59
  }
}
infos {
  cmd_id: 315
  element: LK
  edit_type: MV
  lk {
    mod_id: 17
    task_id: 18
    lk_id: 49
  }
  pos {
    x: 36
    y: 61
  }
  pos {
    x: 50
    y: 61
  }
}
infos {
  cmd_id: 318
  element: FB
  edit_type: ADD
  fb {
    mod_id: 17
    task_id: 18
    fb_id: 52
    flib_name: "Logic"
    fc_name: "NOT"
  }
  pos {
    x: 91
    y: 105
  }
}
infos {
  cmd_id: 322
  element: LK
  edit_type: ADD
  lk {
    mod_id: 17
    task_id: 18
    lk_id: 53
    src_fb_id: 47
    src_pin_index: 1
    target_fb_id: 52
    target_pin_index: 1
  }
  pos {
    x: 69
    y: 59
  }
  pos {
    x: 77
    y: 59
  }
}
infos {
  cmd_id: 343
  element: LK
  edit_type: ADD
  lk {
    mod_id: 17
    task_id: 18
    lk_id: 54
    src_fb_id: 52
    src_pin_index: 1
    target_fb_id: 27
    target_pin_index: 1
  }
  pos {
    x: 95
    y: 59
  }
  pos {
    x: 106
    y: 59
  }
  pos {
    x: 106
    y: 112
  }
  pos {
    x: 118
    y: 112
  }
}
infos {
  cmd_id: 367
  element: FB
  edit_type: ADD
  fb {
    mod_id: 17
    task_id: 18
    fb_id: 55
    flib_name: "Comparison"
    fc_name: "GT_DOUBLE"
  }
  pos {
    x: 17
    y: 42
  }
}
infos {
  cmd_id: 368
  element: FB
  edit_type: ADD
  fb {
    mod_id: 17
    task_id: 18
    fb_id: 56
    flib_name: "Comparison"
    fc_name: "LE_DOUBLE"
  }
  pos {
    x: 17
    y: 54
  }
}
infos {
  cmd_id: 371
  element: FB
  edit_type: MV
  fb {
    mod_id: 17
    task_id: 18
    fb_id: 55
  }
  pos {
    x: 122
    y: 42
  }
}
infos {
  cmd_id: 372
  element: FB
  edit_type: MV
  fb {
    mod_id: 17
    task_id: 18
    fb_id: 56
  }
  pos {
    x: 122
    y: 54
  }
}
infos {
  cmd_id: 373
  element: VI
  edit_type: ADD
  vi {
    mod_id: 17
    task_id: 18
    fb_id: 55
    pin_index: 1
    ev_id: 39
    vi_id: 57
  }
}
infos {
  cmd_id: 374
  element: VI
  edit_type: ADD
  vi {
    mod_id: 17
    task_id: 18
    fb_id: 56
    pin_index: 1
    ev_id: 39
    vi_id: 58
  }
}
infos {
  cmd_id: 375
  element: PIN
  edit_type: SET
  pin {
    mod_id: 17
    task_id: 18
    fb_id: 55
    pin_index: 2
    pin_val {
      t: T_FLOAT64
      v {
        d: 10
      }
      tm: 1683613762703933478
    }
  }
}
infos {
  cmd_id: 376
  element: PIN
  edit_type: SET
  pin {
    mod_id: 17
    task_id: 18
    fb_id: 56
    pin_index: 2
    pin_val {
      t: T_FLOAT64
      v {
        d: 40
      }
      tm: 1683613767856305868
    }
  }
}
infos {
  cmd_id: 377
  element: FB
  edit_type: ADD
  fb {
    mod_id: 17
    task_id: 18
    fb_id: 59
    flib_name: "Logic"
    fc_name: "AND"
  }
  pos {
    x: 154
    y: 50
  }
}
infos {
  cmd_id: 378
  element: LK
  edit_type: ADD
  lk {
    mod_id: 17
    task_id: 18
    lk_id: 60
    src_fb_id: 55
    src_pin_index: 1
    target_fb_id: 59
    target_pin_index: 1
  }
  pos {
    x: 141
    y: 49
  }
  pos {
    x: 147
    y: 49
  }
  pos {
    x: 147
    y: 57
  }
  pos {
    x: 154
    y: 57
  }
}
infos {
  cmd_id: 379
  element: LK
  edit_type: ADD
  lk {
    mod_id: 17
    task_id: 18
    lk_id: 61
    src_fb_id: 56
    src_pin_index: 1
    target_fb_id: 59
    target_pin_index: 2
  }
  pos {
    x: 141
    y: 61
  }
  pos {
    x: 147
    y: 61
  }
  pos {
    x: 147
    y: 59
  }
  pos {
    x: 154
    y: 59
  }
}
infos {
  cmd_id: 380
  element: FB
  edit_type: MV
  fb {
    mod_id: 17
    task_id: 18
    fb_id: 22
  }
  pos {
    x: 153
    y: 76
  }
}
infos {
  cmd_id: 385
  element: EV
  edit_type: ADD
  ev {
    ev_id: 62
    ev_name: "Condition2"
    ev_type: 1
    ev_desc: "Desc"
    init_val {
      t: T_BOOL
      v {
        b: true
      }
      tm: 1683613833164956010
    }
  }
}
infos {
  cmd_id: 386
  element: VO
  edit_type: ADD
  vo {
    mod_id: 17
    task_id: 18
    fb_id: 59
    pin_index: 1
    ev_id: 62
    vo_id: 63
  }
}
infos {
  cmd_id: 387
  element: VI
  edit_type: ADD
  vi {
    mod_id: 17
    task_id: 18
    fb_id: 22
    pin_index: 1
    ev_id: 62
    vi_id: 64
  }
}
infos {
  cmd_id: 388
  element: FB
  edit_type: ADD
  fb {
    mod_id: 17
    task_id: 18
    fb_id: 65
    flib_name: "Comparison"
    fc_name: "GT_DOUBLE"
  }
  pos {
    x: 122
    y: 42
  }
}
infos {
  cmd_id: 392
  element: FB
  edit_type: MV
  fb {
    mod_id: 17
    task_id: 18
    fb_id: 23
  }
  pos {
    x: 228
    y: 74
  }
}
infos {
  cmd_id: 393
  element: LK
  edit_type: MV
  lk {
    mod_id: 17
    task_id: 18
    lk_id: 26
  }
  pos {
    x: 174
    y: 83
  }
  pos {
    x: 228
    y: 83
  }
}
infos {
  cmd_id: 394
  element: FB
  edit_type: MV
  fb {
    mod_id: 17
    task_id: 18
    fb_id: 65
  }
  pos {
    x: 193
    y: 59
  }
}
infos {
  cmd_id: 395
  element: VI
  edit_type: ADD
  vi {
    mod_id: 17
    task_id: 18
    fb_id: 65
    pin_index: 1
    ev_id: 39
    vi_id: 66
  }
}
infos {
  cmd_id: 396
  element: PIN
  edit_type: SET
  pin {
    mod_id: 17
    task_id: 18
    fb_id: 65
    pin_index: 2
    pin_val {
      t: T_FLOAT64
      v {
        d: 40
      }
      tm: 1683613872661866226
    }
  }
}
infos {
  cmd_id: 397
  element: LK
  edit_type: ADD
  lk {
    mod_id: 17
    task_id: 18
    lk_id: 67
    src_fb_id: 65
    src_pin_index: 1
    target_fb_id: 23
    target_pin_index: 1
  }
  pos {
    x: 212
    y: 66
  }
  pos {
    x: 220
    y: 66
  }
  pos {
    x: 220
    y: 81
  }
  pos {
    x: 228
    y: 81
  }
}
infos {
  cmd_id: 398
  element: VI
  edit_type: ADD
  vi {
    mod_id: 17
    task_id: 18
    fb_id: 28
    pin_index: 1
    ev_id: 62
    vi_id: 68
  }
}
infos {
  cmd_id: 399
  element: PIN
  edit_type: SET
  pin {
    mod_id: 17
    task_id: 18
    fb_id: 20
    pin_index: 1
    pin_val {
      t: T_BOOL
      v {
        b: true
      }
      tm: 1683613924358495007
    }
  }
}
infos {
  cmd_id: 400
  element: PIN
  edit_type: SET
  pin {
    mod_id: 17
    task_id: 18
    fb_id: 20
    pin_index: 2
    pin_val {
      t: T_BOOL
      v {
        b: true
      }
      tm: 1683613927162136534
    }
  }
}
infos {
  cmd_id: 401
  element: FB
  edit_type: ADD
  fb {
    mod_id: 17
    task_id: 18
    fb_id: 69
    flib_name: "Arithmetic"
    fc_name: "MOVE_BOOL"
  }
  pos {
    x: 26
    y: 124
  }
}
infos {
  cmd_id: 402
  element: VO
  edit_type: ADD
  vo {
    mod_id: 17
    task_id: 18
    fb_id: 69
    pin_index: 1
    ev_id: 41
    vo_id: 70
  }
}
infos {
  cmd_id: 403
  element: PIN
  edit_type: SET
  pin {
    mod_id: 17
    task_id: 18
    fb_id: 20
    pin_index: 1
    pin_val {
      t: T_BOOL
      v {
        b: false
      }
      tm: 1683615511495657847
    }
  }
}
infos {
  cmd_id: 404
  element: PIN
  edit_type: SET
  pin {
    mod_id: 17
    task_id: 18
    fb_id: 20
    pin_index: 2
    pin_val {
      t: T_BOOL
      v {
        b: false
      }
      tm: 1683615564695033713
    }
  }
}
infos {
  cmd_id: 405
  element: PIN
  edit_type: SET
  pin {
    mod_id: 17
    task_id: 18
    fb_id: 20
    pin_index: 1
    pin_val {
      t: T_BOOL
      v {
        b: true
      }
      tm: 1683615568902996375
    }
  }
}
infos {
  cmd_id: 409
  element: FB
  edit_type: MV
  fb {
    mod_id: 17
    task_id: 18
    fb_id: 52
  }
  pos {
    x: 74
    y: 101
  }
}
infos {
  cmd_id: 410
  element: LK
  edit_type: MV
  lk {
    mod_id: 17
    task_id: 18
    lk_id: 53
  }
  pos {
    x: 69
    y: 59
  }
  pos {
    x: 69
    y: 108
  }
  pos {
    x: 74
    y: 108
  }
}
infos {
  cmd_id: 412
  element: LK
  edit_type: MV
  lk {
    mod_id: 17
    task_id: 18
    lk_id: 50
  }
  pos {
    x: 69
    y: 59
  }
  pos {
    x: 69
    y: 86
  }
  pos {
    x: 79
    y: 86
  }
}
infos {
  cmd_id: 421
  element: FB
  edit_type: MV
  fb {
    mod_id: 17
    task_id: 18
    fb_id: 27
  }
  pos {
    x: 117
    y: 107
  }
}
infos {
  cmd_id: 423
  element: LK
  edit_type: MV
  lk {
    mod_id: 17
    task_id: 18
    lk_id: 30
  }
  pos {
    x: 43
    y: 88
  }
  pos {
    x: 51
    y: 88
  }
  pos {
    x: 51
    y: 116
  }
  pos {
    x: 117
    y: 116
  }
}
infos {
  cmd_id: 424
  element: LK
  edit_type: MV
  lk {
    mod_id: 17
    task_id: 18
    lk_id: 54
  }
  pos {
    x: 92
    y: 108
  }
  pos {
    x: 92
    y: 114
  }
  pos {
    x: 117
    y: 114
  }
}
infos {
  cmd_id: 425
  element: VI
  edit_type: RM
  vi {
    mod_id: 17
    task_id: 18
    fb_id: 47
    pin_index: 3
    ev_id: 41
    vi_id: 51
  }
}
infos {
  cmd_id: 426
  element: LK
  edit_type: RM
  lk {
    mod_id: 17
    task_id: 18
    lk_id: 53
  }
}
infos {
  cmd_id: 427
  element: LK
  edit_type: RM
  lk {
    mod_id: 17
    task_id: 18
    lk_id: 50
  }
}
infos {
  cmd_id: 428
  element: LK
  edit_type: RM
  lk {
    mod_id: 17
    task_id: 18
    lk_id: 49
  }
}
infos {
  cmd_id: 429
  element: LK
  edit_type: RM
  lk {
    mod_id: 17
    task_id: 18
    lk_id: 48
  }
}
infos {
  cmd_id: 430
  element: FB
  edit_type: RM
  fb {
    mod_id: 17
    task_id: 18
    fb_id: 47
  }
}
infos {
  cmd_id: 431
  element: FB
  edit_type: ADD
  fb {
    mod_id: 17
    task_id: 18
    fb_id: 71
    flib_name: "Logic"
    fc_name: "AND"
  }
  pos {
    x: 49
    y: 50
  }
}
infos {
  cmd_id: 432
  element: LK
  edit_type: ADD
  lk {
    mod_id: 17
    task_id: 18
    lk_id: 72
    src_fb_id: 42
    src_pin_index: 1
    target_fb_id: 71
    target_pin_index: 1
  }
  pos {
    x: 36
    y: 49
  }
  pos {
    x: 42
    y: 49
  }
  pos {
    x: 42
    y: 57
  }
  pos {
    x: 49
    y: 57
  }
}
infos {
  cmd_id: 433
  element: LK
  edit_type: ADD
  lk {
    mod_id: 17
    task_id: 18
    lk_id: 73
    src_fb_id: 44
    src_pin_index: 1
    target_fb_id: 71
    target_pin_index: 2
  }
  pos {
    x: 36
    y: 61
  }
  pos {
    x: 42
    y: 61
  }
  pos {
    x: 42
    y: 59
  }
  pos {
    x: 49
    y: 59
  }
}
infos {
  cmd_id: 440
  element: FB
  edit_type: ADD
  fb {
    mod_id: 17
    task_id: 18
    fb_id: 74
    flib_name: "Logic"
    fc_name: "AND"
  }
  pos {
    x: 75
    y: 61
  }
}
infos {
  cmd_id: 441
  element: LK
  edit_type: ADD
  lk {
    mod_id: 17
    task_id: 18
    lk_id: 75
    src_fb_id: 71
    src_pin_index: 1
    target_fb_id: 74
    target_pin_index: 1
  }
  pos {
    x: 63
    y: 56
  }
  pos {
    x: 69
    y: 56
  }
  pos {
    x: 69
    y: 68
  }
  pos {
    x: 75
    y: 68
  }
}
infos {
  cmd_id: 442
  element: VI
  edit_type: ADD
  vi {
    mod_id: 17
    task_id: 18
    fb_id: 74
    pin_index: 2
    ev_id: 41
    vi_id: 76
  }
}
infos {
  cmd_id: 459
  element: LK
  edit_type: ADD
  lk {
    mod_id: 17
    task_id: 18
    lk_id: 77
    src_fb_id: 74
    src_pin_index: 1
    target_fb_id: 21
    target_pin_index: 1
  }
  pos {
    x: 78
    y: 55
  }
  pos {
    x: 78
    y: 86
  }
  pos {
    x: 79
    y: 86
  }
}
infos {
  cmd_id: 466
  element: FB
  edit_type: ADD
  fb {
    mod_id: 17
    task_id: 18
    fb_id: 78
    flib_name: "Logic"
    fc_name: "AND"
  }
  pos {
    x: 49
    y: 70
  }
}
infos {
  cmd_id: 467
  element: LK
  edit_type: ADD
  lk {
    mod_id: 17
    task_id: 18
    lk_id: 79
    src_fb_id: 71
    src_pin_index: 1
    target_fb_id: 78
    target_pin_index: 1
  }
  pos {
    x: 46
    y: 48
  }
  pos {
    x: 47
    y: 48
  }
  pos {
    x: 47
    y: 77
  }
  pos {
    x: 49
    y: 77
  }
}
infos {
  cmd_id: 470
  element: FB
  edit_type: ADD
  fb {
    mod_id: 17
    task_id: 18
    fb_id: 80
    flib_name: "Logic"
    fc_name: "NOT"
  }
  pos {
    x: 36
    y: 73
  }
}
infos {
  cmd_id: 478
  element: FB
  edit_type: MV
  fb {
    mod_id: 17
    task_id: 18
    fb_id: 80
  }
  pos {
    x: 26
    y: 66
  }
}
infos {
  cmd_id: 479
  element: VI
  edit_type: ADD
  vi {
    mod_id: 17
    task_id: 18
    fb_id: 80
    pin_index: 1
    ev_id: 41
    vi_id: 81
  }
}
infos {
  cmd_id: 480
  element: LK
  edit_type: ADD
  lk {
    mod_id: 17
    task_id: 18
    lk_id: 82
    src_fb_id: 80
    src_pin_index: 1
    target_fb_id: 78
    target_pin_index: 2
  }
  pos {
    x: 44
    y: 73
  }
  pos {
    x: 48
    y: 73
  }
  pos {
    x: 48
    y: 72
  }
  pos {
    x: 53
    y: 72
  }
}
infos {
  cmd_id: 481
  element: LK
  edit_type: RM
  lk {
    mod_id: 17
    task_id: 18
    lk_id: 54
  }
}
infos {
  cmd_id: 482
  element: FB
  edit_type: RM
  fb {
    mod_id: 17
    task_id: 18
    fb_id: 52
  }
}
infos {
  cmd_id: 483
  element: LK
  edit_type: ADD
  lk {
    mod_id: 17
    task_id: 18
    lk_id: 83
    src_fb_id: 78
    src_pin_index: 1
    target_fb_id: 27
    target_pin_index: 1
  }
  pos {
    x: 72
    y: 70
  }
  pos {
    x: 94
    y: 70
  }
  pos {
    x: 94
    y: 114
  }
  pos {
    x: 117
    y: 114
  }
}
infos {
  cmd_id: 485
  element: TASK
  edit_type: ADD
  task {
    task_type: ASYNC
    mod_id: 17
    task_id: 84
    task_name: "Task_1"
    interval: 1000
  }
}
infos {
  cmd_id: 486
  element: TASK
  edit_type: ADD
  task {
    task_type: ASYNC
    mod_id: 17
    task_id: 85
    task_name: "Task_2"
    interval: 1000
  }
}
infos {
  cmd_id: 487
  element: TASK
  edit_type: ADD
  task {
    task_type: ASYNC
    mod_id: 17
    task_id: 86
    task_name: "Task_3"
    interval: 1000
  }
}
infos {
  cmd_id: 488
  element: TASK
  edit_type: ADD
  task {
    task_type: ASYNC
    mod_id: 17
    task_id: 87
    task_name: "Task_4"
    interval: 1000
  }
}
infos {
  cmd_id: 489
  element: TASK
  edit_type: ADD
  task {
    task_type: ASYNC
    mod_id: 17
    task_id: 88
    task_name: "Task_5"
    interval: 1000
  }
}
infos {
  cmd_id: 490
  element: TASK
  edit_type: ADD
  task {
    task_type: ASYNC
    mod_id: 17
    task_id: 89
    task_name: "Task_6"
    interval: 1000
  }
}
infos {
  cmd_id: 491
  element: FB
  edit_type: ADD
  fb {
    mod_id: 17
    task_id: 18
    fb_id: 90
    flib_name: "Task"
    fc_name: "TASK"
  }
  pos {
    x: 163
    y: 126
  }
}
infos {
  cmd_id: 492
  element: FB
  edit_type: ADD
  fb {
    mod_id: 17
    task_id: 18
    fb_id: 91
    flib_name: "Task"
    fc_name: "EVENT"
  }
  pos {
    x: 147
    y: 128
  }
}
infos {
  cmd_id: 496
  element: LK
  edit_type: ADD
  lk {
    mod_id: 17
    task_id: 18
    lk_id: 92
    src_fb_id: 27
    src_pin_index: 2
    target_fb_id: 91
    target_pin_index: 1
  }
  pos {
    x: 138
    y: 116
  }
  pos {
    x: 139
    y: 116
  }
  pos {
    x: 139
    y: 126
  }
  pos {
    x: 140
    y: 126
  }
}
infos {
  cmd_id: 499
  element: LK
  edit_type: ADD
  lk {
    mod_id: 17
    task_id: 18
    lk_id: 93
    src_fb_id: 91
    src_pin_index: 1
    target_fb_id: 90
    target_pin_index: 1
  }
  pos {
    x: 164
    y: 126
  }
  pos {
    x: 168
    y: 126
  }
  pos {
    x: 168
    y: 131
  }
  pos {
    x: 172
    y: 131
  }
}
infos {
  cmd_id: 505
  element: FB
  edit_type: MV
  fb {
    mod_id: 17
    task_id: 18
    fb_id: 91
  }
  pos {
    x: 140
    y: 131
  }
}
infos {
  cmd_id: 506
  element: LK
  edit_type: MV
  lk {
    mod_id: 17
    task_id: 18
    lk_id: 92
  }
  pos {
    x: 138
    y: 116
  }
  pos {
    x: 139
    y: 116
  }
  pos {
    x: 139
    y: 138
  }
  pos {
    x: 140
    y: 138
  }
}
infos {
  cmd_id: 508
  element: FB
  edit_type: MV
  fb {
    mod_id: 17
    task_id: 18
    fb_id: 90
  }
  pos {
    x: 173
    y: 131
  }
}
infos {
  cmd_id: 509
  element: LK
  edit_type: MV
  lk {
    mod_id: 17
    task_id: 18
    lk_id: 93
  }
  pos {
    x: 162
    y: 138
  }
  pos {
    x: 173
    y: 138
  }
}
infos {
  cmd_id: 510
  element: PIN
  edit_type: SET
  pin {
    mod_id: 17
    task_id: 18
    fb_id: 90
    pin_index: 2
    pin_val {
      t: T_STRING
      v {
        str: "Task"
      }
      tm: 1683687463591391792
    }
  }
}
infos {
  cmd_id: 511
  element: PIN
  edit_type: SET
  pin {
    mod_id: 17
    task_id: 18
    fb_id: 90
    pin_index: 3
    pin_val {
      t: T_STRING
      v {
        str: "Task_1"
      }
      tm: 1683687471506550610
    }
  }
}
infos {
  cmd_id: 512
  element: PIN
  edit_type: SET
  pin {
    mod_id: 17
    task_id: 18
    fb_id: 90
    pin_index: 4
    pin_val {
      t: T_TIME
      v {
        tm: 2000
      }
      tm: 1683687478145504940
    }
  }
}
infos {
  cmd_id: 513
  element: PIN
  edit_type: SET
  pin {
    mod_id: 17
    task_id: 18
    fb_id: 90
    pin_index: 5
    pin_val {
      t: T_BOOL
      v {
        b: true
      }
      tm: 1683687481378853657
    }
  }
}
infos {
  cmd_id: 516
  element: FB
  edit_type: MV
  fb {
    mod_id: 17
    task_id: 18
    fb_id: 28
  }
  pos {
    x: 181
    y: 105
  }
}
infos {
  cmd_id: 517
  element: LK
  edit_type: MV
  lk {
    mod_id: 17
    task_id: 18
    lk_id: 29
  }
  pos {
    x: 138
    y: 114
  }
  pos {
    x: 181
    y: 114
  }
}
infos {
  cmd_id: 518
  element: FB
  edit_type: ADD
  fb {
    mod_id: 17
    task_id: 18
    fb_id: 94
    flib_name: "Task"
    fc_name: "TASK"
  }
  pos {
    x: 173
    y: 131
  }
}
infos {
  cmd_id: 521
  element: LK
  edit_type: ADD
  lk {
    mod_id: 17
    task_id: 18
    lk_id: 95
    src_fb_id: 90
    src_pin_index: 1
    target_fb_id: 94
    target_pin_index: 1
  }
  pos {
    x: 200
    y: 138
  }
  pos {
    x: 205
    y: 138
  }
  pos {
    x: 205
    y: 136
  }
  pos {
    x: 211
    y: 136
  }
}
infos {
  cmd_id: 524
  element: PIN
  edit_type: SET
  pin {
    mod_id: 17
    task_id: 18
    fb_id: 94
    pin_index: 2
    pin_val {
      t: T_STRING
      v {
        str: "Task"
      }
      tm: 1683687502307593047
    }
  }
}
infos {
  cmd_id: 525
  element: PIN
  edit_type: SET
  pin {
    mod_id: 17
    task_id: 18
    fb_id: 94
    pin_index: 3
    pin_val {
      t: T_STRING
      v {
        str: "Task_2"
      }
      tm: 1683687510070138944
    }
  }
}
infos {
  cmd_id: 526
  element: PIN
  edit_type: SET
  pin {
    mod_id: 17
    task_id: 18
    fb_id: 94
    pin_index: 4
    pin_val {
      t: T_TIME
      v {
        tm: 1000
      }
      tm: 1683687514672015866
    }
  }
}
infos {
  cmd_id: 527
  element: PIN
  edit_type: SET
  pin {
    mod_id: 17
    task_id: 18
    fb_id: 94
    pin_index: 5
    pin_val {
      t: T_BOOL
      v {
        b: true
      }
      tm: 1683687516656833695
    }
  }
}
infos {
  cmd_id: 528
  element: FB
  edit_type: ADD
  fb {
    mod_id: 17
    task_id: 18
    fb_id: 96
    flib_name: "Task"
    fc_name: "EVENT"
  }
  pos {
    x: 140
    y: 131
  }
}
infos {
  cmd_id: 531
  element: LK
  edit_type: ADD
  lk {
    mod_id: 17
    task_id: 18
    lk_id: 97
    src_fb_id: 28
    src_pin_index: 2
    target_fb_id: 96
    target_pin_index: 1
  }
  pos {
    x: 202
    y: 114
  }
  pos {
    x: 210
    y: 114
  }
  pos {
    x: 210
    y: 113
  }
  pos {
    x: 218
    y: 113
  }
}
infos {
  cmd_id: 532
  element: FB
  edit_type: MV
  fb {
    mod_id: 17
    task_id: 18
    fb_id: 96
  }
  pos {
    x: 219
    y: 107
  }
}
infos {
  cmd_id: 533
  element: LK
  edit_type: MV
  lk {
    mod_id: 17
    task_id: 18
    lk_id: 97
  }
  pos {
    x: 202
    y: 114
  }
  pos {
    x: 219
    y: 114
  }
}
infos {
  cmd_id: 534
  element: FB
  edit_type: ADD
  fb {
    mod_id: 17
    task_id: 18
    fb_id: 98
    flib_name: "Task"
    fc_name: "TASK"
  }
  pos {
    x: 211
    y: 131
  }
}
infos {
  cmd_id: 536
  element: LK
  edit_type: ADD
  lk {
    mod_id: 17
    task_id: 18
    lk_id: 99
    src_fb_id: 96
    src_pin_index: 1
    target_fb_id: 98
    target_pin_index: 1
  }
  pos {
    x: 241
    y: 114
  }
  pos {
    x: 244
    y: 114
  }
  pos {
    x: 244
    y: 112
  }
  pos {
    x: 248
    y: 112
  }
}
infos {
  cmd_id: 537
  element: FB
  edit_type: MV
  fb {
    mod_id: 17
    task_id: 18
    fb_id: 98
  }
  pos {
    x: 249
    y: 109
  }
}
infos {
  cmd_id: 538
  element: LK
  edit_type: MV
  lk {
    mod_id: 17
    task_id: 18
    lk_id: 99
  }
  pos {
    x: 241
    y: 114
  }
  pos {
    x: 244
    y: 114
  }
  pos {
    x: 244
    y: 116
  }
  pos {
    x: 249
    y: 116
  }
}
infos {
  cmd_id: 539
  element: PIN
  edit_type: SET
  pin {
    mod_id: 17
    task_id: 18
    fb_id: 98
    pin_index: 2
    pin_val {
      t: T_STRING
      v {
        str: "Task"
      }
      tm: 1683687546318220546
    }
  }
}
infos {
  cmd_id: 540
  element: PIN
  edit_type: SET
  pin {
    mod_id: 17
    task_id: 18
    fb_id: 98
    pin_index: 3
    pin_val {
      t: T_STRING
      v {
        str: "Task_3"
      }
      tm: 1683687552740420182
    }
  }
}
infos {
  cmd_id: 541
  element: PIN
  edit_type: SET
  pin {
    mod_id: 17
    task_id: 18
    fb_id: 98
    pin_index: 4
    pin_val {
      t: T_TIME
      v {
        tm: 2000
      }
      tm: 1683687557885781018
    }
  }
}
infos {
  cmd_id: 542
  element: PIN
  edit_type: SET
  pin {
    mod_id: 17
    task_id: 18
    fb_id: 98
    pin_index: 5
    pin_val {
      t: T_BOOL
      v {
        b: true
      }
      tm: 1683687563407145520
    }
  }
}
infos {
  cmd_id: 543
  element: FB
  edit_type: ADD
  fb {
    mod_id: 17
    task_id: 84
    fb_id: 100
    flib_name: "Task"
    fc_name: "TASK"
  }
  pos {
    x: 173
    y: 131
  }
}
infos {
  cmd_id: 544
  element: FB
  edit_type: ADD
  fb {
    mod_id: 17
    task_id: 84
    fb_id: 101
    flib_name: "Task"
    fc_name: "TASK"
  }
  pos {
    x: 211
    y: 131
  }
}
infos {
  cmd_id: 545
  element: LK
  edit_type: ADD
  lk {
    mod_id: 17
    task_id: 84
    lk_id: 102
    src_fb_id: 100
    src_pin_index: 1
    target_fb_id: 101
    target_pin_index: 1
  }
  pos {
    x: 200
    y: 138
  }
  pos {
    x: 211
    y: 138
  }
}
infos {
  cmd_id: 549
  element: PIN
  edit_type: SET
  pin {
    mod_id: 17
    task_id: 84
    fb_id: 100
    pin_index: 2
    pin_val {
      t: T_STRING
      v {
        str: "Task"
      }
      tm: 1683687587933608455
    }
  }
}
infos {
  cmd_id: 550
  element: PIN
  edit_type: SET
  pin {
    mod_id: 17
    task_id: 84
    fb_id: 100
    pin_index: 3
    pin_val {
      t: T_STRING
      v {
        str: "Task_4"
      }
      tm: 1683687593687246061
    }
  }
}
infos {
  cmd_id: 551
  element: PIN
  edit_type: SET
  pin {
    mod_id: 17
    task_id: 84
    fb_id: 101
    pin_index: 2
    pin_val {
      t: T_STRING
      v {
        str: "Task"
      }
      tm: 1683687601589319337
    }
  }
}
infos {
  cmd_id: 552
  element: PIN
  edit_type: SET
  pin {
    mod_id: 17
    task_id: 84
    fb_id: 101
    pin_index: 3
    pin_val {
      t: T_STRING
      v {
        str: "Task_5"
      }
      tm: 1683687609086809549
    }
  }
}
infos {
  cmd_id: 553
  element: PIN
  edit_type: SET
  pin {
    mod_id: 17
    task_id: 84
    fb_id: 100
    pin_index: 4
    pin_val {
      t: T_TIME
      v {
        tm: 1000
      }
      tm: 1683687614784288028
    }
  }
}
infos {
  cmd_id: 554
  element: PIN
  edit_type: SET
  pin {
    mod_id: 17
    task_id: 84
    fb_id: 101
    pin_index: 4
    pin_val {
      t: T_TIME
      v {
        tm: 1000
      }
      tm: 1683687618096726492
    }
  }
}
infos {
  cmd_id: 555
  element: PIN
  edit_type: SET
  pin {
    mod_id: 17
    task_id: 84
    fb_id: 100
    pin_index: 5
    pin_val {
      t: T_BOOL
      v {
        b: true
      }
      tm: 1683687634292392746
    }
  }
}
infos {
  cmd_id: 556
  element: PIN
  edit_type: SET
  pin {
    mod_id: 17
    task_id: 84
    fb_id: 101
    pin_index: 5
    pin_val {
      t: T_BOOL
      v {
        b: true
      }
      tm: 1683687636100817332
    }
  }
}
infos {
  cmd_id: 557
  element: FB
  edit_type: ADD
  fb {
    mod_id: 17
    task_id: 84
    fb_id: 103
    flib_name: "Task"
    fc_name: "TASK_STATE"
  }
  pos {
    x: 147
    y: 67
  }
}
infos {
  cmd_id: 559
  element: FB
  edit_type: ADD
  fb {
    mod_id: 17
    task_id: 85
    fb_id: 104
    flib_name: "Task"
    fc_name: "TASK_STATE"
  }
  pos {
    x: 163
    y: 72
  }
}
infos {
  cmd_id: 565
  element: FB
  edit_type: ADD
  fb {
    mod_id: 17
    task_id: 86
    fb_id: 105
    flib_name: "Task"
    fc_name: "TASK_STATE"
  }
  pos {
    x: 141
    y: 5
  }
}
infos {
  cmd_id: 566
  element: FB
  edit_type: ADD
  fb {
    mod_id: 17
    task_id: 87
    fb_id: 106
    flib_name: "Task"
    fc_name: "TASK_STATE"
  }
  pos {
    x: 141
    y: 5
  }
}
infos {
  cmd_id: 567
  element: FB
  edit_type: ADD
  fb {
    mod_id: 17
    task_id: 88
    fb_id: 107
    flib_name: "Task"
    fc_name: "TASK_STATE"
  }
  pos {
    x: 141
    y: 5
  }
}
infos {
  cmd_id: 568
  element: FB
  edit_type: ADD
  fb {
    mod_id: 17
    task_id: 89
    fb_id: 108
    flib_name: "Task"
    fc_name: "TASK_STATE"
  }
  pos {
    x: 141
    y: 5
  }
}
infos {
  cmd_id: 570
  element: FB
  edit_type: MV
  fb {
    mod_id: 17
    task_id: 85
    fb_id: 104
  }
  pos {
    x: 4
  }
}
infos {
  cmd_id: 577
  element: FB
  edit_type: MV
  fb {
    mod_id: 17
    task_id: 84
    fb_id: 103
  }
  pos {
    x: 4
    y: 1
  }
}
infos {
  cmd_id: 579
  element: FB
  edit_type: MV
  fb {
    mod_id: 17
    task_id: 87
    fb_id: 106
  }
  pos {
    x: 2
    y: 1
  }
}
infos {
  cmd_id: 580
  element: FB
  edit_type: MV
  fb {
    mod_id: 17
    task_id: 88
    fb_id: 107
  }
  pos {
    x: 3
  }
}
infos {
  cmd_id: 581
  element: FB
  edit_type: MV
  fb {
    mod_id: 17
    task_id: 89
    fb_id: 108
  }
  pos {
    x: 3
  }
}
infos {
  cmd_id: 582
  element: TASK
  edit_type: ADD
  task {
    task_type: ASYNC
    mod_id: 17
    task_id: 109
    task_name: "Task_7"
    interval: 1000
  }
}
infos {
  cmd_id: 583
  element: FB
  edit_type: ADD
  fb {
    mod_id: 17
    task_id: 109
    fb_id: 110
    flib_name: "Task"
    fc_name: "TASK_STATE"
  }
  pos {
    x: 3
  }
}
infos {
  cmd_id: 584
  element: FB
  edit_type: ADD
  fb {
    mod_id: 17
    task_id: 84
    fb_id: 111
    flib_name: "Task"
    fc_name: "TASK"
  }
  pos {
    x: 58
    y: 38
  }
}
infos {
  cmd_id: 586
  element: PIN
  edit_type: SET
  pin {
    mod_id: 17
    task_id: 84
    fb_id: 111
    pin_index: 1
    pin_val {
      t: T_BOOL
      v {
        b: true
      }
      tm: 1683687798835683815
    }
  }
}
infos {
  cmd_id: 587
  element: LK
  edit_type: ADD
  lk {
    mod_id: 17
    task_id: 84
    lk_id: 112
    src_fb_id: 100
    src_pin_index: 1
    target_fb_id: 111
    target_pin_index: 1
  }
  pos {
    x: 47
    y: 45
  }
  pos {
    x: 52
    y: 45
  }
  pos {
    x: 52
    y: 75
  }
  pos {
    x: 57
    y: 75
  }
}
infos {
  cmd_id: 588
  element: PIN
  edit_type: SET
  pin {
    mod_id: 17
    task_id: 84
    fb_id: 111
    pin_index: 2
    pin_val {
      t: T_STRING
      v {
        str: "Task"
      }
      tm: 1683687811425769836
    }
  }
}
infos {
  cmd_id: 589
  element: PIN
  edit_type: SET
  pin {
    mod_id: 17
    task_id: 84
    fb_id: 111
    pin_index: 3
    pin_val {
      t: T_STRING
      v {
        str: "Task_6"
      }
      tm: 1683687817246817042
    }
  }
}
infos {
  cmd_id: 590
  element: FB
  edit_type: ADD
  fb {
    mod_id: 17
    task_id: 85
    fb_id: 113
    flib_name: "Arithmetic"
    fc_name: "ADD_INT"
  }
  pos {
    x: 65
    y: 49
  }
}
infos {
  cmd_id: 591
  element: EV
  edit_type: ADD
  ev {
    ev_id: 114
    ev_name: "V_I_1"
    ev_type: 2
    ev_desc: "Desc"
    init_val {
      t: T_INT32
      v {
        i: 0
      }
      tm: 1683687859776163208
    }
  }
}
infos {
  cmd_id: 592
  element: VI
  edit_type: ADD
  vi {
    mod_id: 17
    task_id: 85
    fb_id: 113
    pin_index: 1
    ev_id: 114
    vi_id: 115
  }
}
infos {
  cmd_id: 593
  element: VO
  edit_type: ADD
  vo {
    mod_id: 17
    task_id: 85
    fb_id: 113
    pin_index: 1
    ev_id: 114
    vo_id: 116
  }
}
infos {
  cmd_id: 594
  element: PIN
  edit_type: SET
  pin {
    mod_id: 17
    task_id: 85
    fb_id: 113
    pin_index: 2
    pin_val {
      t: T_INT32
      v {
        i: 2
      }
      tm: 1683687868825231542
    }
  }
}
infos {
  cmd_id: 595
  element: FB
  edit_type: MV
  fb {
    mod_id: 17
    task_id: 85
    fb_id: 113
  }
  pos {
    x: 40
    y: 29
  }
}
infos {
  cmd_id: 596
  element: FB
  edit_type: MV
  fb {
    mod_id: 17
    task_id: 86
    fb_id: 105
  }
  pos {
    x: 3
  }
}
infos {
  cmd_id: 597
  element: FB
  edit_type: ADD
  fb {
    mod_id: 17
    task_id: 86
    fb_id: 117
    flib_name: "Devices"
    fc_name: "SIM_READ"
  }
  pos {
    x: 33
    y: 44
  }
}
infos {
  cmd_id: 598
  element: PIN
  edit_type: SET
  pin {
    mod_id: 17
    task_id: 86
    fb_id: 117
    pin_index: 1
    pin_val {
      t: T_STRING
      v {
        str: "SIM"
      }
      tm: 1683687903407771450
    }
  }
}
infos {
  cmd_id: 599
  element: PIN
  edit_type: SET
  pin {
    mod_id: 17
    task_id: 86
    fb_id: 117
    pin_index: 8
    pin_val {
      t: T_STRING
      v {
        str: "$SECOND"
      }
      tm: 1683687914522996191
    }
  }
}
infos {
  cmd_id: 600
  element: PIN
  edit_type: SET
  pin {
    mod_id: 17
    task_id: 86
    fb_id: 117
    pin_index: 9
    pin_val {
      t: T_STRING
      v {
        str: "$YEAR"
      }
      tm: 1683687922318570033
    }
  }
}
infos {
  cmd_id: 601
  element: FB
  edit_type: ADD
  fb {
    mod_id: 17
    task_id: 87
    fb_id: 118
    flib_name: "Arithmetic"
    fc_name: "ADD_INT"
  }
  pos {
    x: 40
    y: 29
  }
}
infos {
  cmd_id: 605
  element: VI
  edit_type: ADD
  vi {
    mod_id: 17
    task_id: 87
    fb_id: 118
    pin_index: 1
    ev_id: 31
    vi_id: 119
  }
}
infos {
  cmd_id: 606
  element: PIN
  edit_type: SET
  pin {
    mod_id: 17
    task_id: 87
    fb_id: 118
    pin_index: 2
    pin_val {
      t: T_INT32
      v {
        i: 2
      }
      tm: 1683687979609410215
    }
  }
}
infos {
  cmd_id: 607
  element: FB
  edit_type: MV
  fb {
    mod_id: 17
    task_id: 87
    fb_id: 118
  }
  pos {
    x: 34
    y: 34
  }
}
infos {
  cmd_id: 608
  element: EV
  edit_type: ADD
  ev {
    ev_id: 120
    ev_name: "V_I_2"
    ev_type: 2
    ev_desc: "Desc"
    init_val {
      t: T_INT32
      v {
        i: 0
      }
      tm: 1683688011830205490
    }
  }
}
infos {
  cmd_id: 609
  element: FB
  edit_type: ADD
  fb {
    mod_id: 17
    task_id: 88
    fb_id: 121
    flib_name: "Arithmetic"
    fc_name: "ADD_INT"
  }
  pos {
    x: 40
    y: 29
  }
}
infos {
  cmd_id: 611
  element: FB
  edit_type: ADD
  fb {
    mod_id: 17
    task_id: 88
    fb_id: 122
    flib_name: "Task"
    fc_name: "SLEEP"
  }
  pos {
    x: 31
    y: 37
  }
}
infos {
  cmd_id: 612
  element: FB
  edit_type: MV
  fb {
    mod_id: 17
    task_id: 88
    fb_id: 122
  }
  pos {
    x: 25
    y: 33
  }
}
infos {
  cmd_id: 613
  element: PIN
  edit_type: SET
  pin {
    mod_id: 17
    task_id: 88
    fb_id: 122
    pin_index: 2
    pin_val {
      t: T_TIME
      v {
        tm: 500
      }
      tm: 1683688033499085066
    }
  }
}
infos {
  cmd_id: 616
  element: LK
  edit_type: ADD
  lk {
    mod_id: 17
    task_id: 88
    lk_id: 123
    src_fb_id: 122
    src_pin_index: 1
    target_fb_id: 121
  }
  pos {
    x: 50
    y: 40
  }
  pos {
    x: 59
    y: 40
  }
  pos {
    x: 59
    y: 37
  }
  pos {
    x: 68
    y: 37
  }
}
infos {
  cmd_id: 621
  element: PIN
  edit_type: SET
  pin {
    mod_id: 17
    task_id: 88
    fb_id: 122
    pin_index: 1
    pin_val {
      t: T_BOOL
      v {
        b: true
      }
      tm: 1683688063778956104
    }
  }
}
infos {
  cmd_id: 623
  element: LK
  edit_type: MV
  lk {
    mod_id: 17
    task_id: 88
    lk_id: 123
  }
  pos {
    x: 50
    y: 40
  }
  pos {
    x: 68
    y: 40
  }
}
infos {
  cmd_id: 624
  element: LK
  edit_type: RM
  lk {
    mod_id: 17
    task_id: 88
    lk_id: 123
  }
}
infos {
  cmd_id: 627
  element: FB
  edit_type: ADD
  fb {
    mod_id: 17
    task_id: 89
    fb_id: 124
    flib_name: "Devices"
    fc_name: "SIM_READ"
  }
  pos {
    x: 33
    y: 44
  }
}
infos {
  cmd_id: 628
  element: PIN
  edit_type: SET
  pin {
    mod_id: 17
    task_id: 89
    fb_id: 124
    pin_index: 9
    pin_val {
      t: T_STRING
      v {
        str: "$SECOND"
      }
      tm: 1683688096836188735
    }
  }
}
infos {
  cmd_id: 629
  element: FB
  edit_type: ADD
  fb {
    mod_id: 17
    task_id: 89
    fb_id: 125
    flib_name: "Converter"
    fc_name: "D2F"
  }
  pos {
    x: 79
    y: 60
  }
}
infos {
  cmd_id: 630
  element: LK
  edit_type: ADD
  lk {
    mod_id: 17
    task_id: 89
    lk_id: 126
    src_fb_id: 124
    src_pin_index: 8
    target_fb_id: 125
    target_pin_index: 1
  }
  pos {
    x: 53
    y: 65
  }
  pos {
    x: 66
    y: 65
  }
  pos {
    x: 66
    y: 67
  }
  pos {
    x: 79
    y: 67
  }
}
infos {
  cmd_id: 633
  element: FB
  edit_type: MV
  fb {
    mod_id: 17
    task_id: 89
    fb_id: 125
  }
  pos {
    x: 67
    y: 46
  }
}
infos {
  cmd_id: 634
  element: LK
  edit_type: MV
  lk {
    mod_id: 17
    task_id: 89
    lk_id: 126
  }
  pos {
    x: 53
    y: 65
  }
  pos {
    x: 66
    y: 65
  }
  pos {
    x: 66
    y: 53
  }
  pos {
    x: 67
    y: 53
  }
}
infos {
  cmd_id: 635
  element: FB
  edit_type: ADD
  fb {
    mod_id: 17
    task_id: 89
    fb_id: 127
    flib_name: "Arithmetic"
    fc_name: "MOVE_DOUBLE"
  }
  pos {
    x: 107
    y: 50
  }
}
infos {
  cmd_id: 636
  element: FB
  edit_type: MV
  fb {
    mod_id: 17
    task_id: 89
    fb_id: 127
  }
  pos {
    x: 103
    y: 45
  }
}
infos {
  cmd_id: 637
  element: FB
  edit_type: RM
  fb {
    mod_id: 17
    task_id: 89
    fb_id: 127
  }
}
infos {
  cmd_id: 638
  element: FB
  edit_type: ADD
  fb {
    mod_id: 17
    task_id: 89
    fb_id: 128
    flib_name: "Arithmetic"
    fc_name: "MUL_FLOAT"
  }
  pos {
    x: 101
    y: 53
  }
}
infos {
  cmd_id: 639
  element: LK
  edit_type: ADD
  lk {
    mod_id: 17
    task_id: 89
    lk_id: 129
    src_fb_id: 125
    src_pin_index: 1
    target_fb_id: 128
    target_pin_index: 1
  }
  pos {
    x: 85
    y: 53
  }
  pos {
    x: 93
    y: 53
  }
  pos {
    x: 93
    y: 60
  }
  pos {
    x: 101
    y: 60
  }
}
infos {
  cmd_id: 640
  element: PIN
  edit_type: SET
  pin {
    mod_id: 17
    task_id: 89
    fb_id: 128
    pin_index: 2
    pin_val {
      t: T_FLOAT32
      v {
        f: 5.8
      }
      tm: 1683688188590374950
    }
  }
}
infos {
  cmd_id: 641
  element: FB
  edit_type: MV
  fb {
    mod_id: 17
    task_id: 89
    fb_id: 128
  }
  pos {
    x: 101
    y: 51
  }
}
infos {
  cmd_id: 642
  element: LK
  edit_type: MV
  lk {
    mod_id: 17
    task_id: 89
    lk_id: 129
  }
  pos {
    x: 85
    y: 53
  }
  pos {
    x: 93
    y: 53
  }
  pos {
    x: 93
    y: 58
  }
  pos {
    x: 101
    y: 58
  }
}
infos {
  cmd_id: 643
  element: FB
  edit_type: ADD
  fb {
    mod_id: 17
    task_id: 84
    fb_id: 130
    flib_name: "Task"
    fc_name: "TASK"
  }
  pos {
    x: 58
    y: 38
  }
}
infos {
  cmd_id: 645
  element: LK
  edit_type: ADD
  lk {
    mod_id: 17
    task_id: 84
    lk_id: 131
    src_fb_id: 101
    src_pin_index: 1
    target_fb_id: 130
    target_pin_index: 1
  }
  pos {
    x: 85
    y: 45
  }
  pos {
    x: 101
    y: 45
  }
  pos {
    x: 101
    y: 44
  }
  pos {
    x: 117
    y: 44
  }
}
infos {
  cmd_id: 650
  element: PIN
  edit_type: SET
  pin {
    mod_id: 17
    task_id: 84
    fb_id: 130
    pin_index: 2
    pin_val {
      t: T_STRING
      v {
        str: "Task"
      }
      tm: 1683688233697043460
    }
  }
}
infos {
  cmd_id: 651
  element: PIN
  edit_type: SET
  pin {
    mod_id: 17
    task_id: 84
    fb_id: 130
    pin_index: 3
    pin_val {
      t: T_STRING
      v {
        str: "Task_7"
      }
      tm: 1683688241050223945
    }
  }
}
infos {
  cmd_id: 652
  element: PIN
  edit_type: SET
  pin {
    mod_id: 17
    task_id: 84
    fb_id: 130
    pin_index: 4
    pin_val {
      t: T_TIME
      v {
        tm: 0
      }
      tm: 1683688244733889659
    }
  }
}
infos {
  cmd_id: 653
  element: PIN
  edit_type: SET
  pin {
    mod_id: 17
    task_id: 84
    fb_id: 130
    pin_index: 5
    pin_val {
      t: T_BOOL
      v {
        b: false
      }
      tm: 1683688246736098766
    }
  }
}
infos {
  cmd_id: 656
  element: FB
  edit_type: MV
  fb {
    mod_id: 17
    task_id: 18
    fb_id: 94
  }
  pos {
    x: 222
    y: 131
  }
}
infos {
  cmd_id: 657
  element: LK
  edit_type: MV
  lk {
    mod_id: 17
    task_id: 18
    lk_id: 95
  }
  pos {
    x: 200
    y: 138
  }
  pos {
    x: 222
    y: 138
  }
}
infos {
  cmd_id: 658
  element: PIN
  edit_type: SET
  pin {
    mod_id: 17
    task_id: 89
    fb_id: 124
    pin_index: 1
    pin_val {
      t: T_STRING
      v {
        str: "SIM"
      }
      tm: 1683688625592778757
    }
  }
}
infos {
  cmd_id: 662
  element: FB
  edit_type: MV
  fb {
    mod_id: 17
    task_id: 84
    fb_id: 100
  }
  pos {
    x: 7
    y: 37
  }
}
infos {
  cmd_id: 665
  element: FB
  edit_type: MV
  fb {
    mod_id: 17
    task_id: 84
    fb_id: 101
  }
  pos {
    x: 65
    y: 37
  }
}
infos {
  cmd_id: 666
  element: LK
  edit_type: MV
  lk {
    mod_id: 17
    task_id: 84
    lk_id: 102
  }
  pos {
    x: 34
    y: 44
  }
  pos {
    x: 65
    y: 44
  }
}
infos {
  cmd_id: 668
  element: FB
  edit_type: MV
  fb {
    mod_id: 17
    task_id: 84
    fb_id: 130
  }
  pos {
    x: 113
    y: 37
  }
}
infos {
  cmd_id: 669
  element: LK
  edit_type: MV
  lk {
    mod_id: 17
    task_id: 84
    lk_id: 131
  }
  pos {
    x: 92
    y: 44
  }
  pos {
    x: 113
    y: 44
  }
}
infos {
  cmd_id: 670
  element: FB
  edit_type: MV
  fb {
    mod_id: 17
    task_id: 84
    fb_id: 111
  }
  pos {
    x: 67
    y: 67
  }
}
infos {
  cmd_id: 671
  element: LK
  edit_type: MV
  lk {
    mod_id: 17
    task_id: 84
    lk_id: 112
  }
  pos {
    x: 34
    y: 44
  }
  pos {
    x: 52
    y: 44
  }
  pos {
    x: 52
    y: 74
  }
  pos {
    x: 67
    y: 74
  }
}
infos {
  cmd_id: 672
  element: FB
  edit_type: MV
  fb {
    mod_id: 17
    task_id: 88
    fb_id: 121
  }
  pos {
    x: 84
    y: 33
  }
}
infos {
  cmd_id: 673
  element: VI
  edit_type: ADD
  vi {
    mod_id: 17
    task_id: 88
    fb_id: 121
    pin_index: 1
    ev_id: 120
    vi_id: 132
  }
}
infos {
  cmd_id: 674
  element: PIN
  edit_type: SET
  pin {
    mod_id: 17
    task_id: 88
    fb_id: 121
    pin_index: 2
    pin_val {
      t: T_INT32
      v {
        i: 3
      }
      tm: 1683688674204807596
    }
  }
}
infos {
  cmd_id: 675
  element: VO
  edit_type: ADD
  vo {
    mod_id: 17
    task_id: 88
    fb_id: 121
    pin_index: 1
    ev_id: 120
    vo_id: 133
  }
}
infos {
  cmd_id: 676
  element: PIN
  edit_type: SET
  pin {
    mod_id: 17
    task_id: 84
    fb_id: 100
    pin_index: 1
    pin_val {
      t: T_BOOL
      v {
        b: true
      }
      tm: 1683689346858203980
    }
  }
}
infos {
  cmd_id: 677
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
        str: "$YEAR"
      }
      tm: 1683689979452984652
    }
  }
}
infos {
  cmd_id: 678
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
        str: "$MONTH"
      }
      tm: 1683689985787983310
    }
  }
}
infos {
  cmd_id: 679
  element: PIN
  edit_type: SET
  pin {
    mod_id: 1
    task_id: 2
    fb_id: 6
    pin_index: 6
    pin_val {
      t: T_STRING
      v {
        str: "$HOUR"
      }
      tm: 1683689991863517492
    }
  }
}
infos {
  cmd_id: 680
  element: PIN
  edit_type: SET
  pin {
    mod_id: 1
    task_id: 2
    fb_id: 6
    pin_index: 7
    pin_val {
      t: T_STRING
      v {
        str: "$MINUTE"
      }
      tm: 1683690027813165747
    }
  }
}
infos {
  cmd_id: 681
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
        str: "$DAY"
      }
      tm: 1683690037867173214
    }
  }
}
infos {
  cmd_id: 682
  element: LK
  edit_type: MV
  lk {
    mod_id: 1
    task_id: 2
    lk_id: 14
  }
  pos {
    x: 27
    y: 39
  }
  pos {
    x: 45
    y: 39
  }
  pos {
    x: 45
    y: 75
  }
  pos {
    x: 58
    y: 75
  }
}
infos {
  cmd_id: 683
  element: LK
  edit_type: MV
  lk {
    mod_id: 1
    task_id: 2
    lk_id: 10
  }
  pos {
    x: 27
    y: 39
  }
  pos {
    x: 45
    y: 39
  }
  pos {
    x: 45
    y: 58
  }
  pos {
    x: 90
    y: 58
  }
}
infos {
  cmd_id: 690
  element: FB
  edit_type: MV
  fb {
    mod_id: 17
    task_id: 18
    fb_id: 44
  }
  pos {
    x: 6
    y: 46
  }
}
infos {
  cmd_id: 694
  element: FB
  edit_type: MV
  fb {
    mod_id: 17
    task_id: 18
    fb_id: 42
  }
  pos {
    x: 6
    y: 34
  }
}
infos {
  cmd_id: 706
  element: FB
  edit_type: MV
  fb {
    mod_id: 17
    task_id: 18
    fb_id: 21
  }
  pos {
    x: 86
    y: 79
  }
}
infos {
  cmd_id: 707
  element: FB
  edit_type: MV
  fb {
    mod_id: 17
    task_id: 18
    fb_id: 74
  }
  pos {
    x: 62
    y: 49
  }
}
infos {
  cmd_id: 708
  element: FB
  edit_type: MV
  fb {
    mod_id: 17
    task_id: 18
    fb_id: 78
  }
  pos {
    x: 60
    y: 63
  }
}
infos {
  cmd_id: 709
  element: LK
  edit_type: MV
  lk {
    mod_id: 17
    task_id: 18
    lk_id: 24
  }
  pos {
    x: 43
    y: 88
  }
  pos {
    x: 86
    y: 88
  }
}
infos {
  cmd_id: 710
  element: LK
  edit_type: MV
  lk {
    mod_id: 17
    task_id: 18
    lk_id: 25
  }
  pos {
    x: 107
    y: 86
  }
  pos {
    x: 107
    y: 85
  }
  pos {
    x: 153
    y: 85
  }
}
infos {
  cmd_id: 712
  element: LK
  edit_type: MV
  lk {
    mod_id: 17
    task_id: 18
    lk_id: 77
  }
  pos {
    x: 81
    y: 56
  }
  pos {
    x: 81
    y: 86
  }
  pos {
    x: 86
    y: 86
  }
}
infos {
  cmd_id: 714
  element: LK
  edit_type: MV
  lk {
    mod_id: 17
    task_id: 18
    lk_id: 82
  }
  pos {
    x: 44
    y: 73
  }
  pos {
    x: 48
    y: 73
  }
  pos {
    x: 48
    y: 72
  }
  pos {
    x: 60
    y: 72
  }
}
infos {
  cmd_id: 715
  element: LK
  edit_type: MV
  lk {
    mod_id: 17
    task_id: 18
    lk_id: 83
  }
  pos {
    x: 79
    y: 70
  }
  pos {
    x: 79
    y: 114
  }
  pos {
    x: 117
    y: 114
  }
}
infos {
  cmd_id: 717
  element: FB
  edit_type: MV
  fb {
    mod_id: 17
    task_id: 18
    fb_id: 71
  }
  pos {
    x: 30
    y: 41
  }
}
infos {
  cmd_id: 718
  element: LK
  edit_type: MV
  lk {
    mod_id: 17
    task_id: 18
    lk_id: 72
  }
  pos {
    x: 25
    y: 41
  }
  pos {
    x: 25
    y: 48
  }
  pos {
    x: 30
    y: 48
  }
}
infos {
  cmd_id: 720
  element: LK
  edit_type: MV
  lk {
    mod_id: 17
    task_id: 18
    lk_id: 75
  }
  pos {
    x: 49
    y: 48
  }
  pos {
    x: 62
    y: 48
  }
  pos {
    x: 62
    y: 56
  }
}
infos {
  cmd_id: 721
  element: LK
  edit_type: MV
  lk {
    mod_id: 17
    task_id: 18
    lk_id: 79
  }
  pos {
    x: 49
    y: 48
  }
  pos {
    x: 51
    y: 48
  }
  pos {
    x: 51
    y: 70
  }
  pos {
    x: 60
    y: 70
  }
}
infos {
  cmd_id: 722
  element: LK
  edit_type: MV
  lk {
    mod_id: 17
    task_id: 18
    lk_id: 73
  }
  pos {
    x: 25
    y: 53
  }
  pos {
    x: 27
    y: 53
  }
  pos {
    x: 27
    y: 50
  }
  pos {
    x: 30
    y: 50
  }
}
infos {
  cmd_id: 726
  element: FB
  edit_type: MV
  fb {
    mod_id: 1
    task_id: 2
    fb_id: 3
  }
  pos {
    x: 4
  }
}