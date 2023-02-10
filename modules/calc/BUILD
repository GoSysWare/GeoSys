load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library")
load("//tools:cpplint.bzl", "cpplint")

package(default_visibility = ["//visibility:public"])


cc_binary(
    name = "robot_engine",
    srcs = [
        "main.cpp",
    ],
    linkopts = [
        "-lpthread",
    ],
    linkstatic = False,
    deps = [
        "//modules/calc/kernel:calc_kernel",
        "//modules/calc/lib:calc_library",
        "//modules/calc/include/lib:lib_include",
        "//cyber",

    ],
)


cc_binary(
    name = "test_calc",
    srcs = [
        "test.cpp",

    ],
    linkopts = [
        "-lpthread",

    ],
    linkstatic = False,
    deps = [
        "//modules/calc/kernel:k_lib",
        "//modules/calc/kernel:k_evdata",
        "//modules/calc/kernel:k_functionblock",
        "//modules/calc/kernel:k_program",
        "//modules/calc/kernel:k_module",
        "//modules/calc/lib/Arithmetic:Arithmetic",
        "//modules/calc/lib/Counter:Counter",
        "//modules/calc/lib/Fsm:Fsm",
        "//modules/calc/lib/Task:Task",
        # "//modules/calc/lib/Opencv:Opencv",
        "//modules/calc/include:calc_include",
        "//modules/calc/include/lib:lib_include",
        "//modules/calc/proto:value_cc_proto",
        "//modules/calc/proto:cmd_cc_proto",
        "//modules/calc/proto:task_def_cc_proto",
        "//cyber",


    ],
)

cc_binary(
    name = "test_opencv",
    srcs = [
        "test_opencv.cpp",

    ],
    linkopts = [
        "-lpthread",

    ],
    linkstatic = False,
    deps = [
        "//modules/calc/kernel:k_lib",
        "//modules/calc/kernel:k_evdata",
        "//modules/calc/kernel:k_functionblock",
        "//modules/calc/kernel:k_program",
        "//modules/calc/lib/Arithmetic:Arithmetic",
        "//modules/calc/lib/Counter:Counter",
        "//modules/calc/lib/Opencv:Opencv",
        "//modules/calc/include:calc_include",
        "//modules/calc/include/lib:lib_include",

    ],
)

cc_binary(
    name = "test_DFS",
    srcs = [
        "test_DFS.cpp",

    ],
    linkopts = [
        "-lpthread",

    ],
    linkstatic = False,
    deps = [

    ],
)

cc_binary(
    name = "test_comm",
    srcs = [
        "test_comm.cpp",

    ],
    linkopts = [
        "-lpthread",

    ],
    linkstatic = False,
    deps = [

    ],
)

cpplint()
