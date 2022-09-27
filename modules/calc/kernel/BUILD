load("@rules_cc//cc:defs.bzl", "cc_library", "cc_test")
load("//tools:cpplint.bzl", "cpplint")

package(default_visibility = ["//visibility:public"])


cc_library(
    name = "calc_kernel",
    includes = [
    ],
    hdrs = [

    ],
    srcs = [
        "k_bus.cpp",
        "k_command.cpp",
        "k_evdata.cpp",
        "k_functionblock.cpp",
        "k_lib.cpp",
        "k_program.cpp",
        "k_module.cpp",
        "k_project.cpp",
        "k_util.cpp",
    ],
    deps = [
        "//modules/calc/include:calc_include",
        "//modules/calc/include/lib:lib_include",
        "//modules/calc/proto:value_cc_proto",
        "//modules/calc/proto:cmd_cc_proto",
        "//modules/calc/proto:edit_cc_proto",
        "//modules/calc/proto:task_def_cc_proto",
        "//modules/calc/proto:snapshot_cc_proto",
        "//modules/calc/common:calc_gflags",

    ],
)

cc_library(
    name = "k_evdata",
    includes = [
    ],
    hdrs = [

    ],
    srcs = [
        "k_evdata.cpp",
    ],
    deps = [
        "//modules/calc/include:calc_include",
        "//modules/calc/include/lib:lib_include",
        "//modules/calc/proto:value_cc_proto",
    ],
)


cc_library(
    name = "k_functionblock",
    includes = [
    ],
    hdrs = [

    ],
    srcs = [
        "k_functionblock.cpp",
    ],
    deps = [
        "//modules/calc/include:calc_include",
        "//modules/calc/include/lib:lib_include",
        "//modules/calc/proto:value_cc_proto",
        "//modules/calc/kernel:k_evdata",
    ],
)

cc_library(
    name = "k_lib",
    includes = [
    ],
    hdrs = [

    ],
    srcs = [
        "k_lib.cpp",
    ],
    deps = [
        "//modules/calc/include:calc_include",
        "//modules/calc/include/lib:lib_include",
        "//modules/calc/proto:value_cc_proto",
    ],
)

cc_library(
    name = "k_process",
    includes = [
    ],
    hdrs = [

    ],
    srcs = [
        "k_process.cpp",
    ],
    deps = [
        "//modules/calc/include:calc_include",
        "//modules/calc/include/lib:lib_include",
        "//modules/calc/proto:value_cc_proto",
    ],
)
cc_library(
    name = "k_program",
    includes = [
    ],
    hdrs = [

    ],
    srcs = [
        "k_program.cpp",
    ],
    deps = [
        "//modules/calc/include:calc_include",
        "//modules/calc/include/lib:lib_include",
        "//modules/calc/proto:value_cc_proto",
        "//modules/calc/proto:task_def_cc_proto",

    ],
)
cc_library(
    name = "k_module",
    includes = [
    ],
    hdrs = [

    ],
    srcs = [
        "k_module.cpp",
    ],
    deps = [
        "//modules/calc/include:calc_include",
        "//modules/calc/include/lib:lib_include",
        "//modules/calc/proto:value_cc_proto",
        "//modules/calc/proto:cmd_cc_proto",
        "//modules/calc/proto:task_def_cc_proto",
        "//cyber"

    ],
)
cc_library(
    name = "k_project",
    includes = [
    ],
    hdrs = [

    ],
    srcs = [
        "k_project.cpp",
    ],
    deps = [
        "//modules/calc/include:calc_include",
        "//modules/calc/include/lib:lib_include",
        "//modules/calc/proto:value_cc_proto",
        "//modules/calc/proto:cmd_cc_proto",
        "//modules/calc/proto:task_def_cc_proto",
    ],
)

cc_library(
    name = "k_command",
    includes = [
    ],
    hdrs = [

    ],
    srcs = [
        "k_command.cpp",
    ],
    deps = [
        "//modules/calc/include:calc_include",
        "//modules/calc/include/lib:lib_include",
        "//modules/calc/proto:value_cc_proto",
        "//modules/calc/proto:cmd_cc_proto",
        "//modules/calc/proto:task_def_cc_proto",

    ],
)




