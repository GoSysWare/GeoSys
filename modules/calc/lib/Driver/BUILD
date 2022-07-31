load("@rules_cc//cc:defs.bzl", "cc_library", "cc_test")
load("//tools:cpplint.bzl", "cpplint")

package(default_visibility = ["//visibility:public"])


cc_library(
    name = "Driver",
    includes = [
    ],
    hdrs = [
        "D_AS_VAL",
        "D_DS_VAL",
        "D_DT_VAL",
        "MTR_LGE",
        "MTR_LTE",
        "S_E_VAL",
    ],
    srcs = [
        "Driver.cpp",
    ],
    deps = [
        "//modules/calc/include:calc_include",
        "//modules/calc/include/lib:lib_include",
    ],
)
