load("@rules_cc//cc:defs.bzl", "cc_library", "cc_test")
load("//tools:cpplint.bzl", "cpplint")

package(default_visibility = ["//visibility:public"])


cc_library(
    name = "Comm",
    includes = [
    ],
    hdrs = [
        "RG_BOOL",
        "RG_INT",
        "RG_REAL",
        "WG_BOOL",
        "WG_INT",
        "WG_REAL",

    ],
    srcs = [
        "Comm.c",
    ],
    deps = [
        "//modules/calc/include:calc_include",
        "//modules/calc/include/lib:lib_include",
    ],
)
