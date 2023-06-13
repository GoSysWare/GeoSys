infos {
  cmd_id: 14
  edit_type: SET
  proj {
    proj_name: "rotbot-engine-project"
    proj_uuid: "{e1335591-5f02-44e2-aba2-858ef9b3eaf8}"
  }
}
infos {
  cmd_id: 1
  element: MOD
  edit_type: ADD
  mod {
    mod_id: 1
    mod_name: "m1"
  }
}
infos {
  cmd_id: 2
  element: TASK
  edit_type: ADD
  task {
    mod_id: 1
    task_id: 2
    task_name: "p1"
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
    flib_name: "Http"
    fc_name: "CURL_SEND"
  }
  pos {
    x: 25
    y: 13
  }
}
infos {
  cmd_id: 4
  element: FB
  edit_type: MV
  fb {
    mod_id: 1
    task_id: 2
    fb_id: 3
    fb_name: "https://c63a6f30-2fbc-4deb-bf6f-"
  }
  pos {
    x: 25
    y: 13
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
    pin_index: 1
    pin_val {
      t: T_STRING
      v {
        str: "http://127.0.0.1:5000/getname"
      }
      tm: 1686650797647883666
    }
  }
}
infos {
  cmd_id: 8
  element: FB
  edit_type: MV
  fb {
    mod_id: 1
    task_id: 2
    fb_id: 3
  }
  pos {
    x: 48
    y: 15
  }
}
infos {
  cmd_id: 9
  element: FB
  edit_type: ADD
  fb {
    mod_id: 1
    task_id: 2
    fb_id: 4
    flib_name: "Http"
    fc_name: "CURL_SEND"
  }
  pos {
    x: 23
    y: 42
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
    pin_index: 1
    pin_val {
      t: T_STRING
      v {
        str: "127.0.0.1:8899/login"
      }
      tm: 1686658112833193839
    }
  }
}
infos {
  cmd_id: 11
  element: PIN
  edit_type: SET
  pin {
    mod_id: 1
    task_id: 2
    fb_id: 4
    pin_index: 2
    pin_val {
      t: T_STRING
      v {
        str: "{\"account\":\"1001\",\"password\":\"123\"}"
      }
      tm: 1686658157617642561
    }
  }
}
infos {
  cmd_id: 12
  element: PIN
  edit_type: SET
  pin {
    mod_id: 1
    task_id: 2
    fb_id: 4
    pin_index: 3
    pin_val {
      t: T_STRING
      v {
        str: "post"
      }
      tm: 1686658162449461883
    }
  }
}
infos {
  cmd_id: 13
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
        str: "127.0.0.1:8899/users"
      }
      tm: 1686659556934919951
    }
  }
}
infos {
  cmd_id: 14
  element: PIN
  edit_type: SET
  pin {
    mod_id: 1
    task_id: 2
    fb_id: 4
    pin_index: 4
    pin_val {
      t: T_STRING
      v {
        str: "multipart/form-data"
      }
      tm: 1686659808641529288
    }
  }
}
