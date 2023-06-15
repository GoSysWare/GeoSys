infos {
  cmd_id: 10
  edit_type: SET
  proj {
    proj_name: "rotbot-engine-project"
    proj_uuid: "{563a822d-99df-4998-add9-405c0ba60e41}"
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
    task_type: ASYNC
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
    flib_name: "Devices"
    fc_name: "CAMERA_INIT"
  }
  pos {
    x: 26
    y: 12
  }
}
infos {
  cmd_id: 4
  element: PIN
  edit_type: SET
  pin {
    mod_id: 1
    task_id: 2
    fb_id: 3
    pin_index: 1
    pin_val {
      t: T_STRING
      v {
        str: "SIM"
      }
      tm: 1686831352907420938
    }
  }
}
infos {
  cmd_id: 5
  element: PIN
  edit_type: SET
  pin {
    mod_id: 1
    task_id: 2
    fb_id: 3
    pin_index: 2
    pin_val {
      t: T_STRING
      v {
        str: "test"
      }
      tm: 1686831358147310026
    }
  }
}
infos {
  cmd_id: 6
  element: FB
  edit_type: ADD
  fb {
    mod_id: 1
    task_id: 2
    fb_id: 4
    flib_name: "Arithmetic"
    fc_name: "ADD_INT"
  }
  pos {
    x: 34
    y: 39
  }
}
infos {
  cmd_id: 7
  element: EV
  edit_type: ADD
  ev {
    ev_id: 5
    ev_name: "EV1"
    ev_type: 2
    ev_desc: "Desc"
    init_val {
      t: T_INT32
      v {
        i: 0
      }
      tm: 1686831379779933535
    }
  }
}
infos {
  cmd_id: 8
  element: VI
  edit_type: ADD
  vi {
    mod_id: 1
    task_id: 2
    fb_id: 4
    pin_index: 1
    ev_id: 5
    vi_id: 6
  }
}
infos {
  cmd_id: 9
  element: VO
  edit_type: ADD
  vo {
    mod_id: 1
    task_id: 2
    fb_id: 4
    pin_index: 1
    ev_id: 5
    vo_id: 7
  }
}
infos {
  cmd_id: 10
  element: PIN
  edit_type: SET
  pin {
    mod_id: 1
    task_id: 2
    fb_id: 4
    pin_index: 2
    pin_val {
      t: T_INT32
      v {
        i: 2
      }
      tm: 1686831388939709690
    }
  }
}
