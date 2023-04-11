infos {
  edit_type: SET
  proj {
    proj_name: "rotbot-engine-project"
    proj_uuid: "{a3463631-c8b6-4891-9777-b1ebd6387889}"
  }
}
infos {
  cmd_id: 1
  element: MOD
  edit_type: ADD
  mod {
    mod_id: 1
    mod_name: "PID"
  }
}
infos {
  cmd_id: 2
  element: TASK
  edit_type: ADD
  task {
    mod_id: 1
    task_id: 2
    task_name: "PID"
    interval: 50
  }
}
infos {
  cmd_id: 3
  element: TASK
  edit_type: RM
  task {
    mod_id: 1
    task_id: 2
  }
}
infos {
  cmd_id: 4
  element: TASK
  edit_type: ADD
  task {
    mod_id: 1
    task_id: 3
    task_name: "P1"
    interval: 50
  }
}
infos {
  cmd_id: 5
  element: FB
  edit_type: ADD
  fb {
    mod_id: 1
    task_id: 3
    fb_id: 4
    flib_name: "System"
    fc_name: "SYSSTATE"
  }
  pos {
    x: 43
    y: 48
  }
}
infos {
  cmd_id: 6
  element: FB
  edit_type: ADD
  fb {
    mod_id: 1
    task_id: 3
    fb_id: 5
    flib_name: "Control"
    fc_name: "PID"
  }
  pos {
    x: 126
    y: 88
  }
}
infos {
  cmd_id: 7
  element: PIN
  edit_type: SET
  pin {
    mod_id: 1
    task_id: 3
    fb_id: 5
    pin_index: 1
    pin_val {
      v {
        t: T_BOOL
        b: false
      }
      tm: 1681202086744543929
    }
  }
}
infos {
  cmd_id: 8
  element: PIN
  edit_type: SET
  pin {
    mod_id: 1
    task_id: 3
    fb_id: 5
    pin_index: 2
    pin_val {
      v {
        t: T_BOOL
        b: false
      }
      tm: 1681202090327696363
    }
  }
}
infos {
  cmd_id: 9
  element: PIN
  edit_type: SET
  pin {
    mod_id: 1
    task_id: 3
    fb_id: 5
    pin_index: 3
    pin_val {
      v {
        t: T_FLOAT64
        d: 6
      }
      tm: 1681202104794116681
    }
  }
}
infos {
  cmd_id: 10
  element: FB
  edit_type: ADD
  fb {
    mod_id: 1
    task_id: 3
    fb_id: 6
    flib_name: "Devices"
    fc_name: "SIM_READ"
  }
  pos {
    x: 63
    y: 106
  }
}
infos {
  cmd_id: 11
  element: PIN
  edit_type: SET
  pin {
    mod_id: 1
    task_id: 3
    fb_id: 6
    pin_index: 1
    pin_val {
      v {
        t: T_STRING
        str: "RANDOM(8)"
      }
      tm: 1681202135043658264
    }
  }
}
infos {
  cmd_id: 12
  element: PIN
  edit_type: SET
  pin {
    mod_id: 1
    task_id: 3
    fb_id: 6
    pin_index: 1
    pin_val {
      v {
        t: T_STRING
        str: "SIM"
      }
      tm: 1681202148399319438
    }
  }
}
infos {
  cmd_id: 13
  element: PIN
  edit_type: SET
  pin {
    mod_id: 1
    task_id: 3
    fb_id: 6
    pin_index: 2
    pin_val {
      v {
        t: T_STRING
        str: "RANDOM(8)"
      }
      tm: 1681202158626522287
    }
  }
}
infos {
  cmd_id: 14
  element: LK
  edit_type: ADD
  lk {
    mod_id: 1
    task_id: 3
    lk_id: 7
    src_fb_id: 6
    src_pin_index: 2
    target_fb_id: 5
    target_pin_index: 3
  }
  pos {
    x: 79
    y: 115
  }
  pos {
    x: 102
    y: 115
  }
  pos {
    x: 102
    y: 99
  }
  pos {
    x: 126
    y: 99
  }
}
infos {
  cmd_id: 15
  element: LK
  edit_type: RM
  lk {
    mod_id: 1
    task_id: 3
    lk_id: 7
  }
}
infos {
  cmd_id: 16
  element: FB
  edit_type: MV
  fb {
    mod_id: 1
    task_id: 3
    fb_id: 6
  }
  pos {
    x: 64
    y: 106
  }
}
infos {
  cmd_id: 17
  element: LK
  edit_type: ADD
  lk {
    mod_id: 1
    task_id: 3
    lk_id: 8
    src_fb_id: 6
    src_pin_index: 1
    target_fb_id: 5
    target_pin_index: 4
  }
  pos {
    x: 80
    y: 113
  }
  pos {
    x: 103
    y: 113
  }
  pos {
    x: 103
    y: 101
  }
  pos {
    x: 126
    y: 101
  }
}
infos {
  cmd_id: 18
  element: PIN
  edit_type: SET
  pin {
    mod_id: 1
    task_id: 3
    fb_id: 5
    pin_index: 5
    pin_val {
      v {
        t: T_FLOAT64
        d: 0.30000001192092896
      }
      tm: 1681202261692160213
    }
  }
}
infos {
  cmd_id: 19
  element: PIN
  edit_type: SET
  pin {
    mod_id: 1
    task_id: 3
    fb_id: 5
    pin_index: 6
    pin_val {
      v {
        t: T_BOOL
        b: true
      }
      tm: 1681202266942028849
    }
  }
}
infos {
  cmd_id: 20
  element: PIN
  edit_type: SET
  pin {
    mod_id: 1
    task_id: 3
    fb_id: 5
    pin_index: 7
    pin_val {
      v {
        t: T_BOOL
        b: true
      }
      tm: 1681202270416078058
    }
  }
}
infos {
  cmd_id: 21
  element: PIN
  edit_type: SET
  pin {
    mod_id: 1
    task_id: 3
    fb_id: 5
    pin_index: 8
    pin_val {
      v {
        t: T_BOOL
        b: true
      }
      tm: 1681202274741773339
    }
  }
}
infos {
  cmd_id: 22
  element: PIN
  edit_type: SET
  pin {
    mod_id: 1
    task_id: 3
    fb_id: 5
    pin_index: 9
    pin_val {
      v {
        t: T_BOOL
        b: false
      }
      tm: 1681202279308239441
    }
  }
}
infos {
  cmd_id: 23
  element: PIN
  edit_type: SET
  pin {
    mod_id: 1
    task_id: 3
    fb_id: 5
    pin_index: 10
    pin_val {
      v {
        t: T_FLOAT64
        d: 0.60000002384185791
      }
      tm: 1681202286208481640
    }
  }
}
infos {
  cmd_id: 24
  element: PIN
  edit_type: SET
  pin {
    mod_id: 1
    task_id: 3
    fb_id: 5
    pin_index: 11
    pin_val {
      v {
        t: T_FLOAT64
        d: 0.10000000149011612
      }
      tm: 1681202293692677417
    }
  }
}
infos {
  cmd_id: 25
  element: PIN
  edit_type: SET
  pin {
    mod_id: 1
    task_id: 3
    fb_id: 5
    pin_index: 12
    pin_val {
      v {
        t: T_FLOAT64
        d: 0.20000000298023224
      }
      tm: 1681202303508064231
    }
  }
}
infos {
  cmd_id: 26
  element: PIN
  edit_type: SET
  pin {
    mod_id: 1
    task_id: 3
    fb_id: 5
    pin_index: 13
    pin_val {
      v {
        t: T_FLOAT64
        d: 0.05000000074505806
      }
      tm: 1681202310141296382
    }
  }
}
infos {
  cmd_id: 27
  element: PIN
  edit_type: SET
  pin {
    mod_id: 1
    task_id: 3
    fb_id: 5
    pin_index: 14
    pin_val {
      v {
        t: T_FLOAT64
        d: 10
      }
      tm: 1681202331291412765
    }
  }
}
infos {
  cmd_id: 28
  element: PIN
  edit_type: SET
  pin {
    mod_id: 1
    task_id: 3
    fb_id: 5
    pin_index: 15
    pin_val {
      v {
        t: T_FLOAT64
        d: 1
      }
      tm: 1681202340341064868
    }
  }
}
infos {
  cmd_id: 29
  element: PIN
  edit_type: SET
  pin {
    mod_id: 1
    task_id: 3
    fb_id: 6
    pin_index: 2
    pin_val {
      v {
        t: T_STRING
        str: "RANDOM(5.0,7.0)"
      }
      tm: 1681205376231761767
    }
  }
}
infos {
  cmd_id: 30
  element: PIN
  edit_type: SET
  pin {
    mod_id: 1
    task_id: 3
    fb_id: 6
    pin_index: 2
    pin_val {
      v {
        t: T_STRING
        str: "RANDOM(5.0,7.0)"
      }
      tm: 1681205458711138324
    }
  }
}
infos {
  cmd_id: 31
  element: PIN
  edit_type: SET
  pin {
    mod_id: 1
    task_id: 3
    fb_id: 6
    pin_index: 2
    pin_val {
      v {
        t: T_STRING
        str: "RANDOM(5.0,7.0)"
      }
      tm: 1681205477493220605
    }
  }
}
infos {
  cmd_id: 32
  element: FB
  edit_type: MV
  fb {
    mod_id: 1
    task_id: 3
    fb_id: 5
  }
  pos {
    x: 155
    y: 90
  }
}
infos {
  cmd_id: 33
  element: LK
  edit_type: MV
  lk {
    mod_id: 1
    task_id: 3
    lk_id: 8
  }
  pos {
    x: 80
    y: 113
  }
  pos {
    x: 103
    y: 113
  }
  pos {
    x: 103
    y: 103
  }
  pos {
    x: 155
    y: 103
  }
}
infos {
  cmd_id: 34
  element: PIN
  edit_type: SET
  pin {
    mod_id: 1
    task_id: 3
    fb_id: 5
    pin_index: 3
    pin_val {
      v {
        t: T_FLOAT64
        d: 100
      }
      tm: 1681255951878432679
    }
  }
}
infos {
  cmd_id: 35
  element: PIN
  edit_type: SET
  pin {
    mod_id: 1
    task_id: 3
    fb_id: 6
    pin_index: 2
    pin_val {
      v {
        t: T_STRING
        str: "RANDOM(95,102)"
      }
      tm: 1681255983306400773
    }
  }
}
