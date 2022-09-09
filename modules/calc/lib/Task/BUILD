load("@rules_cc//cc:defs.bzl", "cc_library", "cc_test")
load("//tools:cpplint.bzl", "cpplint")

package(default_visibility = ["//visibility:public"])


cc_library(
    name = "Task",
    includes = [
    ],
    hdrs = [
        "TASK",
        "REQUEST",
        "RESPONSE",

    ],
    srcs = [
        "Fsm.cpp",
    ],
    deps = [
        "//modules/calc/include:calc_include",
        "//modules/calc/include/lib:lib_include",
        "//modules/calc/proto:value_cc_proto",
    ],
)
