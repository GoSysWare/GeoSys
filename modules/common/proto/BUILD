
load("@rules_cc//cc:defs.bzl", "cc_binary","cc_proto_library")
load("@rules_proto//proto:defs.bzl", "proto_library")
load("//tools:python_rules.bzl", "py_proto_library")


package(default_visibility = ["//visibility:public"])


cc_proto_library(
    name = "action_cc_proto",
    deps = [
        ":action_proto",
    ],
)

proto_library(
    name = "action_proto",
    srcs = ["action.proto"],
)

py_proto_library(
    name = "action_py_pb2",
    deps = [
        ":action_proto",
    ],
)


cc_proto_library(
    name = "std_msgs_cc_proto",
    deps = [
        ":std_msgs_proto",
    ],
)

py_proto_library(
    name = "std_msgs_py_pb2",
    deps = [
        ":std_msgs_proto",
    ],
)

proto_library(
    name = "std_msgs_proto",
    srcs = ["std_msgs.proto"],
    deps = [
    ],
)



cc_proto_library(
    name = "geometry_msgs_cc_proto",
    deps = [
        ":geometry_msgs_proto",
    ],
)

py_proto_library(
    name = "geometry_msgs_py_pb2",
    deps = [
        ":geometry_msgs_proto",
    ],
)
proto_library(
    name = "geometry_msgs_proto",
    srcs = ["geometry_msgs.proto"],
    deps = [
        ":std_msgs_proto",

    ],
)


cc_proto_library(
    name = "bond_cc_proto",
    deps = [
        ":bond_proto",
    ],
)

py_proto_library(
    name = "bondpy_pb2",
    deps = [
        ":bond_proto",
    ],
)
proto_library(
    name = "bond_proto",
    srcs = ["bond.proto"],
    deps = [
        ":std_msgs_proto",
    ],
)



# ddddddd


cc_proto_library(
    name = "error_code_proto",
    deps = [
        ":error_code_proto_lib",
    ],
)

proto_library(
    name = "error_code_proto_lib",
    srcs = [
        "error_code.proto",
    ],
)

cc_proto_library(
    name = "header_proto",
    deps = [
        ":header_proto_lib",
    ],
)

proto_library(
    name = "header_proto_lib",
    srcs = [
        "header.proto",
    ],
    deps = [
        ":error_code_proto_lib",
    ],
)

