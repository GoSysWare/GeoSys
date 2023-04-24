load("@rules_cc//cc:defs.bzl", "cc_library", "cc_test")
load("//tools:cpplint.bzl", "cpplint")

package(default_visibility = ["//visibility:public"])


cc_library(
    name = "Geometry",
    includes = [
    ],
    hdrs = [
        "PATH_MERGE",
        "PATH_SPLIT",
        "PATH_CREATE",

    ],
    srcs = [
        "Geometry.cpp",
    ],
    deps = [
        "//modules/calc/include:calc_include",
        "//modules/calc/include/lib:lib_include",
        "//modules/calc/proto:bus_cc_proto",
        "//modules/calc/proto:navigation_cc_proto",

    ],
)
