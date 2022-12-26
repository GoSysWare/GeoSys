load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library")
load("//third_party/qt5:qt.bzl", "qt_cc_library")

package(default_visibility = ["//visibility:public"])



qt_cc_library(
    name = "draw",
    srcs = glob(
        ["*.cpp"],
    ),
    hdrs = glob([
        "*.h",
    ]),
    copts = [
    ],

    # res = glob([
    #     "resource.qrc",
    # ]),

    res = [
        "resource.qrc",
    ],
    uis = glob([
    ]),
    deps = [
        "//modules/calc/proto:bus_cc_proto",
        "//modules/calc/include:calc_include",
        "//modules/calc/include/lib:lib_include",   
        "//modules/calc/kernel:calc_kernel",   
        "//modules/calc/lib:calc_library",   
        
        "@qt//:qt_core",
        "@qt//:qt_gui",

    ],
)

# qt_cc_library(
#     name = "cadpanel",
#     srcs =[
#         "cadpanel.cpp",
#     ],
#     hdrs = [
#         "cadpanel.h",
#     ],
#     copts = [
#     ],
#     deps = [
#         ":plselobject",
#         ":plmainmodel",
#         "//modules/calc/proto:bus_cc_proto",
#         "//modules/calc/include:calc_include",
#         "//modules/calc/include/lib:lib_include",   
#         "@qt//:qt_core",
#         "@qt//:qt_gui",

#     ],
# )

# qt_cc_library(
#     name = "dlgaddmodule",
#     srcs =[
#         "dlgaddmodule.cpp",
#     ],
#     hdrs = [
#         "dlgaddmodule.h",
#     ],
#     copts = [
#     ],
#     deps = [
#         ":gdefine",
#         "//modules/calc/proto:bus_cc_proto",
#         "//modules/calc/include:calc_include",
#         "//modules/calc/include/lib:lib_include",   
#         "@qt//:qt_core",
#         "@qt//:qt_gui",

#     ],
# )
# qt_cc_library(
#     name = "dlgaddprog",
#     srcs =[
#         "dlgaddprog.cpp",
#     ],
#     hdrs = [
#         "dlgaddprog.h",
#     ],
#     copts = [
#     ],
#     deps = [
#         ":gdefine",
#         "//modules/calc/proto:bus_cc_proto",
#         "//modules/calc/include:calc_include",
#         "//modules/calc/include/lib:lib_include",   
#         "@qt//:qt_core",
#         "@qt//:qt_gui",

#     ],
# )


# qt_cc_library(
#     name = "dlgevdata",
#     srcs =[
#         "dlgevdata.cpp",
#     ],
#     hdrs = [
#         "dlgevdata.h",
#     ],
#     copts = [
#     ],
#     deps = [
#         ":plevdata",
#         "//modules/calc/proto:bus_cc_proto",
#         "//modules/calc/include:calc_include",
#         "//modules/calc/include/lib:lib_include",   
#         "@qt//:qt_core",
#         "@qt//:qt_gui",

#     ],
# )
# qt_cc_library(
#     name = "dlgipaddress",
#     srcs =[
#         "dlgipaddress.cpp",
#     ],
#     hdrs = [
#         "dlgipaddress.h",
#     ],
#     copts = [
#     ],
#     deps = [
#         "//modules/calc/proto:bus_cc_proto",
#         "//modules/calc/include:calc_include",
#         "//modules/calc/include/lib:lib_include",   
#         "@qt//:qt_core",
#         "@qt//:qt_gui",

#     ],
# )
# qt_cc_library(
#     name = "dlgobjname",
#     srcs =[
#         "dlgobjname.cpp",
#     ],
#     hdrs = [
#         "dlgobjname.h",
#     ],
#     copts = [
#     ],
#     deps = [
#         "//modules/calc/proto:bus_cc_proto",
#         "//modules/calc/include:calc_include",
#         "//modules/calc/include/lib:lib_include",   
#         "@qt//:qt_core",
#         "@qt//:qt_gui",

#     ],
# )
# qt_cc_library(
#     name = "dlgpinset",
#     srcs =[
#         "dlgpinset.cpp",
#     ],
#     hdrs = [
#         "dlgpinset.h",
#     ],
#     copts = [
#     ],
#     deps = [
#         ":plevdata",
#         ":dlgevdata",
#         "//modules/calc/proto:bus_cc_proto",
#         "//modules/calc/include:calc_include",
#         "//modules/calc/include/lib:lib_include",   
#         "@qt//:qt_core",
#         "@qt//:qt_gui",

#     ],
# )
# qt_cc_library(
#     name = "dlgsaveproj",
#     srcs =[
#         "dlgsaveproj.cpp",
#     ],
#     hdrs = [
#         "dlgsaveproj.h",
#     ],
#     copts = [
#     ],
#     deps = [
#         "//modules/calc/proto:bus_cc_proto",
#         "//modules/calc/include:calc_include",
#         "//modules/calc/include/lib:lib_include",   
#         "@qt//:qt_core",
#         "@qt//:qt_gui",

