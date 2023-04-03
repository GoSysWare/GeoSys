infos {
  edit_type: SET
  proj {
    proj_name: "rotbot-engine-project"
    proj_uuid: "{790b6f91-e5de-4a18-afbc-417af2ae8008}"
  }
}
infos {
  cmd_id: 1
  element: EV
  edit_type: ADD
  ev {
    ev_id: 1
    ev_name: "FSM_Con"
    ev_type: 2
    ev_desc: "Desc"
    init_val {
      v {
        t: T_INT32
        i: 0
      }
      tm: 1680510107874771220
    }
  }
}
infos {
  cmd_id: 2
  element: EV
  edit_type: ADD
  ev {
    ev_id: 2
    ev_name: "FSM_State"
    ev_type: 2
    ev_desc: "Desc"
    init_val {
      v {
        t: T_INT32
        i: 0
      }
      tm: 1680511832255674879
    }
  }
}
infos {
  cmd_id: 3
  element: MOD
  edit_type: ADD
  mod {
    mod_id: 3
    mod_name: "F1"
  }
}
infos {
  cmd_id: 4
  element: TASK
  edit_type: ADD
  task {
    mod_id: 3
    task_id: 4
    task_name: "FSM1"
    interval: 1000
  }
}
infos {
  cmd_id: 5
  element: FB
  edit_type: ADD
  fb {
    mod_id: 3
    task_id: 4
    fb_id: 5
    flib_name: "Converter"
    fc_name: "UI2I"
  }
  pos {
    x: 60
    y: 4
  }
}
infos {
  cmd_id: 6
  element: FB
  edit_type: ADD
  fb {
    mod_id: 3
    task_id: 4
    fb_id: 6
    flib_name: "Fsm"
    fc_name: "FSM"
  }
  pos {
    x: 37
    y: 62
  }
}
infos {
  cmd_id: 7
  element: FB
  edit_type: ADD
  fb {
    mod_id: 3
    task_id: 4
    fb_id: 7
    flib_name: "Fsm"
    fc_name: "FSM"
  }
  pos {
    x: 112
    y: 61
  }
}
infos {
  cmd_id: 8
  element: FB
  edit_type: ADD
  fb {
    mod_id: 3
    task_id: 4
    fb_id: 8
    flib_name: "Fsm"
    fc_name: "FSM"
  }
  pos {
    x: 159
    y: 59
  }
}
infos {
  cmd_id: 9
  element: FB
  edit_type: ADD
  fb {
    mod_id: 3
    task_id: 4
    fb_id: 9
    flib_name: "Trigger"
    fc_name: "U_TRIG"
  }
  pos {
    x: 70
    y: 88
  }
}
infos {
  cmd_id: 10
  element: FB
  edit_type: ADD
  fb {
    mod_id: 3
    task_id: 4
    fb_id: 10
    flib_name: "Trigger"
    fc_name: "U_TRIG"
  }
  pos {
    x: 120
    y: 90
  }
}
infos {
  cmd_id: 11
  element: FB
  edit_type: ADD
  fb {
    mod_id: 3
    task_id: 4
    fb_id: 11
    flib_name: "Trigger"
    fc_name: "U_TRIG"
  }
  pos {
    x: 187
    y: 94
  }
}
infos {
  cmd_id: 12
  element: FB
  edit_type: ADD
  fb {
    mod_id: 3
    task_id: 4
    fb_id: 12
    flib_name: "Comparison"
    fc_name: "EQ_INT"
  }
  pos {
    x: 79
    y: 44
  }
}
infos {
  cmd_id: 13
  element: FB
  edit_type: ADD
  fb {
    mod_id: 3
    task_id: 4
    fb_id: 13
    flib_name: "Comparison"
    fc_name: "EQ_INT"
  }
  pos {
    x: 131
    y: 44
  }
}
infos {
  cmd_id: 14
  element: FB
  edit_type: ADD
  fb {
    mod_id: 3
    task_id: 4
    fb_id: 14
    flib_name: "Comparison"
    fc_name: "LE_INT"
  }
  pos {
    x: 14
    y: 36
  }
}
infos {
  cmd_id: 15
  element: FB
  edit_type: ADD
  fb {
    mod_id: 3
    task_id: 4
    fb_id: 15
    flib_name: "Fsm"
    fc_name: "FSM"
  }
  pos {
    x: 238
    y: 72
  }
}
infos {
  cmd_id: 16
  element: FB
  edit_type: ADD
  fb {
    mod_id: 3
    task_id: 4
    fb_id: 16
    flib_name: "Comparison"
    fc_name: "LE_INT"
  }
  pos {
    x: 203
    y: 36
  }
}
infos {
  cmd_id: 17
  element: FB
  edit_type: ADD
  fb {
    mod_id: 3
    task_id: 4
    fb_id: 17
    flib_name: "Fsm"
    fc_name: "FSM"
  }
  pos {
    x: 110
    y: 117
  }
}
infos {
  cmd_id: 18
  element: FB
  edit_type: ADD
  fb {
    mod_id: 3
    task_id: 4
    fb_id: 18
    flib_name: "Devices"
    fc_name: "SIM_READ"
  }
  pos {
    x: 13
    y: 8
  }
}
infos {
  cmd_id: 19
  element: FB
  edit_type: ADD
  fb {
    mod_id: 3
    task_id: 4
    fb_id: 19
    flib_name: "Converter"
    fc_name: "D2UI"
  }
  pos {
    x: 40
    y: 14
  }
}
infos {
  cmd_id: 20
  element: LK
  edit_type: ADD
  lk {
    mod_id: 3
    task_id: 4
    lk_id: 20
    src_fb_id: 6
    src_pin_index: 1
    target_fb_id: 7
    target_pin_index: 2
  }
  pos {
    x: 54
    y: 69
  }
  pos {
    x: 60
    y: 69
  }
  pos {
    x: 60
    y: 70
  }
  pos {
    x: 112
    y: 70
  }
}
infos {
  cmd_id: 21
  element: LK
  edit_type: ADD
  lk {
    mod_id: 3
    task_id: 4
    lk_id: 21
    src_fb_id: 7
    src_pin_index: 1
    target_fb_id: 8
    target_pin_index: 2
  }
  pos {
    x: 129
    y: 68
  }
  pos {
    x: 159
    y: 68
  }
}
infos {
  cmd_id: 22
  element: LK
  edit_type: ADD
  lk {
    mod_id: 3
    task_id: 4
    lk_id: 22
    src_fb_id: 6
    src_pin_index: 2
    target_fb_id: 9
    target_pin_index: 1
  }
  pos {
    x: 54
    y: 71
  }
  pos {
    x: 57
    y: 71
  }
  pos {
    x: 57
    y: 95
  }
  pos {
    x: 70
    y: 95
  }
}
infos {
  cmd_id: 23
  element: LK
  edit_type: ADD
  lk {
    mod_id: 3
    task_id: 4
    lk_id: 23
    src_fb_id: 7
    src_pin_index: 2
    target_fb_id: 10
    target_pin_index: 1
  }
  pos {
    x: 129
    y: 70
  }
  pos {
    x: 105
    y: 70
  }
  pos {
    x: 105
    y: 97
  }
  pos {
    x: 120
    y: 97
  }
}
infos {
  cmd_id: 24
  element: LK
  edit_type: ADD
  lk {
    mod_id: 3
    task_id: 4
    lk_id: 24
    src_fb_id: 8
    src_pin_index: 2
    target_fb_id: 11
    target_pin_index: 1
  }
  pos {
    x: 176
    y: 68
  }
  pos {
    x: 176
    y: 101
  }
  pos {
    x: 187
    y: 101
  }
}
infos {
  cmd_id: 25
  element: LK
  edit_type: ADD
  lk {
    mod_id: 3
    task_id: 4
    lk_id: 25
    src_fb_id: 12
    src_pin_index: 1
    target_fb_id: 7
    target_pin_index: 1
  }
  pos {
    x: 94
    y: 51
  }
  pos {
    x: 99
    y: 51
  }
  pos {
    x: 99
    y: 68
  }
  pos {
    x: 112
    y: 68
  }
}
infos {
  cmd_id: 26
  element: LK
  edit_type: ADD
  lk {
    mod_id: 3
    task_id: 4
    lk_id: 26
    src_fb_id: 5
    src_pin_index: 1
    target_fb_id: 12
    target_pin_index: 1
  }
  pos {
    x: 74
    y: 11
  }
  pos {
    x: 77
    y: 11
  }
  pos {
    x: 77
    y: 51
  }
  pos {
    x: 79
    y: 51
  }
}
infos {
  cmd_id: 27
  element: LK
  edit_type: ADD
  lk {
    mod_id: 3
    task_id: 4
    lk_id: 27
    src_fb_id: 13
    src_pin_index: 1
    target_fb_id: 8
    target_pin_index: 1
  }
  pos {
    x: 146
    y: 51
  }
  pos {
    x: 141
    y: 51
  }
  pos {
    x: 141
    y: 66
  }
  pos {
    x: 159
    y: 66
  }
}
infos {
  cmd_id: 28
  element: LK
  edit_type: ADD
  lk {
    mod_id: 3
    task_id: 4
    lk_id: 28
    src_fb_id: 5
    src_pin_index: 1
    target_fb_id: 13
    target_pin_index: 1
  }
  pos {
    x: 74
    y: 11
  }
  pos {
    x: 93
    y: 11
  }
  pos {
    x: 93
    y: 51
  }
  pos {
    x: 131
    y: 51
  }
}
infos {
  cmd_id: 29
  element: LK
  edit_type: ADD
  lk {
    mod_id: 3
    task_id: 4
    lk_id: 29
    src_fb_id: 5
    src_pin_index: 1
    target_fb_id: 14
    target_pin_index: 1
  }
  pos {
    x: 74
    y: 11
  }
  pos {
    x: 73
    y: 11
  }
  pos {
    x: 73
    y: 30
  }
  pos {
    x: 8
    y: 30
  }
  pos {
    x: 8
    y: 43
  }
  pos {
    x: 14
    y: 43
  }
}
infos {
  cmd_id: 30
  element: LK
  edit_type: ADD
  lk {
    mod_id: 3
    task_id: 4
    lk_id: 30
    src_fb_id: 14
    src_pin_index: 1
    target_fb_id: 6
    target_pin_index: 1
  }
  pos {
    x: 29
    y: 43
  }
  pos {
    x: 35
    y: 43
  }
  pos {
    x: 35
    y: 69
  }
  pos {
    x: 37
    y: 69
  }
}
infos {
  cmd_id: 31
  element: LK
  edit_type: ADD
  lk {
    mod_id: 3
    task_id: 4
    lk_id: 31
    src_fb_id: 8
    src_pin_index: 1
    target_fb_id: 15
    target_pin_index: 2
  }
  pos {
    x: 176
    y: 66
  }
  pos {
    x: 207
    y: 66
  }
  pos {
    x: 207
    y: 81
  }
  pos {
    x: 238
    y: 81
  }
}
infos {
  cmd_id: 32
  element: LK
  edit_type: ADD
  lk {
    mod_id: 3
    task_id: 4
    lk_id: 32
    src_fb_id: 5
    src_pin_index: 1
    target_fb_id: 16
    target_pin_index: 1
  }
  pos {
    x: 74
    y: 11
  }
  pos {
    x: 129
    y: 11
  }
  pos {
    x: 129
    y: 43
  }
  pos {
    x: 203
    y: 43
  }
}
infos {
  cmd_id: 33
  element: LK
  edit_type: ADD
  lk {
    mod_id: 3
    task_id: 4
    lk_id: 33
    src_fb_id: 16
    src_pin_index: 1
    target_fb_id: 15
    target_pin_index: 1
  }
  pos {
    x: 218
    y: 43
  }
  pos {
    x: 228
    y: 43
  }
  pos {
    x: 228
    y: 79
  }
  pos {
    x: 238
    y: 79
  }
}
infos {
  cmd_id: 34
  element: LK
  edit_type: ADD
  lk {
    mod_id: 3
    task_id: 4
    lk_id: 34
    src_fb_id: 18
    src_pin_index: 2
    target_fb_id: 19
    target_pin_index: 1
  }
  pos {
    x: 29
    y: 17
  }
  pos {
    x: 34
    y: 17
  }
  pos {
    x: 34
    y: 21
  }
  pos {
    x: 40
    y: 21
  }
}
infos {
  cmd_id: 35
  element: LK
  edit_type: ADD
  lk {
    mod_id: 3
    task_id: 4
    lk_id: 35
    src_fb_id: 19
    src_pin_index: 1
    target_fb_id: 5
    target_pin_index: 1
  }
  pos {
    x: 54
    y: 21
  }
  pos {
    x: 57
    y: 21
  }
  pos {
    x: 57
    y: 11
  }
  pos {
    x: 60
    y: 11
  }
}
infos {
  cmd_id: 36
  element: VI
  edit_type: ADD
  vi {
    mod_id: 3
    task_id: 4
    fb_id: 6
    pin_index: 3
    ev_id: 2
    vi_id: 36
  }
}
infos {
  cmd_id: 37
  element: VI
  edit_type: ADD
  vi {
    mod_id: 3
    task_id: 4
    fb_id: 7
    pin_index: 3
    ev_id: 2
    vi_id: 37
  }
}
infos {
  cmd_id: 38
  element: VI
  edit_type: ADD
  vi {
    mod_id: 3
    task_id: 4
    fb_id: 8
    pin_index: 3
    ev_id: 2
    vi_id: 38
  }
}
infos {
  cmd_id: 39
  element: VI
  edit_type: ADD
  vi {
    mod_id: 3
    task_id: 4
    fb_id: 15
    pin_index: 3
    ev_id: 2
    vi_id: 39
  }
}
infos {
  cmd_id: 40
  element: VI
  edit_type: ADD
  vi {
    mod_id: 3
    task_id: 4
    fb_id: 17
    pin_index: 3
    ev_id: 2
    vi_id: 40
  }
}
infos {
  cmd_id: 41
  element: VO
  edit_type: ADD
  vo {
    mod_id: 3
    task_id: 4
    fb_id: 5
    pin_index: 1
    ev_id: 1
    vo_id: 41
  }
}
infos {
  cmd_id: 42
  element: PIN
  edit_type: SET
  pin {
    mod_id: 3
    task_id: 4
    fb_id: 6
    pin_index: 1
    pin_val {
      v {
        t: T_BOOL
        b: true
      }
      tm: 1680506923091798228
    }
  }
}
infos {
  cmd_id: 43
  element: PIN
  edit_type: SET
  pin {
    mod_id: 3
    task_id: 4
    fb_id: 6
    pin_index: 2
    pin_val {
      v {
        t: T_BOOL
        b: true
      }
      tm: 1680506940475871121
    }
  }
}
infos {
  cmd_id: 44
  element: PIN
  edit_type: SET
  pin {
    mod_id: 3
    task_id: 4
    fb_id: 7
    pin_index: 1
    pin_val {
      v {
        t: T_BOOL
        b: true
      }
      tm: 1680506963651761954
    }
  }
}
infos {
  cmd_id: 45
  element: PIN
  edit_type: SET
  pin {
    mod_id: 3
    task_id: 4
    fb_id: 8
    pin_index: 1
    pin_val {
      v {
        t: T_BOOL
        b: true
      }
      tm: 1680506969892545297
    }
  }
}
infos {
  cmd_id: 46
  element: PIN
  edit_type: SET
  pin {
    mod_id: 3
    task_id: 4
    fb_id: 6
    pin_index: 4
    pin_val {
      v {
        t: T_INT32
        i: 10
      }
      tm: 1680506999100887772
    }
  }
}
infos {
  cmd_id: 47
  element: PIN
  edit_type: SET
  pin {
    mod_id: 3
    task_id: 4
    fb_id: 7
    pin_index: 4
    pin_val {
      v {
        t: T_INT32
        i: 10
      }
      tm: 1680507004709028514
    }
  }
}
infos {
  cmd_id: 48
  element: PIN
  edit_type: SET
  pin {
    mod_id: 3
    task_id: 4
    fb_id: 8
    pin_index: 4
    pin_val {
      v {
        t: T_INT32
        i: 10
      }
      tm: 1680507012197094632
    }
  }
}
infos {
  cmd_id: 49
  element: PIN
  edit_type: SET
  pin {
    mod_id: 3
    task_id: 4
    fb_id: 7
    pin_index: 4
    pin_val {
      v {
        t: T_INT32
        i: 30
      }
      tm: 1680507021269594745
    }
  }
}
infos {
  cmd_id: 50
  element: PIN
  edit_type: SET
  pin {
    mod_id: 3
    task_id: 4
    fb_id: 7
    pin_index: 4
    pin_val {
      v {
        t: T_INT32
        i: 20
      }
      tm: 1680507028013777203
    }
  }
}
infos {
  cmd_id: 51
  element: PIN
  edit_type: SET
  pin {
    mod_id: 3
    task_id: 4
    fb_id: 8
    pin_index: 4
    pin_val {
      v {
        t: T_INT32
        i: 30
      }
      tm: 1680507033085617396
    }
  }
}
infos {
  cmd_id: 52
  element: PIN
  edit_type: SET
  pin {
    mod_id: 3
    task_id: 4
    fb_id: 6
    pin_index: 2
    pin_val {
      v {
        t: T_BOOL
        b: false
      }
      tm: 1680507401531253282
    }
  }
}
infos {
  cmd_id: 53
  element: PIN
  edit_type: SET
  pin {
    mod_id: 3
    task_id: 4
    fb_id: 12
    pin_index: 2
    pin_val {
      v {
        t: T_INT32
        i: 10
      }
      tm: 1680510142176676540
    }
  }
}
infos {
  cmd_id: 54
  element: PIN
  edit_type: SET
  pin {
    mod_id: 3
    task_id: 4
    fb_id: 13
    pin_index: 2
    pin_val {
      v {
        t: T_INT32
        i: 20
      }
      tm: 1680510172870979268
    }
  }
}
infos {
  cmd_id: 55
  element: PIN
  edit_type: SET
  pin {
    mod_id: 3
    task_id: 4
    fb_id: 12
    pin_index: 2
    pin_val {
      v {
        t: T_INT32
        i: 20
      }
      tm: 1680510261561845372
    }
  }
}
infos {
  cmd_id: 56
  element: PIN
  edit_type: SET
  pin {
    mod_id: 3
    task_id: 4
    fb_id: 13
    pin_index: 2
    pin_val {
      v {
        t: T_INT32
        i: 30
      }
      tm: 1680510266705497283
    }
  }
}
infos {
  cmd_id: 57
  element: PIN
  edit_type: SET
  pin {
    mod_id: 3
    task_id: 4
    fb_id: 14
    pin_index: 2
    pin_val {
      v {
        t: T_INT32
        i: 10
      }
      tm: 1680510652185593997
    }
  }
}
infos {
  cmd_id: 58
  element: PIN
  edit_type: SET
  pin {
    mod_id: 3
    task_id: 4
    fb_id: 6
    pin_index: 2
    pin_val {
      v {
        t: T_BOOL
        b: true
      }
      tm: 1680510754859027632
    }
  }
}
infos {
  cmd_id: 59
  element: PIN
  edit_type: SET
  pin {
    mod_id: 3
    task_id: 4
    fb_id: 16
    pin_index: 2
    pin_val {
      v {
        t: T_INT32
        i: 50
      }
      tm: 1680513083060213567
    }
  }
}
infos {
  cmd_id: 60
  element: PIN
  edit_type: SET
  pin {
    mod_id: 3
    task_id: 4
    fb_id: 15
    pin_index: 4
    pin_val {
      v {
        t: T_INT32
        i: 10
      }
      tm: 1680513107620359305
    }
  }
}
infos {
  cmd_id: 61
  element: FB
  edit_type: MV
  fb {
    mod_id: 3
    task_id: 4
    fb_id: 5
  }
  pos {
    x: 71
    y: 2
  }
}
infos {
  cmd_id: 62
  element: LK
  edit_type: MV
  lk {
    mod_id: 3
    task_id: 4
    lk_id: 26
  }
  pos {
    x: 85
    y: 9
  }
  pos {
    x: 77
    y: 9
  }
  pos {
    x: 77
    y: 51
  }
  pos {
    x: 79
    y: 51
  }
}
infos {
  cmd_id: 63
  element: LK
  edit_type: MV
  lk {
    mod_id: 3
    task_id: 4
    lk_id: 28
  }
  pos {
    x: 85
    y: 9
  }
  pos {
    x: 93
    y: 9
  }
  pos {
    x: 93
    y: 51
  }
  pos {
    x: 131
    y: 51
  }
}
infos {
  cmd_id: 64
  element: LK
  edit_type: MV
  lk {
    mod_id: 3
    task_id: 4
    lk_id: 29
  }
  pos {
    x: 85
    y: 9
  }
  pos {
    x: 73
    y: 9
  }
  pos {
    x: 73
    y: 30
  }
  pos {
    x: 8
    y: 30
  }
  pos {
    x: 8
    y: 43
  }
  pos {
    x: 14
    y: 43
  }
}
infos {
  cmd_id: 65
  element: LK
  edit_type: MV
  lk {
    mod_id: 3
    task_id: 4
    lk_id: 32
  }
  pos {
    x: 85
    y: 9
  }
  pos {
    x: 129
    y: 9
  }
  pos {
    x: 129
    y: 43
  }
  pos {
    x: 203
    y: 43
  }
}
infos {
  cmd_id: 67
  element: FB
  edit_type: MV
  fb {
    mod_id: 3
    task_id: 4
    fb_id: 19
  }
  pos {
    x: 43
    y: 7
  }
}
infos {
  cmd_id: 68
  element: LK
  edit_type: MV
  lk {
    mod_id: 3
    task_id: 4
    lk_id: 34
  }
  pos {
    x: 29
    y: 17
  }
  pos {
    x: 34
    y: 17
  }
  pos {
    x: 34
    y: 14
  }
  pos {
    x: 43
    y: 14
  }
}
infos {
  cmd_id: 69
  element: LK
  edit_type: MV
  lk {
    mod_id: 3
    task_id: 4
    lk_id: 35
  }
  pos {
    x: 57
    y: 14
  }
  pos {
    x: 57
    y: 9
  }
  pos {
    x: 71
    y: 9
  }
}
infos {
  cmd_id: 70
  element: PIN
  edit_type: SET
  pin {
    mod_id: 3
    task_id: 4
    fb_id: 18
    pin_index: 1
    pin_val {
      v {
        t: T_STRING
        str: "SIM"
      }
      tm: 1680514505435611224
    }
  }
}
