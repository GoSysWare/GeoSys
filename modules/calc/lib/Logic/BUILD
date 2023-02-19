load("@rules_cc//cc:defs.bzl", "cc_library", "cc_test")
load("//tools:cpplint.bzl", "cpplint")

package(default_visibility = ["//visibility:public"])


cc_library(
    name = "Logic",
    includes = [
    ],
    hdrs = [
        "AND",
        "AND4",
        "NOT",
        "OR",
        "OR4",
        "XOR",
        "RS",
        "SR",
        "SCALING",
        "SIX_SEL_N",
        # "THRSEL",
        "TWOSEL",
    ],
    srcs = [
        "Logic.cpp",
    ],
    deps = [
        "//modules/calc/include:calc_include",
        "//modules/calc/include/lib:lib_include",
        "//modules/calc/proto:bus_cc_proto",

    ],
)
