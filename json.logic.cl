infos {
  cmd_id: 11
  edit_type: SET
  proj {
    proj_name: "rotbot-engine-project"
    proj_uuid: "{de9fb033-7875-45a0-a51a-fa423d736ff0}"
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
    fc_name: "JSON_SERIAL"
  }
  pos {
    x: 13
    y: 11
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
    flib_name: "Value"
    fc_name: "JSON_SERIAL"
  }
  pos {
    x: 13
    y: 45
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
    flib_name: "Value"
    fc_name: "JSON_PATCH"
  }
  pos {
    x: 55
    y: 34
  }
}
infos {
  cmd_id: 6
  element: FB
  edit_type: ADD
  fb {
    mod_id: 1
    task_id: 2
    fb_id: 6
    flib_name: "Value"
    fc_name: "JSON_SERIAL"
  }
  pos {
    x: 13
    y: 79
  }
}
infos {
  cmd_id: 7
  element: FB
  edit_type: ADD
  fb {
    mod_id: 1
    task_id: 2
    fb_id: 7
    flib_name: "Value"
    fc_name: "JSON_PATCH"
  }
  pos {
    x: 93
    y: 56
  }
}
infos {
  cmd_id: 8
  element: LK
  edit_type: ADD
  lk {
    mod_id: 1
    task_id: 2
    lk_id: 8
    src_fb_id: 3
    src_pin_index: 1
    target_fb_id: 5
    target_pin_index: 3
  }
  pos {
    x: 34
    y: 18
  }
  pos {
    x: 44
    y: 18
  }
  pos {
    x: 44
    y: 45
  }
  pos {
    x: 55
    y: 45
  }
}
infos {
  cmd_id: 9
  element: LK
  edit_type: ADD
  lk {
    mod_id: 1
    task_id: 2
    lk_id: 9
    src_fb_id: 4
    src_pin_index: 1
    target_fb_id: 5
    target_pin_index: 4
  }
  pos {
    x: 34
    y: 52
  }
  pos {
    x: 44
    y: 52
  }
  pos {
    x: 44
    y: 47
  }
  pos {
    x: 55
    y: 47
  }
}
infos {
  cmd_id: 10
  element: LK
  edit_type: ADD
  lk {
    mod_id: 1
    task_id: 2
    lk_id: 10
    src_fb_id: 6
    src_pin_index: 1
    target_fb_id: 7
    target_pin_index: 4
  }
  pos {
    x: 34
    y: 86
  }
  pos {
    x: 63
    y: 86
  }
  pos {
    x: 63
    y: 69
  }
  pos {
    x: 93
    y: 69
  }
}
infos {
  cmd_id: 11
  element: LK
  edit_type: ADD
  lk {
    mod_id: 1
    task_id: 2
    lk_id: 11
    src_fb_id: 5
    src_pin_index: 1
    target_fb_id: 7
    target_pin_index: 3
  }
  pos {
    x: 76
    y: 41
  }
  pos {
    x: 84
    y: 41
  }
  pos {
    x: 84
    y: 67
  }
  pos {
    x: 93
    y: 67
  }
}
