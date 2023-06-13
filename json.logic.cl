infos {
  cmd_id: 8
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
        str: "https://c63a6f30-2fbc-4deb-bf6f-078236fbec11.mock.pstmn.io/getname"
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
