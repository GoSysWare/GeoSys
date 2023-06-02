infos {
  cmd_id: 10
  edit_type: SET
  proj {
    proj_name: "rotbot-engine-project"
    proj_uuid: "{7441906e-63e4-4055-b454-cc9d7561b041}"
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
    flib_name: "Value"
    fc_name: "JSON_SERIAL_OBJ"
  }
  pos {
    x: 19
    y: 9
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
    pin_index: 2
    pin_val {
      t: T_STRING
      v {
        str: "str1"
      }
      tm: 1685675686329280803
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
    pin_index: 3
    pin_val {
      t: T_STRING
      v {
        str: "val1"
      }
      tm: 1685675692185432169
    }
  }
}
infos {
  cmd_id: 6
  element: PIN
  edit_type: SET
  pin {
    mod_id: 1
    task_id: 2
    fb_id: 3
    pin_index: 7
    pin_val {
      t: T_STRING
      v {
        str: "str3"
      }
      tm: 1685675699576796375
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
    fb_id: 3
    pin_index: 7
    pin_val {
      t: T_STRING
      v {
        str: "val3"
      }
      tm: 1685675709008195398
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
    fb_id: 3
    pin_index: 6
    pin_val {
      t: T_STRING
      v {
        str: "str3"
      }
      tm: 1685675714544041862
    }
  }
}
infos {
  cmd_id: 9
  element: EV
  edit_type: ADD
  ev {
    ev_id: 4
    ev_name: "Json_str_1"
    ev_type: 9
    ev_desc: "Desc"
    init_val {
      t: T_STRING
      v {
        str: ""
      }
      tm: 1685675897649431433
    }
  }
}
infos {
  cmd_id: 10
  element: VO
  edit_type: ADD
  vo {
    mod_id: 1
    task_id: 2
    fb_id: 3
    pin_index: 1
    ev_id: 4
    vo_id: 5
  }
}
