infos {
  edit_type: SET
  proj {
    proj_name: "rotbot-engine-project"
    proj_uuid: "{ca3746c8-a4bf-4a31-b6bc-4cb14a32b590}"
  }
}
infos {
  cmd_id: 1
  element: MOD
  edit_type: ADD
  mod {
    mod_id: 1
    mod_name: "A1"
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
    flib_name: "Arithmetic"
    fc_name: "ADD_DOUBLE"
  }
  pos {
    x: 13
    y: 47
  }
}
infos {
  cmd_id: 4
  element: FB
  edit_type: ADD
  fb {
    mod_id: 1
    task_id: 2
    fb_id: 4
    flib_name: "Arithmetic"
    fc_name: "ADD_FLOAT"
  }
  pos {
    x: 57
    y: 54
  }
}
infos {
  cmd_id: 5
  element: FB
  edit_type: ADD
  fb {
    mod_id: 1
    task_id: 2
    fb_id: 5
    flib_name: "Arithmetic"
    fc_name: "ADD_FLOAT"
  }
  pos {
    x: 112
    y: 58
  }
}
infos {
  cmd_id: 6
  element: LK
  edit_type: ADD
  lk {
    mod_id: 1
    task_id: 2
    lk_id: 6
    src_fb_id: 4
    src_pin_index: 1
    target_fb_id: 5
    target_pin_index: 1
  }
  pos {
    x: 72
    y: 61
  }
  pos {
    x: 85
    y: 61
  }
  pos {
    x: 85
    y: 65
  }
  pos {
    x: 112
    y: 65
  }
}
infos {
  cmd_id: 7
  element: TASK
  edit_type: ADD
  task {
    mod_id: 1
    task_id: 7
    task_name: "P2"
    interval: 1000
  }
}
infos {
  cmd_id: 8
  element: MOD
  edit_type: ADD
  mod {
    mod_id: 8
    mod_name: "A2"
  }
}
