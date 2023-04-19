load("@rules_cc//cc:defs.bzl", "cc_library", "cc_test")
load("//tools:cpplint.bzl", "cpplint")

package(default_visibility = ["//visibility:public"])


cc_library(
    name = "System",
    includes = [
    ],
    hdrs = [
        "SYS_STATE",
        "FILE_READ_ONCE",
    ],
    srcs = [
        "System.cpp",
    ],
    deps = [
        "//modules/calc/include:calc_include",
        "//modules/calc/include/lib:lib_include",
        "//modules/calc/proto:bus_cc_proto",
        "//cyber"
    ],
)
