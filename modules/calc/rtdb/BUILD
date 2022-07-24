load("@rules_cc//cc:defs.bzl", "cc_library", "cc_test")
load("//tools:cpplint.bzl", "cpplint")

package(default_visibility = ["//visibility:public"])

cc_library(
    name = "calc_rtdb",
    deps = [
        "//modules/calc/rtdb:rtdb_lib",
    ],
)
cc_library(
    name = "rtdb_lib",
    hdrs = [
        "station.h",
        "rtdb.h",
        "RBTree.h",
        "BinTree.h",
        "helper.h",
        "CapiGlobal.h"
    ],
    srcs = [
        "station.c",
        "rtdb.c",
        "RBTree.c",
        "BinTree.c",
        "helper.c",
        ],
    deps = [
        "//modules/calc/include:calc_include",
    ]

)


cpplint()
