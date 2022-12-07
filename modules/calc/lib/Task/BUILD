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
        "Task.cpp",
    ],
    deps = [
        "//modules/calc/include:calc_include",
        "//modules/calc/include/lib:lib_include",
        "//modules/calc/proto:value_cc_proto",
        "//modules/calc/proto:task_def_cc_proto",
        "//modules/calc/proto:cmd_cc_proto",
        "//modules/calc/proto:edit_cc_proto",
    ],
)
