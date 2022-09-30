load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library")
load("//third_party/qt5:qt.bzl", "qt_cc_library")

package(default_visibility = ["//visibility:public"])


cc_binary(
    name = "test_qt_btchat",
    includes = [
        ".",
    ],
    linkopts = [
    ],
    deps = [
        ":btchat",
    ],
)

qt_cc_library(
    name = "btscanner",
    srcs = glob(
        ["btscanner/*.cpp"],
    ),
    hdrs = glob([
        "btscanner/*.h",
    ]),
    copts = [
    ],
    includes = [
        ".",
        "btscanner",
    ],
    res = glob([
        "btscanner/*.qrc",
    ]),
    uis = glob([
        "btscanner/*.ui",
    ]),
    deps = [
        "@qt//:qt_bluetooth",
        "@qt//:qt_gui",
    ],
)
