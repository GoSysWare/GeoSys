load("@rules_cc//cc:defs.bzl", "cc_library")

package(default_visibility = ["//visibility:public"])

licenses(["notice"])

cc_library(
    name = "paho",
    includes = [
        ".",
    ],
    linkopts = [
        "-L/usr/local/lib",
        "-lpaho-mqtt3c",
        "-lpaho-mqtt3a",
    ],

)
