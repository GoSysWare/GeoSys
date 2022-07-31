load("@rules_cc//cc:defs.bzl", "cc_library", "cc_test")
load("//tools:cpplint.bzl", "cpplint")

package(default_visibility = ["//visibility:public"])


cc_library(
    name = "Comparison",
    includes = [
    ],
    hdrs = [
        "EQ_INT",
        "EQ_LREAL",
        "EQ_REAL",
        "GE_INT",
        "GE_LREAL",
        "GE_REAL",
        "GT_INT",
        "GT_LREAL",
        "GT_REAL",
        "LE_INT",
        "LE_LREAL",
        "LE_REAL",
        "LT_INT",
        "LT_LREAL",
        "LT_REAL",
        "NE_INT",
        "NE_LREAL",
        "NE_REAL",
    ],
    srcs = [
        "Comparison.cpp",
    ],
    deps = [
        "//modules/calc/include:calc_include",
        "//modules/calc/include/lib:lib_include",
    ],
)
