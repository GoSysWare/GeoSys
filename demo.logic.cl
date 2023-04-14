infos {
  edit_type: SET
  proj {
    proj_name: "rotbot-engine-project"
    proj_uuid: "{97d9ca72-bc17-4ba3-8e11-2186db0f2918}"
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