#     ],
# )

# qt_cc_library(
#     name = "evdatamodel",
#     srcs =[
#         "evdatamodel.cpp",
#     ],
#     hdrs = [
#         "evdatamodel.h",
#     ],
#     copts = [
#     ],
#     deps = [
#         ":plevdata",
#         "//modules/calc/proto:bus_cc_proto",
#         "//modules/calc/include:calc_include",
#         "//modules/calc/include/lib:lib_include",   
#         "@qt//:qt_core",
#         "@qt//:qt_gui",

#     ],
# )

# qt_cc_library(
#     name = "evdatapanel",
#     srcs =[
#         "evdatapanel.cpp",
#     ],
#     hdrs = [
#         "evdatapanel.h",
#     ],
#     copts = [
#     ],
#     deps = [
#         ":plevdata",
#         "//modules/calc/proto:bus_cc_proto",
#         "//modules/calc/include:calc_include",
#         "//modules/calc/include/lib:lib_include",   
#         "@qt//:qt_core",
#         "@qt//:qt_gui",

#     ],
# )
# qt_cc_library(
#     name = "gdefine",
#     srcs =[
#     ],
#     hdrs = [
#         "gdefine.h",
#     ],
#     copts = [
#     ],
#     deps = [

#     ],
# )
# qt_cc_library(
#     name = "libpanel",
#     srcs =[
#         "libpanel.cpp",
#     ],
#     hdrs = [
#         "libpanel.h",
#     ],
#     copts = [
#     ],
#     deps = [
#         "//modules/calc/proto:bus_cc_proto",
#         "//modules/calc/include:calc_include",
#         "//modules/calc/include/lib:lib_include",   
#         "@qt//:qt_core",
#         "@qt//:qt_gui",

#     ],
# )

# qt_cc_library(
#     name = "modulepanel",
#     srcs =[
#         "modulepanel.cpp",
#     ],
#     hdrs = [
#         "modulepanel.h",
#     ],
#     copts = [
#     ],
#     deps = [

#         "//modules/calc/proto:bus_cc_proto",
#         "//modules/calc/include:calc_include",
#         "//modules/calc/include/lib:lib_include",   
#         "@qt//:qt_core",
#         "@qt//:qt_gui",

#     ],
# )

# qt_cc_library(
#     name = "plcommand",
#     srcs =[
#         "plcommand.cpp",
#     ],
#     hdrs = [
#         "plcommand.h",
#     ],
#     copts = [
#     ],
#     deps = [
#         ":plmodule",
#         ":plvlink",
#         ":pllink",
#         ":plevdata",
#         ":plprogram",
#         ":plproject",
#         ":evdatamodel",
#         "//modules/calc/proto:bus_cc_proto",
#         "//modules/calc/include:calc_include",
#         "//modules/calc/include/lib:lib_include",   
#         "@qt//:qt_core",
#     ],
# )
# qt_cc_library(
#     name = "plevdata",
#     srcs =[
#         "plevdata.cpp",
#     ],
#     hdrs = [
#         "plevdata.h",
#     ],
#     copts = [
#     ],
#     deps = [
#         "//modules/calc/proto:value_cc_proto",
#         "//modules/calc/include:calc_include",
#         "//modules/calc/include/lib:lib_include",   
#         "@qt//:qt_core",
#     ],
# )

# qt_cc_library(
#     name = "plfunctionblock",
#     srcs =[
#         "plfunctionblock.cpp",
#     ],
#     hdrs = [
#         "plfunctionblock.h",
#     ],
#     copts = [
#     ],
#     deps = [
#         ":plpoint",
#         ":plpin",
#         "//modules/calc/proto:value_cc_proto",
#         "//modules/calc/include:calc_include",
#         "//modules/calc/include/lib:lib_include",   
#         "@qt//:qt_core",

#     ],
# )

# qt_cc_library(
#     name = "pllink",
#     srcs =[
#         "pllink.cpp",
#     ],
#     hdrs = [
#         "pllink.h",
#     ],
#     copts = [
#     ],
#     deps = [
#         ":plpoint",
#         ":plpin",
#         "//modules/calc/proto:value_cc_proto",
#         "//modules/calc/include:calc_include",
#         "//modules/calc/include/lib:lib_include",   
#         "@qt//:qt_core",

#     ],
# )
# qt_cc_library(
#     name = "plmainframe",
#     srcs =[
#         "plmainframe.cpp",
#     ],
#     hdrs = [
#         "plmainframe.h",
#     ],
#     copts = [
#     ],
#     deps = [
#         ":plpoint",
#         ":plpin",
#         "//modules/calc/proto:value_cc_proto",
#         "//modules/calc/include:calc_include",
#         "//modules/calc/include/lib:lib_include",   
#         "@qt//:qt_core",
#         "@qt//:qt_gui",


#     ],
# )


