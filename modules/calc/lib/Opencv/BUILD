load("@rules_cc//cc:defs.bzl", "cc_library", "cc_test")
load("//tools:cpplint.bzl", "cpplint")

package(default_visibility = ["//visibility:public"])


cc_library(
    name = "Opencv",
    includes = [
    ],
    hdrs = [
        "IMG_READ",
        "IMG_WRITE",

    ],
    srcs = [
        "Opencv.cpp",

    ],
    deps = [
        "//modules/calc/include:calc_include",
        "//modules/calc/include/lib:lib_include",
        "//modules/calc/proto:value_cc_proto",
        "//modules/calc/proto:image_cc_proto",
        "@opencv"
    ],
)
