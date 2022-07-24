load("@rules_cc//cc:defs.bzl", "cc_library", "cc_test")
load("//tools:cpplint.bzl", "cpplint")

package(default_visibility = ["//visibility:public"])


cc_library(
    name = "Arithmetic",
    includes = [
    ],
    hdrs = [
        "ADD_INT",
        "ADD_LREAL",
        "ADD_REAL",
        "DIV_INT",
        "DIV_LREAL",
        "DIV_REAL",
        "MOVE_BOOL",
        "MOVE_INT",
        "MOVE_LREAL",
        "MOVE_REAL",
        "MUL_INT",
        "MUL_LREAL",
        "MUL_REAL",
        "SUB_INT",
        "SUB_LREAL",
        "SUB_REAL",
    ],
    srcs = [
        "Arithmetic.c",
    ],
    deps = [
        "//modules/calc/include:calc_include",
        "//modules/calc/include/lib:lib_include",
    ],
)
