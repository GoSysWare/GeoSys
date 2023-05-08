infos {
  cmd_id: 26
  edit_type: SET
  proj {
    proj_name: "rotbot-engine-project"
    proj_uuid: "{8678863d-6697-4967-aaf0-53e0633d6625}"
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
  element: TASK
  edit_type: ADD
  task {
    mod_id: 1
    task_id: 2
    task_name: "P1"
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
    flib_name: "Comparison"
    fc_name: "EQ_UINT"
  }
  pos {
    x: 19
    y: 69
  }
}
infos {
  cmd_id: 5
  element: FB
  edit_type: ADD
  fb {
    mod_id: 1
    task_id: 2
    fb_id: 4
    flib_name: "Devices"
    fc_name: "SIM_READ"
  }
  pos {
    x: 11
    y: 63
  }
}
infos {
  cmd_id: 7
  element: PIN
  edit_type: SET
  pin {
    mod_id: 1
    task_id: 2
    fb_id: 4
    pin_index: 1
    pin_val {
      v {
        t: T_STRING
        str: "SIM"
      }
      tm: 1683514986640527153
    }
  }
}
infos {
  cmd_id: 8
  element: PIN
  edit_type: SET
  pin {
    mod_id: 1
    task_id: 2
    fb_id: 4
    pin_index: 5
    pin_val {
      v {
        t: T_STRING
        str: "$SECOND"
      }
      tm: 1683514994185327331
    }
  }
}
infos {
  cmd_id: 11
  element: FB
  edit_type: MV
  fb {
    mod_id: 1
    task_id: 2
    fb_id: 4
  }
  pos {
    x: 7
    y: 56
  }
}
infos {
  cmd_id: 12
  element: EV
  edit_type: ADD
  ev {
    ev_id: 5
    ev_name: "EV1"
    ev_type: 3
    ev_desc: "Desc"
    init_val {
      v {
        t: T_UINT32
        ui: 0
      }
      tm: 1683515019387833196
    }
  }
}
infos {
  cmd_id: 13
  element: FB
  edit_type: ADD
  fb {
    mod_id: 1
    task_id: 2
    fb_id: 6
    flib_name: "Converter"
    fc_name: "D2UI"
  }
  pos {
    x: 48
    y: 80
  }
}
infos {
  cmd_id: 15
  element: FB
  edit_type: MV
  fb {
    mod_id: 1
    task_id: 2
    fb_id: 6
  }
  pos {
    x: 45
    y: 58
  }
}
infos {
  cmd_id: 16
  element: LK
  edit_type: ADD
  lk {
    mod_id: 1
    task_id: 2
    lk_id: 7
    src_fb_id: 4
    src_pin_index: 4
    target_fb_id: 6
    target_pin_index: 1
  }
  pos {
    x: 27
    y: 69
  }
  pos {
    x: 36
    y: 69
  }
  pos {
    x: 36
    y: 65
  }
  pos {
    x: 45
    y: 65
  }
}
infos {
  cmd_id: 17
  element: VO
  edit_type: ADD
  vo {
    mod_id: 1
    task_id: 2
    fb_id: 6
    pin_index: 1
    ev_id: 5
    vo_id: 8
  }
}
infos {
  cmd_id: 18
  element: VI
  edit_type: ADD
  vi {
    mod_id: 1
    task_id: 2
    fb_id: 3
    pin_index: 1
    ev_id: 5
    vi_id: 9
  }
}
infos {
  cmd_id: 19
  element: PIN
  edit_type: SET
  pin {
    mod_id: 1
    task_id: 2
    fb_id: 3
    pin_index: 2
    pin_val {
      v {
        t: T_UINT32
        ui: 0
      }
      tm: 1683515046950625244
    }
  }
}
infos {
  cmd_id: 20
  element: FB
  edit_type: MV
  fb {
    mod_id: 1
    task_id: 2
    fb_id: 3
  }
  pos {
    x: 52
    y: 83
  }
}
infos {
  cmd_id: 21
  element: FB
  edit_type: ADD
  fb {
    mod_id: 1
    task_id: 2
    fb_id: 10
    flib_name: "Fsm"
    fc_name: "FSM"
  }
  pos {
    x: 94
    y: 90
  }
}
infos {
  cmd_id: 22
  element: LK
  edit_type: ADD
  lk {
    mod_id: 1
    task_id: 2
    lk_id: 11
    src_fb_id: 3
    src_pin_index: 1
    target_fb_id: 10
    target_pin_index: 1
  }
  pos {
    x: 71
    y: 90
  }
  pos {
    x: 82
    y: 90
  }
  pos {
    x: 82
    y: 97
  }
  pos {
    x: 94
    y: 97
  }
}
infos {
  cmd_id: 23
  element: EV
  edit_type: ADD
  ev {
    ev_id: 12
    ev_name: "FSM"
    ev_type: 2
    ev_desc: "Desc"
    init_val {
      v {
        t: T_INT32
        i: 0
      }
      tm: 1683515073209521553
    }
  }
}
infos {
  cmd_id: 24
  element: VI
  edit_type: ADD
  vi {
    mod_id: 1
    task_id: 2
    fb_id: 10
    pin_index: 3
    ev_id: 12
    vi_id: 13
  }
}
infos {
  cmd_id: 25
  element: PIN
  edit_type: SET
  pin {
    mod_id: 1
    task_id: 2
    fb_id: 10
    pin_index: 4
    pin_val {
      v {
        t: T_INT32
        i: 1
      }
      tm: 1683515078506047174
    }
  }
}
infos {
  cmd_id: 26
  element: PIN
  edit_type: SET
  pin {
    mod_id: 1
    task_id: 2
    fb_id: 10
    pin_index: 2
    pin_val {
      v {
        t: T_BOOL
        b: true
      }
      tm: 1683515081026246366
    }
  }
}
