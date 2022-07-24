load("@rules_cc//cc:defs.bzl", "cc_library", "cc_test")
load("//tools:cpplint.bzl", "cpplint")

package(default_visibility = ["//visibility:public"])

cc_library(
    name = "rtdb",
    deps = [
        "//modules/calc/rtdb:bin_tree",
    ],
)
cc_library(
    name = "rtdb_lib",
    hdrs = ["rtdb.h"],
    srcs = ["rtdb.c"],
    deps = [
    ]
)
        
cc_library(
    name = "bin_tree",
    hdrs = ["BinTree.h"],
    srcs = ["BinTree.c"],
    deps = [
        "//modules/calc/rtdb:capi_gloabel"
    ]
        
)
cc_library(
    name = "helper",
    hdrs = ["helper.h"],
    srcs = ["helper.c"],
    deps = [
    ]
        
)

cc_library(
    name = "capi_gloabel",
    hdrs = ["CapiGlobal.h"],
    srcs = [],
    deps = [
    ],
)
cc_library(
    name = "rb_tree",
    hdrs = ["RBTree.h"],
    srcs = ["RBTree.c"],
    deps = [
       "//modules/calc/rtdb:capi_gloabel",
       "//modules/calc/rtdb:bin_tree"

    ]
        
)




cpplint()
