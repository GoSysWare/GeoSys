load("@rules_cc//cc:defs.bzl", "cc_library")

package(default_visibility = ["//visibility:public"])

licenses(["notice"])

cc_library(
    name = "avcodec",
    includes = ["."],
    linkopts = [
       "-L/usr/lib/x86_64-linux-gnu",
        "-lavcodec",
    ],
)

cc_library(
    name = "avformat",
    includes = ["."],
    linkopts = [
       "-L/usr/lib/x86_64-linux-gnu",
        "-lavformat",
    ],
)

cc_library(
    name = "swscale",
    includes = ["."],
    linkopts = [
       "-L/usr/lib/x86_64-linux-gnu",
        "-lswscale",
    ],
)

cc_library(
    name = "avutil",
    includes = ["."],
    linkopts = [
       "-L/usr/lib/x86_64-linux-gnu",
        "-lavutil",
    ],
)
