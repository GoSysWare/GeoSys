infos {
  edit_type: SET
  proj {
    proj_name: "rotbot-engine-project"
    proj_uuid: "{b0c43f73-2ed0-452a-9104-59b8d15ba8a6}"
  }
}
infos {
  cmd_id: 1
  element: EV
  edit_type: ADD
  ev {
    ev_id: 1
    ev_name: "F_name_1"
    ev_type: 9
    ev_desc: "Desc"
    init_val {
      v {
        t: T_STRING
        str: "/home/shuimujie/Works/bamboo_ws/bin/debug/shape_predictor_5_face_landmarks.dat"
      }
      tm: 1678442501870500340
    }
  }
}
infos {
  cmd_id: 2
  element: MOD
  edit_type: ADD
  mod {
    mod_id: 2
    mod_name: "M1"
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
    flib_name: "System"
    fc_name: "FILE_OPEN_ONCE"
  }
  pos {
    x: 89
    y: 41
  }
}
infos {
  cmd_id: 5
  element: VI
  edit_type: ADD
  vi {
    mod_id: 2
    task_id: 3
    fb_id: 4
    pin_index: 1
    ev_id: 1
    vi_id: 5
  }
}
