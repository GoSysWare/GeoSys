load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "fastcdr",
    includes = [
        ".",
    ],
    linkopts = [
        "-L/usr/local/lib",
        "-lfastcdr",
    ],
    visibility = ["//visibility:public"],
)
