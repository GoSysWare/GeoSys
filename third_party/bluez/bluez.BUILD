load("@rules_cc//cc:defs.bzl", "cc_library")

licenses(["notice"])

package(default_visibility = ["//visibility:public"])

# TODO(all) rules_boost
cc_library(
    name = "bluez",
    includes = ["include"],
    linkopts = [
       "-L/usr/lib/x86_64-linux-gnu",
       "-lbluetooth",

    ],
)
