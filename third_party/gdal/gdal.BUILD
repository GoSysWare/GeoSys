load("@rules_cc//cc:defs.bzl", "cc_library")

package(default_visibility = ["//visibility:public"])

licenses(["notice"])

cc_library(
    name = "gdal",
    includes = [
        ".",
    ],
    linkopts = [
        "-L/usr/local/lib",
        "-lgdal",
    ],

)
