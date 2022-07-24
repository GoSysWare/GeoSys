load("@rules_cc//cc:defs.bzl", "cc_library")

licenses(["notice"])

package(default_visibility = ["//visibility:public"])

# TODO(all) rules_boost
cc_library(
    name = "behaviortree",
    includes = ["."],
    linkopts = [
        "-L/usr/local/lib",
        "-lbehaviortree_cpp_v3",
    ],
)
