load("@rules_cc//cc:defs.bzl", "cc_library", "cc_test")
load("//tools:cpplint.bzl", "cpplint")

package(default_visibility = ["//visibility:public"])


cc_library(
    name = "Converter",
    includes = [
    ],
    hdrs = [
        "B2DT",
        "B2I",
        "B2LR",
        "B2R",
        "DT2B",
        "DT2I",
        "DT2LR",
        "DT2R",
        "I2B",
        "I2DT",
        "I2LR",
        "I2R",
        "LR2B",
        "LR2DT",
        "LR2I",
        "LR2R",
        "R2B",
        "R2DT",
        "R2I",
        "R2LR",
        "SCALING",
    ],
    srcs = [
        "Converter.cpp",
    ],
    deps = [
        "//modules/calc/include:calc_include",
        "//modules/calc/include/lib:lib_include",
    ],
)
