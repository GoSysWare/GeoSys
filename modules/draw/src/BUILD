load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library")
load("//third_party/qt5:qt.bzl", "qt_cc_library")

package(default_visibility = ["//visibility:public"])


# cc_binary(
#     name = "robot draw",
#     includes = [
#         ".",
#     ],
#     linkopts = [
#     ],
#     deps = [
#         ":btchat",
#     ],
# )

# qt_cc_library(
#     name = "plevdata",
#     srcs = glob(
#         ["btscanner/*.cpp"],
#     ),
#     hdrs = glob([
#         "btscanner/*.h",
#     ]),
#     copts = [
#     ],
#     includes = [
#         ".",
#         "btscanner",
#     ],
#     res = glob([
#         "btscanner/*.qrc",
#     ]),
#     uis = glob([
#         "btscanner/*.ui",
#     ]),
#     deps = [
#         "@qt//:qt_bluetooth",
#         "@qt//:qt_gui",
#     ],
# )

qt_cc_library(
    name = "plevdata",
    srcs =[
        "plevdata.cpp",
    ],
    hdrs = [
        "plevdata.h",
    ],
    copts = [
    ],
    deps = [
        "//modules/calc/proto:value_cc_proto",
        "//modules/calc/include:calc_include",
        "//modules/calc/include/lib:lib_include",   
        "@qt//:qt_core",
    ],
)

qt_cc_library(
    name = "plpin",
    srcs =[
        "plpin.cpp",
    ],
    hdrs = [
        "plpin.h",
    ],
    copts = [
    ],
    deps = [
        "//modules/calc/proto:value_cc_proto",
        "//modules/calc/include:calc_include",
        "//modules/calc/include/lib:lib_include",   
        "@qt//:qt_core",

    ],
)

qt_cc_library(
    name = "plpoint",
    srcs =[
        "plpoint.cpp",
    ],
    hdrs = [
        "plpoint.h",
    ],
    copts = [
    ],
    deps = [
        "//modules/calc/proto:value_cc_proto",
        "//modules/calc/include:calc_include",
        "//modules/calc/include/lib:lib_include",   
        "@qt//:qt_core",

    ],
)
qt_cc_library(
    name = "pllink",
    srcs =[
        "pllink.cpp",
    ],
    hdrs = [
        "pllink.h",
    ],
    copts = [
    ],
    deps = [
        ":plpoint",
        ":plpin",
        "//modules/calc/proto:value_cc_proto",
        "//modules/calc/include:calc_include",
        "//modules/calc/include/lib:lib_include",   
        "@qt//:qt_core",

    ],
)

qt_cc_library(
    name = "plfunctionblock",
    srcs =[
        "plfunctionblock.cpp",
    ],
    hdrs = [
        "plfunctionblock.h",
    ],
    copts = [
    ],
    deps = [
        ":plpoint",
        ":plpin",
        "//modules/calc/proto:value_cc_proto",
        "//modules/calc/include:calc_include",
        "//modules/calc/include/lib:lib_include",   
        "@qt//:qt_core",

    ],
)
qt_cc_library(
    name = "plprogram",
    srcs =[
        "plprogram.cpp",
    ],
    hdrs = [
        "plprogram.h",
    ],
    copts = [
    ],
    deps = [
        ":plfunctionblock",
        ":plpoint",
        ":plpin",
        ":pllink",
        "//modules/calc/proto:value_cc_proto",
        "//modules/calc/include:calc_include",
        "//modules/calc/include/lib:lib_include",   
        "@qt//:qt_core",

    ],
)

qt_cc_library(
    name = "plproject",
    srcs =[
        "plproject.cpp",
    ],
    hdrs = [
        "plproject.h",
    ],
    copts = [
    ],
    deps = [

        "//modules/calc/proto:value_cc_proto",
        "//modules/calc/include:calc_include",
        "//modules/calc/include/lib:lib_include",   
        "@qt//:qt_core",

    ],
)

qt_cc_library(
    name = "plselobject",
    srcs =[
        "plselobject.cpp",
    ],
    hdrs = [
        "plselobject.h",
    ],
    copts = [
    ],
    deps = [
        ":pllink",
        ":plfunctionblock",
        "//modules/calc/proto:value_cc_proto",
        "//modules/calc/include:calc_include",
        "//modules/calc/include/lib:lib_include",   
        "@qt//:qt_core",

    ],
)

qt_cc_library(
    name = "pltarget",
    srcs =[
        "pltarget.cpp",
    ],
    hdrs = [
        "pltarget.h",
    ],
    copts = [
    ],
    deps = [

        "//modules/calc/proto:value_cc_proto",
        "//modules/calc/include:calc_include",
        "//modules/calc/include/lib:lib_include",   
        "@qt//:qt_core",
        "@qt//:qt_gui",

    ],
)

qt_cc_library(
    name = "dlgaddprog",
    srcs =[
        "dlgaddprog.cpp",
    ],
    hdrs = [
        "dlgaddprog.h",
    ],
    copts = [
    ],
    deps = [
        ":plevdata",
        ":plprogram",
        "//modules/calc/proto:value_cc_proto",
        "//modules/calc/include:calc_include",
        "//modules/calc/include/lib:lib_include",   
        "@qt//:qt_core",
        "@qt//:qt_gui",

    ],
)

qt_cc_library(
    name = "plcommand",
    srcs =[
        "plcommand.cpp",
    ],
    hdrs = [
        "plcommand.h",
    ],
    copts = [
    ],
    deps = [
        ":plevdata",
        ":plprogram",
        "//modules/calc/proto:value_cc_proto",
        "//modules/calc/include:calc_include",
        "//modules/calc/include/lib:lib_include",   
        "@qt//:qt_core",
        "@qt//:qt_gui",

    ],
)

qt_cc_library(
    name = "cadpanel",
    srcs =[
        "cadpanel.cpp",
    ],
    hdrs = [
        "cadpanel.h",
    ],
    copts = [
    ],
    deps = [

        "//modules/calc/proto:value_cc_proto",
        "//modules/calc/include:calc_include",
        "//modules/calc/include/lib:lib_include",   
        "@qt//:qt_core",
        "@qt//:qt_gui",

    ],
)


qt_cc_library(
    name = "plmainmodel",
    srcs =[
        "plmainmodel.cpp",
    ],
    hdrs = [
        "plmainmodel.h",
    ],
    copts = [
    ],
    deps = [
        ":plevdata",
        "//modules/calc/proto:value_cc_proto",
        "//modules/calc/include:calc_include",
        "//modules/calc/include/lib:lib_include",   
        "@qt//:qt_core",
        "@qt//:qt_gui",

    ],
)


