infos {
  edit_type: SET
  proj {
    proj_name: "rotbot-engine-project"
    proj_uuid: "{d4bf6554-e067-4b10-8c62-b465aaee1639}"
  }
}
infos {
  cmd_id: 1
  element: EV
  edit_type: ADD
  ev {
    ev_id: 1
    ev_name: "EV"
    ev_type: 9
    ev_desc: "Desc"
    init_val {
      v {
        t: T_STRING
        str: "SIM"
      }
      tm: 1677657673435531409
    }
  }
}
infos {
  cmd_id: 2
  element: MOD
  edit_type: ADD
  mod {
    mod_id: 2
    mod_name: "FOE"
  }
}
infos {
  cmd_id: 3
  element: TASK
  edit_type: ADD
  task {
    mod_id: 2
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
    mod_id: 2
    task_id: 3
    fb_id: 4
    flib_name: "Devices"
    fc_name: "SIM_READ"
  }
  pos {
    x: 43
    y: 28
  }
}
infos {
  cmd_id: 5
  element: FB
  edit_type: ADD
  fb {
    mod_id: 2
    task_id: 3
    fb_id: 5
    flib_name: "Converter"
    fc_name: "D2LL"
  }
  pos {
    x: 81
    y: 24
  }
}
infos {
  cmd_id: 6
  element: LK
  edit_type: ADD
  lk {
    mod_id: 2
    task_id: 3
    lk_id: 6
    src_fb_id: 4
    src_pin_index: 1
    target_fb_id: 5
    target_pin_index: 1
  }
  pos {
    x: 59
    y: 35
  }
  pos {
    x: 70
    y: 35
  }
  pos {
    x: 70
    y: 31
  }
  pos {
    x: 81
    y: 31
  }
}
infos {
  cmd_id: 7
  element: VI
  edit_type: ADD
  vi {
    mod_id: 2
    task_id: 3
    fb_id: 4
    pin_index: 1
    ev_id: 1
    vi_id: 7
  }
}
infos {
  cmd_id: 8
  element: TASK
  edit_type: ADD
  task {
    mod_id: 2
    task_id: 8
    task_name: "P2"
    interval: 2000
  }
}
