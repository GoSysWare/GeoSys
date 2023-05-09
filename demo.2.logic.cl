infos {
  cmd_id: 424
  edit_type: SET
  proj {
    proj_name: "rotbot-engine-project"
    proj_uuid: "{cc6a38f3-43b9-4231-8a7a-55196813b7f3}"
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
  cmd_id: 6
  element: FB
  edit_type: MV
  fb {
    mod_id: 1
    task_id: 2
    fb_id: 3
  }
  pos {
    x: 5
    y: 3
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
  cmd_id: 50
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
    x: 41
    y: 39
  }
  pos {
    x: 41
    y: 58
  }
  pos {
    x: 90
    y: 58
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
  cmd_id: 59
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
    x: 41
    y: 39
  }
  pos {
    x: 41
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
  cmd_id: 266
  element: FB
  edit_type: MV
  fb {
    mod_id: 17
    task_id: 18
    fb_id: 42
  }
  pos {
    x: 17
    y: 42
  }
}
infos {
  cmd_id: 273
  element: FB
  edit_type: MV
  fb {
    mod_id: 17
    task_id: 18
    fb_id: 44
  }
  pos {
    x: 17
    y: 54
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
  cmd_id: 323
  element: FB
  edit_type: MV
  fb {
    mod_id: 17
    task_id: 18
    fb_id: 21
  }
  pos {
    x: 79
    y: 79
  }
}
infos {
  cmd_id: 324
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
    x: 79
    y: 88
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
  cmd_id: 360
  element: FB
  edit_type: MV
  fb {
    mod_id: 17
    task_id: 18
    fb_id: 28
  }
  pos {
    x: 177
    y: 103
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
  cmd_id: 381
  element: LK
  edit_type: MV
  lk {
    mod_id: 17
    task_id: 18
    lk_id: 25
  }
  pos {
    x: 100
    y: 86
  }
  pos {
    x: 100
    y: 85
  }
  pos {
    x: 153
    y: 85
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
  cmd_id: 422
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
    x: 177
    y: 114
  }
  pos {
    x: 177
    y: 112
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
