infos {
  edit_type: SET
  proj {
    proj_name: "rotbot-engine-project"
    proj_uuid: "{438d2221-b413-4229-88b6-760ad1e49b3c}"
  }
}
infos {
  cmd_id: 1
  element: EV
  edit_type: ADD
  ev {
    ev_id: 1
    ev_name: "I1"
    ev_type: 2
    ev_desc: "int 1"
    init_val {
      v {
        t: T_INT32
        i: 100
      }
      tm: 1676355102060948895
    }
  }
}
infos {
  cmd_id: 2
  element: EV
  edit_type: ADD
  ev {
    ev_id: 2
    ev_name: "I2"
    ev_type: 2
    ev_desc: "int 2"
    init_val {
      v {
        t: T_INT32
        i: 200
      }
      tm: 1676355110332427551
    }
  }
}
infos {
  cmd_id: 3
  element: EV
  edit_type: ADD
  ev {
    ev_id: 3
    ev_name: "I3"
    ev_type: 2
    ev_desc: "int 2"
    init_val {
      v {
        t: T_INT32
        i: 300
      }
      tm: 1676355117774716831
    }
  }
}
infos {
  cmd_id: 4
  element: EV
  edit_type: ADD
  ev {
    ev_id: 4
    ev_name: "I4"
    ev_type: 2
    ev_desc: "int 4"
    init_val {
      v {
        t: T_INT32
        i: 104
      }
      tm: 1676355130635830800
    }
  }
}
infos {
  cmd_id: 5
  element: EV
  edit_type: ADD
  ev {
    ev_id: 5
    ev_name: "I5"
    ev_type: 2
    ev_desc: "int 5"
    init_val {
      v {
        t: T_INT32
        i: 105
      }
      tm: 1676355146177925368
    }
  }
}
infos {
  cmd_id: 6
  element: EV
  edit_type: ADD
  ev {
    ev_id: 6
    ev_name: "UI1"
    ev_type: 3
    ev_desc: "uint 1"
    init_val {
      v {
        t: T_UINT32
        ui: 201
      }
      tm: 1676355171765541438
    }
  }
}
infos {
  cmd_id: 7
  element: EV
  edit_type: ADD
  ev {
    ev_id: 7
    ev_name: "UI2"
    ev_type: 3
    ev_desc: "uint 2"
    init_val {
      v {
        t: T_UINT32
        ui: 202
      }
      tm: 1676355178548029987
    }
  }
}
infos {
  cmd_id: 8
  element: EV
  edit_type: ADD
  ev {
    ev_id: 8
    ev_name: "UI3"
    ev_type: 3
    ev_desc: "uint 3"
    init_val {
      v {
        t: T_UINT32
        ui: 203
      }
      tm: 1676355188648114766
    }
  }
}
infos {
  cmd_id: 9
  element: EV
  edit_type: ADD
  ev {
    ev_id: 9
    ev_name: "F1"
    ev_type: 6
    ev_desc: "float 1"
    init_val {
      v {
        t: T_FLOAT32
        f: 101.1
      }
      tm: 1676355215913175981
    }
  }
}
infos {
  cmd_id: 10
  element: EV
  edit_type: ADD
  ev {
    ev_id: 10
    ev_name: "F2"
    ev_type: 6
    ev_desc: "float 2"
    init_val {
      v {
        t: T_FLOAT32
        f: 102.1
      }
      tm: 1676355225206780789
    }
  }
}
infos {
  cmd_id: 11
  element: EV
  edit_type: ADD
  ev {
    ev_id: 11
    ev_name: "F3"
    ev_type: 6
    ev_desc: "float 3"
    init_val {
      v {
        t: T_FLOAT32
        f: 103.1
      }
      tm: 1676355240971557730
    }
  }
}
infos {
  cmd_id: 12
  element: EV
  edit_type: ADD
  ev {
    ev_id: 12
    ev_name: "FsmSatus"
    ev_type: 2
    ev_desc: "Desc"
    init_val {
      v {
        t: T_INT32
        i: 0
      }
      tm: 1676535213607616581
    }
  }
}
infos {
  cmd_id: 13
  element: EV
  edit_type: ADD
  ev {
    ev_id: 13
    ev_name: "Fsm1"
    ev_type: 1
    ev_desc: "Desc"
    init_val {
      v {
        t: T_BOOL
        b: false
      }
      tm: 1676535348228248030
    }
  }
}
infos {
  cmd_id: 14
  element: EV
  edit_type: ADD
  ev {
    ev_id: 14
    ev_name: "Fsm2"
    ev_type: 1
    ev_desc: "Desc"
    init_val {
      v {
        t: T_BOOL
        b: false
      }
      tm: 1676535353283853942
    }
  }
}
infos {
  cmd_id: 15
  element: EV
  edit_type: ADD
  ev {
    ev_id: 15
    ev_name: "Fsm3"
    ev_type: 1
    ev_desc: "Desc"
    init_val {
      v {
        t: T_BOOL
        b: false
      }
      tm: 1676535358003432320
    }
  }
}
infos {
  cmd_id: 16
  element: MOD
  edit_type: ADD
  mod {
    mod_id: 16
    mod_name: "FGH"
  }
}
infos {
  cmd_id: 17
  element: TASK
  edit_type: ADD
  task {
    mod_id: 16
    task_id: 17
    task_name: "IOP1"
    interval: 2000
  }
}
infos {
  cmd_id: 18
  element: FB
  edit_type: ADD
  fb {
    mod_id: 16
    task_id: 17
    fb_id: 18
    flib_name: "Counter"
    fc_name: "CTUD_INT"
  }
  pos {
    x: 44
    y: 43
  }
}
infos {
  cmd_id: 19
  element: FB
  edit_type: ADD
  fb {
    mod_id: 16
    task_id: 17
    fb_id: 19
    flib_name: "Counter"
    fc_name: "CTUD_INT"
  }
  pos {
    x: 94
    y: 46
  }
}
infos {
  cmd_id: 20
  element: TASK
  edit_type: ADD
  task {
    mod_id: 16
    task_id: 20
    task_name: "IOP2"
    interval: 3000
  }
}
infos {
  cmd_id: 21
  element: FB
  edit_type: ADD
  fb {
    mod_id: 16
    task_id: 20
    fb_id: 21
    flib_name: "Arithmetic"
    fc_name: "ADD_INT"
  }
  pos {
    x: 41
    y: 46
  }
}
infos {
  cmd_id: 22
  element: FB
  edit_type: ADD
  fb {
    mod_id: 16
    task_id: 20
    fb_id: 22
    flib_name: "Arithmetic"
    fc_name: "ADD_INT"
  }
  pos {
    x: 85
    y: 52
  }
}
infos {
  cmd_id: 23
  element: FB
  edit_type: ADD
  fb {
    mod_id: 16
    task_id: 20
    fb_id: 23
    flib_name: "Arithmetic"
    fc_name: "ADD_INT"
  }
  pos {
    x: 57
    y: 19
  }
}
infos {
  cmd_id: 24
  element: FB
  edit_type: ADD
  fb {
    mod_id: 16
    task_id: 20
    fb_id: 24
    flib_name: "Arithmetic"
    fc_name: "ADD_INT"
  }
  pos {
    x: 101
    y: 25
  }
}
infos {
  cmd_id: 25
  element: LK
  edit_type: ADD
  lk {
    mod_id: 16
    task_id: 20
    lk_id: 25
    src_fb_id: 21
    src_pin_index: 1
    target_fb_id: 22
    target_pin_index: 1
  }
  pos {
    x: 56
    y: 53
  }
  pos {
    x: 70
    y: 53
  }
  pos {
    x: 70
    y: 59
  }
  pos {
    x: 85
    y: 59
  }
}
infos {
  cmd_id: 26
  element: LK
  edit_type: ADD
  lk {
    mod_id: 16
    task_id: 20
    lk_id: 26
    src_fb_id: 23
    src_pin_index: 1
    target_fb_id: 24
    target_pin_index: 1
  }
  pos {
    x: 72
    y: 26
  }
  pos {
    x: 86
    y: 26
  }
  pos {
    x: 86
    y: 32
  }
  pos {
    x: 101
    y: 32
  }
}
infos {
  cmd_id: 27
  element: VI
  edit_type: ADD
  vi {
    mod_id: 16
    task_id: 20
    fb_id: 21
    pin_index: 1
    ev_id: 1
    vi_id: 27
  }
}
infos {
  cmd_id: 28
  element: VI
  edit_type: ADD
  vi {
    mod_id: 16
    task_id: 20
    fb_id: 21
    pin_index: 2
    ev_id: 2
    vi_id: 28
  }
}
infos {
  cmd_id: 29
  element: VI
  edit_type: ADD
  vi {
    mod_id: 16
    task_id: 20
    fb_id: 22
    pin_index: 2
    ev_id: 3
    vi_id: 29
  }
}
infos {
  cmd_id: 30
  element: VO
  edit_type: ADD
  vo {
    mod_id: 16
    task_id: 20
    fb_id: 22
    pin_index: 1
    ev_id: 4
    vo_id: 30
  }
}
infos {
  cmd_id: 31
  element: MOD
  edit_type: ADD
  mod {
    mod_id: 31
    mod_name: "UIV"
  }
}
infos {
  cmd_id: 32
  element: TASK
  edit_type: ADD
  task {
    mod_id: 31
    task_id: 32
    task_name: "BMW1"
    interval: 2000
  }
}
infos {
  cmd_id: 33
  element: FB
  edit_type: ADD
  fb {
    mod_id: 31
    task_id: 32
    fb_id: 33
    flib_name: "Counter"
    fc_name: "CTUD_INT"
  }
  pos {
    x: 39
    y: 46
  }
}
infos {
  cmd_id: 34
  element: TASK
  edit_type: ADD
  task {
    mod_id: 31
    task_id: 34
    task_name: "BMW2"
    interval: 4000
  }
}
infos {
  cmd_id: 35
  element: FB
  edit_type: ADD
  fb {
    mod_id: 31
    task_id: 34
    fb_id: 35
    flib_name: "Counter"
    fc_name: "CTUD_INT"
  }
  pos {
    x: 26
    y: 25
  }
}
infos {
  cmd_id: 36
  element: TASK
  edit_type: ADD
  task {
    mod_id: 31
    task_id: 36
    task_name: "BMW3"
    interval: 2000
  }
}
infos {
  cmd_id: 37
  element: FB
  edit_type: ADD
  fb {
    mod_id: 31
    task_id: 36
    fb_id: 37
    flib_name: "Fsm"
    fc_name: "FSM"
  }
  pos {
    x: 31
    y: 34
  }
}
infos {
  cmd_id: 38
  element: FB
  edit_type: ADD
  fb {
    mod_id: 31
    task_id: 36
    fb_id: 38
    flib_name: "Fsm"
    fc_name: "FSM"
  }
  pos {
    x: 84
    y: 13
  }
}
infos {
  cmd_id: 39
  element: FB
  edit_type: ADD
  fb {
    mod_id: 31
    task_id: 36
    fb_id: 39
    flib_name: "Fsm"
    fc_name: "FSM"
  }
  pos {
    x: 123
    y: 38
  }
}
infos {
  cmd_id: 40
  element: FB
  edit_type: ADD
  fb {
    mod_id: 31
    task_id: 36
    fb_id: 40
    flib_name: "Trigger"
    fc_name: "U_TRIG"
  }
  pos {
    x: 64
    y: 52
  }
}
infos {
  cmd_id: 41
  element: FB
  edit_type: ADD
  fb {
    mod_id: 31
    task_id: 36
    fb_id: 41
    flib_name: "Trigger"
    fc_name: "U_TRIG"
  }
  pos {
    x: 130
    y: 15
  }
}
infos {
  cmd_id: 42
  element: FB
  edit_type: ADD
  fb {
    mod_id: 31
    task_id: 36
    fb_id: 42
    flib_name: "Trigger"
    fc_name: "U_TRIG"
  }
  pos {
    x: 157
    y: 59
  }
}
infos {
  cmd_id: 43
  element: FB
  edit_type: ADD
  fb {
    mod_id: 31
    task_id: 36
    fb_id: 43
    flib_name: "Counter"
    fc_name: "CTUD_INT"
  }
  pos {
    x: 18
    y: 12
  }
}
infos {
  cmd_id: 44
  element: LK
  edit_type: ADD
  lk {
    mod_id: 31
    task_id: 36
    lk_id: 44
    src_fb_id: 37
    src_pin_index: 2
    target_fb_id: 40
    target_pin_index: 1
  }
  pos {
    x: 48
    y: 43
  }
  pos {
    x: 56
    y: 43
  }
  pos {
    x: 56
    y: 59
  }
  pos {
    x: 64
    y: 59
  }
}
infos {
  cmd_id: 45
  element: LK
  edit_type: ADD
  lk {
    mod_id: 31
    task_id: 36
    lk_id: 45
    src_fb_id: 38
    src_pin_index: 2
    target_fb_id: 41
    target_pin_index: 1
  }
  pos {
    x: 101
    y: 22
  }
  pos {
    x: 130
    y: 22
  }
}
infos {
  cmd_id: 46
  element: LK
  edit_type: ADD
  lk {
    mod_id: 31
    task_id: 36
    lk_id: 46
    src_fb_id: 39
    src_pin_index: 2
    target_fb_id: 42
    target_pin_index: 1
  }
  pos {
    x: 140
    y: 47
  }
  pos {
    x: 148
    y: 47
  }
  pos {
    x: 148
    y: 66
  }
  pos {
    x: 157
    y: 66
  }
}
infos {
  cmd_id: 47
  element: LK
  edit_type: ADD
  lk {
    mod_id: 31
    task_id: 36
    lk_id: 47
    src_fb_id: 37
    src_pin_index: 1
    target_fb_id: 38
    target_pin_index: 2
  }
  pos {
    x: 48
    y: 41
  }
  pos {
    x: 66
    y: 41
  }
  pos {
    x: 66
    y: 22
  }
  pos {
    x: 84
    y: 22
  }
}
infos {
  cmd_id: 48
  element: LK
  edit_type: ADD
  lk {
    mod_id: 31
    task_id: 36
    lk_id: 48
    src_fb_id: 38
    src_pin_index: 1
    target_fb_id: 39
    target_pin_index: 2
  }
  pos {
    x: 101
    y: 20
  }
  pos {
    x: 112
    y: 20
  }
  pos {
    x: 112
    y: 47
  }
  pos {
    x: 123
    y: 47
  }
}
infos {
  cmd_id: 49
  element: VI
  edit_type: ADD
  vi {
    mod_id: 31
    task_id: 36
    fb_id: 37
    pin_index: 3
    ev_id: 12
    vi_id: 49
  }
}
infos {
  cmd_id: 50
  element: VI
  edit_type: ADD
  vi {
    mod_id: 31
    task_id: 36
    fb_id: 38
    pin_index: 3
    ev_id: 12
    vi_id: 50
  }
}
infos {
  cmd_id: 51
  element: VI
  edit_type: ADD
  vi {
    mod_id: 31
    task_id: 36
    fb_id: 39
    pin_index: 3
    ev_id: 12
    vi_id: 51
  }
}
infos {
  cmd_id: 52
  element: VO
  edit_type: ADD
  vo {
    mod_id: 31
    task_id: 36
    fb_id: 37
    pin_index: 2
    ev_id: 13
    vo_id: 52
  }
}
infos {
  cmd_id: 53
  element: VO
  edit_type: ADD
  vo {
    mod_id: 31
    task_id: 36
    fb_id: 38
    pin_index: 2
    ev_id: 14
    vo_id: 53
  }
}
infos {
  cmd_id: 54
  element: VO
  edit_type: ADD
  vo {
    mod_id: 31
    task_id: 36
    fb_id: 39
    pin_index: 2
    ev_id: 15
    vo_id: 54
  }
}
infos {
  cmd_id: 55
  element: VO
  edit_type: ADD
  vo {
    mod_id: 31
    task_id: 36
    fb_id: 43
    pin_index: 3
    ev_id: 12
    vo_id: 55
  }
}
infos {
  cmd_id: 56
  element: PIN
  edit_type: SET
  pin {
    mod_id: 16
    task_id: 17
    fb_id: 18
    pin_index: 5
    pin_val {
      v {
        t: T_INT32
        i: 2000
      }
      tm: 1676354871598576150
    }
  }
}
infos {
  cmd_id: 57
  element: PIN
  edit_type: SET
  pin {
    mod_id: 16
    task_id: 17
    fb_id: 18
    pin_index: 1
    pin_val {
      v {
        t: T_BOOL
        b: true
      }
      tm: 1676354876857515097
    }
  }
}
infos {
  cmd_id: 58
  element: PIN
  edit_type: SET
  pin {
    mod_id: 31
    task_id: 34
    fb_id: 35
    pin_index: 5
    pin_val {
      v {
        t: T_INT32
        i: 2000
      }
      tm: 1676354918468474203
    }
  }
}
infos {
  cmd_id: 59
  element: PIN
  edit_type: SET
  pin {
    mod_id: 31
    task_id: 34
    fb_id: 35
    pin_index: 1
    pin_val {
      v {
        t: T_BOOL
        b: true
      }
      tm: 1676354926359839782
    }
  }
}
infos {
  cmd_id: 60
  element: PIN
  edit_type: SET
  pin {
    mod_id: 31
    task_id: 32
    fb_id: 33
    pin_index: 5
    pin_val {
      v {
        t: T_INT32
        i: 500
      }
      tm: 1676354938788141205
    }
  }
}
infos {
  cmd_id: 61
  element: PIN
  edit_type: SET
  pin {
    mod_id: 31
    task_id: 32
    fb_id: 33
    pin_index: 1
    pin_val {
      v {
        t: T_BOOL
        b: true
      }
      tm: 1676354943085381154
    }
  }
}
infos {
  cmd_id: 62
  element: PIN
  edit_type: SET
  pin {
    mod_id: 31
    task_id: 36
    fb_id: 37
    pin_index: 4
    pin_val {
      v {
        t: T_INT32
        i: 10
      }
      tm: 1676535307261002251
    }
  }
}
infos {
  cmd_id: 63
  element: PIN
  edit_type: SET
  pin {
    mod_id: 31
    task_id: 36
    fb_id: 38
    pin_index: 4
    pin_val {
      v {
        t: T_INT32
        i: 20
      }
      tm: 1676535311868478275
    }
  }
}
infos {
  cmd_id: 64
  element: PIN
  edit_type: SET
  pin {
    mod_id: 31
    task_id: 36
    fb_id: 39
    pin_index: 4
    pin_val {
      v {
        t: T_INT32
        i: 30
      }
      tm: 1676535317622559741
    }
  }
}
infos {
  cmd_id: 65
  element: PIN
  edit_type: SET
  pin {
    mod_id: 31
    task_id: 36
    fb_id: 37
    pin_index: 1
    pin_val {
      v {
        t: T_BOOL
        b: true
      }
      tm: 1676535484408987319
    }
  }
}
infos {
  cmd_id: 66
  element: PIN
  edit_type: SET
  pin {
    mod_id: 31
    task_id: 36
    fb_id: 43
    pin_index: 5
    pin_val {
      v {
        t: T_INT32
        i: 2000
      }
      tm: 1676535699097751732
    }
  }
}
infos {
  cmd_id: 67
  element: PIN
  edit_type: SET
  pin {
    mod_id: 31
    task_id: 36
    fb_id: 43
    pin_index: 1
    pin_val {
      v {
        t: T_BOOL
        b: true
      }
      tm: 1676535703577543774
    }
  }
}
