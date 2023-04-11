load("@rules_cc//cc:defs.bzl", "cc_library", "cc_test")
load("//tools:cpplint.bzl", "cpplint")

package(default_visibility = ["//visibility:public"])


cc_library(
    name = "Control",
    includes = [
    ],
    hdrs = [
        # "BALANCE",
        # "DDS",
        # "DIFF",
        # "ES_MA",
        # "FILTER",
        # "FIRST",
        # "HL_ALM",
        # "HL_LMT",
        # "INTEG",
        # "LEADLAG",
        # "LIMV",
        "PID",
        # "RAT_ALM",
        # "RAT_LMT",
        # "RMP",
        # "SFT_BOOL",
        # "SFT_REAL",
        # "SS_MA",
        # "TOTALIZER",
    ],
    srcs = [
        "Control.cpp",
    ],
    deps = [
          "//modules/calc/include:calc_include",
        "//modules/calc/include/lib:lib_include",
        "//modules/calc/proto:bus_cc_proto",
    ],
)
