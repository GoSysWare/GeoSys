infos {
  cmd_id: 8
  edit_type: SET
  proj {
    proj_name: "rotbot-engine-project"
    proj_uuid: "{e8061426-cbb6-4596-bd11-55eeace1ce0f}"
  }
}
infos {
  cmd_id: 1
  element: MOD
  edit_type: ADD
  mod {
    mod_id: 1
    mod_name: "F1"
  }
}
infos {
  cmd_id: 2
  element: TASK
  edit_type: ADD
  task {
    mod_id: 1
    task_id: 2
    task_name: "B1"
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
    fc_name: "ADD_INT"
  }
  pos {
    x: 29
    y: 22
  }
}
infos {
  cmd_id: 6
  element: FB
  edit_type: MV
  fb {
    mod_id: 1
    task_id: 2
    fb_id: 3
  }
  pos {
    x: 33
    y: 9
  }
}
infos {
  cmd_id: 7
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
    x: 49
    y: 39
  }
}
infos {
  cmd_id: 8
  element: FB
  edit_type: RM
  fb {
    mod_id: 1
    task_id: 2
    fb_id: 3
  }
}
