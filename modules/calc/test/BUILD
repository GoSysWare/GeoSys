load("@rules_cc//cc:defs.bzl", "cc_binary")
load("//tools:cpplint.bzl", "cpplint")

package(default_visibility = ["//visibility:public"])

cc_binary(
    name = "test_proto",
    srcs = [
        "test_proto.cpp",
    ],
    linkopts = [
        "-lpthread",
        "-ldl",

    ],
    linkstatic = False,
    deps = [
        "//cyber",
        "//modules/calc/devices/sim:device_sim",
        "//modules/calc/include:calc_include",
        "//modules/calc/ioss",
        "//modules/calc/proto:bus_cc_proto",
        "//modules/calc/proto:ioss_cc_proto",
        "//modules/calc/proto:geo_cc_proto",
        "//modules/calc/proto:nav_cc_proto",
    ],
)

cpplint()
