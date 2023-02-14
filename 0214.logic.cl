infos {
  edit_type: SET
  proj {
    proj_name: "rotbot-engine-project"
    proj_uuid: "{32d243ff-a6ac-45a8-ad42-b0508b1c24a1}"
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
  element: MOD
  edit_type: ADD
  mod {
    mod_id: 12
    mod_name: "FGH"
  }
}
infos {
  cmd_id: 13
  element: TASK
  edit_type: ADD
  task {
    mod_id: 12
    task_id: 13
    task_name: "IOP1"
    interval: 2000
  }
}
infos {
  cmd_id: 14
  element: FB
  edit_type: ADD
  fb {
    mod_id: 12
    task_id: 13
    fb_id: 14
    flib_name: "Counter"
    fc_name: "CTUD_INT"
  }
  pos {
    x: 44
    y: 43
  }
}
infos {
  cmd_id: 15
  element: FB
  edit_type: ADD
  fb {
    mod_id: 12
    task_id: 13
    fb_id: 15
    flib_name: "Counter"
    fc_name: "CTUD_INT"
  }
  pos {
    x: 94
    y: 46
  }
}
infos {
  cmd_id: 16
  element: TASK
  edit_type: ADD
  task {
    mod_id: 12
    task_id: 16
    task_name: "IOP2"
    interval: 3000
  }
}
infos {
  cmd_id: 17
  element: FB
  edit_type: ADD
  fb {
    mod_id: 12
    task_id: 16
    fb_id: 17
    flib_name: "Arithmetic"
    fc_name: "ADD_INT"
  }
  pos {
    x: 41
    y: 46
  }
}
infos {
  cmd_id: 18
  element: FB
  edit_type: ADD
  fb {
    mod_id: 12
    task_id: 16
    fb_id: 18
    flib_name: "Arithmetic"
    fc_name: "ADD_INT"
  }
  pos {
    x: 85
    y: 52
  }
}
infos {
  cmd_id: 19
  element: FB
  edit_type: ADD
  fb {
    mod_id: 12
    task_id: 16
    fb_id: 19
    flib_name: "Arithmetic"
    fc_name: "ADD_INT"
  }
  pos {
    x: 57
    y: 19
  }
}
infos {
  cmd_id: 20
  element: FB
  edit_type: ADD
  fb {
    mod_id: 12
    task_id: 16
    fb_id: 20
    flib_name: "Arithmetic"
    fc_name: "ADD_INT"
  }
  pos {
    x: 101
    y: 25
  }
}
infos {
  cmd_id: 21
  element: LK
  edit_type: ADD
  lk {
    mod_id: 12
    task_id: 16
    lk_id: 21
    src_fb_id: 17
    src_pin_index: 1
    target_fb_id: 18
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
  cmd_id: 22
  element: LK
  edit_type: ADD
  lk {
    mod_id: 12
    task_id: 16
    lk_id: 22
    src_fb_id: 19
    src_pin_index: 1
    target_fb_id: 20
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
  cmd_id: 23
  element: VI
  edit_type: ADD
  vi {
    mod_id: 12
    task_id: 16
    fb_id: 17
    pin_index: 1
    ev_id: 1
    vi_id: 23
  }
}
infos {
  cmd_id: 24
  element: VI
  edit_type: ADD
  vi {
    mod_id: 12
    task_id: 16
    fb_id: 17
    pin_index: 2
    ev_id: 2
    vi_id: 24
  }
}
infos {
  cmd_id: 25
  element: VI
  edit_type: ADD
  vi {
    mod_id: 12
    task_id: 16
    fb_id: 18
    pin_index: 2
    ev_id: 3
    vi_id: 25
  }
}
infos {
  cmd_id: 26
  element: VO
  edit_type: ADD
  vo {
    mod_id: 12
    task_id: 16
    fb_id: 18
    pin_index: 1
    ev_id: 4
    vo_id: 26
  }
}
infos {
  cmd_id: 27
  element: MOD
  edit_type: ADD
  mod {
    mod_id: 27
    mod_name: "UIV"
  }
}
infos {
  cmd_id: 28
  element: TASK
  edit_type: ADD
  task {
    mod_id: 27
    task_id: 28
    task_name: "BMW1"
    interval: 2000
  }
}
infos {
  cmd_id: 29
  element: FB
  edit_type: ADD
  fb {
    mod_id: 27
    task_id: 28
    fb_id: 29
    flib_name: "Counter"
    fc_name: "CTUD_INT"
  }
  pos {
    x: 39
    y: 46
  }
}
infos {
  cmd_id: 30
  element: TASK
  edit_type: ADD
  task {
    mod_id: 27
    task_id: 30
    task_name: "BMW2"
    interval: 4000
  }
}
infos {
  cmd_id: 31
  element: FB
  edit_type: ADD
  fb {
    mod_id: 27
    task_id: 30
    fb_id: 31
    flib_name: "Counter"
    fc_name: "CTUD_INT"
  }
  pos {
    x: 26
    y: 25
  }
}
infos {
  cmd_id: 32
  element: TASK
  edit_type: ADD
  task {
    mod_id: 27
    task_id: 32
    task_name: "BMW3"
    interval: 2000
  }
}
infos {
  cmd_id: 33
  element: PIN
  edit_type: SET
  pin {
    mod_id: 12
    task_id: 13
    fb_id: 14
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
  cmd_id: 34
  element: PIN
  edit_type: SET
  pin {
    mod_id: 12
    task_id: 13
    fb_id: 14
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
  cmd_id: 35
  element: PIN
  edit_type: SET
  pin {
    mod_id: 27
    task_id: 30
    fb_id: 31
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
  cmd_id: 36
  element: PIN
  edit_type: SET
  pin {
    mod_id: 27
    task_id: 30
    fb_id: 31
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
  cmd_id: 37
  element: PIN
  edit_type: SET
  pin {
    mod_id: 27
    task_id: 28
    fb_id: 29
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
  cmd_id: 38
  element: PIN
  edit_type: SET
  pin {
    mod_id: 27
    task_id: 28
    fb_id: 29
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
