infos {
  edit_type: SET
  proj {
    proj_name: "rotbot-engine-project"
    proj_uuid: "{087dcede-f4f7-4eef-a61b-f7e94f304906}"
  }
}
infos {
  cmd_id: 1
  element: EV
  edit_type: ADD
  ev {
    ev_id: 1
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
  cmd_id: 2
  element: EV
  edit_type: ADD
  ev {
    ev_id: 2
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
  cmd_id: 3
  element: EV
  edit_type: ADD
  ev {
    ev_id: 3
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
  cmd_id: 4
  element: EV
  edit_type: ADD
  ev {
    ev_id: 4
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
  cmd_id: 5
  element: EV
  edit_type: ADD
  ev {
    ev_id: 5
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
  cmd_id: 6
  element: EV
  edit_type: ADD
  ev {
    ev_id: 6
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
  cmd_id: 7
  element: EV
  edit_type: ADD
  ev {
    ev_id: 7
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
  cmd_id: 8
  element: EV
  edit_type: ADD
  ev {
    ev_id: 8
    ev_name: "AUTO"
    ev_type: 1
    ev_desc: "Desc"
    init_val {
      v {
        t: T_BOOL
        b: false
      }
      tm: 1681438468239537302
    }
  }
}
infos {
  cmd_id: 9
  element: MOD
  edit_type: ADD
  mod {
    mod_id: 9
    mod_name: "Module 1"
  }
}
infos {
  cmd_id: 10
  element: TASK
  edit_type: ADD
  task {
    mod_id: 9
    task_id: 10
    task_name: "BASE"
    interval: 1000
  }
}
infos {
  cmd_id: 11
  element: FB
  edit_type: ADD
  fb {
    mod_id: 9
    task_id: 10
    fb_id: 11
    flib_name: "Arithmetic"
    fc_name: "ADD_INT"
    fb_name: "\345\212\240\346\263\225"
  }
  pos {
    x: 117
    y: 28
  }
}
infos {
  cmd_id: 12
  element: FB
  edit_type: ADD
  fb {
    mod_id: 9
    task_id: 10
    fb_id: 12
    flib_name: "System"
    fc_name: "SYSSTATE"
    fb_name: "\347\263\273\347\273\237\347\233\221\346\265\213"
  }
  pos {
    x: 15
    y: 3
  }
}
infos {
  cmd_id: 13
  element: FB
  edit_type: ADD
  fb {
    mod_id: 9
    task_id: 10
    fb_id: 13
    flib_name: "Devices"
    fc_name: "SIM_READ"
    fb_name: "\346\250\241\346\213\237\344\277\241\345\217\267"
  }
  pos {
    x: 21
    y: 28
  }
}
infos {
  cmd_id: 14
  element: FB
  edit_type: ADD
  fb {
    mod_id: 9
    task_id: 10
    fb_id: 14
    flib_name: "Converter"
    fc_name: "D2I"
    fb_name: "Double\347\261\273\345\236\213\350\275\254\346\215\242Int"
  }
  pos {
    x: 63
    y: 28
  }
}
infos {
  cmd_id: 15
  element: FB
  edit_type: ADD
  fb {
    mod_id: 9
    task_id: 10
    fb_id: 15
    flib_name: "Arithmetic"
    fc_name: "DIV_INT"
    fb_name: "\351\231\244\346\263\225"
  }
  pos {
    x: 174
    y: 28
  }
}
infos {
  cmd_id: 16
  element: FB
  edit_type: ADD
  fb {
    mod_id: 9
    task_id: 10
    fb_id: 16
    flib_name: "Arithmetic"
    fc_name: "MUL_INT"
    fb_name: "\344\271\230\346\263\225"
  }
  pos {
    x: 174
    y: 42
  }
}
infos {
  cmd_id: 17
  element: FB
  edit_type: ADD
  fb {
    mod_id: 9
    task_id: 10
    fb_id: 17
    flib_name: "Arithmetic"
    fc_name: "MUL_DOUBLE"
    fb_name: "Double \344\271\230\346\263\225"
  }
  pos {
    x: 72
    y: 64
  }
}
infos {
  cmd_id: 18
  element: FB
  edit_type: ADD
  fb {
    mod_id: 9
    task_id: 10
    fb_id: 18
    flib_name: "Arithmetic"
    fc_name: "SUB_DOUBLE"
    fb_name: "Ddouble \345\207\217\346\263\225"
  }
  pos {
    x: 125
    y: 64
  }
}
infos {
  cmd_id: 19
  element: FB
  edit_type: ADD
  fb {
    mod_id: 9
    task_id: 10
    fb_id: 19
    flib_name: "Converter"
    fc_name: "D2STR"
    fb_name: "DOUBLE \350\275\254\346\215\242STRING"
  }
  pos {
    x: 126
    y: 84
  }
}
infos {
  cmd_id: 20
  element: FB
  edit_type: ADD
  fb {
    mod_id: 9
    task_id: 10
    fb_id: 20
    flib_name: "Converter"
    fc_name: "D2UI"
    fb_name: "\350\275\254\346\215\242\346\272\242\345\207\272"
  }
  pos {
    x: 72
    y: 83
  }
}
infos {
  cmd_id: 21
  element: FB
  edit_type: ADD
  fb {
    mod_id: 9
    task_id: 10
    fb_id: 21
    flib_name: "Converter"
    fc_name: "D2UI"
  }
  pos {
    x: 64
    y: 42
  }
}
infos {
  cmd_id: 22
  element: FB
  edit_type: ADD
  fb {
    mod_id: 9
    task_id: 10
    fb_id: 22
    flib_name: "Comparison"
    fc_name: "GE_UINT"
    fb_name: "Uint \345\244\247\344\272\216\346\257\224\350\276\203"
  }
  pos {
    x: 72
    y: 106
  }
}
infos {
  cmd_id: 23
  element: FB
  edit_type: ADD
  fb {
    mod_id: 9
    task_id: 10
    fb_id: 23
    flib_name: "Comparison"
    fc_name: "NE_UINT"
    fb_name: "Uint \344\270\215\347\255\211\344\272\216\346\257\224\350\276\203"
  }
  pos {
    x: 72
    y: 123
  }
}
infos {
  cmd_id: 24
  element: FB
  edit_type: ADD
  fb {
    mod_id: 9
    task_id: 10
    fb_id: 24
    flib_name: "Logic"
    fc_name: "AND4"
    fb_name: "\344\270\216"
  }
  pos {
    x: 124
    y: 106
  }
}
infos {
  cmd_id: 25
  element: FB
  edit_type: ADD
  fb {
    mod_id: 9
    task_id: 10
    fb_id: 25
    flib_name: "Logic"
    fc_name: "OR"
    fb_name: "\346\210\226"
  }
  pos {
    x: 124
    y: 129
  }
}
infos {
  cmd_id: 26
  element: FB
  edit_type: ADD
  fb {
    mod_id: 9
    task_id: 10
    fb_id: 26
    flib_name: "Logic"
    fc_name: "NOT"
    fb_name: "\351\235\236"
  }
  pos {
    x: 125
    y: 148
  }
}
infos {
  cmd_id: 27
  element: LK
  edit_type: ADD
  lk {
    mod_id: 9
    task_id: 10
    lk_id: 27
    src_fb_id: 13
    src_pin_index: 1
    target_fb_id: 14
    target_pin_index: 1
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
  cmd_id: 28
  element: LK
  edit_type: ADD
  lk {
    mod_id: 9
    task_id: 10
    lk_id: 28
    src_fb_id: 14
    src_pin_index: 1
    target_fb_id: 11
    target_pin_index: 1
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
  cmd_id: 29
  element: LK
  edit_type: ADD
  lk {
    mod_id: 9
    task_id: 10
    lk_id: 29
    src_fb_id: 11
    src_pin_index: 1
    target_fb_id: 15
    target_pin_index: 1
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
  cmd_id: 30
  element: LK
  edit_type: ADD
  lk {
    mod_id: 9
    task_id: 10
    lk_id: 30
    src_fb_id: 11
    src_pin_index: 1
    target_fb_id: 16
    target_pin_index: 1
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
  cmd_id: 31
  element: LK
  edit_type: ADD
  lk {
    mod_id: 9
    task_id: 10
    lk_id: 31
    src_fb_id: 17
    src_pin_index: 1
    target_fb_id: 18
    target_pin_index: 1
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
  cmd_id: 32
  element: LK
  edit_type: ADD
  lk {
    mod_id: 9
    task_id: 10
    lk_id: 32
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
  cmd_id: 33
  element: LK
  edit_type: ADD
  lk {
    mod_id: 9
    task_id: 10
    lk_id: 33
    src_fb_id: 13
    src_pin_index: 8
    target_fb_id: 21
    target_pin_index: 1
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
  cmd_id: 34
  element: LK
  edit_type: ADD
  lk {
    mod_id: 9
    task_id: 10
    lk_id: 34
    src_fb_id: 22
    src_pin_index: 1
    target_fb_id: 24
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
  cmd_id: 35
  element: LK
  edit_type: ADD
  lk {
    mod_id: 9
    task_id: 10
    lk_id: 35
    src_fb_id: 23
    src_pin_index: 1
    target_fb_id: 24
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
  cmd_id: 36
  element: LK
  edit_type: ADD
  lk {
    mod_id: 9
    task_id: 10
    lk_id: 36
    src_fb_id: 23
    src_pin_index: 1
    target_fb_id: 25
    target_pin_index: 1
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
  cmd_id: 37
  element: LK
  edit_type: ADD
  lk {
    mod_id: 9
    task_id: 10
    lk_id: 37
    src_fb_id: 23
    src_pin_index: 1
    target_fb_id: 26
    target_pin_index: 1
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
  cmd_id: 38
  element: VI
  edit_type: ADD
  vi {
    mod_id: 9
    task_id: 10
    fb_id: 17
    pin_index: 1
    ev_id: 1
    vi_id: 38
  }
}
infos {
  cmd_id: 39
  element: VI
  edit_type: ADD
  vi {
    mod_id: 9
    task_id: 10
    fb_id: 22
    pin_index: 1
    ev_id: 4
    vi_id: 39
  }
}
infos {
  cmd_id: 40
  element: VI
  edit_type: ADD
  vi {
    mod_id: 9
    task_id: 10
    fb_id: 23
    pin_index: 1
    ev_id: 4
    vi_id: 40
  }
}
infos {
  cmd_id: 41
  element: VO
  edit_type: ADD
  vo {
    mod_id: 9
    task_id: 10
    fb_id: 13
    pin_index: 5
    ev_id: 1
    vo_id: 41
  }
}
infos {
  cmd_id: 42
  element: VO
  edit_type: ADD
  vo {
    mod_id: 9
    task_id: 10
    fb_id: 18
    pin_index: 1
    ev_id: 2
    vo_id: 42
  }
}
infos {
  cmd_id: 43
  element: VO
  edit_type: ADD
  vo {
    mod_id: 9
    task_id: 10
    fb_id: 21
    pin_index: 1
    ev_id: 4
    vo_id: 43
  }
}
infos {
  cmd_id: 44
  element: VO
  edit_type: ADD
  vo {
    mod_id: 9
    task_id: 10
    fb_id: 24
    pin_index: 1
    ev_id: 5
    vo_id: 44
  }
}
infos {
  cmd_id: 45
  element: VO
  edit_type: ADD
  vo {
    mod_id: 9
    task_id: 10
    fb_id: 26
    pin_index: 1
    ev_id: 6
    vo_id: 45
  }
}
infos {
  cmd_id: 46
  element: TASK
  edit_type: ADD
  task {
    mod_id: 9
    task_id: 46
    task_name: "FSM"
    interval: 1000
  }
}
infos {
  cmd_id: 47
  element: FB
  edit_type: ADD
  fb {
    mod_id: 9
    task_id: 46
    fb_id: 47
    flib_name: "Fsm"
    fc_name: "FSM"
    fb_name: "\347\212\266\346\200\201==1"
  }
  pos {
    x: 60
    y: 107
  }
}
infos {
  cmd_id: 48
  element: FB
  edit_type: ADD
  fb {
    mod_id: 9
    task_id: 46
    fb_id: 48
    flib_name: "Fsm"
    fc_name: "FSM"
    fb_name: "\347\212\266\346\200\201==2"
  }
  pos {
    x: 128
    y: 105
  }
}
infos {
  cmd_id: 49
  element: FB
  edit_type: ADD
  fb {
    mod_id: 9
    task_id: 46
    fb_id: 49
    flib_name: "Fsm"
    fc_name: "FSM"
    fb_name: "\347\212\266\346\200\201==3"
  }
  pos {
    x: 173
    y: 103
  }
}
infos {
  cmd_id: 50
  element: FB
  edit_type: ADD
  fb {
    mod_id: 9
    task_id: 46
    fb_id: 50
    flib_name: "Fsm"
    fc_name: "FSM"
    fb_name: "\347\212\266\346\200\201==4"
  }
  pos {
    x: 226
    y: 101
  }
}
infos {
  cmd_id: 51
  element: FB
  edit_type: ADD
  fb {
    mod_id: 9
    task_id: 46
    fb_id: 51
    flib_name: "Fsm"
    fc_name: "FSM"
    fb_name: "\347\212\266\346\200\201==1"
  }
  pos {
    x: 273
    y: 99
  }
}
infos {
  cmd_id: 52
  element: FB
  edit_type: ADD
  fb {
    mod_id: 9
    task_id: 46
    fb_id: 52
    flib_name: "Devices"
    fc_name: "SIM_READ"
  }
  pos {
    x: 43
    y: 14
  }
}
infos {
  cmd_id: 53
  element: FB
  edit_type: ADD
  fb {
    mod_id: 9
    task_id: 46
    fb_id: 53
    flib_name: "Converter"
    fc_name: "D2UI"
  }
  pos {
    x: 86
    y: 20
  }
}
infos {
  cmd_id: 54
  element: FB
  edit_type: ADD
  fb {
    mod_id: 9
    task_id: 46
    fb_id: 54
    flib_name: "Comparison"
    fc_name: "EQ_UINT"
    fb_name: "SPEED==0"
  }
  pos {
    x: 16
    y: 107
  }
}
infos {
  cmd_id: 55
  element: FB
  edit_type: ADD
  fb {
    mod_id: 9
    task_id: 46
    fb_id: 55
    flib_name: "Comparison"
    fc_name: "LE_UINT"
    fb_name: "SPEED<10"
  }
  pos {
    x: 21
    y: 62
  }
}
infos {
  cmd_id: 56
  element: FB
  edit_type: ADD
  fb {
    mod_id: 9
    task_id: 46
    fb_id: 56
    flib_name: "Comparison"
    fc_name: "LE_UINT"
    fb_name: "SPEED<30"
  }
  pos {
    x: 111
    y: 39
  }
}
infos {
  cmd_id: 57
  element: FB
  edit_type: ADD
  fb {
    mod_id: 9
    task_id: 46
    fb_id: 57
    flib_name: "Logic"
    fc_name: "AND"
    fb_name: "SPEED>10 && SPEED<30"
  }
  pos {
    x: 140
    y: 61
  }
}
infos {
  cmd_id: 58
  element: FB
  edit_type: ADD
  fb {
    mod_id: 9
    task_id: 46
    fb_id: 58
    flib_name: "Fsm"
    fc_name: "FSM"
    fb_name: "\347\212\266\346\200\201==5"
  }
  pos {
    x: 129
    y: 133
  }
}
infos {
  cmd_id: 59
  element: FB
  edit_type: ADD
  fb {
    mod_id: 9
    task_id: 46
    fb_id: 59
    flib_name: "Fsm"
    fc_name: "FSM"
    fb_name: "\347\212\266\346\200\201==4"
  }
  pos {
    x: 227
    y: 131
  }
}
infos {
  cmd_id: 60
  element: FB
  edit_type: ADD
  fb {
    mod_id: 9
    task_id: 46
    fb_id: 60
    flib_name: "Comparison"
    fc_name: "GT_UINT"
    fb_name: "SPEED>10"
  }
  pos {
    x: 106
    y: 63
  }
}
infos {
  cmd_id: 61
  element: FB
  edit_type: ADD
  fb {
    mod_id: 9
    task_id: 46
    fb_id: 61
    flib_name: "Logic"
    fc_name: "AND"
  }
  pos {
    x: 54
    y: 62
  }
}
infos {
  cmd_id: 62
  element: FB
  edit_type: ADD
  fb {
    mod_id: 9
    task_id: 46
    fb_id: 62
    flib_name: "Logic"
    fc_name: "NOT"
    fb_name: "ATUO==1 && SPEED <10"
  }
  pos {
    x: 91
    y: 82
  }
}
infos {
  cmd_id: 63
  element: FB
  edit_type: ADD
  fb {
    mod_id: 9
    task_id: 46
    fb_id: 63
    flib_name: "Arithmetic"
    fc_name: "MOVE_BOOL"
  }
  pos {
    x: 22
    y: 145
  }
}
infos {
  cmd_id: 64
  element: FB
  edit_type: ADD
  fb {
    mod_id: 9
    task_id: 46
    fb_id: 64
    flib_name: "Comparison"
    fc_name: "GT_UINT"
    fb_name: "SPEED>40"
  }
  pos {
    x: 192
    y: 75
  }
}
infos {
  cmd_id: 65
  element: FB
  edit_type: ADD
  fb {
    mod_id: 9
    task_id: 46
    fb_id: 65
    flib_name: "Comparison"
    fc_name: "GT_UINT"
    fb_name: "SPEED>50"
  }
  pos {
    x: 242
    y: 75
  }
}
infos {
  cmd_id: 66
  element: LK
  edit_type: ADD
  lk {
    mod_id: 9
    task_id: 46
    lk_id: 66
    src_fb_id: 47
    src_pin_index: 1
    target_fb_id: 48
    target_pin_index: 2
  }
  pos {
    x: 81
    y: 114
  }
  pos {
    x: 128
    y: 114
  }
}
infos {
  cmd_id: 67
  element: LK
  edit_type: ADD
  lk {
    mod_id: 9
    task_id: 46
    lk_id: 67
    src_fb_id: 48
    src_pin_index: 1
    target_fb_id: 49
    target_pin_index: 2
  }
  pos {
    x: 149
    y: 112
  }
  pos {
    x: 173
    y: 112
  }
}
infos {
  cmd_id: 68
  element: LK
  edit_type: ADD
  lk {
    mod_id: 9
    task_id: 46
    lk_id: 68
    src_fb_id: 49
    src_pin_index: 1
    target_fb_id: 50
    target_pin_index: 2
  }
  pos {
    x: 194
    y: 110
  }
  pos {
    x: 226
    y: 110
  }
}
infos {
  cmd_id: 69
  element: LK
  edit_type: ADD
  lk {
    mod_id: 9
    task_id: 46
    lk_id: 69
    src_fb_id: 50
    src_pin_index: 1
    target_fb_id: 51
    target_pin_index: 2
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
  cmd_id: 70
  element: LK
  edit_type: ADD
  lk {
    mod_id: 9
    task_id: 46
    lk_id: 70
    src_fb_id: 52
    src_pin_index: 4
    target_fb_id: 53
    target_pin_index: 1
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
  cmd_id: 71
  element: LK
  edit_type: ADD
  lk {
    mod_id: 9
    task_id: 46
    lk_id: 71
    src_fb_id: 54
    src_pin_index: 1
    target_fb_id: 47
    target_pin_index: 1
  }
  pos {
    x: 35
    y: 114
  }
  pos {
    x: 60
    y: 114
  }
}
infos {
  cmd_id: 72
  element: LK
  edit_type: ADD
  lk {
    mod_id: 9
    task_id: 46
    lk_id: 72
    src_fb_id: 56
    src_pin_index: 1
    target_fb_id: 57
    target_pin_index: 1
  }
  pos {
    x: 130
    y: 46
  }
  pos {
    x: 132
    y: 46
  }
  pos {
    x: 132
    y: 68
  }
  pos {
    x: 140
    y: 68
  }
}
infos {
  cmd_id: 73
  element: LK
  edit_type: ADD
  lk {
    mod_id: 9
    task_id: 46
    lk_id: 73
    src_fb_id: 57
    src_pin_index: 1
    target_fb_id: 49
    target_pin_index: 1
  }
  pos {
    x: 159
    y: 68
  }
  pos {
    x: 163
    y: 68
  }
  pos {
    x: 163
    y: 110
  }
  pos {
    x: 173
    y: 110
  }
}
infos {
  cmd_id: 74
  element: LK
  edit_type: ADD
  lk {
    mod_id: 9
    task_id: 46
    lk_id: 74
    src_fb_id: 47
    src_pin_index: 1
    target_fb_id: 58
    target_pin_index: 2
  }
  pos {
    x: 81
    y: 114
  }
  pos {
    x: 89
    y: 114
  }
  pos {
    x: 89
    y: 142
  }
  pos {
    x: 129
    y: 142
  }
}
infos {
  cmd_id: 75
  element: LK
  edit_type: ADD
  lk {
    mod_id: 9
    task_id: 46
    lk_id: 75
    src_fb_id: 58
    src_pin_index: 1
    target_fb_id: 59
    target_pin_index: 2
  }
  pos {
    x: 150
    y: 140
  }
  pos {
    x: 227
    y: 140
  }
}
infos {
  cmd_id: 76
  element: LK
  edit_type: ADD
  lk {
    mod_id: 9
    task_id: 46
    lk_id: 76
    src_fb_id: 60
    src_pin_index: 1
    target_fb_id: 57
    target_pin_index: 2
  }
  pos {
    x: 125
    y: 70
  }
  pos {
    x: 140
    y: 70
  }
}
infos {
  cmd_id: 77
  element: LK
  edit_type: ADD
  lk {
    mod_id: 9
    task_id: 46
    lk_id: 77
    src_fb_id: 55
    src_pin_index: 1
    target_fb_id: 61
    target_pin_index: 1
  }
  pos {
    x: 40
    y: 69
  }
  pos {
    x: 54
    y: 69
  }
}
infos {
  cmd_id: 78
  element: LK
  edit_type: ADD
  lk {
    mod_id: 9
    task_id: 46
    lk_id: 78
    src_fb_id: 61
    src_pin_index: 1
    target_fb_id: 58
    target_pin_index: 1
  }
  pos {
    x: 73
    y: 69
  }
  pos {
    x: 86
    y: 69
  }
  pos {
    x: 86
    y: 140
  }
  pos {
    x: 129
    y: 140
  }
}
infos {
  cmd_id: 79
  element: LK
  edit_type: ADD
  lk {
    mod_id: 9
    task_id: 46
    lk_id: 79
    src_fb_id: 61
    src_pin_index: 1
    target_fb_id: 62
    target_pin_index: 1
  }
  pos {
    x: 73
    y: 69
  }
  pos {
    x: 86
    y: 69
  }
  pos {
    x: 86
    y: 89
  }
  pos {
    x: 91
    y: 89
  }
}
infos {
  cmd_id: 80
  element: LK
  edit_type: ADD
  lk {
    mod_id: 9
    task_id: 46
    lk_id: 80
    src_fb_id: 62
    src_pin_index: 1
    target_fb_id: 48
    target_pin_index: 1
  }
  pos {
    x: 109
    y: 89
  }
  pos {
    x: 111
    y: 89
  }
  pos {
    x: 111
    y: 112
  }
  pos {
    x: 128
    y: 112
  }
}
infos {
  cmd_id: 81
  element: LK
  edit_type: ADD
  lk {
    mod_id: 9
    task_id: 46
    lk_id: 81
    src_fb_id: 57
    src_pin_index: 1
    target_fb_id: 59
    target_pin_index: 1
  }
  pos {
    x: 159
    y: 68
  }
  pos {
    x: 163
    y: 68
  }
  pos {
    x: 163
    y: 138
  }
  pos {
    x: 227
    y: 138
  }
}
infos {
  cmd_id: 82
  element: LK
  edit_type: ADD
  lk {
    mod_id: 9
    task_id: 46
    lk_id: 82
    src_fb_id: 64
    src_pin_index: 1
    target_fb_id: 50
    target_pin_index: 1
  }
  pos {
    x: 211
    y: 82
  }
  pos {
    x: 218
    y: 82
  }
  pos {
    x: 218
    y: 108
  }
  pos {
    x: 226
    y: 108
  }
}
infos {
  cmd_id: 83
  element: LK
  edit_type: ADD
  lk {
    mod_id: 9
    task_id: 46
    lk_id: 83
    src_fb_id: 65
    src_pin_index: 1
    target_fb_id: 51
    target_pin_index: 1
  }
  pos {
    x: 261
    y: 82
  }
  pos {
    x: 267
    y: 82
  }
  pos {
    x: 267
    y: 106
  }
  pos {
    x: 273
    y: 106
  }
}
infos {
  cmd_id: 84
  element: VI
  edit_type: ADD
  vi {
    mod_id: 9
    task_id: 46
    fb_id: 54
    pin_index: 2
    ev_id: 3
    vi_id: 84
  }
}
infos {
  cmd_id: 85
  element: VI
  edit_type: ADD
  vi {
    mod_id: 9
    task_id: 46
    fb_id: 55
    pin_index: 1
    ev_id: 3
    vi_id: 85
  }
}
infos {
  cmd_id: 86
  element: VI
  edit_type: ADD
  vi {
    mod_id: 9
    task_id: 46
    fb_id: 47
    pin_index: 3
    ev_id: 7
    vi_id: 86
  }
}
infos {
  cmd_id: 87
  element: VI
  edit_type: ADD
  vi {
    mod_id: 9
    task_id: 46
    fb_id: 48
    pin_index: 3
    ev_id: 7
    vi_id: 87
  }
}
infos {
  cmd_id: 88
  element: VI
  edit_type: ADD
  vi {
    mod_id: 9
    task_id: 46
    fb_id: 49
    pin_index: 3
    ev_id: 7
    vi_id: 88
  }
}
infos {
  cmd_id: 89
  element: VI
  edit_type: ADD
  vi {
    mod_id: 9
    task_id: 46
    fb_id: 50
    pin_index: 3
    ev_id: 7
    vi_id: 89
  }
}
infos {
  cmd_id: 90
  element: VI
  edit_type: ADD
  vi {
    mod_id: 9
    task_id: 46
    fb_id: 51
    pin_index: 3
    ev_id: 7
    vi_id: 90
  }
}
infos {
  cmd_id: 91
  element: VI
  edit_type: ADD
  vi {
    mod_id: 9
    task_id: 46
    fb_id: 56
    pin_index: 1
    ev_id: 3
    vi_id: 91
  }
}
infos {
  cmd_id: 92
  element: VI
  edit_type: ADD
  vi {
    mod_id: 9
    task_id: 46
    fb_id: 60
    pin_index: 1
    ev_id: 3
    vi_id: 92
  }
}
infos {
  cmd_id: 93
  element: VI
  edit_type: ADD
  vi {
    mod_id: 9
    task_id: 46
    fb_id: 64
    pin_index: 1
    ev_id: 3
    vi_id: 93
  }
}
infos {
  cmd_id: 94
  element: VI
  edit_type: ADD
  vi {
    mod_id: 9
    task_id: 46
    fb_id: 65
    pin_index: 1
    ev_id: 3
    vi_id: 94
  }
}
infos {
  cmd_id: 95
  element: VI
  edit_type: ADD
  vi {
    mod_id: 9
    task_id: 46
    fb_id: 58
    pin_index: 3
    ev_id: 7
    vi_id: 95
  }
}
infos {
  cmd_id: 96
  element: VI
  edit_type: ADD
  vi {
    mod_id: 9
    task_id: 46
    fb_id: 59
    pin_index: 3
    ev_id: 7
    vi_id: 96
  }
}
infos {
  cmd_id: 97
  element: VO
  edit_type: ADD
  vo {
    mod_id: 9
    task_id: 46
    fb_id: 53
    pin_index: 1
    ev_id: 3
    vo_id: 97
  }
}
infos {
  cmd_id: 98
  element: VO
  edit_type: ADD
  vo {
    mod_id: 9
    task_id: 46
    fb_id: 63
    pin_index: 1
    ev_id: 8
    vo_id: 98
  }
}
infos {
  cmd_id: 99
  element: MOD
  edit_type: ADD
  mod {
    mod_id: 99
    mod_name: "Module 2"
  }
}
infos {
  cmd_id: 100
  element: PIN
  edit_type: SET
  pin {
    mod_id: 9
    task_id: 10
    fb_id: 13
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
  cmd_id: 101
  element: PIN
  edit_type: SET
  pin {
    mod_id: 9
    task_id: 10
    fb_id: 11
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
  cmd_id: 102
  element: PIN
  edit_type: SET
  pin {
    mod_id: 9
    task_id: 10
    fb_id: 15
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
  cmd_id: 103
  element: PIN
  edit_type: SET
  pin {
    mod_id: 9
    task_id: 10
    fb_id: 16
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
  cmd_id: 104
  element: PIN
  edit_type: SET
  pin {
    mod_id: 9
    task_id: 10
    fb_id: 13
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
  cmd_id: 105
  element: PIN
  edit_type: SET
  pin {
    mod_id: 9
    task_id: 10
    fb_id: 13
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
  cmd_id: 106
  element: PIN
  edit_type: SET
  pin {
    mod_id: 9
    task_id: 10
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
  cmd_id: 107
  element: PIN
  edit_type: SET
  pin {
    mod_id: 9
    task_id: 10
    fb_id: 20
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
  cmd_id: 108
  element: PIN
  edit_type: SET
  pin {
    mod_id: 9
    task_id: 10
    fb_id: 13
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
  cmd_id: 109
  element: PIN
  edit_type: SET
  pin {
    mod_id: 9
    task_id: 10
    fb_id: 13
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
  cmd_id: 110
  element: PIN
  edit_type: SET
  pin {
    mod_id: 9
    task_id: 10
    fb_id: 22
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
  cmd_id: 111
  element: PIN
  edit_type: SET
  pin {
    mod_id: 9
    task_id: 10
    fb_id: 23
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
  cmd_id: 112
  element: PIN
  edit_type: SET
  pin {
    mod_id: 9
    task_id: 10
    fb_id: 24
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
  cmd_id: 113
  element: PIN
  edit_type: SET
  pin {
    mod_id: 9
    task_id: 10
    fb_id: 24
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
  cmd_id: 114
  element: PIN
  edit_type: SET
  pin {
    mod_id: 9
    task_id: 10
    fb_id: 25
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
  cmd_id: 115
  element: PIN
  edit_type: SET
  pin {
    mod_id: 9
    task_id: 46
    fb_id: 47
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
  cmd_id: 116
  element: PIN
  edit_type: SET
  pin {
    mod_id: 9
    task_id: 46
    fb_id: 48
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
  cmd_id: 117
  element: PIN
  edit_type: SET
  pin {
    mod_id: 9
    task_id: 46
    fb_id: 49
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
  cmd_id: 118
  element: PIN
  edit_type: SET
  pin {
    mod_id: 9
    task_id: 46
    fb_id: 50
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
  cmd_id: 119
  element: PIN
  edit_type: SET
  pin {
    mod_id: 9
    task_id: 46
    fb_id: 51
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
  cmd_id: 120
  element: PIN
  edit_type: SET
  pin {
    mod_id: 9
    task_id: 46
    fb_id: 52
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
  cmd_id: 121
  element: PIN
  edit_type: SET
  pin {
    mod_id: 9
    task_id: 46
    fb_id: 52
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
  cmd_id: 122
  element: PIN
  edit_type: SET
  pin {
    mod_id: 9
    task_id: 46
    fb_id: 47
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
  cmd_id: 123
  element: PIN
  edit_type: SET
  pin {
    mod_id: 9
    task_id: 46
    fb_id: 47
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
  cmd_id: 124
  element: PIN
  edit_type: SET
  pin {
    mod_id: 9
    task_id: 46
    fb_id: 54
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
  cmd_id: 125
  element: PIN
  edit_type: SET
  pin {
    mod_id: 9
    task_id: 46
    fb_id: 55
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
  cmd_id: 126
  element: PIN
  edit_type: SET
  pin {
    mod_id: 9
    task_id: 46
    fb_id: 56
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
  cmd_id: 127
  element: PIN
  edit_type: SET
  pin {
    mod_id: 9
    task_id: 46
    fb_id: 60
    pin_index: 2
    pin_val {
      v {
        t: T_UINT32
        ui: 10
      }
      tm: 1681437647745303500
    }
  }
}
infos {
  cmd_id: 128
  element: PIN
  edit_type: SET
  pin {
    mod_id: 9
    task_id: 46
    fb_id: 61
    pin_index: 2
    pin_val {
      v {
        t: T_BOOL
        b: true
      }
      tm: 1681438207742837028
    }
  }
}
infos {
  cmd_id: 129
  element: PIN
  edit_type: SET
  pin {
    mod_id: 9
    task_id: 46
    fb_id: 61
    pin_index: 2
    pin_val {
      v {
        t: T_BOOL
        b: false
      }
      tm: 1681438214604689424
    }
  }
}
infos {
  cmd_id: 130
  element: PIN
  edit_type: SET
  pin {
    mod_id: 9
    task_id: 46
    fb_id: 63
    pin_index: 1
    pin_val {
      v {
        t: T_BOOL
        b: true
      }
      tm: 1681438498540371972
    }
  }
}
infos {
  cmd_id: 131
  element: PIN
  edit_type: SET
  pin {
    mod_id: 9
    task_id: 46
    fb_id: 64
    pin_index: 2
    pin_val {
      v {
        t: T_UINT32
        ui: 40
      }
      tm: 1681438674968002811
    }
  }
}
infos {
  cmd_id: 132
  element: PIN
  edit_type: SET
  pin {
    mod_id: 9
    task_id: 46
    fb_id: 65
    pin_index: 2
    pin_val {
      v {
        t: T_UINT32
        ui: 55
      }
      tm: 1681438713754148278
    }
  }
}
infos {
  cmd_id: 133
  element: PIN
  edit_type: SET
  pin {
    mod_id: 9
    task_id: 46
    fb_id: 58
    pin_index: 4
    pin_val {
      v {
        t: T_INT32
        i: 5
      }
      tm: 1681438974157492659
    }
  }
}
infos {
  cmd_id: 134
  element: PIN
  edit_type: SET
  pin {
    mod_id: 9
    task_id: 46
    fb_id: 59
    pin_index: 4
    pin_val {
      v {
        t: T_INT32
        i: 4
      }
      tm: 1681438977918042531
    }
  }
}
infos {
  cmd_id: 135
  element: VI
  edit_type: ADD
  vi {
    mod_id: 9
    task_id: 46
    fb_id: 61
    pin_index: 2
    ev_id: 8
    vi_id: 100
  }
}
infos {
  cmd_id: 136
  element: FB
  edit_type: MV
  fb {
    mod_id: 9
    task_id: 46
    fb_id: 62
  }
  pos {
    x: 91
    y: 82
  }
}
infos {
  cmd_id: 137
  element: FB
  edit_type: MV
  fb {
    mod_id: 9
    task_id: 46
    fb_id: 61
    fb_name: "ATUO==1 && SPEED <10"
  }
  pos {
    x: 54
    y: 62
  }
}
infos {
  cmd_id: 138
  element: FB
  edit_type: MV
  fb {
    mod_id: 9
    task_id: 46
    fb_id: 62
    fb_name: "!(ATUO==1 && SPEED <10)"
  }
  pos {
    x: 91
    y: 82
  }
}
infos {
  cmd_id: 139
  element: FB
  edit_type: ADD
  fb {
    mod_id: 9
    task_id: 46
    fb_id: 101
    flib_name: "Task"
    fc_name: "EVENT"
  }
  pos {
    x: 92
    y: 161
  }
}
infos {
  cmd_id: 140
  element: LK
  edit_type: ADD
  lk {
    mod_id: 9
    task_id: 46
    lk_id: 102
    src_fb_id: 47
    src_pin_index: 2
    target_fb_id: 101
    target_pin_index: 1
  }
  pos {
    x: 81
    y: 116
  }
  pos {
    x: 86
    y: 116
  }
  pos {
    x: 86
    y: 168
  }
  pos {
    x: 92
    y: 168
  }
}
infos {
  cmd_id: 142
  element: FB
  edit_type: ADD
  fb {
    mod_id: 9
    task_id: 46
    fb_id: 103
    flib_name: "Task"
    fc_name: "TASK"
  }
  pos {
    x: 129
    y: 190
  }
}
infos {
  cmd_id: 147
  element: FB
  edit_type: MV
  fb {
    mod_id: 9
    task_id: 46
    fb_id: 101
  }
  pos {
    x: 86
    y: 192
  }
}
infos {
  cmd_id: 149
  element: LK
  edit_type: MV
  lk {
    mod_id: 9
    task_id: 46
    lk_id: 102
  }
  pos {
    x: 81
    y: 116
  }
  pos {
    x: 81
    y: 199
  }
  pos {
    x: 86
    y: 199
  }
}
infos {
  cmd_id: 150
  element: LK
  edit_type: ADD
  lk {
    mod_id: 9
    task_id: 46
    lk_id: 104
    src_fb_id: 101
    src_pin_index: 1
    target_fb_id: 103
    target_pin_index: 1
  }
  pos {
    x: 108
    y: 199
  }
  pos {
    x: 118
    y: 199
  }
  pos {
    x: 118
    y: 197
  }
  pos {
    x: 129
    y: 197
  }
}
infos {
  cmd_id: 151
  element: PIN
  edit_type: SET
  pin {
    mod_id: 9
    task_id: 46
    fb_id: 103
    pin_index: 2
    pin_val {
      v {
        t: T_STRING
        str: "MOD1"
      }
      tm: 1681457900307994766
    }
  }
}
infos {
  cmd_id: 152
  element: PIN
  edit_type: SET
  pin {
    mod_id: 9
    task_id: 46
    fb_id: 103
    pin_index: 3
    pin_val {
      v {
        t: T_STRING
        str: "P1"
      }
      tm: 1681457908452281043
    }
  }
}
infos {
  cmd_id: 153
  element: PIN
  edit_type: SET
  pin {
    mod_id: 9
    task_id: 46
    fb_id: 103
    pin_index: 4
    pin_val {
      v {
        t: T_TIME
        tm: 3000
      }
      tm: 1681457920186104840
    }
  }
}
infos {
  cmd_id: 158
  element: FB
  edit_type: MV
  fb {
    mod_id: 9
    task_id: 46
    fb_id: 103
  }
  pos {
    x: 131
    y: 192
  }
}
infos {
  cmd_id: 159
  element: LK
  edit_type: MV
  lk {
    mod_id: 9
    task_id: 46
    lk_id: 104
  }
  pos {
    x: 108
    y: 199
  }
  pos {
    x: 131
    y: 199
  }
}
infos {
  cmd_id: 160
  element: MOD
  edit_type: ADD
  mod {
    mod_id: 105
    mod_name: "SUBTASK"
  }
}
infos {
  cmd_id: 161
  element: TASK
  edit_type: ADD
  task {
    task_type: ASYNC
    mod_id: 105
    task_id: 106
    task_name: "Task_1"
    interval: 1000
  }
}
infos {
  cmd_id: 162
  element: TASK
  edit_type: ADD
  task {
    task_type: ASYNC
    mod_id: 105
    task_id: 107
    task_name: "Task_2"
    interval: 1000
  }
}
infos {
  cmd_id: 163
  element: TASK
  edit_type: ADD
  task {
    task_type: ASYNC
    mod_id: 105
    task_id: 108
    task_name: "Task_3"
    interval: 1000
  }
}
infos {
  cmd_id: 164
  element: TASK
  edit_type: ADD
  task {
    task_type: ASYNC
    mod_id: 105
    task_id: 109
    task_name: "Task_4"
    interval: 1000
  }
}
infos {
  cmd_id: 165
  element: TASK
  edit_type: ADD
  task {
    task_type: ASYNC
    mod_id: 105
    task_id: 110
    task_name: "Task_5"
    interval: 1000
  }
}
infos {
  cmd_id: 166
  element: TASK
  edit_type: ADD
  task {
    task_type: ASYNC
    mod_id: 105
    task_id: 111
    task_name: "TASK_6"
    interval: 1000
  }
}
infos {
  cmd_id: 167
  element: TASK
  edit_type: SET
  task {
    task_type: ASYNC
    mod_id: 105
    task_id: 111
    task_name: "Task_6"
  }
}
infos {
  cmd_id: 168
  element: FB
  edit_type: ADD
  fb {
    mod_id: 105
    task_id: 106
    fb_id: 112
    flib_name: "System"
    fc_name: "SYSSTATE"
  }
  pos {
    x: 26
    y: 93
  }
}
infos {
  cmd_id: 169
  element: FB
  edit_type: ADD
  fb {
    mod_id: 105
    task_id: 107
    fb_id: 113
    flib_name: "System"
    fc_name: "SYSSTATE"
  }
  pos {
    x: 39
    y: 95
  }
}
infos {
  cmd_id: 170
  element: FB
  edit_type: ADD
  fb {
    mod_id: 105
    task_id: 108
    fb_id: 114
    flib_name: "System"
    fc_name: "SYSSTATE"
  }
  pos {
    x: 39
    y: 95
  }
}
infos {
  cmd_id: 171
  element: FB
  edit_type: ADD
  fb {
    mod_id: 105
    task_id: 109
    fb_id: 115
    flib_name: "System"
    fc_name: "SYSSTATE"
  }
  pos {
    x: 39
    y: 95
  }
}
infos {
  cmd_id: 172
  element: FB
  edit_type: ADD
  fb {
    mod_id: 105
    task_id: 110
    fb_id: 116
    flib_name: "System"
    fc_name: "SYSSTATE"
  }
  pos {
    x: 39
    y: 95
  }
}
infos {
  cmd_id: 173
  element: FB
  edit_type: ADD
  fb {
    mod_id: 105
    task_id: 111
    fb_id: 117
    flib_name: "System"
    fc_name: "SYSSTATE"
  }
  pos {
    x: 39
    y: 95
  }
}
infos {
  cmd_id: 174
  element: PIN
  edit_type: SET
  pin {
    mod_id: 9
    task_id: 46
    fb_id: 103
    pin_index: 2
    pin_val {
      v {
        t: T_STRING
        str: "SUBTASK"
      }
      tm: 1681459259174030695
    }
  }
}
infos {
  cmd_id: 175
  element: PIN
  edit_type: SET
  pin {
    mod_id: 9
    task_id: 46
    fb_id: 103
    pin_index: 3
    pin_val {
      v {
        t: T_STRING
        str: "TASK_1"
      }
      tm: 1681459270749673850
    }
  }
}
infos {
  cmd_id: 176
  element: FB
  edit_type: ADD
  fb {
    mod_id: 9
    task_id: 46
    fb_id: 118
    flib_name: "System"
    fc_name: "SYSSTATE"
  }
  pos {
    x: 39
    y: 95
  }
}
infos {
  cmd_id: 177
  element: FB
  edit_type: MV
  fb {
    mod_id: 9
    task_id: 46
    fb_id: 118
  }
  pos {
    x: 146
    y: 162
  }
}
infos {
  cmd_id: 178
  element: FB
  edit_type: RM
  fb {
    mod_id: 9
    task_id: 46
    fb_id: 118
  }
}
infos {
  cmd_id: 179
  element: FB
  edit_type: ADD
  fb {
    mod_id: 9
    task_id: 46
    fb_id: 119
    flib_name: "Task"
    fc_name: "EVENT"
  }
  pos {
    x: 86
    y: 192
  }
}
infos {
  cmd_id: 181
  element: LK
  edit_type: ADD
  lk {
    mod_id: 9
    task_id: 46
    lk_id: 120
    src_fb_id: 103
    src_pin_index: 1
    target_fb_id: 119
    target_pin_index: 1
  }
  pos {
    x: 158
    y: 199
  }
  pos {
    x: 176
    y: 199
  }
}
infos {
  cmd_id: 182
  element: FB
  edit_type: ADD
  fb {
    mod_id: 9
    task_id: 46
    fb_id: 121
    flib_name: "Task"
    fc_name: "TASK"
  }
  pos {
    x: 131
    y: 192
  }
}
infos {
  cmd_id: 185
  element: LK
  edit_type: ADD
  lk {
    mod_id: 9
    task_id: 46
    lk_id: 122
    src_fb_id: 119
    src_pin_index: 1
    target_fb_id: 121
    target_pin_index: 1
  }
  pos {
    x: 198
    y: 199
  }
  pos {
    x: 208
    y: 199
  }
  pos {
    x: 208
    y: 196
  }
  pos {
    x: 219
    y: 196
  }
}
infos {
  cmd_id: 188
  element: FB
  edit_type: MV
  fb {
    mod_id: 9
    task_id: 46
    fb_id: 121
  }
  pos {
    x: 221
    y: 192
  }
}
infos {
  cmd_id: 190
  element: PIN
  edit_type: SET
  pin {
    mod_id: 9
    task_id: 46
    fb_id: 121
    pin_index: 2
    pin_val {
      v {
        t: T_STRING
        str: "SUBTASK"
      }
      tm: 1681459341165580334
    }
  }
}
infos {
  cmd_id: 191
  element: PIN
  edit_type: SET
  pin {
    mod_id: 9
    task_id: 46
    fb_id: 121
    pin_index: 3
    pin_val {
      v {
        t: T_STRING
        str: "Task_2"
      }
      tm: 1681459361284969917
    }
  }
}
infos {
  cmd_id: 192
  element: PIN
  edit_type: SET
  pin {
    mod_id: 9
    task_id: 46
    fb_id: 103
    pin_index: 3
    pin_val {
      v {
        t: T_STRING
        str: "Task_2"
      }
      tm: 1681459370261742789
    }
  }
}
infos {
  cmd_id: 193
  element: PIN
  edit_type: SET
  pin {
    mod_id: 9
    task_id: 46
    fb_id: 121
    pin_index: 4
    pin_val {
      v {
        t: T_TIME
        tm: 1000
      }
      tm: 1681459378022089384
    }
  }
}
infos {
  cmd_id: 194
  element: PIN
  edit_type: SET
  pin {
    mod_id: 9
    task_id: 46
    fb_id: 121
    pin_index: 5
    pin_val {
      v {
        t: T_BOOL
        b: true
      }
      tm: 1681459381965500669
    }
  }
}
infos {
  cmd_id: 195
  element: PIN
  edit_type: SET
  pin {
    mod_id: 9
    task_id: 46
    fb_id: 103
    pin_index: 5
    pin_val {
      v {
        t: T_BOOL
        b: false
      }
      tm: 1681459385237447710
    }
  }
}
infos {
  cmd_id: 196
  element: PIN
  edit_type: SET
  pin {
    mod_id: 9
    task_id: 46
    fb_id: 103
    pin_index: 3
    pin_val {
      v {
        t: T_STRING
        str: "Task_1"
      }
      tm: 1681459725996581085
    }
  }
}
infos {
  cmd_id: 197
  element: FB
  edit_type: ADD
  fb {
    mod_id: 105
    task_id: 106
    fb_id: 123
    flib_name: "Arithmetic"
    fc_name: "ADD_INT"
  }
  pos {
    x: 43
    y: 137
  }
}
infos {
  cmd_id: 199
  element: EV
  edit_type: ADD
  ev {
    ev_id: 124
    ev_name: "T_INT_1"
    ev_type: 2
    ev_desc: "Desc"
    init_val {
      v {
        t: T_INT32
        i: 0
      }
      tm: 1681461667230464344
    }
  }
}
infos {
  cmd_id: 200
  element: VI
  edit_type: ADD
  vi {
    mod_id: 105
    task_id: 106
    fb_id: 123
    pin_index: 1
    ev_id: 124
    vi_id: 125
  }
}
infos {
  cmd_id: 201
  element: PIN
  edit_type: SET
  pin {
    mod_id: 105
    task_id: 106
    fb_id: 123
    pin_index: 2
    pin_val {
      v {
        t: T_INT32
        i: 1
      }
      tm: 1681461676558953246
    }
  }
}
infos {
  cmd_id: 202
  element: VO
  edit_type: ADD
  vo {
    mod_id: 105
    task_id: 106
    fb_id: 123
    pin_index: 1
    ev_id: 124
    vo_id: 126
  }
}
infos {
  cmd_id: 203
  element: FB
  edit_type: ADD
  fb {
    mod_id: 105
    task_id: 107
    fb_id: 127
    flib_name: "Arithmetic"
    fc_name: "MUL_FLOAT"
  }
  pos {
    x: 54
    y: 140
  }
}
infos {
  cmd_id: 205
  element: FB
  edit_type: MV
  fb {
    mod_id: 105
    task_id: 107
    fb_id: 127
  }
  pos {
    x: 41
    y: 139
  }
}
infos {
  cmd_id: 206
  element: FB
  edit_type: RM
  fb {
    mod_id: 105
    task_id: 107
    fb_id: 127
  }
}
infos {
  cmd_id: 207
  element: FB
  edit_type: ADD
  fb {
    mod_id: 105
    task_id: 107
    fb_id: 128
    flib_name: "Task"
    fc_name: "TASK"
  }
  pos {
    x: 50
    y: 136
  }
}
infos {
  cmd_id: 208
  element: PIN
  edit_type: SET
  pin {
    mod_id: 105
    task_id: 107
    fb_id: 128
    pin_index: 1
    pin_val {
      v {
        t: T_BOOL
        b: true
      }
      tm: 1681461777734632515
    }
  }
}
infos {
  cmd_id: 209
  element: PIN
  edit_type: SET
  pin {
    mod_id: 105
    task_id: 107
    fb_id: 128
    pin_index: 2
    pin_val {
      v {
        t: T_STRING
        str: "SUBTASK"
      }
      tm: 1681461793343256511
    }
  }
}
infos {
  cmd_id: 210
  element: PIN
  edit_type: SET
  pin {
    mod_id: 105
    task_id: 107
    fb_id: 128
    pin_index: 3
    pin_val {
      v {
        t: T_STRING
        str: "Task_4"
      }
      tm: 1681461800542901419
    }
  }
}
infos {
  cmd_id: 211
  element: PIN
  edit_type: SET
  pin {
    mod_id: 105
    task_id: 107
    fb_id: 128
    pin_index: 4
    pin_val {
      v {
        t: T_TIME
        tm: 3000
      }
      tm: 1681461808702853656
    }
  }
}
infos {
  cmd_id: 212
  element: PIN
  edit_type: SET
  pin {
    mod_id: 105
    task_id: 107
    fb_id: 128
    pin_index: 5
    pin_val {
      v {
        t: T_BOOL
        b: false
      }
      tm: 1681461813103258319
    }
  }
}
infos {
  cmd_id: 214
  element: FB
  edit_type: ADD
  fb {
    mod_id: 105
    task_id: 107
    fb_id: 129
    flib_name: "Task"
    fc_name: "TASK"
  }
  pos {
    x: 46
    y: 134
  }
}
infos {
  cmd_id: 217
  element: LK
  edit_type: ADD
  lk {
    mod_id: 105
    task_id: 107
    lk_id: 130
    src_fb_id: 128
    src_pin_index: 1
    target_fb_id: 129
    target_pin_index: 1
  }
  pos {
    x: 73
    y: 141
  }
  pos {
    x: 83
    y: 141
  }
  pos {
    x: 83
    y: 140
  }
  pos {
    x: 94
    y: 140
  }
}
infos {
  cmd_id: 220
  element: PIN
  edit_type: SET
  pin {
    mod_id: 105
    task_id: 107
    fb_id: 129
    pin_index: 2
    pin_val {
      v {
        t: T_STRING
        str: "SUBTASK"
      }
      tm: 1681461840734779625
    }
  }
}
infos {
  cmd_id: 221
  element: PIN
  edit_type: SET
  pin {
    mod_id: 105
    task_id: 107
    fb_id: 129
    pin_index: 3
    pin_val {
      v {
        t: T_STRING
        str: "Task_5"
      }
      tm: 1681461848661264429
    }
  }
}
infos {
  cmd_id: 222
  element: PIN
  edit_type: SET
  pin {
    mod_id: 105
    task_id: 107
    fb_id: 129
    pin_index: 4
    pin_val {
      v {
        t: T_TIME
        tm: 2000
      }
      tm: 1681461862712496476
    }
  }
}
infos {
  cmd_id: 223
  element: PIN
  edit_type: SET
  pin {
    mod_id: 105
    task_id: 107
    fb_id: 129
    pin_index: 5
    pin_val {
      v {
        t: T_BOOL
        b: false
      }
      tm: 1681461867048733795
    }
  }
}
infos {
  cmd_id: 224
  element: FB
  edit_type: ADD
  fb {
    mod_id: 105
    task_id: 109
    fb_id: 131
    flib_name: "Arithmetic"
    fc_name: "ADD_INT"
  }
  pos {
    x: 50
    y: 138
  }
}
infos {
  cmd_id: 225
  element: EV
  edit_type: ADD
  ev {
    ev_id: 132
    ev_name: "T_INT_2"
    ev_type: 2
    ev_desc: "Desc"
    init_val {
      v {
        t: T_INT32
        i: 0
      }
      tm: 1681461921877235658
    }
  }
}
infos {
  cmd_id: 226
  element: VI
  edit_type: ADD
  vi {
    mod_id: 105
    task_id: 109
    fb_id: 131
    pin_index: 1
    ev_id: 132
    vi_id: 133
  }
}
infos {
  cmd_id: 227
  element: VO
  edit_type: ADD
  vo {
    mod_id: 105
    task_id: 109
    fb_id: 131
    pin_index: 1
    ev_id: 132
    vo_id: 134
  }
}
infos {
  cmd_id: 228
  element: PIN
  edit_type: SET
  pin {
    mod_id: 105
    task_id: 109
    fb_id: 131
    pin_index: 2
    pin_val {
      v {
        t: T_INT32
        i: 2
      }
      tm: 1681461934909480525
    }
  }
}
infos {
  cmd_id: 229
  element: FB
  edit_type: MV
  fb {
    mod_id: 105
    task_id: 107
    fb_id: 113
  }
  pos {
    x: 29
    y: 17
  }
}
infos {
  cmd_id: 233
  element: FB
  edit_type: MV
  fb {
    mod_id: 105
    task_id: 106
    fb_id: 112
  }
  pos {
    x: 25
    y: 17
  }
}
infos {
  cmd_id: 234
  element: FB
  edit_type: MV
  fb {
    mod_id: 105
    task_id: 106
    fb_id: 123
  }
  pos {
    x: 28
    y: 53
  }
}
infos {
  cmd_id: 235
  element: FB
  edit_type: MV
  fb {
    mod_id: 105
    task_id: 108
    fb_id: 114
  }
  pos {
    x: 23
    y: 16
  }
}
infos {
  cmd_id: 236
  element: FB
  edit_type: MV
  fb {
    mod_id: 105
    task_id: 109
    fb_id: 115
  }
  pos {
    x: 28
    y: 6
  }
}
infos {
  cmd_id: 237
  element: FB
  edit_type: MV
  fb {
    mod_id: 105
    task_id: 109
    fb_id: 131
  }
  pos {
    x: 39
    y: 49
  }
}
infos {
  cmd_id: 238
  element: FB
  edit_type: MV
  fb {
    mod_id: 105
    task_id: 110
    fb_id: 116
  }
  pos {
    x: 24
    y: 11
  }
}
infos {
  cmd_id: 239
  element: FB
  edit_type: MV
  fb {
    mod_id: 105
    task_id: 111
    fb_id: 117
  }
  pos {
    x: 18
    y: 8
  }
}
infos {
  cmd_id: 240
  element: FB
  edit_type: ADD
  fb {
    mod_id: 105
    task_id: 107
    fb_id: 135
    flib_name: "Task"
    fc_name: "TASK"
  }
  pos {
    x: 84
    y: 56
  }
}
infos {
  cmd_id: 242
  element: LK
  edit_type: ADD
  lk {
    mod_id: 105
    task_id: 107
    lk_id: 136
    src_fb_id: 129
    src_pin_index: 1
    target_fb_id: 135
    target_pin_index: 1
  }
  pos {
    x: 111
    y: 63
  }
  pos {
    x: 120
    y: 63
  }
  pos {
    x: 120
    y: 62
  }
  pos {
    x: 130
    y: 62
  }
}
infos {
  cmd_id: 251
  element: PIN
  edit_type: SET
  pin {
    mod_id: 105
    task_id: 107
    fb_id: 135
    pin_index: 5
    pin_val {
      v {
        t: T_BOOL
        b: false
      }
      tm: 1681462637030798117
    }
  }
}
infos {
  cmd_id: 252
  element: PIN
  edit_type: SET
  pin {
    mod_id: 105
    task_id: 107
    fb_id: 135
    pin_index: 2
    pin_val {
      v {
        t: T_STRING
        str: "SUBTASK"
      }
      tm: 1681462645167425757
    }
  }
}
infos {
  cmd_id: 253
  element: PIN
  edit_type: SET
  pin {
    mod_id: 105
    task_id: 107
    fb_id: 135
    pin_index: 3
    pin_val {
      v {
        t: T_STRING
        str: "Task_3"
      }
      tm: 1681462654711414668
    }
  }
}
infos {
  cmd_id: 254
  element: FB
  edit_type: ADD
  fb {
    mod_id: 105
    task_id: 110
    fb_id: 137
    flib_name: "Task"
    fc_name: "TASK"
  }
  pos {
    x: 66
    y: 57
  }
}
infos {
  cmd_id: 255
  element: PIN
  edit_type: SET
  pin {
    mod_id: 105
    task_id: 110
    fb_id: 137
    pin_index: 2
    pin_val {
      v {
        t: T_STRING
        str: "SUBTASK"
      }
      tm: 1681462707504407676
    }
  }
}
infos {
  cmd_id: 256
  element: PIN
  edit_type: SET
  pin {
    mod_id: 105
    task_id: 110
    fb_id: 137
    pin_index: 3
    pin_val {
      v {
        t: T_STRING
        str: "Task_6"
      }
      tm: 1681462714472249183
    }
  }
}
infos {
  cmd_id: 257
  element: PIN
  edit_type: SET
  pin {
    mod_id: 105
    task_id: 110
    fb_id: 137
    pin_index: 4
    pin_val {
      v {
        t: T_TIME
        tm: 1000
      }
      tm: 1681462720800377823
    }
  }
}
infos {
  cmd_id: 258
  element: PIN
  edit_type: SET
  pin {
    mod_id: 105
    task_id: 110
    fb_id: 137
    pin_index: 5
    pin_val {
      v {
        t: T_BOOL
        b: false
      }
      tm: 1681462725761100538
    }
  }
}
infos {
  cmd_id: 259
  element: FB
  edit_type: MV
  fb {
    mod_id: 105
    task_id: 110
    fb_id: 137
  }
  pos {
    x: 40
    y: 56
  }
}
infos {
  cmd_id: 260
  element: FB
  edit_type: ADD
  fb {
    mod_id: 105
    task_id: 111
    fb_id: 138
    flib_name: "Task"
    fc_name: "SLEEP"
  }
  pos {
    x: 44
    y: 67
  }
}
infos {
  cmd_id: 261
  element: PIN
  edit_type: SET
  pin {
    mod_id: 105
    task_id: 111
    fb_id: 138
    pin_index: 2
    pin_val {
      v {
        t: T_TIME
        tm: 5000
      }
      tm: 1681462744169052378
    }
  }
}
infos {
  cmd_id: 262
  element: FB
  edit_type: MV
  fb {
    mod_id: 105
    task_id: 111
    fb_id: 138
  }
  pos {
    x: 32
    y: 41
  }
}
infos {
  cmd_id: 263
  element: PIN
  edit_type: SET
  pin {
    mod_id: 105
    task_id: 110
    fb_id: 137
    pin_index: 1
    pin_val {
      v {
        t: T_BOOL
        b: true
      }
      tm: 1681462860635700260
    }
  }
}
infos {
  cmd_id: 264
  element: FB
  edit_type: ADD
  fb {
    mod_id: 9
    task_id: 46
    fb_id: 139
    flib_name: "System"
    fc_name: "SYSSTATE"
  }
  pos {
    x: 36
    y: 194
  }
}
infos {
  cmd_id: 266
  element: FB
  edit_type: MV
  fb {
    mod_id: 9
    task_id: 46
    fb_id: 139
  }
  pos {
    x: 12
    y: 187
  }
}
infos {
  cmd_id: 277
  element: FB
  edit_type: MV
  fb {
    mod_id: 105
    task_id: 107
    fb_id: 128
  }
  pos {
    x: 29
    y: 56
  }
}
infos {
  cmd_id: 299
  element: FB
  edit_type: MV
  fb {
    mod_id: 105
    task_id: 107
    fb_id: 135
  }
  pos {
    x: 172
    y: 56
  }
}
infos {
  cmd_id: 301
  element: FB
  edit_type: MV
  fb {
    mod_id: 105
    task_id: 107
    fb_id: 129
  }
  pos {
    x: 101
    y: 56
  }
}
infos {
  cmd_id: 302
  element: LK
  edit_type: MV
  lk {
    mod_id: 105
    task_id: 107
    lk_id: 130
  }
  pos {
    x: 56
    y: 63
  }
  pos {
    x: 101
    y: 63
  }
}
infos {
  cmd_id: 303
  element: LK
  edit_type: MV
  lk {
    mod_id: 105
    task_id: 107
    lk_id: 136
  }
  pos {
    x: 128
    y: 63
  }
  pos {
    x: 172
    y: 63
  }
}
infos {
  cmd_id: 304
  element: FB
  edit_type: MV
  fb {
    mod_id: 9
    task_id: 46
    fb_id: 103
    fb_name: "\345\274\202\346\255\245\344\273\273\345\212\2411"
  }
  pos {
    x: 131
    y: 192
  }
}
infos {
  cmd_id: 306
  element: FB
  edit_type: MV
  fb {
    mod_id: 105
    task_id: 107
    fb_id: 128
    fb_name: "\345\274\202\346\255\245\344\273\273\345\212\2414"
  }
  pos {
    x: 29
    y: 56
  }
}
infos {
  cmd_id: 307
  element: FB
  edit_type: MV
  fb {
    mod_id: 105
    task_id: 107
    fb_id: 129
    fb_name: "\345\274\202\346\255\245\344\273\273\345\212\2415"
  }
  pos {
    x: 101
    y: 56
  }
}
infos {
  cmd_id: 308
  element: FB
  edit_type: MV
  fb {
    mod_id: 105
    task_id: 107
    fb_id: 135
    fb_name: "\345\274\202\346\255\245\344\273\273\345\212\2413"
  }
  pos {
    x: 172
    y: 56
  }
}
infos {
  cmd_id: 309
  element: FB
  edit_type: MV
  fb {
    mod_id: 105
    task_id: 110
    fb_id: 137
    fb_name: "\345\274\202\346\255\245\344\273\273\345\212\2416"
  }
  pos {
    x: 40
    y: 56
  }
}
infos {
  cmd_id: 310
  element: PIN
  edit_type: SET
  pin {
    mod_id: 105
    task_id: 107
    fb_id: 128
    pin_index: 5
    pin_val {
      v {
        t: T_BOOL
        b: true
      }
      tm: 1681464343654313345
    }
  }
}
infos {
  cmd_id: 311
  element: PIN
  edit_type: SET
  pin {
    mod_id: 105
    task_id: 107
    fb_id: 129
    pin_index: 5
    pin_val {
      v {
        t: T_BOOL
        b: true
      }
      tm: 1681464347534268252
    }
  }
}
infos {
  cmd_id: 312
  element: PIN
  edit_type: SET
  pin {
    mod_id: 105
    task_id: 107
    fb_id: 135
    pin_index: 5
    pin_val {
      v {
        t: T_BOOL
        b: true
      }
      tm: 1681464350550442107
    }
  }
}
infos {
  cmd_id: 313
  element: PIN
  edit_type: SET
  pin {
    mod_id: 105
    task_id: 110
    fb_id: 137
    pin_index: 5
    pin_val {
      v {
        t: T_BOOL
        b: true
      }
      tm: 1681464356654517059
    }
  }
}
infos {
  cmd_id: 322
  element: FB
  edit_type: MV
  fb {
    mod_id: 9
    task_id: 46
    fb_id: 119
  }
  pos {
    x: 187
    y: 192
  }
}
infos {
  cmd_id: 323
  element: LK
  edit_type: MV
  lk {
    mod_id: 9
    task_id: 46
    lk_id: 120
  }
  pos {
    x: 158
    y: 199
  }
  pos {
    x: 187
    y: 199
  }
}
infos {
  cmd_id: 329
  element: FB
  edit_type: MV
  fb {
    mod_id: 9
    task_id: 46
    fb_id: 121
    fb_name: "\345\274\202\346\255\245\344\273\273\345\212\2412"
  }
  pos {
    x: 242
    y: 192
  }
}
infos {
  cmd_id: 330
  element: LK
  edit_type: MV
  lk {
    mod_id: 9
    task_id: 46
    lk_id: 122
  }
  pos {
    x: 209
    y: 199
  }
  pos {
    x: 242
    y: 199
  }
}
infos {
  cmd_id: 331
  element: FB
  edit_type: ADD
  fb {
    mod_id: 105
    task_id: 106
    fb_id: 140
    flib_name: "Task"
    fc_name: "SLEEP"
  }
  pos {
    x: 83
    y: 49
  }
}
infos {
  cmd_id: 342
  element: FB
  edit_type: ADD
  fb {
    mod_id: 105
    task_id: 106
    fb_id: 141
    flib_name: "Logic"
    fc_name: "NOT"
  }
  pos {
    x: 72
    y: 57
  }
}
infos {
  cmd_id: 345
  element: FB
  edit_type: MV
  fb {
    mod_id: 105
    task_id: 106
    fb_id: 141
  }
  pos {
    x: 70
    y: 51
  }
}
infos {
  cmd_id: 347
  element: FB
  edit_type: RM
  fb {
    mod_id: 105
    task_id: 106
    fb_id: 141
  }
}
infos {
  cmd_id: 348
  element: FB
  edit_type: ADD
  fb {
    mod_id: 105
    task_id: 106
    fb_id: 142
    flib_name: "Comparison"
    fc_name: "NE_INT"
  }
  pos {
    x: 79
    y: 57
  }
}
infos {
  cmd_id: 349
  element: FB
  edit_type: MV
  fb {
    mod_id: 105
    task_id: 106
    fb_id: 142
  }
  pos {
    x: 71
    y: 45
  }
}
infos {
  cmd_id: 350
  element: LK
  edit_type: ADD
  lk {
    mod_id: 105
    task_id: 106
    lk_id: 143
    src_fb_id: 123
    target_fb_id: 142
    target_pin_index: 1
  }
  pos {
    x: 47
    y: 58
  }
  pos {
    x: 59
    y: 58
  }
  pos {
    x: 59
    y: 52
  }
  pos {
    x: 71
    y: 52
  }
}
infos {
  cmd_id: 351
  element: PIN
  edit_type: SET
  pin {
    mod_id: 105
    task_id: 106
    fb_id: 142
    pin_index: 2
    pin_val {
      v {
        t: T_INT32
        i: 0
      }
      tm: 1681571174138136249
    }
  }
}
infos {
  cmd_id: 352
  element: LK
  edit_type: ADD
  lk {
    mod_id: 105
    task_id: 106
    lk_id: 144
    src_fb_id: 142
    src_pin_index: 1
    target_fb_id: 140
    target_pin_index: 1
  }
  pos {
    x: 90
    y: 52
  }
  pos {
    x: 99
    y: 52
  }
  pos {
    x: 99
    y: 56
  }
  pos {
    x: 109
    y: 56
  }
}
infos {
  cmd_id: 359
  element: FB
  edit_type: MV
  fb {
    mod_id: 105
    task_id: 106
    fb_id: 140
  }
  pos {
    x: 113
    y: 45
  }
}
infos {
  cmd_id: 360
  element: LK
  edit_type: MV
  lk {
    mod_id: 105
    task_id: 106
    lk_id: 144
  }
  pos {
    x: 90
    y: 52
  }
  pos {
    x: 113
    y: 52
  }
}
infos {
  cmd_id: 361
  element: FB
  edit_type: ADD
  fb {
    mod_id: 105
    task_id: 106
    fb_id: 145
    flib_name: "Arithmetic"
    fc_name: "MUL_INT"
  }
  pos {
    x: 159
    y: 67
  }
}
infos {
  cmd_id: 365
  element: LK
  edit_type: ADD
  lk {
    mod_id: 105
    task_id: 106
    lk_id: 146
    src_fb_id: 140
    src_pin_index: 1
    target_fb_id: 145
  }
  pos {
    x: 138
    y: 52
  }
  pos {
    x: 148
    y: 52
  }
  pos {
    x: 148
    y: 49
  }
  pos {
    x: 158
    y: 49
  }
}
infos {
  cmd_id: 370
  element: LK
  edit_type: ADD
  lk {
    mod_id: 105
    task_id: 106
    lk_id: 147
    src_fb_id: 123
    src_pin_index: 1
    target_fb_id: 145
    target_pin_index: 1
  }
  pos {
    x: 47
    y: 60
  }
  pos {
    x: 104
    y: 60
  }
  pos {
    x: 104
    y: 53
  }
  pos {
    x: 161
    y: 53
  }
}
infos {
  cmd_id: 375
  element: PIN
  edit_type: SET
  pin {
    mod_id: 105
    task_id: 106
    fb_id: 145
    pin_index: 2
    pin_val {
      v {
        t: T_INT32
        i: 5
      }
      tm: 1681571290289475773
    }
  }
}
infos {
  cmd_id: 376
  element: FB
  edit_type: MV
  fb {
    mod_id: 105
    task_id: 106
    fb_id: 145
  }
  pos {
    x: 196
    y: 47
  }
}
infos {
  cmd_id: 377
  element: LK
  edit_type: MV
  lk {
    mod_id: 105
    task_id: 106
    lk_id: 146
  }
  pos {
    x: 138
    y: 52
  }
  pos {
    x: 196
    y: 52
  }
}
infos {
  cmd_id: 379
  element: LK
  edit_type: MV
  lk {
    mod_id: 105
    task_id: 106
    lk_id: 147
  }
  pos {
    x: 47
    y: 60
  }
  pos {
    x: 47
    y: 69
  }
  pos {
    x: 179
    y: 69
  }
  pos {
    x: 179
    y: 54
  }
  pos {
    x: 196
    y: 54
  }
}
infos {
  cmd_id: 380
  element: PIN
  edit_type: SET
  pin {
    mod_id: 105
    task_id: 106
    fb_id: 140
    pin_index: 2
    pin_val {
      v {
        t: T_TIME
        tm: 5000
      }
      tm: 1681571388005251469
    }
  }
}
infos {
  cmd_id: 381
  element: LK
  edit_type: RM
  lk {
    mod_id: 105
    task_id: 106
    lk_id: 144
  }
}
infos {
  cmd_id: 382
  element: LK
  edit_type: RM
  lk {
    mod_id: 105
    task_id: 106
    lk_id: 143
  }
}
infos {
  cmd_id: 383
  element: FB
  edit_type: RM
  fb {
    mod_id: 105
    task_id: 106
    fb_id: 142
  }
}
infos {
  cmd_id: 384
  element: FB
  edit_type: ADD
  fb {
    mod_id: 105
    task_id: 106
    fb_id: 148
    flib_name: "Comparison"
    fc_name: "EQ_INT"
  }
  pos {
    x: 79
    y: 50
  }
}
infos {
  cmd_id: 385
  element: LK
  edit_type: ADD
  lk {
    mod_id: 105
    task_id: 106
    lk_id: 149
    src_fb_id: 123
    target_fb_id: 148
    target_pin_index: 1
  }
  pos {
    x: 47
    y: 58
  }
  pos {
    x: 63
    y: 58
  }
  pos {
    x: 63
    y: 57
  }
  pos {
    x: 79
    y: 57
  }
}
infos {
  cmd_id: 386
  element: FB
  edit_type: MV
  fb {
    mod_id: 105
    task_id: 106
    fb_id: 148
  }
  pos {
    x: 72
    y: 41
  }
}
infos {
  cmd_id: 387
  element: LK
  edit_type: MV
  lk {
    mod_id: 105
    task_id: 106
    lk_id: 149
  }
  pos {
    x: 47
    y: 58
  }
  pos {
    x: 63
    y: 58
  }
  pos {
    x: 63
    y: 48
  }
  pos {
    x: 72
    y: 48
  }
}
infos {
  cmd_id: 388
  element: PIN
  edit_type: SET
  pin {
    mod_id: 105
    task_id: 106
    fb_id: 148
    pin_index: 2
    pin_val {
      v {
        t: T_INT32
        i: 0
      }
      tm: 1681571512788630782
    }
  }
}
infos {
  cmd_id: 389
  element: LK
  edit_type: ADD
  lk {
    mod_id: 105
    task_id: 106
    lk_id: 150
    src_fb_id: 148
    src_pin_index: 1
    target_fb_id: 140
    target_pin_index: 1
  }
  pos {
    x: 91
    y: 48
  }
  pos {
    x: 102
    y: 48
  }
  pos {
    x: 102
    y: 52
  }
  pos {
    x: 113
    y: 52
  }
}
