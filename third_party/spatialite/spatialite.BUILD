load("@rules_cc//cc:defs.bzl", "cc_library")

package(default_visibility = ["//visibility:public"])

licenses(["notice"])

cc_library(
    name = "spatialite",
    includes = [
        ".",
        "spatialite",
    ],
    linkopts = [
        "-L/usr/local/lib",
        "-lspatialite",
    ],
    deps=[
        "@sqlite3",
        "@proj4",
        "@geos",
    ],
    linkstatic = False,
)
