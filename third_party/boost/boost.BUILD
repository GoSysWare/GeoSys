load("@rules_cc//cc:defs.bzl", "cc_library")

licenses(["notice"])

package(default_visibility = ["//visibility:public"])

# TODO(all) rules_boost
cc_library(
    name = "boost",
    includes = ["."],
    linkopts = [
        "-L/usr/lib/x86_64-linux-gnu",
        "-lboost_system",
        "-lboost_filesystem",
        "-lboost_program_options",
        "-lboost_thread",
    ],
)
