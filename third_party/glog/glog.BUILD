load("@rules_cc//cc:defs.bzl", "cc_library")

package(default_visibility = ["//visibility:public"])

licenses(["notice"])

cc_library(
    name = "glog",
    includes = [
        ".",
    ],
    linkopts = [
        "-L/usr/lib/x86_64-linux-gnu",
        "-lglog",
    ],
    deps = [
        "@com_github_gflags_gflags//:gflags",
    ],
)
