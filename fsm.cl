infos {
  cmd_id: 50
  edit_type: SET
  proj {
    proj_name: "rotbot-engine-project"
    proj_uuid: "{43da547f-50c0-4601-a368-147f52b546e8}"
  }
}
infos {
  cmd_id: 1
  element: MOD
  edit_type: ADD
  mod {
    mod_id: 1
    mod_name: "M1"
  }
}
infos {
  cmd_id: 2
  element: EV
  edit_type: ADD
  ev {
    ev_id: 2
    ev_name: "FSM"
    ev_type: 2
    ev_desc: "Desc"
    init_val {
      v {
        t: T_INT32
        i: 0
      }
      tm: 1683373467281626259
    }
  }
}
infos {
  cmd_id: 3
  element: TASK
  edit_type: ADD
  task {
    mod_id: 1
    task_id: 3
    task_name: "P1"
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
    flib_name: "Fsm"
    fc_name: "FSM"
  }
  pos {
    x: 25
    y: 24
  }
}
infos {
  cmd_id: 5
  element: FB
  edit_type: ADD
  fb {
    mod_id: 1
    task_id: 3
    fb_id: 5
    flib_name: "Fsm"
    fc_name: "FSM"
  }
  pos {
    x: 79
    y: 30
  }
}
infos {
  cmd_id: 9
  element: FB
  edit_type: ADD
  fb {
    mod_id: 1
    task_id: 3
    fb_id: 6
    flib_name: "Fsm"
    fc_name: "FSM"
  }
  pos {
    x: 102
    y: 21
  }
}
infos {
  cmd_id: 13
  element: LK
  edit_type: ADD
  lk {
    mod_id: 1
    task_id: 3
    lk_id: 7
    src_fb_id: 4
    src_pin_index: 1
    target_fb_id: 5
    target_pin_index: 2
  }
  pos {
    x: 39
    y: 23
  }
  pos {
    x: 47
    y: 23
  }
  pos {
    x: 47
    y: 24
  }
  pos {
    x: 55
    y: 24
  }
}
infos {
  cmd_id: 14
  element: LK
  edit_type: ADD
  lk {
    mod_id: 1
    task_id: 3
    lk_id: 8
    src_fb_id: 5
    src_pin_index: 1
    target_fb_id: 6
    target_pin_index: 2
  }
  pos {
    x: 76
    y: 22
  }
  pos {
    x: 87
    y: 22
  }
  pos {
    x: 87
    y: 26
  }
  pos {
    x: 99
    y: 26
  }
}
infos {
  cmd_id: 22
  element: FB
  edit_type: MV
  fb {
    mod_id: 1
    task_id: 3
    fb_id: 5
  }
  pos {
    x: 57
    y: 14
  }
}
infos {
  cmd_id: 27
  element: FB
  edit_type: MV
  fb {
    mod_id: 1
    task_id: 3
    fb_id: 4
  }
  pos {
    x: 9
    y: 13
  }
}
infos {
  cmd_id: 28
  element: LK
  edit_type: MV
  lk {
    mod_id: 1
    task_id: 3
    lk_id: 7
  }
  pos {
    x: 30
    y: 20
  }
  pos {
    x: 47
    y: 20
  }
  pos {
    x: 47
    y: 23
  }
  pos {
    x: 57
    y: 23
  }
}
infos {
  cmd_id: 29
  element: VI
  edit_type: ADD
  vi {
    mod_id: 1
    task_id: 3
    fb_id: 4
    pin_index: 3
    ev_id: 2
    vi_id: 9
  }
}
infos {
  cmd_id: 30
  element: VI
  edit_type: ADD
  vi {
    mod_id: 1
    task_id: 3
    fb_id: 5
    pin_index: 3
    ev_id: 2
    vi_id: 10
  }
}
infos {
  cmd_id: 31
  element: VI
  edit_type: ADD
  vi {
    mod_id: 1
    task_id: 3
    fb_id: 6
    pin_index: 3
    ev_id: 2
    vi_id: 11
  }
}
infos {
  cmd_id: 32
  element: PIN
  edit_type: SET
  pin {
    mod_id: 1
    task_id: 3
    fb_id: 4
    pin_index: 4
    pin_val {
      v {
        t: T_INT32
        i: 1
      }
      tm: 1683373533134949072
    }
  }
}
infos {
  cmd_id: 33
  element: PIN
  edit_type: SET
  pin {
    mod_id: 1
    task_id: 3
    fb_id: 4
    pin_index: 4
    pin_val {
      v {
        t: T_INT32
        i: 0
      }
      tm: 1683373537558690323
    }
  }
}
infos {
  cmd_id: 34
  element: PIN
  edit_type: SET
  pin {
    mod_id: 1
    task_id: 3
    fb_id: 5
    pin_index: 4
    pin_val {
      v {
        t: T_INT32
        i: 1
      }
      tm: 1683373540838763222
    }
  }
}
infos {
  cmd_id: 35
  element: PIN
  edit_type: SET
  pin {
    mod_id: 1
    task_id: 3
    fb_id: 6
    pin_index: 4
    pin_val {
      v {
        t: T_INT32
        i: 2
      }
      tm: 1683373544294916782
    }
  }
}
infos {
  cmd_id: 36
  element: FB
  edit_type: ADD
  fb {
    mod_id: 1
    task_id: 3
    fb_id: 12
    flib_name: "Fsm"
    fc_name: "FSM"
  }
  pos {
    x: 95
    y: 14
  }
}
infos {
  cmd_id: 40
  element: LK
  edit_type: ADD
  lk {
    mod_id: 1
    task_id: 3
    lk_id: 13
    src_fb_id: 6
    src_pin_index: 1
    target_fb_id: 12
    target_pin_index: 2
  }
  pos {
    x: 116
    y: 21
  }
  pos {
    x: 124
    y: 21
  }
  pos {
    x: 124
    y: 24
  }
  pos {
    x: 133
    y: 24
  }
}
infos {
  cmd_id: 41
  element: FB
  edit_type: MV
  fb {
    mod_id: 1
    task_id: 3
    fb_id: 12
  }
  pos {
    x: 138
    y: 13
  }
}
infos {
  cmd_id: 43
  element: FB
  edit_type: MV
  fb {
    mod_id: 1
    task_id: 3
    fb_id: 6
  }
  pos {
    x: 99
    y: 14
  }
}
infos {
  cmd_id: 44
  element: LK
  edit_type: MV
  lk {
    mod_id: 1
    task_id: 3
    lk_id: 8
  }
  pos {
    x: 78
    y: 21
  }
  pos {
    x: 87
    y: 21
  }
  pos {
    x: 87
    y: 23
  }
  pos {
    x: 99
    y: 23
  }
}
infos {
  cmd_id: 45
  element: LK
  edit_type: MV
  lk {
    mod_id: 1
    task_id: 3
    lk_id: 13
  }
  pos {
    x: 120
    y: 21
  }
  pos {
    x: 124
    y: 21
  }
  pos {
    x: 124
    y: 22
  }
  pos {
    x: 138
    y: 22
  }
}
infos {
  cmd_id: 46
  element: FB
  edit_type: ADD
  fb {
    mod_id: 1
    task_id: 3
    fb_id: 14
    flib_name: "Devices"
    fc_name: "SIM_READ"
  }
  pos {
    x: 8
    y: 39
  }
}
infos {
  cmd_id: 47
  element: PIN
  edit_type: SET
  pin {
    mod_id: 1
    task_id: 3
    fb_id: 14
    pin_index: 1
    pin_val {
      v {
        t: T_STRING
        str: "SIM"
      }
      tm: 1683373656892481141
    }
  }
}
infos {
  cmd_id: 48
  element: PIN
  edit_type: SET
  pin {
    mod_id: 1
    task_id: 3
    fb_id: 14
    pin_index: 5
    pin_val {
      v {
        t: T_STRING
        str: "$SECOND"
      }
      tm: 1683373669164931791
    }
  }
}
infos {
  cmd_id: 49
  element: VI
  edit_type: ADD
  vi {
    mod_id: 1
    task_id: 3
    fb_id: 12
    pin_index: 3
    ev_id: 2
    vi_id: 15
  }
}
infos {
  cmd_id: 50
  element: PIN
  edit_type: SET
  pin {
    mod_id: 1
    task_id: 3
    fb_id: 12
    pin_index: 4
    pin_val {
      v {
        t: T_INT32
        i: 0
      }
      tm: 1683373800114267872
    }
  }
}
