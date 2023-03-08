infos {
  edit_type: SET
  proj {
    proj_name: "rotbot-engine-project"
    proj_uuid: "{fa62efa1-4724-4d08-8433-feb45eb6eeb0}"
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
  element: EV
  edit_type: ADD
  ev {
    ev_id: 3
    ev_name: "IMG1"
    ev_type: 2
    ev_desc: "Desc"
    init_val {
      v {
        t: T_IMAGE
        img: "0"
      }
      tm: 1678193344837129344
    }
  }
}
infos {
  cmd_id: 4
  element: MOD
  edit_type: ADD
  mod {
    mod_id: 4
    mod_name: "FOE"
  }
}
infos {
  cmd_id: 5
  element: TASK
  edit_type: ADD
  task {
    mod_id: 4
    task_id: 5
    task_name: "P1"
    interval: 1000
  }
}
infos {
  cmd_id: 6
  element: FB
  edit_type: ADD
  fb {
    mod_id: 4
    task_id: 5
    fb_id: 6
    flib_name: "Devices"
    fc_name: "SIM_READ"
  }
  pos {
    x: 43
    y: 28
  }
}
infos {
  cmd_id: 7
  element: FB
  edit_type: ADD
  fb {
    mod_id: 4
    task_id: 5
    fb_id: 7
    flib_name: "Converter"
    fc_name: "D2LL"
  }
  pos {
    x: 81
    y: 24
  }
}
infos {
  cmd_id: 8
  element: LK
  edit_type: ADD
  lk {
    mod_id: 4
    task_id: 5
    lk_id: 8
    src_fb_id: 6
    src_pin_index: 1
    target_fb_id: 7
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
  cmd_id: 9
  element: VI
  edit_type: ADD
  vi {
    mod_id: 4
    task_id: 5
    fb_id: 6
    pin_index: 1
    ev_id: 1
    vi_id: 9
  }
}
infos {
  cmd_id: 10
  element: TASK
  edit_type: ADD
  task {
    mod_id: 4
    task_id: 10
    task_name: "P2"
    interval: 500
  }
}
infos {
  cmd_id: 11
  element: FB
  edit_type: ADD
  fb {
    mod_id: 4
    task_id: 10
    fb_id: 11
    flib_name: "Devices"
    fc_name: "CAMERA"
  }
  pos {
    x: 49
    y: 59
  }
}
infos {
  cmd_id: 12
  element: VI
  edit_type: ADD
  vi {
    mod_id: 4
    task_id: 10
    fb_id: 11
    pin_index: 1
    ev_id: 2
    vi_id: 12
  }
}
infos {
  cmd_id: 13
  element: VO
  edit_type: ADD
  vo {
    mod_id: 4
    task_id: 10
    fb_id: 11
    pin_index: 1
    ev_id: 3
    vo_id: 13
  }
}
