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
        "k_command.c",
        "k_compress.c",
        "k_evdata.c",
        "k_functionblock.c",
        "k_io.c",
        "k_lib.c",
        "k_process.c",
        "k_program.c",
        "k_project.c",
        "k_state.c",
        "k_util.c",
    ],
    deps = [
        "//modules/calc/include:calc_include",
        "//modules/calc/include/lib:lib_include",
    ],
)
