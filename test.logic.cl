infos {
  cmd_id: 25
  edit_type: SET
  proj {
    proj_name: "rotbot-engine-project"
    proj_uuid: "{15eb6374-ceea-4160-ac6f-a8ebffdc004f}"
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
    flib_name: "System"
    fc_name: "SYS_STATE"
  }
  pos {
    x: 11
    y: 13
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
    flib_name: "Devices"
    fc_name: "SIM_READ"
  }
  pos {
    x: 19
    y: 51
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
    flib_name: "Comparison"
    fc_name: "GE_DOUBLE"
  }
  pos {
    x: 83
    y: 44
  }
}
infos {
  cmd_id: 6
  element: FB
  edit_type: ADD
  fb {
    mod_id: 1
    task_id: 2
    fb_id: 6
    flib_name: "Comparison"
    fc_name: "GE_DOUBLE"
  }
  pos {
    x: 71
    y: 88
  }
}
infos {
  cmd_id: 7
  element: FB
  edit_type: ADD
  fb {
    mod_id: 1
    task_id: 2
    fb_id: 7
    flib_name: "Task"
    fc_name: "TASK"
  }
  pos {
    x: 134
    y: 66
  }
}
infos {
  cmd_id: 8
  element: FB
  edit_type: ADD
  fb {
    mod_id: 1
    task_id: 2
    fb_id: 8
    flib_name: "Task"
    fc_name: "EVENT"
  }
  pos {
    x: 107
    y: 97
  }
}
infos {
  cmd_id: 9
  element: LK
  edit_type: ADD
  lk {
    mod_id: 1
    task_id: 2
    lk_id: 9
    src_fb_id: 4
    src_pin_index: 6
    target_fb_id: 5
    target_pin_index: 1
  }
  pos {
    x: 39
    y: 68
  }
  pos {
    x: 49
    y: 68
  }
  pos {
    x: 49
    y: 51
  }
  pos {
    x: 83
    y: 51
  }
}
infos {
  cmd_id: 10
  element: LK
  edit_type: ADD
  lk {
    mod_id: 1
    task_id: 2
    lk_id: 10
    src_fb_id: 4
    src_pin_index: 7
    target_fb_id: 6
    target_pin_index: 1
  }
  pos {
    x: 39
    y: 70
  }
  pos {
    x: 55
    y: 70
  }
  pos {
    x: 55
    y: 95
  }
  pos {
    x: 71
    y: 95
  }
}
infos {
  cmd_id: 11
  element: LK
  edit_type: ADD
  lk {
    mod_id: 1
    task_id: 2
    lk_id: 11
    src_fb_id: 6
    src_pin_index: 1
    target_fb_id: 8
    target_pin_index: 1
  }
  pos {
    x: 90
    y: 95
  }
  pos {
    x: 98
    y: 95
  }
  pos {
    x: 98
    y: 104
  }
  pos {
    x: 107
    y: 104
  }
}
infos {
  cmd_id: 12
  element: LK
  edit_type: ADD
  lk {
    mod_id: 1
    task_id: 2
    lk_id: 12
    src_fb_id: 8
    src_pin_index: 1
    target_fb_id: 7
    target_pin_index: 1
  }
  pos {
    x: 129
    y: 104
  }
  pos {
    x: 131
    y: 104
  }
  pos {
    x: 131
    y: 73
  }
  pos {
    x: 134
    y: 73
  }
}
infos {
  cmd_id: 13
  element: TASK
  edit_type: ADD
  task {
    task_type: ASYNC
    mod_id: 1
    task_id: 13
    task_name: "P2"
    interval: 1000
  }
}
infos {
  cmd_id: 14
  element: FB
  edit_type: ADD
  fb {
    mod_id: 1
    task_id: 13
    fb_id: 14
    flib_name: "System"
    fc_name: "SYS_STATE"
  }
  pos {
    x: 14
    y: 18
  }
}
infos {
  cmd_id: 15
  element: FB
  edit_type: ADD
  fb {
    mod_id: 1
    task_id: 13
    fb_id: 15
    flib_name: "Task"
    fc_name: "SLEEP"
  }
  pos {
    x: 40
    y: 58
  }
}
infos {
  cmd_id: 16
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
      tm: 1681995203281388421
    }
  }
}
infos {
  cmd_id: 17
  element: PIN
  edit_type: SET
  pin {
    mod_id: 1
    task_id: 2
    fb_id: 4
    pin_index: 7
    pin_val {
      v {
        t: T_STRING
        str: "$SECOND"
      }
      tm: 1681995216498767836
    }
  }
}
infos {
  cmd_id: 18
  element: PIN
  edit_type: SET
  pin {
    mod_id: 1
    task_id: 2
    fb_id: 4
    pin_index: 8
    pin_val {
      v {
        t: T_STRING
        str: "RANDOM(0,7)"
      }
      tm: 1681995309568330426
    }
  }
}
infos {
  cmd_id: 19
  element: PIN
  edit_type: SET
  pin {
    mod_id: 1
    task_id: 2
    fb_id: 5
    pin_index: 2
    pin_val {
      v {
        t: T_FLOAT64
        d: 30
      }
      tm: 1681995320884760138
    }
  }
}
infos {
  cmd_id: 20
  element: PIN
  edit_type: SET
  pin {
    mod_id: 1
    task_id: 2
    fb_id: 6
    pin_index: 2
    pin_val {
      v {
        t: T_FLOAT64
        d: 3.5
      }
      tm: 1681995340685093424
    }
  }
}
infos {
  cmd_id: 21
  element: PIN
  edit_type: SET
  pin {
    mod_id: 1
    task_id: 2
    fb_id: 7
    pin_index: 2
    pin_val {
      v {
        t: T_STRING
        str: "M1"
      }
      tm: 1681995381685609102
    }
  }
}
infos {
  cmd_id: 22
  element: PIN
  edit_type: SET
  pin {
    mod_id: 1
    task_id: 2
    fb_id: 7
    pin_index: 3
    pin_val {
      v {
        t: T_STRING
        str: "P2"
      }
      tm: 1681995386469584506
    }
  }
}
infos {
  cmd_id: 23
  element: PIN
  edit_type: SET
  pin {
    mod_id: 1
    task_id: 2
    fb_id: 7
    pin_index: 4
    pin_val {
      v {
        t: T_TIME
        tm: 500
      }
      tm: 1681995396753554950
    }
  }
}
infos {
  cmd_id: 24
  element: PIN
  edit_type: SET
  pin {
    mod_id: 1
    task_id: 2
    fb_id: 7
    pin_index: 5
    pin_val {
      v {
        t: T_BOOL
        b: true
      }
      tm: 1681995401136515785
    }
  }
}
infos {
  cmd_id: 25
  element: PIN
  edit_type: SET
  pin {
    mod_id: 1
    task_id: 13
    fb_id: 15
    pin_index: 2
    pin_val {
      v {
        t: T_TIME
        tm: 400
      }
      tm: 1681995441254157122
    }
  }
}
