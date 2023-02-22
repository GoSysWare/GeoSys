infos {
  edit_type: SET
  proj {
    proj_name: "rotbot-engine-project"
    proj_uuid: "{350db513-fc75-43c6-b1ba-ad178ae4ff69}"
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
  element: MOD
  edit_type: ADD
  mod {
    mod_id: 2
    mod_name: "A2"
  }
}
infos {
  cmd_id: 3
  element: TASK
  edit_type: ADD
  task {
    mod_id: 1
    task_id: 3
    task_name: "P1"
    interval: 1000
  }
}
infos {
  cmd_id: 4
  element: TASK
  edit_type: ADD
  task {
    mod_id: 1
    task_id: 4
    task_name: "P2"
    interval: 1000
  }
}
infos {
  cmd_id: 5
  element: FB
  edit_type: ADD
  fb {
    mod_id: 1
    task_id: 3
    fb_id: 5
    flib_name: "Arithmetic"
    fc_name: "ADD_DOUBLE"
  }
  pos {
    x: 40
    y: 36
  }
}
infos {
  cmd_id: 6
  element: FB
  edit_type: ADD
  fb {
    mod_id: 1
    task_id: 3
    fb_id: 6
    flib_name: "Arithmetic"
    fc_name: "ADD_FLOAT"
  }
  pos {
    x: 91
    y: 71
  }
}
infos {
  cmd_id: 7
  element: FB
  edit_type: ADD
  fb {
    mod_id: 1
    task_id: 3
    fb_id: 7
    flib_name: "Arithmetic"
    fc_name: "ADD_FLOAT"
  }
  pos {
    x: 130
    y: 68
  }
}
infos {
  cmd_id: 11
  element: FB
  edit_type: MV
  fb {
    mod_id: 1
    task_id: 3
    fb_id: 5
  }
  pos {
    x: 22
    y: 26
  }
}
infos {
  cmd_id: 13
  element: FB
  edit_type: MV
  fb {
    mod_id: 1
    task_id: 3
    fb_id: 7
  }
  pos {
    x: 112
    y: 58
  }
}
infos {
  cmd_id: 26
  element: LK
  edit_type: ADD
  lk {
    mod_id: 1
    task_id: 3
    lk_id: 8
    src_fb_id: 6
    src_pin_index: 1
    target_fb_id: 7
    target_pin_index: 1
  }
  pos {
    x: 59
    y: 53
  }
  pos {
    x: 85
    y: 53
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
  cmd_id: 31
  element: FB
  edit_type: MV
  fb {
    mod_id: 1
    task_id: 3
    fb_id: 6
  }
  pos {
    x: 58
    y: 42
  }
}
infos {
  cmd_id: 32
  element: LK
  edit_type: MV
  lk {
    mod_id: 1
    task_id: 3
    lk_id: 8
  }
  pos {
    x: 73
    y: 49
  }
  pos {
    x: 85
    y: 49
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
