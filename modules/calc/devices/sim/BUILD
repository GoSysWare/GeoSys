load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library")
load("//tools:cpplint.bzl", "cpplint")

package(default_visibility = ["//visibility:public"])




cc_library(
    name = "device_sim",
    includes = [
    ],
    hdrs = [
        "expression.h",
    ],
    srcs = [
        "expression.cpp",
        "device.cpp"
    ],
    deps = [
        "//modules/calc/ioss:ioss",
        "//modules/calc/proto:ioss_cc_proto",
        "//modules/calc/include:calc_include",
        "//modules/calc/proto:bus_cc_proto",
        "//cyber"

    ],
)


cpplint()
