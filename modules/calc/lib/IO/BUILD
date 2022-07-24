load("@rules_cc//cc:defs.bzl", "cc_library", "cc_test")
load("//tools:cpplint.bzl", "cpplint")

package(default_visibility = ["//visibility:public"])


cc_library(
    name = "IO",
    includes = [
    ],
    hdrs = [
        "DM1x1",
        "DM2x1",
        "DM3x1",
        "DM4x1",
    ],
    srcs = [
        "IO.c",
    ],
    deps = [
        "//modules/calc/include:calc_include",
        "//modules/calc/include/lib:lib_include",
    ],
)
