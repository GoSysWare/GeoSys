load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library")
load("//tools:cpplint.bzl", "cpplint")

package(default_visibility = ["//visibility:public"])


cc_binary(
    name = "calc_core",
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
        "//modules/calc/net:calc_net",
        "//modules/calc/rtdb:calc_rtdb",
        "//modules/calc/include:calc_include",
        "//modules/calc/include/lib:lib_include",

    ],
)



cpplint()
