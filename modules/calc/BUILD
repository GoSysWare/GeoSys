load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library")
load("//tools:cpplint.bzl", "cpplint")

package(default_visibility = ["//visibility:public"])


cc_binary(
    name = "robot_engine",
    srcs = [
        "main.cpp",
    ],
    linkopts = [
        "-lpthread",
    ],
    linkstatic = False,
    deps = [
        "//modules/calc/kernel:calc_kernel",
        "//modules/calc/lib:calc_library",
        "//modules/calc/include/lib:lib_include",
        "//cyber",

    ],
)

cpplint()
