load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_proto_library")
load("//tools:cpplint.bzl", "cpplint")
load("@rules_proto//proto:defs.bzl", "proto_library")
load("//tools:python_rules.bzl", "py_proto_library")

package(default_visibility = ["//visibility:public"])

cc_binary(
    name = "test_bond",
    srcs = [

        "test_bond.cpp",


    ],
    linkopts = [
        "-lpthread",

    ],
    deps = [
         "//modules/bond",

    ],
)



cc_proto_library(
    name = "LiftAction_cc_proto",
    deps = [
        ":LiftAction_proto",
    ],
)

proto_library(
    name = "LiftAction_proto",
    srcs = ["LiftAction.proto"],
    deps = [
        "//modules/common/proto:action_proto",
    ],
)

py_proto_library(
    name = "LiftAction_py_pb2",
    deps = [
        ":LiftAction_proto",
    ],
)

cc_binary(
    name = "lift_action_server",
    srcs = [
        "lift_action_server.cpp",
    ],
    linkopts = [
    ],
    deps = [
        ":LiftAction_cc_proto",
        "//cyber",
        "//modules/action:action_server",
    ],
)

cc_binary(
    name = "lift_action_client",
    srcs = [
        "lift_action_client.cpp",
    ],
    linkopts = [
    ],
    deps = [
        ":LiftAction_cc_proto",
        "//cyber",
        "//modules/action:action_client",
    ],
)


cpplint()