# qt_cc_library(
#     name = "plmainmodel",
#     srcs =[
#         "plmainmodel.cpp",
#     ],
#     hdrs = [
#         "plmainmodel.h",
#     ],
#     copts = [
#     ],
#     deps = [
#         ":plevdata",
#         ":plcommand",
#         ":plmodule",
#         ":plprogram",
#         ":plfunctionblock",
#         ":plpin",
#         ":pllink",
#         ":plpoint",
#         ":plvlink",
#         ":plproject",
#         ":evdatamodel",
#         "//modules/calc/proto:bus_cc_proto",
#         "//modules/calc/include:calc_include",
#         "//modules/calc/include/lib:lib_include",   
#         "@qt//:qt_core",
#     ],
# )

# qt_cc_library(
#     name = "plmodule",
#     srcs =[
#         "plmodule.cpp",
#     ],
#     hdrs = [
#         "plmodule.h",
#     ],
#     copts = [
#     ],
#     deps = [
#         ":plprogram",
#         "//modules/calc/proto:bus_cc_proto",
#         "//modules/calc/include:calc_include",
#         "//modules/calc/include/lib:lib_include",   
#         "@qt//:qt_core",

#     ],
# )

# qt_cc_library(
#     name = "plpin",
#     srcs =[
#         "plpin.cpp",
#     ],
#     hdrs = [
#         "plpin.h",
#     ],
#     copts = [
#     ],
#     deps = [
#         "//modules/calc/proto:bus_cc_proto",
#         "//modules/calc/include:calc_include",
#         "//modules/calc/include/lib:lib_include",   
#         "@qt//:qt_core",

#     ],
# )

# qt_cc_library(
#     name = "plpoint",
#     srcs =[
#         "plpoint.cpp",
#     ],
#     hdrs = [
#         "plpoint.h",
#     ],
#     copts = [
#     ],
#     deps = [
#         "//modules/calc/proto:value_cc_proto",
#         "//modules/calc/include:calc_include",
#         "//modules/calc/include/lib:lib_include",   
#         "@qt//:qt_core",

#     ],
# )

# qt_cc_library(
#     name = "plprogram",
#     srcs =[
#         "plprogram.cpp",
#     ],
#     hdrs = [
#         "plprogram.h",
#     ],
#     copts = [
#     ],
#     deps = [
#         ":plfunctionblock",
#         ":plpoint",
#         ":plpin",
#         ":pllink",
#         ":plvlink",
#         "//modules/calc/proto:bus_cc_proto",
#         "//modules/calc/include:calc_include",
#         "//modules/calc/include/lib:lib_include",   
#         "@qt//:qt_core",

#     ],
# )

# qt_cc_library(
#     name = "plproject",
#     srcs =[
#         "plproject.cpp",
#     ],
#     hdrs = [
#         "plproject.h",
#     ],
#     copts = [
#     ],
#     deps = [

#         "//modules/calc/proto:bus_cc_proto",
#         "//modules/calc/include:calc_include",
#         "//modules/calc/include/lib:lib_include",   
#         "@qt//:qt_core",

#     ],
# )


# qt_cc_library(
#     name = "plselobject",
#     srcs =[
#         "plselobject.cpp",
#     ],
#     hdrs = [
#         "plselobject.h",
#     ],
#     copts = [
#     ],
#     deps = [
#         ":pllink",
#         ":plvlink",
#         ":plevdata",
#         ":plfunctionblock",
#         "//modules/calc/proto:bus_cc_proto",
#         "//modules/calc/include:calc_include",
#         "//modules/calc/include/lib:lib_include",   
#         "@qt//:qt_core",

#     ],
# )

# qt_cc_library(
#     name = "pltarget",
#     srcs =[
#         "pltarget.cpp",
#     ],
#     hdrs = [
#         "pltarget.h",
#     ],
#     copts = [
#     ],
#     deps = [

#         "//modules/calc/proto:bus_cc_proto",
#         "//modules/calc/include:calc_include",
#         "//modules/calc/include/lib:lib_include",   
#         "@qt//:qt_core",
#         "@qt//:qt_gui",

#     ],
# )

# qt_cc_library(
#     name = "plvlink",
#     srcs =[
#         "plvlink.cpp",
#     ],
#     hdrs = [
#         "plvlink.h",
#     ],
#     copts = [
#     ],
#     deps = [
#         ":plpoint",
#         ":plpin",
#         ":plevdata",
#         ":plfunctionblock",
#         "//modules/calc/proto:bus_cc_proto",
#         "//modules/calc/include:calc_include",
#         "//modules/calc/include/lib:lib_include",   
#         "@qt//:qt_core",

#     ],
# )


# qt_cc_library(
#     name = "progpanel",
#     srcs =[
#         "progpanel.cpp",
#     ],
#     hdrs = [
#         "progpanel.h",
#     ],
#     copts = [
#     ],
#     deps = [

#         "//modules/calc/proto:bus_cc_proto",
#         "//modules/calc/include:calc_include",
#         "//modules/calc/include/lib:lib_include",   
#         "@qt//:qt_core",
#         "@qt//:qt_gui",

#     ],
# )





