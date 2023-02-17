infos {
  edit_type: SET
  proj {
    proj_name: "rotbot-engine-project"
    proj_uuid: "{abffe721-3e85-4ae6-bd34-4d35c3f898ef}"
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
    task_name: "TM1"
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
    flib_name: "Timer"
    fc_name: "TON"
  }
  pos {
    x: 56
    y: 52
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
      v {
        t: T_BOOL
        b: true
      }
      tm: 1676621915903868042
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
      v {
        t: T_TIME
        tm: 10000
      }
      tm: 1676621924080423631
    }
  }
}
