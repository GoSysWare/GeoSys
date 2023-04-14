infos {
  edit_type: SET
  proj {
    proj_name: "rotbot-engine-project"
    proj_uuid: "{0a8e4a59-5924-461f-9803-0b7e2dac25e4}"
  }
}
infos {
  cmd_id: 1
  element: MOD
  edit_type: ADD
  mod {
    mod_id: 1
    mod_name: "Module 1"
  }
}
infos {
  cmd_id: 2
  element: MOD
  edit_type: ADD
  mod {
    mod_id: 2
    mod_name: "Module 2"
  }
}
infos {
  cmd_id: 3
  element: TASK
  edit_type: ADD
  task {
    mod_id: 1
    task_id: 3
    task_name: "BASE"
    interval: 1000
  }
}
infos {
  cmd_id: 4
  element: FB
  edit_type: ADD
  fb {
    mod_id: 1
    task_id: 3
    fb_id: 4
    flib_name: "Arithmetic"
    fc_name: "MOVE_BOOL"
  }
  pos {
    x: 43
    y: 30
  }
}
infos {
  cmd_id: 5
  element: FB
  edit_type: MV
  fb {
    mod_id: 1
    task_id: 3
    fb_id: 4
  }
  pos {
    x: 20
    y: 17
  }
}
infos {
  cmd_id: 6
  element: FB
  edit_type: RM
  fb {
    mod_id: 1
    task_id: 3
    fb_id: 4
  }
}
infos {
  cmd_id: 7
  element: FB
  edit_type: ADD
  fb {
    mod_id: 1
    task_id: 3
    fb_id: 5
    flib_name: "Arithmetic"
    fc_name: "ADD_INT"
  }
  pos {
    x: 40
    y: 27
  }
}
infos {
  cmd_id: 8
  element: FB
  edit_type: ADD
  fb {
    mod_id: 1
    task_id: 3
    fb_id: 6
    flib_name: "System"
    fc_name: "SYSSTATE"
  }
  pos {
    x: 11
    y: 8
  }
}
infos {
  cmd_id: 16
  element: FB
  edit_type: ADD
  fb {
    mod_id: 1
    task_id: 3
    fb_id: 7
    flib_name: "Devices"
    fc_name: "SIM_READ"
  }
  pos {
    x: 15
    y: 35
  }
}
infos {
  cmd_id: 18
  element: PIN
  edit_type: SET
  pin {
    mod_id: 1
    task_id: 3
    fb_id: 7
    pin_index: 1
    pin_val {
      v {
        t: T_STRING
        str: "SIM"
      }
      tm: 1681389273012321844
    }
  }
}
infos {
  cmd_id: 20
  element: FB
  edit_type: MV
  fb {
    mod_id: 1
    task_id: 3
    fb_id: 6
  }
  pos {
    x: 15
    y: 3
  }
}
infos {
  cmd_id: 23
  element: FB
  edit_type: ADD
  fb {
    mod_id: 1
    task_id: 3
    fb_id: 8
    flib_name: "Converter"
    fc_name: "D2I"
  }
  pos {
    x: 52
    y: 42
  }
}
infos {
  cmd_id: 26
  element: FB
  edit_type: MV
  fb {
    mod_id: 1
    task_id: 3
    fb_id: 8
  }
  pos {
    x: 51
    y: 27
  }
}
infos {
  cmd_id: 27
  element: LK
  edit_type: ADD
  lk {
    mod_id: 1
    task_id: 3
    lk_id: 9
    src_fb_id: 7
    src_pin_index: 1
    target_fb_id: 8
    target_pin_index: 1
  }
  pos {
    x: 35
    y: 42
  }
  pos {
    x: 43
    y: 42
  }
  pos {
    x: 43
    y: 34
  }
  pos {
    x: 51
    y: 34
  }
}
infos {
  cmd_id: 28
  element: LK
  edit_type: ADD
  lk {
    mod_id: 1
    task_id: 3
    lk_id: 10
    src_fb_id: 8
    src_pin_index: 1
    target_fb_id: 5
    target_pin_index: 1
  }
  pos {
    x: 69
    y: 34
  }
  pos {
    x: 78
    y: 34
  }
  pos {
    x: 78
    y: 30
  }
  pos {
    x: 88
    y: 30
  }
}
infos {
  cmd_id: 29
  element: PIN
  edit_type: SET
  pin {
    mod_id: 1
    task_id: 3
    fb_id: 5
    pin_index: 2
    pin_val {
      v {
        t: T_INT32
        i: 100
      }
      tm: 1681389348653948686
    }
  }
}
infos {
  cmd_id: 32
  element: FB
  edit_type: MV
  fb {
    mod_id: 1
    task_id: 3
    fb_id: 5
  }
  pos {
    x: 90
    y: 27
  }
}
infos {
  cmd_id: 34
  element: FB
  edit_type: ADD
  fb {
    mod_id: 1
    task_id: 3
    fb_id: 11
    flib_name: "Arithmetic"
    fc_name: "DIV_INT"
  }
  pos {
    x: 129
    y: 35
  }
}
infos {
  cmd_id: 35
  element: FB
  edit_type: MV
  fb {
    mod_id: 1
    task_id: 3
    fb_id: 11
  }
  pos {
    x: 127
    y: 27
  }
}
infos {
  cmd_id: 36
  element: LK
  edit_type: ADD
  lk {
    mod_id: 1
    task_id: 3
    lk_id: 12
    src_fb_id: 5
    src_pin_index: 1
    target_fb_id: 11
    target_pin_index: 1
  }
  pos {
    x: 109
    y: 34
  }
  pos {
    x: 127
    y: 34
  }
}
infos {
  cmd_id: 37
  element: PIN
  edit_type: SET
  pin {
    mod_id: 1
    task_id: 3
    fb_id: 11
    pin_index: 2
    pin_val {
      v {
        t: T_INT32
        i: 10
      }
      tm: 1681389379553786801
    }
  }
}
infos {
  cmd_id: 38
  element: FB
  edit_type: ADD
  fb {
    mod_id: 1
    task_id: 3
    fb_id: 13
    flib_name: "Arithmetic"
    fc_name: "MUL_INT"
  }
  pos {
    x: 137
    y: 50
  }
}
infos {
  cmd_id: 39
  element: FB
  edit_type: MV
  fb {
    mod_id: 1
    task_id: 3
    fb_id: 13
  }
  pos {
    x: 127
    y: 43
  }
}
infos {
  cmd_id: 40
  element: LK
  edit_type: ADD
  lk {
    mod_id: 1
    task_id: 3
    lk_id: 14
    src_fb_id: 5
    src_pin_index: 1
    target_fb_id: 13
    target_pin_index: 1
  }
  pos {
    x: 109
    y: 34
  }
  pos {
    x: 118
    y: 34
  }
  pos {
    x: 118
    y: 50
  }
  pos {
    x: 127
    y: 50
  }
}
infos {
  cmd_id: 42
  element: PIN
  edit_type: SET
  pin {
    mod_id: 1
    task_id: 3
    fb_id: 13
    pin_index: 2
    pin_val {
      v {
        t: T_INT32
        i: 5
      }
      tm: 1681389410669280526
    }
  }
}
infos {
  cmd_id: 56
  element: FB
  edit_type: MV
  fb {
    mod_id: 1
    task_id: 3
    fb_id: 6
    fb_name: "\347\263\273\347\273\237\347\233\221\346\265\213"
  }
  pos {
    x: 15
    y: 3
  }
}
infos {
  cmd_id: 62
  element: FB
  edit_type: MV
  fb {
    mod_id: 1
    task_id: 3
    fb_id: 13
    fb_name: "\344\271\230\346\263\225"
  }
  pos {
    x: 174
    y: 42
  }
}
infos {
  cmd_id: 75
  element: FB
  edit_type: MV
  fb {
    mod_id: 1
    task_id: 3
    fb_id: 8
    fb_name: "Double\347\261\273\345\236\213\350\275\254\346\215\242Int"
  }
  pos {
    x: 63
    y: 28
  }
}
infos {
  cmd_id: 78
  element: FB
  edit_type: MV
  fb {
    mod_id: 1
    task_id: 3
    fb_id: 5
    fb_name: "\345\212\240\346\263\225"
  }
  pos {
    x: 117
    y: 28
  }
}
infos {
  cmd_id: 79
  element: LK
  edit_type: MV
  lk {
    mod_id: 1
    task_id: 3
    lk_id: 10
  }
  pos {
    x: 81
    y: 35
  }
  pos {
    x: 117
    y: 35
  }
}
infos {
  cmd_id: 82
  element: LK
  edit_type: MV
  lk {
    mod_id: 1
    task_id: 3
    lk_id: 14
  }
  pos {
    x: 133
    y: 35
  }
  pos {
    x: 97
    y: 35
  }
  pos {
    x: 97
    y: 49
  }
  pos {
    x: 174
    y: 49
  }
}
infos {
  cmd_id: 83
  element: FB
  edit_type: MV
  fb {
    mod_id: 1
    task_id: 3
    fb_id: 11
    fb_name: "\351\231\244\346\263\225"
  }
  pos {
    x: 174
    y: 28
  }
}
infos {
  cmd_id: 84
  element: LK
  edit_type: MV
  lk {
    mod_id: 1
    task_id: 3
    lk_id: 12
  }
  pos {
    x: 136
    y: 35
  }
  pos {
    x: 174
    y: 35
  }
}
infos {
  cmd_id: 85
  element: PIN
  edit_type: SET
  pin {
    mod_id: 1
    task_id: 3
    fb_id: 7
    pin_index: 2
    pin_val {
      v {
        t: T_STRING
        str: "$SECOND"
      }
      tm: 1681389913251943706
    }
  }
}
infos {
  cmd_id: 86
  element: FB
  edit_type: MV
  fb {
    mod_id: 1
    task_id: 3
    fb_id: 7
    fb_name: "\346\250\241\346\213\237\344\277\241\345\217\267"
  }
  pos {
    x: 21
    y: 28
  }
}
infos {
  cmd_id: 87
  element: LK
  edit_type: MV
  lk {
    mod_id: 1
    task_id: 3
    lk_id: 9
  }
  pos {
    x: 41
    y: 35
  }
  pos {
    x: 63
    y: 35
  }
}
infos {
  cmd_id: 88
  element: EV
  edit_type: ADD
  ev {
    ev_id: 15
    ev_name: "VAR_D_1"
    ev_type: 7
    ev_desc: "Desc"
    init_val {
      v {
        t: T_FLOAT64
        d: 0
      }
      tm: 1681390059182250282
    }
  }
}
infos {
  cmd_id: 89
  element: PIN
  edit_type: SET
  pin {
    mod_id: 1
    task_id: 3
    fb_id: 7
    pin_index: 6
    pin_val {
      v {
        t: T_STRING
        str: "RANDOM(10,30)"
      }
      tm: 1681390081110505874
    }
  }
}
infos {
  cmd_id: 90
  element: VO
  edit_type: ADD
  vo {
    mod_id: 1
    task_id: 3
    fb_id: 7
    pin_index: 5
    ev_id: 15
    vo_id: 16
  }
}
infos {
  cmd_id: 91
  element: FB
  edit_type: ADD
  fb {
    mod_id: 1
    task_id: 3
    fb_id: 17
    flib_name: "Arithmetic"
    fc_name: "MUL_DOUBLE"
  }
  pos {
    x: 72
    y: 64
  }
}
infos {
  cmd_id: 92
  element: VI
  edit_type: ADD
  vi {
    mod_id: 1
    task_id: 3
    fb_id: 17
    pin_index: 1
    ev_id: 15
    vi_id: 18
  }
}
infos {
  cmd_id: 93
  element: PIN
  edit_type: SET
  pin {
    mod_id: 1
    task_id: 3
    fb_id: 17
    pin_index: 2
    pin_val {
      v {
        t: T_FLOAT64
        d: 4
      }
      tm: 1681390122567857142
    }
  }
}
infos {
  cmd_id: 94
  element: FB
  edit_type: ADD
  fb {
    mod_id: 1
    task_id: 3
    fb_id: 19
    flib_name: "Arithmetic"
    fc_name: "SUB_DOUBLE"
  }
  pos {
    x: 123
    y: 73
  }
}
infos {
  cmd_id: 95
  element: LK
  edit_type: ADD
  lk {
    mod_id: 1
    task_id: 3
    lk_id: 20
    src_fb_id: 17
    src_pin_index: 1
    target_fb_id: 19
    target_pin_index: 1
  }
  pos {
    x: 91
    y: 71
  }
  pos {
    x: 107
    y: 71
  }
  pos {
    x: 107
    y: 80
  }
  pos {
    x: 123
    y: 80
  }
}
infos {
  cmd_id: 100
  element: FB
  edit_type: MV
  fb {
    mod_id: 1
    task_id: 3
    fb_id: 19
  }
  pos {
    x: 125
    y: 64
  }
}
infos {
  cmd_id: 101
  element: LK
  edit_type: MV
  lk {
    mod_id: 1
    task_id: 3
    lk_id: 20
  }
  pos {
    x: 91
    y: 71
  }
  pos {
    x: 125
    y: 71
  }
}
infos {
  cmd_id: 102
  element: EV
  edit_type: ADD
  ev {
    ev_id: 21
    ev_name: "VAR_D_2"
    ev_type: 7
    ev_desc: "Desc"
    init_val {
      v {
        t: T_FLOAT64
        d: 0
      }
      tm: 1681390217274104541
    }
  }
}
infos {
  cmd_id: 103
  element: VO
  edit_type: ADD
  vo {
    mod_id: 1
    task_id: 3
    fb_id: 19
    pin_index: 1
    ev_id: 21
    vo_id: 22
  }
}
infos {
  cmd_id: 104
  element: FB
  edit_type: MV
  fb {
    mod_id: 1
    task_id: 3
    fb_id: 17
    fb_name: "Double \344\271\230\346\263\225"
  }
  pos {
    x: 72
    y: 64
  }
}
infos {
  cmd_id: 105
  element: FB
  edit_type: MV
  fb {
    mod_id: 1
    task_id: 3
    fb_id: 19
    fb_name: "Ddouble \345\207\217\346\263\225"
  }
  pos {
    x: 125
    y: 64
  }
}
infos {
  cmd_id: 106
  element: FB
  edit_type: ADD
  fb {
    mod_id: 1
    task_id: 3
    fb_id: 23
    flib_name: "Converter"
    fc_name: "D2STR"
  }
  pos {
    x: 170
    y: 82
  }
}
infos {
  cmd_id: 107
  element: FB
  edit_type: MV
  fb {
    mod_id: 1
    task_id: 3
    fb_id: 23
  }
  pos {
    x: 126
    y: 84
  }
}
infos {
  cmd_id: 108
  element: FB
  edit_type: MV
  fb {
    mod_id: 1
    task_id: 3
    fb_id: 23
    fb_name: "DOUBLE \350\275\254\346\215\242STRING\345\234\250"
  }
  pos {
    x: 126
    y: 84
  }
}
infos {
  cmd_id: 109
  element: FB
  edit_type: MV
  fb {
    mod_id: 1
    task_id: 3
    fb_id: 23
    fb_name: "DOUBLE \350\275\254\346\215\242STRING"
  }
  pos {
    x: 126
    y: 84
  }
}
infos {
  cmd_id: 110
  element: LK
  edit_type: ADD
  lk {
    mod_id: 1
    task_id: 3
    lk_id: 24
    src_fb_id: 17
    src_pin_index: 1
    target_fb_id: 23
    target_pin_index: 1
  }
  pos {
    x: 91
    y: 71
  }
  pos {
    x: 108
    y: 71
  }
  pos {
    x: 108
    y: 91
  }
  pos {
    x: 126
    y: 91
  }
}
infos {
  cmd_id: 111
  element: FB
  edit_type: ADD
  fb {
    mod_id: 1
    task_id: 3
    fb_id: 25
    flib_name: "Converter"
    fc_name: "D2UI"
  }
  pos {
    x: 80
    y: 103
  }
}
infos {
  cmd_id: 112
  element: PIN
  edit_type: SET
  pin {
    mod_id: 1
    task_id: 3
    fb_id: 25
    pin_index: 1
    pin_val {
      v {
        t: T_FLOAT64
        d: -1.5670000314712524
      }
      tm: 1681390525958231642
    }
  }
}
infos {
  cmd_id: 113
  element: FB
  edit_type: MV
  fb {
    mod_id: 1
    task_id: 3
    fb_id: 25
  }
  pos {
    x: 74
    y: 101
  }
}
infos {
  cmd_id: 116
  element: EV
  edit_type: ADD
  ev {
    ev_id: 26
    ev_name: "SPEED"
    ev_type: 3
    ev_desc: "\345\275\223\345\211\215\350\275\246\351\200\237"
    init_val {
      v {
        t: T_UINT32
        ui: 0
      }
      tm: 1681391756514041211
    }
  }
}
infos {
  cmd_id: 119
  element: PIN
  edit_type: SET
  pin {
    mod_id: 1
    task_id: 3
    fb_id: 7
    pin_index: 9
    pin_val {
      v {
        t: T_STRING
        str: "\357\277\245SECOND"
      }
      tm: 1681391838813644311
    }
  }
}
infos {
  cmd_id: 120
  element: PIN
  edit_type: SET
  pin {
    mod_id: 1
    task_id: 3
    fb_id: 7
    pin_index: 9
    pin_val {
      v {
        t: T_STRING
        str: "$SECOND"
      }
      tm: 1681391855396405663
    }
  }
}
infos {
  cmd_id: 121
  element: FB
  edit_type: ADD
  fb {
    mod_id: 1
    task_id: 3
    fb_id: 27
    flib_name: "Converter"
    fc_name: "D2UI"
  }
  pos {
    x: 61
    y: 50
  }
}
infos {
  cmd_id: 123
  element: LK
  edit_type: ADD
  lk {
    mod_id: 1
    task_id: 3
    lk_id: 28
    src_fb_id: 7
    src_pin_index: 8
    target_fb_id: 27
    target_pin_index: 1
  }
  pos {
    x: 41
    y: 49
  }
  pos {
    x: 52
    y: 49
  }
  pos {
    x: 52
    y: 54
  }
  pos {
    x: 64
    y: 54
  }
}
infos {
  cmd_id: 128
  element: FB
  edit_type: MV
  fb {
    mod_id: 1
    task_id: 3
    fb_id: 27
  }
  pos {
    x: 64
    y: 42
  }
}
infos {
  cmd_id: 129
  element: LK
  edit_type: MV
  lk {
    mod_id: 1
    task_id: 3
    lk_id: 28
  }
  pos {
    x: 41
    y: 49
  }
  pos {
    x: 64
    y: 49
  }
}
infos {
  cmd_id: 130
  element: EV
  edit_type: ADD
  ev {
    ev_id: 29
    ev_name: "UI_1"
    ev_type: 3
    ev_desc: "ceshi"
    init_val {
      v {
        t: T_UINT32
        ui: 0
      }
      tm: 1681391940976818792
    }
  }
}
infos {
  cmd_id: 131
  element: VO
  edit_type: ADD
  vo {
    mod_id: 1
    task_id: 3
    fb_id: 27
    pin_index: 1
    ev_id: 29
    vo_id: 30
  }
}
infos {
  cmd_id: 132
  element: FB
  edit_type: MV
  fb {
    mod_id: 1
    task_id: 3
    fb_id: 25
    fb_name: "\350\275\254\346\215\242\346\272\242\345\207\272"
  }
  pos {
    x: 72
    y: 83
  }
}
infos {
  cmd_id: 133
  element: FB
  edit_type: ADD
  fb {
    mod_id: 1
    task_id: 3
    fb_id: 31
    flib_name: "Comparison"
    fc_name: "GE_UINT"
  }
  pos {
    x: 79
    y: 109
  }
}
infos {
  cmd_id: 134
  element: VI
  edit_type: ADD
  vi {
    mod_id: 1
    task_id: 3
    fb_id: 31
    pin_index: 1
    ev_id: 29
    vi_id: 32
  }
}
infos {
  cmd_id: 135
  element: PIN
  edit_type: SET
  pin {
    mod_id: 1
    task_id: 3
    fb_id: 31
    pin_index: 2
    pin_val {
      v {
        t: T_UINT32
        ui: 30
      }
      tm: 1681391985968155815
    }
  }
}
infos {
  cmd_id: 136
  element: FB
  edit_type: MV
  fb {
    mod_id: 1
    task_id: 3
    fb_id: 31
  }
  pos {
    x: 72
    y: 106
  }
}
infos {
  cmd_id: 137
  element: FB
  edit_type: MV
  fb {
    mod_id: 1
    task_id: 3
    fb_id: 31
    fb_name: "Uint \345\244\247\344\272\216\346\257\224\350\276\203"
  }
  pos {
    x: 72
    y: 106
  }
}
infos {
  cmd_id: 138
  element: FB
  edit_type: ADD
  fb {
    mod_id: 1
    task_id: 3
    fb_id: 33
    flib_name: "Comparison"
    fc_name: "NE_UINT"
  }
  pos {
    x: 80
    y: 128
  }
}
infos {
  cmd_id: 139
  element: FB
  edit_type: MV
  fb {
    mod_id: 1
    task_id: 3
    fb_id: 33
  }
  pos {
    x: 72
    y: 123
  }
}
infos {
  cmd_id: 140
  element: VI
  edit_type: ADD
  vi {
    mod_id: 1
    task_id: 3
    fb_id: 33
    pin_index: 1
    ev_id: 29
    vi_id: 34
  }
}
infos {
  cmd_id: 141
  element: FB
  edit_type: MV
  fb {
    mod_id: 1
    task_id: 3
    fb_id: 33
    fb_name: "Uint \344\270\215\347\255\211\344\272\216\346\257\224\350\276\203"
  }
  pos {
    x: 72
    y: 123
  }
}
infos {
  cmd_id: 142
  element: PIN
  edit_type: SET
  pin {
    mod_id: 1
    task_id: 3
    fb_id: 33
    pin_index: 2
    pin_val {
      v {
        t: T_UINT32
        ui: 20
      }
      tm: 1681392098535057673
    }
  }
}
infos {
  cmd_id: 143
  element: FB
  edit_type: ADD
  fb {
    mod_id: 1
    task_id: 3
    fb_id: 35
    flib_name: "Logic"
    fc_name: "AND4"
  }
  pos {
    x: 121
    y: 113
  }
}
infos {
  cmd_id: 144
  element: FB
  edit_type: MV
  fb {
    mod_id: 1
    task_id: 3
    fb_id: 35
  }
  pos {
    x: 124
    y: 106
  }
}
infos {
  cmd_id: 145
  element: LK
  edit_type: ADD
  lk {
    mod_id: 1
    task_id: 3
    lk_id: 36
    src_fb_id: 31
    src_pin_index: 1
    target_fb_id: 35
    target_pin_index: 1
  }
  pos {
    x: 91
    y: 113
  }
  pos {
    x: 124
    y: 113
  }
}
infos {
  cmd_id: 146
  element: LK
  edit_type: ADD
  lk {
    mod_id: 1
    task_id: 3
    lk_id: 37
    src_fb_id: 33
    src_pin_index: 1
    target_fb_id: 35
    target_pin_index: 2
  }
  pos {
    x: 91
    y: 130
  }
  pos {
    x: 107
    y: 130
  }
  pos {
    x: 107
    y: 115
  }
  pos {
    x: 124
    y: 115
  }
}
infos {
  cmd_id: 147
  element: PIN
  edit_type: SET
  pin {
    mod_id: 1
    task_id: 3
    fb_id: 35
    pin_index: 3
    pin_val {
      v {
        t: T_BOOL
        b: true
      }
      tm: 1681392126501870835
    }
  }
}
infos {
  cmd_id: 148
  element: PIN
  edit_type: SET
  pin {
    mod_id: 1
    task_id: 3
    fb_id: 35
    pin_index: 4
    pin_val {
      v {
        t: T_BOOL
        b: true
      }
      tm: 1681392129150109025
    }
  }
}
infos {
  cmd_id: 149
  element: EV
  edit_type: ADD
  ev {
    ev_id: 38
    ev_name: "Bool_1"
    ev_type: 1
    ev_desc: "ceshi"
    init_val {
      v {
        t: T_BOOL
        b: false
      }
      tm: 1681392151285941025
    }
  }
}
infos {
  cmd_id: 150
  element: VO
  edit_type: ADD
  vo {
    mod_id: 1
    task_id: 3
    fb_id: 35
    pin_index: 1
    ev_id: 38
    vo_id: 39
  }
}
infos {
  cmd_id: 151
  element: FB
  edit_type: ADD
  fb {
    mod_id: 1
    task_id: 3
    fb_id: 40
    flib_name: "Logic"
    fc_name: "OR"
  }
  pos {
    x: 131
    y: 134
  }
}
infos {
  cmd_id: 152
  element: LK
  edit_type: ADD
  lk {
    mod_id: 1
    task_id: 3
    lk_id: 41
    src_fb_id: 33
    src_pin_index: 1
    target_fb_id: 40
    target_pin_index: 1
  }
  pos {
    x: 91
    y: 130
  }
  pos {
    x: 111
    y: 130
  }
  pos {
    x: 111
    y: 141
  }
  pos {
    x: 131
    y: 141
  }
}
infos {
  cmd_id: 154
  element: FB
  edit_type: MV
  fb {
    mod_id: 1
    task_id: 3
    fb_id: 40
  }
  pos {
    x: 124
    y: 129
  }
}
infos {
  cmd_id: 155
  element: LK
  edit_type: MV
  lk {
    mod_id: 1
    task_id: 3
    lk_id: 41
  }
  pos {
    x: 91
    y: 130
  }
  pos {
    x: 107
    y: 130
  }
  pos {
    x: 107
    y: 136
  }
  pos {
    x: 124
    y: 136
  }
}
infos {
  cmd_id: 156
  element: PIN
  edit_type: SET
  pin {
    mod_id: 1
    task_id: 3
    fb_id: 40
    pin_index: 2
    pin_val {
      v {
        t: T_BOOL
        b: true
      }
      tm: 1681392205670493028
    }
  }
}
infos {
  cmd_id: 157
  element: FB
  edit_type: ADD
  fb {
    mod_id: 1
    task_id: 3
    fb_id: 42
    flib_name: "Logic"
    fc_name: "NOT"
  }
  pos {
    x: 133
    y: 152
  }
}
infos {
  cmd_id: 158
  element: FB
  edit_type: MV
  fb {
    mod_id: 1
    task_id: 3
    fb_id: 42
  }
  pos {
    x: 125
    y: 148
  }
}
infos {
  cmd_id: 159
  element: LK
  edit_type: ADD
  lk {
    mod_id: 1
    task_id: 3
    lk_id: 43
    src_fb_id: 33
    src_pin_index: 1
    target_fb_id: 42
    target_pin_index: 1
  }
  pos {
    x: 91
    y: 130
  }
  pos {
    x: 108
    y: 130
  }
  pos {
    x: 108
    y: 155
  }
  pos {
    x: 125
    y: 155
  }
}
infos {
  cmd_id: 160
  element: LK
  edit_type: MV
  lk {
    mod_id: 1
    task_id: 3
    lk_id: 43
  }
  pos {
    x: 91
    y: 130
  }
  pos {
    x: 107
    y: 130
  }
  pos {
    x: 107
    y: 155
  }
  pos {
    x: 125
    y: 155
  }
}
infos {
  cmd_id: 161
  element: EV
  edit_type: ADD
  ev {
    ev_id: 44
    ev_name: "Bool_2"
    ev_type: 1
    ev_desc: "ceshi"
    init_val {
      v {
        t: T_BOOL
        b: true
      }
      tm: 1681392250886556508
    }
  }
}
infos {
  cmd_id: 162
  element: VO
  edit_type: ADD
  vo {
    mod_id: 1
    task_id: 3
    fb_id: 42
    pin_index: 1
    ev_id: 44
    vo_id: 45
  }
}
infos {
  cmd_id: 163
  element: FB
  edit_type: MV
  fb {
    mod_id: 1
    task_id: 3
    fb_id: 35
    fb_name: "\344\270\216"
  }
  pos {
    x: 124
    y: 106
  }
}
infos {
  cmd_id: 164
  element: FB
  edit_type: MV
  fb {
    mod_id: 1
    task_id: 3
    fb_id: 40
    fb_name: "\346\210\226"
  }
  pos {
    x: 124
    y: 129
  }
}
infos {
  cmd_id: 165
  element: FB
  edit_type: MV
  fb {
    mod_id: 1
    task_id: 3
    fb_id: 42
    fb_name: "\351\235\236"
  }
  pos {
    x: 125
    y: 148
  }
}
infos {
  cmd_id: 166
  element: TASK
  edit_type: ADD
  task {
    mod_id: 1
    task_id: 46
    task_name: "FSM"
    interval: 1000
  }
}
infos {
  cmd_id: 167
  element: EV
  edit_type: ADD
  ev {
    ev_id: 47
    ev_name: "FSM_State"
    ev_type: 2
    ev_desc: "Desc"
    init_val {
      v {
        t: T_INT32
        i: 0
      }
      tm: 1681392704066944665
    }
  }
}
infos {
  cmd_id: 168
  element: FB
  edit_type: ADD
  fb {
    mod_id: 1
    task_id: 46
    fb_id: 48
    flib_name: "Fsm"
    fc_name: "FSM"
  }
  pos {
    x: 46
    y: 111
  }
}
infos {
  cmd_id: 169
  element: FB
  edit_type: ADD
  fb {
    mod_id: 1
    task_id: 46
    fb_id: 49
    flib_name: "Fsm"
    fc_name: "FSM"
  }
  pos {
    x: 128
    y: 117
  }
}
infos {
  cmd_id: 173
  element: FB
  edit_type: ADD
  fb {
    mod_id: 1
    task_id: 46
    fb_id: 50
    flib_name: "Fsm"
    fc_name: "FSM"
  }
  pos {
    x: 191
    y: 114
  }
}
infos {
  cmd_id: 174
  element: FB
  edit_type: ADD
  fb {
    mod_id: 1
    task_id: 46
    fb_id: 51
    flib_name: "Fsm"
    fc_name: "FSM"
  }
  pos {
    x: 260
    y: 118
  }
}
infos {
  cmd_id: 181
  element: FB
  edit_type: ADD
  fb {
    mod_id: 1
    task_id: 46
    fb_id: 52
    flib_name: "Fsm"
    fc_name: "FSM"
  }
  pos {
    x: 226
    y: 107
  }
}
infos {
  cmd_id: 185
  element: PIN
  edit_type: SET
  pin {
    mod_id: 1
    task_id: 46
    fb_id: 48
    pin_index: 4
    pin_val {
      v {
        t: T_INT32
        i: 1
      }
      tm: 1681393707260383526
    }
  }
}
infos {
  cmd_id: 186
  element: PIN
  edit_type: SET
  pin {
    mod_id: 1
    task_id: 46
    fb_id: 49
    pin_index: 4
    pin_val {
      v {
        t: T_INT32
        i: 2
      }
      tm: 1681393710948686277
    }
  }
}
infos {
  cmd_id: 187
  element: PIN
  edit_type: SET
  pin {
    mod_id: 1
    task_id: 46
    fb_id: 50
    pin_index: 4
    pin_val {
      v {
        t: T_INT32
        i: 3
      }
      tm: 1681393714188719332
    }
  }
}
infos {
  cmd_id: 188
  element: PIN
  edit_type: SET
  pin {
    mod_id: 1
    task_id: 46
    fb_id: 51
    pin_index: 4
    pin_val {
      v {
        t: T_INT32
        i: 4
      }
      tm: 1681393717228645616
    }
  }
}
infos {
  cmd_id: 189
  element: PIN
  edit_type: SET
  pin {
    mod_id: 1
    task_id: 46
    fb_id: 52
    pin_index: 4
    pin_val {
      v {
        t: T_INT32
        i: 1
      }
      tm: 1681393721228594723
    }
  }
}
infos {
  cmd_id: 190
  element: LK
  edit_type: ADD
  lk {
    mod_id: 1
    task_id: 46
    lk_id: 53
    src_fb_id: 48
    src_pin_index: 1
    target_fb_id: 49
    target_pin_index: 2
  }
  pos {
    x: 63
    y: 114
  }
  pos {
    x: 85
    y: 114
  }
  pos {
    x: 85
    y: 116
  }
  pos {
    x: 107
    y: 116
  }
}
infos {
  cmd_id: 191
  element: LK
  edit_type: ADD
  lk {
    mod_id: 1
    task_id: 46
    lk_id: 54
    src_fb_id: 49
    src_pin_index: 1
    target_fb_id: 50
    target_pin_index: 2
  }
  pos {
    x: 128
    y: 114
  }
  pos {
    x: 147
    y: 114
  }
  pos {
    x: 147
    y: 116
  }
  pos {
    x: 166
    y: 116
  }
}
infos {
  cmd_id: 192
  element: LK
  edit_type: ADD
  lk {
    mod_id: 1
    task_id: 46
    lk_id: 55
    src_fb_id: 50
    src_pin_index: 1
    target_fb_id: 51
    target_pin_index: 2
  }
  pos {
    x: 187
    y: 114
  }
  pos {
    x: 206
    y: 114
  }
  pos {
    x: 206
    y: 116
  }
  pos {
    x: 226
    y: 116
  }
}
infos {
  cmd_id: 193
  element: LK
  edit_type: ADD
  lk {
    mod_id: 1
    task_id: 46
    lk_id: 56
    src_fb_id: 51
    src_pin_index: 1
    target_fb_id: 52
    target_pin_index: 2
  }
  pos {
    x: 247
    y: 114
  }
  pos {
    x: 260
    y: 114
  }
  pos {
    x: 260
    y: 115
  }
  pos {
    x: 274
    y: 115
  }
}
infos {
  cmd_id: 194
  element: FB
  edit_type: MV
  fb {
    mod_id: 1
    task_id: 46
    fb_id: 49
  }
  pos {
    x: 107
    y: 105
  }
}
infos {
  cmd_id: 197
  element: FB
  edit_type: MV
  fb {
    mod_id: 1
    task_id: 46
    fb_id: 50
  }
  pos {
    x: 165
    y: 103
  }
}
infos {
  cmd_id: 198
  element: LK
  edit_type: MV
  lk {
    mod_id: 1
    task_id: 46
    lk_id: 54
  }
  pos {
    x: 128
    y: 112
  }
  pos {
    x: 165
    y: 112
  }
}
infos {
  cmd_id: 209
  element: FB
  edit_type: MV
  fb {
    mod_id: 1
    task_id: 46
    fb_id: 51
  }
  pos {
    x: 226
    y: 101
  }
}
infos {
  cmd_id: 210
  element: LK
  edit_type: MV
  lk {
    mod_id: 1
    task_id: 46
    lk_id: 55
  }
  pos {
    x: 186
    y: 110
  }
  pos {
    x: 226
    y: 110
  }
}
infos {
  cmd_id: 216
  element: FB
  edit_type: MV
  fb {
    mod_id: 1
    task_id: 46
    fb_id: 52
  }
  pos {
    x: 273
    y: 99
  }
}
infos {
  cmd_id: 217
  element: LK
  edit_type: MV
  lk {
    mod_id: 1
    task_id: 46
    lk_id: 56
  }
  pos {
    x: 247
    y: 108
  }
  pos {
    x: 273
    y: 108
  }
}
infos {
  cmd_id: 218
  element: FB
  edit_type: ADD
  fb {
    mod_id: 1
    task_id: 46
    fb_id: 57
    flib_name: "Devices"
    fc_name: "SIM_READ"
  }
  pos {
    x: 41
    y: 58
  }
}
infos {
  cmd_id: 220
  element: PIN
  edit_type: SET
  pin {
    mod_id: 1
    task_id: 46
    fb_id: 57
    pin_index: 1
    pin_val {
      v {
        t: T_STRING
        str: "SIM"
      }
      tm: 1681393788453108669
    }
  }
}
infos {
  cmd_id: 221
  element: PIN
  edit_type: SET
  pin {
    mod_id: 1
    task_id: 46
    fb_id: 57
    pin_index: 5
    pin_val {
      v {
        t: T_STRING
        str: "$SECOND"
      }
      tm: 1681393806069276312
    }
  }
}
infos {
  cmd_id: 222
  element: FB
  edit_type: ADD
  fb {
    mod_id: 1
    task_id: 46
    fb_id: 58
    flib_name: "Converter"
    fc_name: "D2UI"
  }
  pos {
    x: 87
    y: 58
  }
}
infos {
  cmd_id: 223
  element: LK
  edit_type: ADD
  lk {
    mod_id: 1
    task_id: 46
    lk_id: 59
    src_fb_id: 57
    src_pin_index: 4
    target_fb_id: 58
    target_pin_index: 1
  }
  pos {
    x: 64
    y: 61
  }
  pos {
    x: 75
    y: 61
  }
  pos {
    x: 75
    y: 65
  }
  pos {
    x: 87
    y: 65
  }
}
infos {
  cmd_id: 234
  element: FB
  edit_type: MV
  fb {
    mod_id: 1
    task_id: 46
    fb_id: 57
  }
  pos {
    x: 43
    y: 14
  }
}
infos {
  cmd_id: 236
  element: FB
  edit_type: MV
  fb {
    mod_id: 1
    task_id: 46
    fb_id: 58
  }
  pos {
    x: 86
    y: 20
  }
}
infos {
  cmd_id: 237
  element: LK
  edit_type: MV
  lk {
    mod_id: 1
    task_id: 46
    lk_id: 59
  }
  pos {
    x: 63
    y: 27
  }
  pos {
    x: 86
    y: 27
  }
}
infos {
  cmd_id: 238
  element: VO
  edit_type: ADD
  vo {
    mod_id: 1
    task_id: 46
    fb_id: 58
    pin_index: 1
    ev_id: 26
    vo_id: 60
  }
}
infos {
  cmd_id: 239
  element: PIN
  edit_type: SET
  pin {
    mod_id: 1
    task_id: 46
    fb_id: 48
    pin_index: 1
    pin_val {
      v {
        t: T_BOOL
        b: true
      }
      tm: 1681393863909547899
    }
  }
}
infos {
  cmd_id: 240
  element: PIN
  edit_type: SET
  pin {
    mod_id: 1
    task_id: 46
    fb_id: 48
    pin_index: 2
    pin_val {
      v {
        t: T_BOOL
        b: true
      }
      tm: 1681393867853697168
    }
  }
}
infos {
  cmd_id: 241
  element: FB
  edit_type: ADD
  fb {
    mod_id: 1
    task_id: 46
    fb_id: 61
    flib_name: "Comparison"
    fc_name: "EQ_UINT"
  }
  pos {
    x: 52
    y: 75
  }
}
infos {
  cmd_id: 242
  element: PIN
  edit_type: SET
  pin {
    mod_id: 1
    task_id: 46
    fb_id: 61
    pin_index: 1
    pin_val {
      v {
        t: T_UINT32
        ui: 0
      }
      tm: 1681393928855174418
    }
  }
}
infos {
  cmd_id: 244
  element: VI
  edit_type: ADD
  vi {
    mod_id: 1
    task_id: 46
    fb_id: 61
    pin_index: 2
    ev_id: 26
    vi_id: 62
  }
}
infos {
  cmd_id: 245
  element: LK
  edit_type: ADD
  lk {
    mod_id: 1
    task_id: 46
    lk_id: 63
    src_fb_id: 61
    src_pin_index: 1
    target_fb_id: 48
    target_pin_index: 1
  }
  pos {
    x: 68
    y: 76
  }
  pos {
    x: 55
    y: 76
  }
  pos {
    x: 55
    y: 114
  }
  pos {
    x: 42
    y: 114
  }
}
infos {
  cmd_id: 254
  element: FB
  edit_type: MV
  fb {
    mod_id: 1
    task_id: 46
    fb_id: 48
  }
  pos {
    x: 60
    y: 107
  }
}
infos {
  cmd_id: 255
  element: LK
  edit_type: MV
  lk {
    mod_id: 1
    task_id: 46
    lk_id: 53
  }
  pos {
    x: 81
    y: 114
  }
  pos {
    x: 107
    y: 114
  }
}
infos {
  cmd_id: 259
  element: FB
  edit_type: MV
  fb {
    mod_id: 1
    task_id: 46
    fb_id: 61
  }
  pos {
    x: 32
    y: 83
  }
}
infos {
  cmd_id: 260
  element: LK
  edit_type: MV
  lk {
    mod_id: 1
    task_id: 46
    lk_id: 63
  }
  pos {
    x: 51
    y: 90
  }
  pos {
    x: 55
    y: 90
  }
  pos {
    x: 55
    y: 114
  }
  pos {
    x: 60
    y: 114
  }
}
infos {
  cmd_id: 261
  element: FB
  edit_type: ADD
  fb {
    mod_id: 1
    task_id: 46
    fb_id: 64
    flib_name: "Comparison"
    fc_name: "LE_UINT"
  }
  pos {
    x: 99
    y: 75
  }
}
infos {
  cmd_id: 262
  element: VI
  edit_type: ADD
  vi {
    mod_id: 1
    task_id: 46
    fb_id: 64
    pin_index: 1
    ev_id: 26
    vi_id: 65
  }
}
infos {
  cmd_id: 263
  element: PIN
  edit_type: SET
  pin {
    mod_id: 1
    task_id: 46
    fb_id: 64
    pin_index: 2
    pin_val {
      v {
        t: T_UINT32
        ui: 10
      }
      tm: 1681394047775741897
    }
  }
}
infos {
  cmd_id: 265
  element: LK
  edit_type: ADD
  lk {
    mod_id: 1
    task_id: 46
    lk_id: 66
    src_fb_id: 64
    src_pin_index: 1
    target_fb_id: 49
    target_pin_index: 1
  }
  pos {
    x: 87
    y: 75
  }
  pos {
    x: 97
    y: 75
  }
  pos {
    x: 97
    y: 112
  }
  pos {
    x: 107
    y: 112
  }
}
infos {
  cmd_id: 266
  element: VI
  edit_type: ADD
  vi {
    mod_id: 1
    task_id: 46
    fb_id: 48
    pin_index: 3
    ev_id: 47
    vi_id: 67
  }
}
infos {
  cmd_id: 267
  element: VI
  edit_type: ADD
  vi {
    mod_id: 1
    task_id: 46
    fb_id: 49
    pin_index: 3
    ev_id: 47
    vi_id: 68
  }
}
infos {
  cmd_id: 268
  element: VI
  edit_type: ADD
  vi {
    mod_id: 1
    task_id: 46
    fb_id: 50
    pin_index: 3
    ev_id: 47
    vi_id: 69
  }
}
infos {
  cmd_id: 269
  element: VI
  edit_type: ADD
  vi {
    mod_id: 1
    task_id: 46
    fb_id: 51
    pin_index: 3
    ev_id: 47
    vi_id: 70
  }
}
infos {
  cmd_id: 270
  element: VI
  edit_type: ADD
  vi {
    mod_id: 1
    task_id: 46
    fb_id: 52
    pin_index: 3
    ev_id: 47
    vi_id: 71
  }
}
infos {
  cmd_id: 271
  element: FB
  edit_type: ADD
  fb {
    mod_id: 1
    task_id: 46
    fb_id: 72
    flib_name: "Comparison"
    fc_name: "LE_UINT"
  }
  pos {
    x: 131
    y: 61
  }
}
infos {
  cmd_id: 273
  element: FB
  edit_type: ADD
  fb {
    mod_id: 1
    task_id: 46
    fb_id: 73
    flib_name: "Comparison"
    fc_name: "LT_UINT"
  }
  pos {
    x: 134
    y: 74
  }
}
infos {
  cmd_id: 278
  element: FB
  edit_type: ADD
  fb {
    mod_id: 1
    task_id: 46
    fb_id: 74
    flib_name: "Logic"
    fc_name: "AND"
  }
  pos {
    x: 162
    y: 58
  }
}
infos {
  cmd_id: 280
  element: LK
  edit_type: ADD
  lk {
    mod_id: 1
    task_id: 46
    lk_id: 75
    src_fb_id: 72
    src_pin_index: 1
    target_fb_id: 74
    target_pin_index: 1
  }
  pos {
    x: 145
    y: 53
  }
  pos {
    x: 153
    y: 53
  }
  pos {
    x: 153
    y: 57
  }
  pos {
    x: 161
    y: 57
  }
}
infos {
  cmd_id: 281
  element: LK
  edit_type: ADD
  lk {
    mod_id: 1
    task_id: 46
    lk_id: 76
    src_fb_id: 73
    src_pin_index: 1
    target_fb_id: 74
    target_pin_index: 2
  }
  pos {
    x: 145
    y: 68
  }
  pos {
    x: 153
    y: 68
  }
  pos {
    x: 153
    y: 59
  }
  pos {
    x: 161
    y: 59
  }
}
infos {
  cmd_id: 282
  element: LK
  edit_type: ADD
  lk {
    mod_id: 1
    task_id: 46
    lk_id: 77
    src_fb_id: 74
    src_pin_index: 1
    target_fb_id: 50
    target_pin_index: 1
  }
  pos {
    x: 180
    y: 57
  }
  pos {
    x: 172
    y: 57
  }
  pos {
    x: 172
    y: 110
  }
  pos {
    x: 165
    y: 110
  }
}
infos {
  cmd_id: 289
  element: FB
  edit_type: MV
  fb {
    mod_id: 1
    task_id: 46
    fb_id: 72
  }
  pos {
    x: 105
    y: 65
  }
}
infos {
  cmd_id: 290
  element: FB
  edit_type: MV
  fb {
    mod_id: 1
    task_id: 46
    fb_id: 73
  }
  pos {
    x: 105
    y: 80
  }
}
infos {
  cmd_id: 291
  element: FB
  edit_type: MV
  fb {
    mod_id: 1
    task_id: 46
    fb_id: 74
  }
  pos {
    x: 140
    y: 69
  }
}
infos {
  cmd_id: 292
  element: LK
  edit_type: MV
  lk {
    mod_id: 1
    task_id: 46
    lk_id: 75
  }
  pos {
    x: 124
    y: 72
  }
  pos {
    x: 132
    y: 72
  }
  pos {
    x: 132
    y: 76
  }
  pos {
    x: 140
    y: 76
  }
}
infos {
  cmd_id: 293
  element: LK
  edit_type: MV
  lk {
    mod_id: 1
    task_id: 46
    lk_id: 76
  }
  pos {
    x: 124
    y: 87
  }
  pos {
    x: 132
    y: 87
  }
  pos {
    x: 132
    y: 78
  }
  pos {
    x: 140
    y: 78
  }
}
infos {
  cmd_id: 295
  element: LK
  edit_type: MV
  lk {
    mod_id: 1
    task_id: 46
    lk_id: 77
  }
  pos {
    x: 159
    y: 76
  }
  pos {
    x: 163
    y: 76
  }
  pos {
    x: 163
    y: 110
  }
  pos {
    x: 165
    y: 110
  }
}
infos {
  cmd_id: 296
  element: FB
  edit_type: MV
  fb {
    mod_id: 1
    task_id: 46
    fb_id: 64
  }
  pos {
    x: 60
    y: 68
  }
}
infos {
  cmd_id: 298
  element: LK
  edit_type: MV
  lk {
    mod_id: 1
    task_id: 46
    lk_id: 66
  }
  pos {
    x: 79
    y: 75
  }
  pos {
    x: 89
    y: 75
  }
  pos {
    x: 89
    y: 112
  }
  pos {
    x: 107
    y: 112
  }
}
infos {
  cmd_id: 299
  element: VI
  edit_type: ADD
  vi {
    mod_id: 1
    task_id: 46
    fb_id: 73
    pin_index: 1
    ev_id: 26
    vi_id: 78
  }
}
infos {
  cmd_id: 300
  element: VI
  edit_type: ADD
  vi {
    mod_id: 1
    task_id: 46
    fb_id: 72
    pin_index: 1
    ev_id: 26
    vi_id: 79
  }
}
infos {
  cmd_id: 301
  element: PIN
  edit_type: SET
  pin {
    mod_id: 1
    task_id: 46
    fb_id: 72
    pin_index: 2
    pin_val {
      v {
        t: T_UINT32
        ui: 30
      }
      tm: 1681394188496796381
    }
  }
}
infos {
  cmd_id: 302
  element: PIN
  edit_type: SET
  pin {
    mod_id: 1
    task_id: 46
    fb_id: 73
    pin_index: 2
    pin_val {
      v {
        t: T_UINT32
        ui: 10
      }
      tm: 1681394192929243388
    }
  }
}
infos {
  cmd_id: 303
  element: FB
  edit_type: ADD
  fb {
    mod_id: 1
    task_id: 46
    fb_id: 80
    flib_name: "Comparison"
    fc_name: "LT_UINT"
  }
  pos {
    x: 105
    y: 80
  }
}
infos {
  cmd_id: 304
  element: FB
  edit_type: MV
  fb {
    mod_id: 1
    task_id: 46
    fb_id: 80
  }
  pos {
    x: 199
    y: 72
  }
}
infos {
  cmd_id: 305
  element: VI
  edit_type: ADD
  vi {
    mod_id: 1
    task_id: 46
    fb_id: 80
    pin_index: 1
    ev_id: 26
    vi_id: 81
  }
}
infos {
  cmd_id: 306
  element: PIN
  edit_type: SET
  pin {
    mod_id: 1
    task_id: 46
    fb_id: 80
    pin_index: 2
    pin_val {
      v {
        t: T_UINT32
        ui: 35
      }
      tm: 1681394223682178228
    }
  }
}
infos {
  cmd_id: 307
  element: LK
  edit_type: ADD
  lk {
    mod_id: 1
    task_id: 46
    lk_id: 82
    src_fb_id: 80
    src_pin_index: 1
    target_fb_id: 51
    target_pin_index: 1
  }
  pos {
    x: 218
    y: 79
  }
  pos {
    x: 222
    y: 79
  }
  pos {
    x: 222
    y: 108
  }
  pos {
    x: 226
    y: 108
  }
}
infos {
  cmd_id: 308
  element: FB
  edit_type: ADD
  fb {
    mod_id: 1
    task_id: 46
    fb_id: 83
    flib_name: "Comparison"
    fc_name: "LT_UINT"
  }
  pos {
    x: 199
    y: 72
  }
}
infos {
  cmd_id: 309
  element: FB
  edit_type: MV
  fb {
    mod_id: 1
    task_id: 46
    fb_id: 83
  }
  pos {
    x: 252
    y: 71
  }
}
infos {
  cmd_id: 310
  element: LK
  edit_type: ADD
  lk {
    mod_id: 1
    task_id: 46
    lk_id: 84
    src_fb_id: 83
    src_pin_index: 1
    target_fb_id: 52
    target_pin_index: 1
  }
  pos {
    x: 271
    y: 78
  }
  pos {
    x: 272
    y: 78
  }
  pos {
    x: 272
    y: 106
  }
  pos {
    x: 273
    y: 106
  }
}
infos {
  cmd_id: 311
  element: VI
  edit_type: ADD
  vi {
    mod_id: 1
    task_id: 46
    fb_id: 83
    pin_index: 1
    ev_id: 26
    vi_id: 85
  }
}
infos {
  cmd_id: 312
  element: PIN
  edit_type: SET
  pin {
    mod_id: 1
    task_id: 46
    fb_id: 83
    pin_index: 2
    pin_val {
      v {
        t: T_UINT32
        ui: 50
      }
      tm: 1681394261105887232
    }
  }
}
