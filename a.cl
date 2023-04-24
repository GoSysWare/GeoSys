infos {
  cmd_id: 36
  edit_type: SET
  proj {
    proj_name: "rotbot-engine-project"
    proj_uuid: "{dd31b22c-9b74-43d2-a132-6d5ff06ace64}"
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
    task_name: "M2"
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
    flib_name: "Geometry"
    fc_name: "PATH_CREATE"
  }
  pos {
    x: 20
    y: 21
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
      v {
        t: T_UINT32
        ui: 5
      }
      tm: 1682307353925003873
    }
  }
}
infos {
  cmd_id: 5
  element: FB
  edit_type: ADD
  fb {
    mod_id: 1
    task_id: 2
    fb_id: 4
    flib_name: "Value"
    fc_name: "V_GET_ANY"
  }
  pos {
    x: 59
    y: 26
  }
}
infos {
  cmd_id: 6
  element: LK
  edit_type: ADD
  lk {
    mod_id: 1
    task_id: 2
    lk_id: 5
    src_fb_id: 3
    src_pin_index: 1
    target_fb_id: 4
    target_pin_index: 1
  }
  pos {
    x: 38
    y: 28
  }
  pos {
    x: 48
    y: 28
  }
  pos {
    x: 48
    y: 33
  }
  pos {
    x: 59
    y: 33
  }
}
infos {
  cmd_id: 9
  element: FB
  edit_type: MV
  fb {
    mod_id: 1
    task_id: 2
    fb_id: 4
  }
  pos {
    x: 59
    y: 25
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
    pin_index: 3
    pin_val {
      v {
        t: T_UINT32
        ui: 2
      }
      tm: 1682307402243611464
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
    pin_index: 2
    pin_val {
      v {
        t: T_STRING
        str: "poses"
      }
      tm: 1682307410962449796
    }
  }
}
infos {
  cmd_id: 13
  element: FB
  edit_type: ADD
  fb {
    mod_id: 1
    task_id: 2
    fb_id: 6
    flib_name: "Value"
    fc_name: "V_GET_ANY"
  }
  pos {
    x: 104
    y: 31
  }
}
infos {
  cmd_id: 14
  element: LK
  edit_type: ADD
  lk {
    mod_id: 1
    task_id: 2
    lk_id: 7
    src_fb_id: 4
    src_pin_index: 1
    target_fb_id: 6
    target_pin_index: 1
  }
  pos {
    x: 80
    y: 32
  }
  pos {
    x: 92
    y: 32
  }
  pos {
    x: 92
    y: 38
  }
  pos {
    x: 104
    y: 38
  }
}
infos {
  cmd_id: 15
  element: PIN
  edit_type: SET
  pin {
    mod_id: 1
    task_id: 2
    fb_id: 6
    pin_index: 2
    pin_val {
      v {
        t: T_STRING
        str: "position"
      }
      tm: 1682307444409353484
    }
  }
}
infos {
  cmd_id: 16
  element: FB
  edit_type: ADD
  fb {
    mod_id: 1
    task_id: 2
    fb_id: 8
    flib_name: "Value"
    fc_name: "V_GET_DOUBLE"
  }
  pos {
    x: 139
    y: 39
  }
}
infos {
  cmd_id: 17
  element: LK
  edit_type: ADD
  lk {
    mod_id: 1
    task_id: 2
    lk_id: 9
    src_fb_id: 6
    src_pin_index: 1
    target_fb_id: 8
    target_pin_index: 1
  }
  pos {
    x: 125
    y: 38
  }
  pos {
    x: 132
    y: 38
  }
  pos {
    x: 132
    y: 46
  }
  pos {
    x: 139
    y: 46
  }
}
infos {
  cmd_id: 18
  element: PIN
  edit_type: SET
  pin {
    mod_id: 1
    task_id: 2
    fb_id: 8
    pin_index: 2
    pin_val {
      v {
        t: T_STRING
        str: "x"
      }
      tm: 1682307466936131208
    }
  }
}
infos {
  cmd_id: 19
  element: PIN
  edit_type: SET
  pin {
    mod_id: 1
    task_id: 2
    fb_id: 4
    pin_index: 3
    pin_val {
      v {
        t: T_UINT32
        ui: 7
      }
      tm: 1682318485469164812
    }
  }
}
infos {
  cmd_id: 20
  element: FB
  edit_type: ADD
  fb {
    mod_id: 1
    task_id: 2
    fb_id: 10
    flib_name: "Value"
    fc_name: "V_GET_DOUBLE"
  }
  pos {
    x: 139
    y: 39
  }
}
infos {
  cmd_id: 22
  element: LK
  edit_type: ADD
  lk {
    mod_id: 1
    task_id: 2
    lk_id: 11
    src_fb_id: 4
    src_pin_index: 1
    target_fb_id: 10
    target_pin_index: 1
  }
  pos {
    x: 80
    y: 32
  }
  pos {
    x: 91
    y: 32
  }
  pos {
    x: 91
    y: 65
  }
  pos {
    x: 102
    y: 65
  }
}
infos {
  cmd_id: 25
  element: PIN
  edit_type: SET
  pin {
    mod_id: 1
    task_id: 2
    fb_id: 10
    pin_index: 2
    pin_val {
      v {
        t: T_STRING
        str: "position.x"
      }
      tm: 1682324643266737966
    }
  }
}
infos {
  cmd_id: 26
  element: FB
  edit_type: MV
  fb {
    mod_id: 1
    task_id: 2
    fb_id: 3
  }
  pos {
    x: 24
    y: 9
  }
}
infos {
  cmd_id: 27
  element: LK
  edit_type: MV
  lk {
    mod_id: 1
    task_id: 2
    lk_id: 5
  }
  pos {
    x: 42
    y: 16
  }
  pos {
    x: 42
    y: 32
  }
  pos {
    x: 59
    y: 32
  }
}
infos {
  cmd_id: 28
  element: FB
  edit_type: MV
  fb {
    mod_id: 1
    task_id: 2
    fb_id: 10
  }
  pos {
    x: 105
    y: 65
  }
}
infos {
  cmd_id: 29
  element: LK
  edit_type: MV
  lk {
    mod_id: 1
    task_id: 2
    lk_id: 11
  }
  pos {
    x: 80
    y: 32
  }
  pos {
    x: 91
    y: 32
  }
  pos {
    x: 91
    y: 72
  }
  pos {
    x: 105
    y: 72
  }
}
infos {
  cmd_id: 30
  element: FB
  edit_type: MV
  fb {
    mod_id: 1
    task_id: 2
    fb_id: 6
  }
  pos {
    x: 105
    y: 38
  }
}
infos {
  cmd_id: 31
  element: LK
  edit_type: MV
  lk {
    mod_id: 1
    task_id: 2
    lk_id: 7
  }
  pos {
    x: 80
    y: 32
  }
  pos {
    x: 92
    y: 32
  }
  pos {
    x: 92
    y: 45
  }
  pos {
    x: 105
    y: 45
  }
}
infos {
  cmd_id: 35
  element: FB
  edit_type: MV
  fb {
    mod_id: 1
    task_id: 2
    fb_id: 8
  }
  pos {
    x: 176
    y: 50
  }
}
infos {
  cmd_id: 36
  element: LK
  edit_type: MV
  lk {
    mod_id: 1
    task_id: 2
    lk_id: 9
  }
  pos {
    x: 126
    y: 45
  }
  pos {
    x: 132
    y: 45
  }
  pos {
    x: 132
    y: 57
  }
  pos {
    x: 176
    y: 57
  }
}
