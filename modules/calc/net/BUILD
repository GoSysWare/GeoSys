load("@rules_cc//cc:defs.bzl", "cc_library", "cc_test")
load("//tools:cpplint.bzl", "cpplint")

package(default_visibility = ["//visibility:public"])


cc_library(
    name = "calc_net",
    includes = [
    ],
    hdrs = [

    ],
    srcs = [
        "cfgbus.cpp",
        "evbus.cpp",
        "stbbus.cpp",
        "vnet.cpp",
        "vtcp.cpp",
        "vudp.cpp",
    ],
    deps = [
        "//modules/calc/include:calc_include",
        "//modules/calc/include/lib:lib_include",
    ],

)
