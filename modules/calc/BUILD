load("@rules_cc//cc:defs.bzl", "cc_binary")
load("//tools:cpplint.bzl", "cpplint")

package(default_visibility = ["//visibility:public"])

cc_binary(
    name = "robot_engine",
    srcs = [
        "main.cpp",
    ],
    linkopts = [
        "-lpthread",
        "-ldl",
        "-lpng",
        "-ljpeg",
        "-lcudnn",
    ],
    deps = [
        "//cyber",
        "//modules/calc/include/lib:lib_include",
        "//modules/calc/ioss",
        "//modules/calc/kernel:calc_kernel",
        "//modules/calc/lib:calc_library",
        "@cuda",
    ],
)

cpplint()
