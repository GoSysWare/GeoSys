load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library")
load("//third_party/qt5:qt.bzl", "qt_cc_library")

package(default_visibility = ["//visibility:public"])


cc_binary(
    name = "robot_draw",
    srcs = [
        "main.cpp"
    ],

    linkopts = [
    ],
    deps = [
        "//modules/draw/src:draw",
    ],
)
