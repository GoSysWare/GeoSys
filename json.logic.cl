infos {
  cmd_id: 11
  edit_type: SET
  proj {
    proj_name: "rotbot-engine-project"
    proj_uuid: "{84894565-5a66-4434-902f-1b595a29c18b}"
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
    task_name: "P2"
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
    x: 15
    y: 10
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
    x: 15
    y: 10
  }
}
infos {
  cmd_id: 6
  element: FB
  edit_type: MV
  fb {
    mod_id: 1
    task_id: 2
    fb_id: 4
  }
  pos {
    x: 14
    y: 53
  }
}
infos {
  cmd_id: 7
  element: FB
  edit_type: ADD
  fb {
    mod_id: 1
    task_id: 2
    fb_id: 5
    flib_name: "Value"
    fc_name: "JSON_SERIAL"
  }
  pos {
    x: 15
    y: 10
  }
}
infos {
  cmd_id: 9
  element: FB
  edit_type: MV
  fb {
    mod_id: 1
    task_id: 2
    fb_id: 5
  }
  pos {
    x: 77
    y: 28
  }
}
infos {
  cmd_id: 10
  element: LK
  edit_type: ADD
  lk {
    mod_id: 1
    task_id: 2
    lk_id: 6
    src_fb_id: 3
    src_pin_index: 1
    target_fb_id: 5
    target_pin_index: 4
  }
  pos {
    x: 36
    y: 17
  }
  pos {
    x: 56
    y: 17
  }
  pos {
    x: 56
    y: 41
  }
  pos {
    x: 77
    y: 41
  }
}
infos {
  cmd_id: 11
  element: LK
  edit_type: ADD
  lk {
    mod_id: 1
    task_id: 2
    lk_id: 7
    src_fb_id: 4
    src_pin_index: 1
    target_fb_id: 5
    target_pin_index: 12
  }
  pos {
    x: 35
    y: 60
  }
  pos {
    x: 56
    y: 60
  }
  pos {
    x: 56
    y: 57
  }
  pos {
    x: 77
    y: 57
  }
}
