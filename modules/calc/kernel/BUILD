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
        "k_command.cpp",
        "k_compress.cpp",
        "k_evdata.cpp",
        "k_functionblock.cpp",
        "k_io.cpp",
        "k_lib.cpp",
        "k_process.cpp",
        "k_program.cpp",
        "k_project.cpp",
        "k_state.cpp",
        "k_util.cpp",
    ],
    deps = [
        "//modules/calc/include:calc_include",
        "//modules/calc/include/lib:lib_include",
    ],
)

cc_library(
    name = "evdata",
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
