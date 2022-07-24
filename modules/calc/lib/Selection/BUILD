load("@rules_cc//cc:defs.bzl", "cc_library", "cc_test")
load("//tools:cpplint.bzl", "cpplint")

package(default_visibility = ["//visibility:public"])


cc_library(
    name = "Selection",
    includes = [
    ],
    hdrs = [
        "SIX_SEL_N",
        "THRSEL",
        "TWOSEL",
    ],
    srcs = [
        "Selection.c",
    ],
    deps = [
        "//modules/calc/include:calc_include",
        "//modules/calc/include/lib:lib_include",
    ],
)
