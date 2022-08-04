# This BUILD file shows how to use protobuf with bazel. Before you can use
# proto_library/<lang>_proto_library rules in a BUILD file, you need to
# include protobuf repo as remote repositories in your WORKSPACE file. See
# the WORKSPACE file in the same directory with this BUILD file for an
# example.

load("@rules_cc//cc:defs.bzl", "cc_proto_library")
load("@rules_proto//proto:defs.bzl", "proto_library")

package(default_visibility = ["//visibility:public"])



cc_proto_library(
    name = "value_cc_proto",
    deps = [":value_proto"],
)

proto_library(
    name = "value_proto",
    srcs = ["value.proto"],
    deps = [
    ],
)
