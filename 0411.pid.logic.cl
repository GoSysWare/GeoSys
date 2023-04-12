infos {
  edit_type: SET
  proj {
    proj_name: "rotbot-engine-project"
    proj_uuid: "{90f71198-6afd-4f02-a837-5079a5e67f05}"
  }
}
infos {
  cmd_id: 1
  element: EV
  edit_type: ADD
  ev {
    ev_id: 1
    ev_name: "EV_1"
    ev_type: 7
    ev_desc: "Desc"
    init_val {
      v {
        t: T_FLOAT64
        d: 0
      }
      tm: 1681278555385924030
    }
  }
}
infos {
  cmd_id: 2
  element: MOD
  edit_type: ADD
  mod {
    mod_id: 2
    mod_name: "PID"
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
    interval: 50
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
    fc_name: "SYSSTATE"
  }
  pos {
    x: 43
    y: 48
  }
}
infos {
  cmd_id: 5
  element: FB
  edit_type: ADD
  fb {
    mod_id: 2
    task_id: 3
    fb_id: 5
    flib_name: "Control"
    fc_name: "PID"
    fb_name: "PID_2"
  }
  pos {
    x: 155
    y: 90
  }
}
infos {
  cmd_id: 6
  element: FB
  edit_type: ADD
  fb {
    mod_id: 2
    task_id: 3
    fb_id: 6
    flib_name: "Devices"
    fc_name: "SIM_READ"
  }
  pos {
    x: 64
    y: 106
  }
}
infos {
  cmd_id: 7
  element: FB
  edit_type: ADD
  fb {
    mod_id: 2
    task_id: 3
    fb_id: 7
    flib_name: "Control"
    fc_name: "PID"
    fb_name: "PID_1"
  }
  pos {
    x: 151
    y: 29
  }
}
infos {
  cmd_id: 8
  element: LK
  edit_type: ADD
  lk {
    mod_id: 2
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
    y: 103
  }
  pos {
    x: 155
    y: 103
  }
}
infos {
  cmd_id: 9
  element: VI
  edit_type: ADD
  vi {
    mod_id: 2
    task_id: 3
    fb_id: 7
    pin_index: 4
    ev_id: 1
    vi_id: 9
  }
}
infos {
  cmd_id: 10
  element: TASK
  edit_type: ADD
  task {
    mod_id: 2
    task_id: 10
    task_name: "P2"
    interval: 500
  }
}
infos {
  cmd_id: 11
  element: FB
  edit_type: ADD
  fb {
    mod_id: 2
    task_id: 10
    fb_id: 11
    flib_name: "Devices"
    fc_name: "SIM_READ"
  }
  pos {
    x: 55
    y: 46
  }
}
infos {
  cmd_id: 12
  element: TASK
  edit_type: ADD
  task {
    mod_id: 2
    task_id: 12
    task_name: "P3"
    interval: 5000
  }
}
infos {
  cmd_id: 13
  element: FB
  edit_type: ADD
  fb {
    mod_id: 2
    task_id: 12
    fb_id: 13
    flib_name: "Devices"
    fc_name: "SIM_READ"
  }
  pos {
    x: 53
    y: 43
  }
}
infos {
  cmd_id: 14
  element: VO
  edit_type: ADD
  vo {
    mod_id: 2
    task_id: 12
    fb_id: 13
    pin_index: 1
    ev_id: 1
    vo_id: 14
  }
}
infos {
  cmd_id: 15
  element: PIN
  edit_type: SET
  pin {
    mod_id: 2
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
  cmd_id: 16
  element: PIN
  edit_type: SET
  pin {
    mod_id: 2
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
  cmd_id: 17
  element: PIN
  edit_type: SET
  pin {
    mod_id: 2
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
  cmd_id: 18
  element: PIN
  edit_type: SET
  pin {
    mod_id: 2
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
  cmd_id: 19
  element: PIN
  edit_type: SET
  pin {
    mod_id: 2
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
  cmd_id: 20
  element: PIN
  edit_type: SET
  pin {
    mod_id: 2
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
  cmd_id: 21
  element: PIN
  edit_type: SET
  pin {
    mod_id: 2
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
  cmd_id: 22
  element: PIN
  edit_type: SET
  pin {
    mod_id: 2
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
  cmd_id: 23
  element: PIN
  edit_type: SET
  pin {
    mod_id: 2
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
  cmd_id: 24
  element: PIN
  edit_type: SET
  pin {
    mod_id: 2
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
  cmd_id: 25
  element: PIN
  edit_type: SET
  pin {
    mod_id: 2
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
  cmd_id: 26
  element: PIN
  edit_type: SET
  pin {
    mod_id: 2
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
  cmd_id: 27
  element: PIN
  edit_type: SET
  pin {
    mod_id: 2
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
  cmd_id: 28
  element: PIN
  edit_type: SET
  pin {
    mod_id: 2
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
  cmd_id: 29
  element: PIN
  edit_type: SET
  pin {
    mod_id: 2
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
  cmd_id: 30
  element: PIN
  edit_type: SET
  pin {
    mod_id: 2
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
  cmd_id: 31
  element: PIN
  edit_type: SET
  pin {
    mod_id: 2
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
  cmd_id: 32
  element: PIN
  edit_type: SET
  pin {
    mod_id: 2
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
  cmd_id: 33
  element: PIN
  edit_type: SET
  pin {
    mod_id: 2
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
  cmd_id: 34
  element: PIN
  edit_type: SET
  pin {
    mod_id: 2
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
  cmd_id: 35
  element: PIN
  edit_type: SET
  pin {
    mod_id: 2
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
  cmd_id: 36
  element: PIN
  edit_type: SET
  pin {
    mod_id: 2
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
infos {
  cmd_id: 37
  element: PIN
  edit_type: SET
  pin {
    mod_id: 2
    task_id: 3
    fb_id: 5
    pin_index: 11
    pin_val {
      v {
        t: T_FLOAT64
        d: 50
      }
      tm: 1681265439589839704
    }
  }
}
infos {
  cmd_id: 38
  element: PIN
  edit_type: SET
  pin {
    mod_id: 2
    task_id: 3
    fb_id: 5
    pin_index: 12
    pin_val {
      v {
        t: T_FLOAT64
        d: 50
      }
      tm: 1681265445111974571
    }
  }
}
infos {
  cmd_id: 39
  element: PIN
  edit_type: SET
  pin {
    mod_id: 2
    task_id: 3
    fb_id: 5
    pin_index: 13
    pin_val {
      v {
        t: T_FLOAT64
        d: 0
      }
      tm: 1681265452604992465
    }
  }
}
infos {
  cmd_id: 40
  element: PIN
  edit_type: SET
  pin {
    mod_id: 2
    task_id: 3
    fb_id: 7
    pin_index: 1
    pin_val {
      v {
        t: T_BOOL
        b: false
      }
      tm: 1681278326093554808
    }
  }
}
infos {
  cmd_id: 41
  element: PIN
  edit_type: SET
  pin {
    mod_id: 2
    task_id: 3
    fb_id: 7
    pin_index: 2
    pin_val {
      v {
        t: T_BOOL
        b: false
      }
      tm: 1681278329227345567
    }
  }
}
infos {
  cmd_id: 42
  element: PIN
  edit_type: SET
  pin {
    mod_id: 2
    task_id: 3
    fb_id: 7
    pin_index: 3
    pin_val {
      v {
        t: T_FLOAT64
        d: 100
      }
      tm: 1681278333016012071
    }
  }
}
infos {
  cmd_id: 43
  element: PIN
  edit_type: SET
  pin {
    mod_id: 2
    task_id: 3
    fb_id: 7
    pin_index: 5
    pin_val {
      v {
        t: T_FLOAT64
        d: 0.30000001192092896
      }
      tm: 1681278348628938136
    }
  }
}
infos {
  cmd_id: 44
  element: PIN
  edit_type: SET
  pin {
    mod_id: 2
    task_id: 3
    fb_id: 7
    pin_index: 6
    pin_val {
      v {
        t: T_BOOL
        b: true
      }
      tm: 1681278354969280908
    }
  }
}
infos {
  cmd_id: 45
  element: PIN
  edit_type: SET
  pin {
    mod_id: 2
    task_id: 3
    fb_id: 7
    pin_index: 7
    pin_val {
      v {
        t: T_BOOL
        b: true
      }
      tm: 1681278357583560409
    }
  }
}
infos {
  cmd_id: 46
  element: PIN
  edit_type: SET
  pin {
    mod_id: 2
    task_id: 3
    fb_id: 7
    pin_index: 8
    pin_val {
      v {
        t: T_BOOL
        b: true
      }
      tm: 1681278360278294199
    }
  }
}
infos {
  cmd_id: 47
  element: PIN
  edit_type: SET
  pin {
    mod_id: 2
    task_id: 3
    fb_id: 7
    pin_index: 9
    pin_val {
      v {
        t: T_BOOL
        b: false
      }
      tm: 1681278363308661281
    }
  }
}
infos {
  cmd_id: 48
  element: PIN
  edit_type: SET
  pin {
    mod_id: 2
    task_id: 3
    fb_id: 7
    pin_index: 10
    pin_val {
      v {
        t: T_FLOAT64
        d: 0.60000002384185791
      }
      tm: 1681278369194245954
    }
  }
}
infos {
  cmd_id: 49
  element: PIN
  edit_type: SET
  pin {
    mod_id: 2
    task_id: 3
    fb_id: 7
    pin_index: 11
    pin_val {
      v {
        t: T_FLOAT64
        d: 50
      }
      tm: 1681278374327385214
    }
  }
}
infos {
  cmd_id: 50
  element: PIN
  edit_type: SET
  pin {
    mod_id: 2
    task_id: 3
    fb_id: 7
    pin_index: 12
    pin_val {
      v {
        t: T_FLOAT64
        d: 50
      }
      tm: 1681278378757676933
    }
  }
}
infos {
  cmd_id: 51
  element: PIN
  edit_type: SET
  pin {
    mod_id: 2
    task_id: 3
    fb_id: 7
    pin_index: 13
    pin_val {
      v {
        t: T_FLOAT64
        d: 0
      }
      tm: 1681278384290756192
    }
  }
}
infos {
  cmd_id: 52
  element: PIN
  edit_type: SET
  pin {
    mod_id: 2
    task_id: 3
    fb_id: 7
    pin_index: 14
    pin_val {
      v {
        t: T_FLOAT64
        d: 10
      }
      tm: 1681278390488798318
    }
  }
}
infos {
  cmd_id: 53
  element: PIN
  edit_type: SET
  pin {
    mod_id: 2
    task_id: 3
    fb_id: 7
    pin_index: 15
    pin_val {
      v {
        t: T_FLOAT64
        d: -10
      }
      tm: 1681278394855204324
    }
  }
}
infos {
  cmd_id: 54
  element: PIN
  edit_type: SET
  pin {
    mod_id: 2
    task_id: 3
    fb_id: 5
    pin_index: 15
    pin_val {
      v {
        t: T_FLOAT64
        d: -10
      }
      tm: 1681278400132934528
    }
  }
}
infos {
  cmd_id: 55
  element: PIN
  edit_type: SET
  pin {
    mod_id: 2
    task_id: 10
    fb_id: 11
    pin_index: 1
    pin_val {
      v {
        t: T_STRING
        str: "SIM"
      }
      tm: 1681278457063445748
    }
  }
}
infos {
  cmd_id: 56
  element: PIN
  edit_type: SET
  pin {
    mod_id: 2
    task_id: 10
    fb_id: 11
    pin_index: 2
    pin_val {
      v {
        t: T_STRING
        str: "RANDOM(90,110)"
      }
      tm: 1681278473053043054
    }
  }
}
infos {
  cmd_id: 57
  element: PIN
  edit_type: SET
  pin {
    mod_id: 2
    task_id: 10
    fb_id: 11
    pin_index: 2
    pin_val {
      v {
        t: T_STRING
        str: "RANDOM(95,102)"
      }
      tm: 1681278492817824826
    }
  }
}
infos {
  cmd_id: 58
  element: PIN
  edit_type: SET
  pin {
    mod_id: 2
    task_id: 12
    fb_id: 13
    pin_index: 1
    pin_val {
      v {
        t: T_STRING
        str: "SIM"
      }
      tm: 1681278790795846468
    }
  }
}
infos {
  cmd_id: 59
  element: PIN
  edit_type: SET
  pin {
    mod_id: 2
    task_id: 12
    fb_id: 13
    pin_index: 2
    pin_val {
      v {
        t: T_STRING
        str: "RANDOM(95,102)"
      }
      tm: 1681278808547568542
    }
  }
}
