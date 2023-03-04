infos {
  edit_type: SET
  proj {
    proj_name: "rotbot-engine-project"
    proj_uuid: "{a76b80d3-939f-4e61-864f-fc5033faf333}"
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
  element: EV
  edit_type: ADD
  ev {
    ev_id: 2
    ev_name: "CAM_1"
    ev_type: 9
    ev_desc: "Desc"
    init_val {
      v {
        t: T_STRING
        str: "front camera"
      }
      tm: 1677943322800674779
    }
  }
}
infos {
  cmd_id: 3
  element: MOD
  edit_type: ADD
  mod {
    mod_id: 3
    mod_name: "FOE"
  }
}
infos {
  cmd_id: 4
  element: TASK
  edit_type: ADD
  task {
    mod_id: 3
    task_id: 4
    task_name: "P1"
    interval: 1000
  }
}
infos {
  cmd_id: 5
  element: FB
  edit_type: ADD
  fb {
    mod_id: 3
    task_id: 4
    fb_id: 5
    flib_name: "Devices"
    fc_name: "SIM_READ"
  }
  pos {
    x: 43
    y: 28
  }
}
infos {
  cmd_id: 6
  element: FB
  edit_type: ADD
  fb {
    mod_id: 3
    task_id: 4
    fb_id: 6
    flib_name: "Converter"
    fc_name: "D2LL"
  }
  pos {
    x: 81
    y: 24
  }
}
infos {
  cmd_id: 7
  element: LK
  edit_type: ADD
  lk {
    mod_id: 3
    task_id: 4
    lk_id: 7
    src_fb_id: 5
    src_pin_index: 1
    target_fb_id: 6
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
  cmd_id: 8
  element: VI
  edit_type: ADD
  vi {
    mod_id: 3
    task_id: 4
    fb_id: 5
    pin_index: 1
    ev_id: 1
    vi_id: 8
  }
}
infos {
  cmd_id: 9
  element: TASK
  edit_type: ADD
  task {
    mod_id: 3
    task_id: 9
    task_name: "P2"
    interval: 500
  }
}
infos {
  cmd_id: 10
  element: FB
  edit_type: ADD
  fb {
    mod_id: 3
    task_id: 9
    fb_id: 10
    flib_name: "Devices"
    fc_name: "CAMERA"
  }
  pos {
    x: 49
    y: 59
  }
}
infos {
  cmd_id: 11
  element: VI
  edit_type: ADD
  vi {
    mod_id: 3
    task_id: 9
    fb_id: 10
    pin_index: 1
    ev_id: 2
    vi_id: 11
  }
}
