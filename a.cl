infos {
  edit_type: SET
  proj {
    proj_name: "rotbot-engine-project"
    proj_uuid: "{a8cd8cfe-d7f1-4385-a4da-7525a961b46e}"
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
  element: TASK
  edit_type: ADD
  task {
    task_type: ASYNC
    mod_id: 1
    task_id: 3
    task_name: "P2"
    interval: 1000
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
    flib_name: "System"
    fc_name: "SYSSTATE"
  }
  pos {
    x: 37
    y: 20
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
    flib_name: "Devices"
    fc_name: "SIM_READ"
  }
  pos {
    x: 34
    y: 62
  }
}
infos {
  cmd_id: 6
  element: PIN
  edit_type: SET
  pin {
    mod_id: 1
    task_id: 2
    fb_id: 5
    pin_index: 1
    pin_val {
      v {
        t: T_STRING
        str: "SIM"
      }
      tm: 1681556506738302931
    }
  }
}
infos {
  cmd_id: 7
  element: PIN
  edit_type: SET
  pin {
    mod_id: 1
    task_id: 2
    fb_id: 5
    pin_index: 5
    pin_val {
      v {
        t: T_STRING
        str: "$SECOND"
      }
      tm: 1681556519671574977
    }
  }
}
infos {
  cmd_id: 8
  element: FB
  edit_type: ADD
  fb {
    mod_id: 1
    task_id: 2
    fb_id: 6
    flib_name: "Comparison"
    fc_name: "EQ_DOUBLE"
  }
  pos {
    x: 83
    y: 76
  }
}
infos {
  cmd_id: 9
  element: LK
  edit_type: ADD
  lk {
    mod_id: 1
    task_id: 2
    lk_id: 7
    src_fb_id: 5
    src_pin_index: 4
    target_fb_id: 6
    target_pin_index: 1
  }
  pos {
    x: 54
    y: 75
  }
  pos {
    x: 68
    y: 75
  }
  pos {
    x: 68
    y: 83
  }
  pos {
    x: 83
    y: 83
  }
}
infos {
  cmd_id: 10
  element: LK
  edit_type: RM
  lk {
    mod_id: 1
    task_id: 2
    lk_id: 7
  }
}
infos {
  cmd_id: 11
  element: FB
  edit_type: RM
  fb {
    mod_id: 1
    task_id: 2
    fb_id: 6
  }
}
infos {
  cmd_id: 12
  element: FB
  edit_type: ADD
  fb {
    mod_id: 1
    task_id: 2
    fb_id: 8
    flib_name: "Comparison"
    fc_name: "GE_DOUBLE"
  }
  pos {
    x: 71
    y: 73
  }
}
infos {
  cmd_id: 13
  element: LK
  edit_type: ADD
  lk {
    mod_id: 1
    task_id: 2
    lk_id: 9
    src_fb_id: 5
    src_pin_index: 4
    target_fb_id: 8
    target_pin_index: 1
  }
  pos {
    x: 54
    y: 75
  }
  pos {
    x: 62
    y: 75
  }
  pos {
    x: 62
    y: 80
  }
  pos {
    x: 71
    y: 80
  }
}
infos {
  cmd_id: 14
  element: PIN
  edit_type: SET
  pin {
    mod_id: 1
    task_id: 2
    fb_id: 8
    pin_index: 2
    pin_val {
      v {
        t: T_FLOAT64
        d: 30
      }
      tm: 1681556594638311300
    }
  }
}
infos {
  cmd_id: 15
  element: FB
  edit_type: ADD
  fb {
    mod_id: 1
    task_id: 2
    fb_id: 10
    flib_name: "Trigger"
    fc_name: "U_TRIG"
  }
  pos {
    x: 118
    y: 75
  }
}
infos {
  cmd_id: 16
  element: LK
  edit_type: ADD
  lk {
    mod_id: 1
    task_id: 2
    lk_id: 11
    src_fb_id: 8
    src_pin_index: 1
    target_fb_id: 10
    target_pin_index: 1
  }
  pos {
    x: 90
    y: 80
  }
  pos {
    x: 104
    y: 80
  }
  pos {
    x: 104
    y: 82
  }
  pos {
    x: 118
    y: 82
  }
}
infos {
  cmd_id: 17
  element: LK
  edit_type: RM
  lk {
    mod_id: 1
    task_id: 2
    lk_id: 11
  }
}
infos {
  cmd_id: 18
  element: FB
  edit_type: RM
  fb {
    mod_id: 1
    task_id: 2
    fb_id: 10
  }
}
infos {
  cmd_id: 19
  element: FB
  edit_type: ADD
  fb {
    mod_id: 1
    task_id: 2
    fb_id: 12
    flib_name: "Task"
    fc_name: "EVENT"
  }
  pos {
    x: 113
    y: 75
  }
}
infos {
  cmd_id: 20
  element: LK
  edit_type: ADD
  lk {
    mod_id: 1
    task_id: 2
    lk_id: 13
    src_fb_id: 8
    src_pin_index: 1
    target_fb_id: 12
    target_pin_index: 1
  }
  pos {
    x: 90
    y: 80
  }
  pos {
    x: 101
    y: 80
  }
  pos {
    x: 101
    y: 82
  }
  pos {
    x: 113
    y: 82
  }
}
infos {
  cmd_id: 21
  element: FB
  edit_type: ADD
  fb {
    mod_id: 1
    task_id: 2
    fb_id: 14
    flib_name: "Task"
    fc_name: "TASK"
  }
  pos {
    x: 154
    y: 84
  }
}
infos {
  cmd_id: 22
  element: LK
  edit_type: ADD
  lk {
    mod_id: 1
    task_id: 2
    lk_id: 15
    src_fb_id: 12
    src_pin_index: 1
    target_fb_id: 14
    target_pin_index: 1
  }
  pos {
    x: 135
    y: 82
  }
  pos {
    x: 144
    y: 82
  }
  pos {
    x: 144
    y: 91
  }
  pos {
    x: 154
    y: 91
  }
}
infos {
  cmd_id: 23
  element: PIN
  edit_type: SET
  pin {
    mod_id: 1
    task_id: 2
    fb_id: 14
    pin_index: 2
    pin_val {
      v {
        t: T_STRING
        str: "M1"
      }
      tm: 1681556646089430862
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
    fb_id: 14
    pin_index: 3
    pin_val {
      v {
        t: T_STRING
        str: "P2"
      }
      tm: 1681556651923032746
    }
  }
}
infos {
  cmd_id: 25
  element: PIN
  edit_type: SET
  pin {
    mod_id: 1
    task_id: 2
    fb_id: 14
    pin_index: 4
    pin_val {
      v {
        t: T_TIME
        tm: 1000
      }
      tm: 1681556659439964059
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
    fb_id: 14
    pin_index: 5
    pin_val {
      v {
        t: T_BOOL
        b: true
      }
      tm: 1681556663889214388
    }
  }
}
infos {
  cmd_id: 27
  element: FB
  edit_type: ADD
  fb {
    mod_id: 1
    task_id: 3
    fb_id: 16
    flib_name: "Task"
    fc_name: "SLEEP"
  }
  pos {
    x: 79
    y: 62
  }
}
infos {
  cmd_id: 28
  element: PIN
  edit_type: SET
  pin {
    mod_id: 1
    task_id: 3
    fb_id: 16
    pin_index: 1
    pin_val {
      v {
        t: T_BOOL
        b: true
      }
      tm: 1681556678924318404
    }
  }
}
infos {
  cmd_id: 29
  element: PIN
  edit_type: SET
  pin {
    mod_id: 1
    task_id: 3
    fb_id: 16
    pin_index: 2
    pin_val {
      v {
        t: T_TIME
        tm: 5000
      }
      tm: 1681556684223171689
    }
  }
}
infos {
  cmd_id: 30
  element: FB
  edit_type: ADD
  fb {
    mod_id: 1
    task_id: 3
    fb_id: 17
    flib_name: "System"
    fc_name: "SYSSTATE"
  }
  pos {
    x: 54
    y: 41
  }
}
infos {
  cmd_id: 31
  element: FB
  edit_type: MV
  fb {
    mod_id: 1
    task_id: 3
    fb_id: 17
  }
  pos {
    x: 46
    y: 29
  }
}
