load("@rules_cc//cc:defs.bzl", "cc_library", "cc_test")
load("//tools:cpplint.bzl", "cpplint")

package(default_visibility = ["//visibility:public"])


cc_library(
    name = "Maths",
    includes = [
    ],
    hdrs = [
        "ABS",
        "ACOS",
        "ASIN",
        "ATAN",
        "AVE4W",
        "COS",
        "EXP",
        "FUN12",
        "LN",
        "LOG",
        "MOD",
        "POLYNOM",
        "SIN",
        "SQRT",
        "TAN",
    ],
    srcs = [
        "Maths.c",
    ],
    deps = [
        "//modules/calc/include:calc_include",
        "//modules/calc/include/lib:lib_include",
    ],
)
