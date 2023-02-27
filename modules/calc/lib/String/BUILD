load("@rules_cc//cc:defs.bzl", "cc_library")

package(default_visibility = ["//visibility:public"])

cc_library(
    name = "String",
    srcs = [
        "String.cpp",
    ],
    hdrs = [
        "STR_APPEND",
        "STR_CLEAR",
        "STR_COMPARE",
        "STR_COPY",
        "STR_EQ",
        "STR_ERASE",
        "STR_FIND",
        "STR_FIND_FIRST_OF",
        "STR_FIND_LAST_OF",
        "STR_INSERT",
        "STR_REPLACE",
        "STR_SUBSTR",
    ],
    includes = [
    ],
    deps = [
        "//modules/calc/include:calc_include",
        "//modules/calc/include/lib:lib_include",
        "//modules/calc/proto:bus_cc_proto",
    ],
)
