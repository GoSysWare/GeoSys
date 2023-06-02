load("@rules_cc//cc:defs.bzl", "cc_library", "cc_test")
load("//tools:cpplint.bzl", "cpplint")

package(default_visibility = ["//visibility:public"])


cc_library(
    name = "Value",
    includes = [
    ],
    hdrs = [
        "JSON_OBJ_MERGE",
        "JSON_SERIAL",
        "JSON2PB",
        "PB2JSON",
        "V_GET_ANY",
        "V_GET_DOUBLE",
        "V_SET_ANY",
        "V_SET_DOUBLE",

    ],
    srcs = [
        "Value.cpp",
    ],
    deps = [
        "//modules/calc/include:calc_include",
        "//modules/calc/include/lib:lib_include",
        "//modules/calc/proto:bus_cc_proto",
        "@nlohmann_json//:single_json",
         ],
)
