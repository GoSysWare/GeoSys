infos {
  edit_type: SET
  proj {
    proj_name: "rotbot-engine-project"
    proj_uuid: "{3181f287-0cee-4542-b7ba-643c95746bad}"
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
    x: 50
    y: 16
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
    x: 30
    y: 69
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
    x: 95
    y: 46
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
    x: 9
    y: 46
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
    flib_name: "Devices"
    fc_name: "SIM_READ"
  }
  pos {
    x: 14
    y: 4
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
    flib_name: "Converter"
    fc_name: "D2UI"
  }
  pos {
    x: 35
    y: 1
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
    flib_name: "System"
    fc_name: "SYSSTATE"
  }
  pos {
    x: 16
    y: 105
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
    x: 47
    y: 76
  }
  pos {
    x: 60
    y: 76
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
    x: 47
    y: 78
  }
  pos {
    x: 55
    y: 78
  }
  pos {
    x: 55
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
    x: 110
    y: 53
  }
  pos {
    x: 99
    y: 53
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
    x: 64
    y: 23
  }
  pos {
    x: 80
    y: 23
  }
  pos {
    x: 80
    y: 53
  }
  pos {
    x: 95
    y: 53
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
    x: 64
    y: 23
  }
  pos {
    x: 115
    y: 23
  }
  pos {
    x: 115
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
    x: 64
    y: 23
  }
  pos {
    x: 80
    y: 23
  }
  pos {
    x: 80
    y: 37
  }
  pos {
    x: 1
    y: 37
  }
  pos {
    x: 1
    y: 53
  }
  pos {
    x: 9
    y: 53
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
    x: 24
    y: 53
  }
  pos {
    x: 25
    y: 53
  }
  pos {
    x: 25
    y: 76
  }
  pos {
    x: 30
    y: 76
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
    x: 64
    y: 23
  }
  pos {
    x: 80
    y: 23
  }
  pos {
    x: 80
    y: 7
  }
  pos {
    x: 129
    y: 7
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
    src_pin_index: 1
    target_fb_id: 5
    target_pin_index: 1
  }
  pos {
    x: 49
    y: 8
  }
  pos {
    x: 46
    y: 8
  }
  pos {
    x: 46
    y: 23
  }
  pos {
    x: 50
    y: 23
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
    src_fb_id: 17
    src_pin_index: 9
    target_fb_id: 18
    target_pin_index: 1
  }
  pos {
    x: 30
    y: 27
  }
  pos {
    x: 36
    y: 27
  }
  pos {
    x: 36
    y: 8
  }
  pos {
    x: 35
    y: 8
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
  element: VO
  edit_type: ADD
  vo {
    mod_id: 3
    task_id: 4
    fb_id: 5
    pin_index: 1
    ev_id: 1
    vo_id: 40
  }
}
infos {
  cmd_id: 41
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
  cmd_id: 42
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
  cmd_id: 43
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
  cmd_id: 44
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
  cmd_id: 45
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
  cmd_id: 46
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
  cmd_id: 47
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
  cmd_id: 48
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
        i: 20
      }
      tm: 1680507028013777203
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
  cmd_id: 51
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
  cmd_id: 52
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
  cmd_id: 53
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
  cmd_id: 54
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
  cmd_id: 55
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
  cmd_id: 56
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
  cmd_id: 57
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
  cmd_id: 58
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
  cmd_id: 59
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
  cmd_id: 60
  element: PIN
  edit_type: SET
  pin {
    mod_id: 3
    task_id: 4
    fb_id: 17
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
infos {
  cmd_id: 61
  element: PIN
  edit_type: SET
  pin {
    mod_id: 3
    task_id: 4
    fb_id: 17
    pin_index: 10
    pin_val {
      v {
        t: T_STRING
        str: "$SECOND"
      }
      tm: 1680576129920733721
    }
  }
}
infos {
  cmd_id: 62
  element: EV
  edit_type: SET
  ev {
    ev_id: 2
    ev_name: "FSM_State"
    ev_type: 2
    ev_desc: "Desc"
    init_val {
      v {
        t: T_INT32
        i: 30
      }
      tm: 1680576645276970404
    }
  }
}
infos {
  cmd_id: 63
  element: EV
  edit_type: SET
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
      tm: 1680576713837643045
    }
  }
}
infos {
  cmd_id: 64
  element: FB
  edit_type: MV
  fb {
    mod_id: 3
    task_id: 4
    fb_id: 19
  }
  pos {
    x: 20
    y: 113
  }
}
infos {
  cmd_id: 65
  element: FB
  edit_type: ADD
  fb {
    mod_id: 3
    task_id: 4
    fb_id: 41
    flib_name: "Task"
    fc_name: "TASK"
  }
  pos {
    x: 95
    y: 111
  }
}
infos {
  cmd_id: 66
  element: LK
  edit_type: ADD
  lk {
    mod_id: 3
    task_id: 4
    lk_id: 42
    src_fb_id: 9
    src_pin_index: 1
    target_fb_id: 41
    target_pin_index: 1
  }
  pos {
    x: 85
    y: 95
  }
  pos {
    x: 90
    y: 95
  }
  pos {
    x: 90
    y: 118
  }
  pos {
    x: 95
    y: 118
  }
}
infos {
  cmd_id: 67
  element: PIN
  edit_type: SET
  pin {
    mod_id: 3
    task_id: 4
    fb_id: 41
    pin_index: 2
    pin_val {
      v {
        t: T_STRING
        str: "P1"
      }
      tm: 1680588560306520240
    }
  }
}
infos {
  cmd_id: 68
  element: PIN
  edit_type: SET
  pin {
    mod_id: 3
    task_id: 4
    fb_id: 41
    pin_index: 2
    pin_val {
      v {
        t: T_STRING
        str: "P1"
      }
      tm: 1680589069912191054
    }
  }
}
infos {
  cmd_id: 69
  element: PIN
  edit_type: SET
  pin {
    mod_id: 3
    task_id: 4
    fb_id: 41
    pin_index: 3
    pin_val {
      v {
        t: T_STRING
        str: "T1"
      }
      tm: 1680589077286769385
    }
  }
}
infos {
  cmd_id: 70
  element: PIN
  edit_type: SET
  pin {
    mod_id: 3
    task_id: 4
    fb_id: 41
    pin_index: 5
    pin_val {
      v {
        t: T_INT32
        i: 1
      }
      tm: 1680589084310666416
    }
  }
}
infos {
  cmd_id: 71
  element: MOD
  edit_type: ADD
  mod {
    mod_id: 43
    mod_name: "P1"
  }
}
infos {
  cmd_id: 72
  element: TASK
  edit_type: ADD
  task {
    mod_id: 43
    task_id: 44
    task_name: "T1"
    interval: 1000
  }
}
infos {
  cmd_id: 73
  element: FB
  edit_type: ADD
  fb {
    mod_id: 43
    task_id: 44
    fb_id: 45
    flib_name: "Counter"
    fc_name: "CTUD_INT"
  }
  pos {
    x: 59
    y: 36
  }
}
infos {
  cmd_id: 74
  element: PIN
  edit_type: SET
  pin {
    mod_id: 43
    task_id: 44
    fb_id: 45
    pin_index: 1
    pin_val {
      v {
        t: T_BOOL
        b: true
      }
      tm: 1680591547991959940
    }
  }
}
infos {
  cmd_id: 75
  element: PIN
  edit_type: SET
  pin {
    mod_id: 43
    task_id: 44
    fb_id: 45
    pin_index: 5
    pin_val {
      v {
        t: T_INT32
        i: 1000
      }
      tm: 1680591553383544350
    }
  }
}
infos {
  cmd_id: 76
  element: FB
  edit_type: ADD
  fb {
    mod_id: 43
    task_id: 44
    fb_id: 46
    flib_name: "System"
    fc_name: "SYSSTATE"
  }
  pos {
    x: 24
    y: 17
  }
}
infos {
  cmd_id: 77
  element: TASK
  edit_type: ADD
  task {
    task_type: ASYNC
    mod_id: 43
    task_id: 47
    task_name: "T2"
    interval: 1000
  }
}
infos {
  cmd_id: 78
  element: FB
  edit_type: ADD
  fb {
    mod_id: 43
    task_id: 47
    fb_id: 48
    flib_name: "Counter"
    fc_name: "CTUD_INT"
  }
  pos {
    x: 32
    y: 36
  }
}
infos {
  cmd_id: 79
  element: PIN
  edit_type: SET
  pin {
    mod_id: 43
    task_id: 47
    fb_id: 48
    pin_index: 1
    pin_val {
      v {
        t: T_BOOL
        b: true
      }
      tm: 1680593241140102039
    }
  }
}
infos {
  cmd_id: 80
  element: PIN
  edit_type: SET
  pin {
    mod_id: 43
    task_id: 47
    fb_id: 48
    pin_index: 5
    pin_val {
      v {
        t: T_INT32
        i: 1000
      }
      tm: 1680593256428231139
    }
  }
}
infos {
  cmd_id: 81
  element: FB
  edit_type: ADD
  fb {
    mod_id: 43
    task_id: 47
    fb_id: 49
    flib_name: "System"
    fc_name: "SYSSTATE"
  }
  pos {
    x: 27
    y: 15
  }
}
infos {
  cmd_id: 83
  element: FB
  edit_type: MV
  fb {
    mod_id: 43
    task_id: 47
    fb_id: 49
  }
  pos {
    x: 21
    y: 18
  }
}
infos {
  cmd_id: 84
  element: FB
  edit_type: MV
  fb {
    mod_id: 43
    task_id: 47
    fb_id: 48
  }
  pos {
    x: 53
    y: 44
  }
}
infos {
  cmd_id: 85
  element: PIN
  edit_type: SET
  pin {
    mod_id: 3
    task_id: 4
    fb_id: 41
    pin_index: 3
    pin_val {
      v {
        t: T_STRING
        str: "T2"
      }
      tm: 1680593359915593727
    }
  }
}
infos {
  cmd_id: 86
  element: FB
  edit_type: ADD
  fb {
    mod_id: 43
    task_id: 47
    fb_id: 50
    flib_name: "Arithmetic"
    fc_name: "ADD_INT"
  }
  pos {
    x: 37
    y: 79
  }
}
infos {
  cmd_id: 87
  element: EV
  edit_type: ADD
  ev {
    ev_id: 51
    ev_name: "I1"
    ev_type: 2
    ev_desc: "Desc"
    init_val {
      v {
        t: T_INT32
        i: 0
      }
      tm: 1680593903487471138
    }
  }
}
infos {
  cmd_id: 88
  element: VI
  edit_type: ADD
  vi {
    mod_id: 43
    task_id: 47
    fb_id: 50
    pin_index: 1
    ev_id: 51
    vi_id: 52
  }
}
infos {
  cmd_id: 89
  element: VO
  edit_type: ADD
  vo {
    mod_id: 43
    task_id: 47
    fb_id: 50
    pin_index: 1
    ev_id: 51
    vo_id: 53
  }
}
infos {
  cmd_id: 90
  element: PIN
  edit_type: SET
  pin {
    mod_id: 43
    task_id: 47
    fb_id: 50
    pin_index: 2
    pin_val {
      v {
        t: T_INT32
        i: 1
      }
      tm: 1680593914439416630
    }
  }
}
infos {
  cmd_id: 103
  element: FB
  edit_type: MV
  fb {
    mod_id: 3
    task_id: 4
    fb_id: 18
  }
  pos {
    x: 43
    y: 17
  }
}
infos {
  cmd_id: 105
  element: LK
  edit_type: MV
  lk {
    mod_id: 3
    task_id: 4
    lk_id: 35
  }
  pos {
    x: 30
    y: 27
  }
  pos {
    x: 36
    y: 27
  }
  pos {
    x: 36
    y: 24
  }
  pos {
    x: 43
    y: 24
  }
}
infos {
  cmd_id: 107
  element: FB
  edit_type: MV
  fb {
    mod_id: 3
    task_id: 4
    fb_id: 5
  }
  pos {
    x: 64
    y: 2
  }
}
infos {
  cmd_id: 108
  element: LK
  edit_type: MV
  lk {
    mod_id: 3
    task_id: 4
    lk_id: 26
  }
  pos {
    x: 78
    y: 9
  }
  pos {
    x: 80
    y: 9
  }
  pos {
    x: 80
    y: 53
  }
  pos {
    x: 95
    y: 53
  }
}
infos {
  cmd_id: 109
  element: LK
  edit_type: MV
  lk {
    mod_id: 3
    task_id: 4
    lk_id: 28
  }
  pos {
    x: 78
    y: 9
  }
  pos {
    x: 115
    y: 9
  }
  pos {
    x: 115
    y: 51
  }
  pos {
    x: 131
    y: 51
  }
}
infos {
  cmd_id: 111
  element: LK
  edit_type: MV
  lk {
    mod_id: 3
    task_id: 4
    lk_id: 32
  }
  pos {
    x: 78
    y: 9
  }
  pos {
    x: 80
    y: 9
  }
  pos {
    x: 80
    y: 7
  }
  pos {
    x: 129
    y: 7
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
  cmd_id: 112
  element: LK
  edit_type: MV
  lk {
    mod_id: 3
    task_id: 4
    lk_id: 34
  }
  pos {
    x: 57
    y: 24
  }
  pos {
    x: 62
    y: 24
  }
  pos {
    x: 62
    y: 9
  }
  pos {
    x: 64
    y: 9
  }
}
infos {
  cmd_id: 117
  element: FB
  edit_type: MV
  fb {
    mod_id: 3
    task_id: 4
    fb_id: 14
  }
  pos {
    x: 12
    y: 45
  }
}
infos {
  cmd_id: 118
  element: LK
  edit_type: MV
  lk {
    mod_id: 3
    task_id: 4
    lk_id: 29
  }
  pos {
    x: 78
    y: 9
  }
  pos {
    x: 80
    y: 9
  }
  pos {
    x: 80
    y: 37
  }
  pos {
    x: 1
    y: 37
  }
  pos {
    x: 1
    y: 52
  }
  pos {
    x: 12
    y: 52
  }
}
infos {
  cmd_id: 120
  element: LK
  edit_type: MV
  lk {
    mod_id: 3
    task_id: 4
    lk_id: 30
  }
  pos {
    x: 27
    y: 52
  }
  pos {
    x: 27
    y: 76
  }
  pos {
    x: 30
    y: 76
  }
}
infos {
  cmd_id: 121
  element: FB
  edit_type: ADD
  fb {
    mod_id: 3
    task_id: 4
    fb_id: 54
    flib_name: "Arithmetic"
    fc_name: "ADD_INT"
  }
  pos {
    x: 55
    y: 135
  }
}
infos {
  cmd_id: 122
  element: FB
  edit_type: MV
  fb {
    mod_id: 3
    task_id: 4
    fb_id: 54
  }
  pos {
    x: 101
    y: 175
  }
}
infos {
  cmd_id: 123
  element: PIN
  edit_type: SET
  pin {
    mod_id: 3
    task_id: 4
    fb_id: 54
    pin_index: 1
    pin_val {
      v {
        t: T_INT32
        i: 12
      }
      tm: 1680782281906390549
    }
  }
}
infos {
  cmd_id: 124
  element: PIN
  edit_type: SET
  pin {
    mod_id: 3
    task_id: 4
    fb_id: 54
    pin_index: 2
    pin_val {
      v {
        t: T_INT32
        i: 32
      }
      tm: 1680782288267285068
    }
  }
}
infos {
  cmd_id: 125
  element: TASK
  edit_type: ADD
  task {
    mod_id: 3
    task_id: 55
    task_name: "FSM2"
    interval: 2000
  }
}
infos {
  cmd_id: 126
  element: FB
  edit_type: ADD
  fb {
    mod_id: 3
    task_id: 55
    fb_id: 56
    flib_name: "System"
    fc_name: "SYSSTATE"
  }
  pos {
    x: 20
    y: 113
  }
}
infos {
  cmd_id: 127
  element: FB
  edit_type: MV
  fb {
    mod_id: 3
    task_id: 55
    fb_id: 56
  }
  pos {
    x: 19
    y: 77
  }
}
infos {
  cmd_id: 128
  element: FB
  edit_type: ADD
  fb {
    mod_id: 43
    task_id: 44
    fb_id: 57
    flib_name: "System"
    fc_name: "SYSSTATE"
  }
  pos {
    x: 20
    y: 113
  }
}
infos {
  cmd_id: 129
  element: FB
  edit_type: MV
  fb {
    mod_id: 43
    task_id: 44
    fb_id: 57
  }
  pos {
    x: 13
    y: 51
  }
}
infos {
  cmd_id: 130
  element: FB
  edit_type: ADD
  fb {
    mod_id: 3
    task_id: 4
    fb_id: 58
    flib_name: "Arithmetic"
    fc_name: "ADD_INT"
  }
  pos {
    x: 154
    y: 20
  }
}
