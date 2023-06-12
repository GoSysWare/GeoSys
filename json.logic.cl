infos {
  cmd_id: 5
  edit_type: SET
  proj {
    proj_name: "rotbot-engine-project"
    proj_uuid: "{d64fbb74-ed39-4328-aff9-eeac1380e82a}"
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
    flib_name: "Http"
    fc_name: "CURL_SEND"
  }
  pos {
    x: 29
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
        str: "https://c63a6f30-2fbc-4deb-bf6f-078236fbec11.mock.pstmn.io/getname"
      }
      tm: 1686573925468933857
    }
  }
}
infos {
  cmd_id: 5
  element: FB
  edit_type: MV
  fb {
    mod_id: 1
    task_id: 2
    fb_id: 3
  }
  pos {
    x: 40
    y: 12
  }
}
