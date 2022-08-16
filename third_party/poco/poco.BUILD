load("@rules_cc//cc:defs.bzl", "cc_library")

package(default_visibility = ["//visibility:public"])

licenses(["notice"])

# cc_library(
#     name = "PocoFoundation",
#     includes = ["."],
#     linkopts = [
#         "-L/opt/homebrew/opt/poco/lib",
#         "-lPocoFoundation",
#     ],
# )
cc_library(
    name = "PocoFoundation",
    includes = ["."],
    linkopts = [
        "-L/usr/lib/x86_64-linux-gnu",
        "-lPocoFoundation",
    ],
)
