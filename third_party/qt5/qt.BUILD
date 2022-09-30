load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "qt_core",
    hdrs = glob(["*"]),
    copts = [
        "-Iinclude",
        "-Iinclude/QtCore",
    ],
    includes = [
        "include",
        "include/QtCore",
    ],
    linkopts = [
        "-Wl,-rpath,/usr/local/Qt-5.14.2//lib",
        "-lQt5Core",
    ],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "qt_widgets",
    hdrs = glob(["*"]),
    copts = [
        "-Iinclude",
        "-Iinclude/QtWidgets",
    ],
    includes = [
        "include",
        "include/QtWidgets",
    ],
    linkopts = [
        "-L/usr/local/Qt-5.14.2//lib",
        "-lQt5Widgets",
    ],
    visibility = ["//visibility:public"],
    deps = [":qt_core"],
)

cc_library(
    name = "qt_gui",
    hdrs = glob(["*"]),
    copts = [
        "-Iinclude",
        "-Iinclude/QtGui",
    ],
    includes = [
        "include",
        "include/QtGui",
    ],
    linkopts = [
        "-L/usr/local/Qt-5.14.2//lib",
        "-lQt5Gui",
    ],
    visibility = ["//visibility:public"],
    deps = [
        ":qt_core",
        ":qt_widgets",
    ],
)

cc_library(
    name = "qt_opengl",
    hdrs = glob(["*"]),
    copts = [
        "-Iinclude",
        "-Iinclude/QtOpenGL",
    ],
    includes = [
        "include",
        "include/QtOpenGL",
    ],
    linkopts = [
        "-L/usr/local/Qt-5.14.2/lib",
        "-lQt5OpenGL",
        "-lGL",
    ],
    visibility = ["//visibility:public"],
    deps = [
        ":qt_core",
        ":qt_gui",
        ":qt_widgets",
    ],
)

cc_library(
    name = "qt_bluetooth",
    hdrs = glob(["*"]),
    copts = [
        "-Iinclude",
        "-Iinclude/QtBluetooth",
    ],
    includes = [
        "include",
        "include/QtBluetooth",
    ],
    linkopts = [
        "-L/usr/local/Qt-5.14.2/lib",
        "-lQt5Bluetooth",
    ],
    visibility = ["//visibility:public"],
    deps = [
        ":qt_core",
    ],
)

cc_library(
    name = "qt_qml",
    hdrs = glob(["*"]),
    copts = [
        "-Iinclude",
        "-Iinclude/QtQml",
    ],
    includes = [
        "include",
        "include/QtQml",
    ],
    linkopts = [
        "-L/usr/local/Qt-5.14.2/lib",
        "-lQt5Qml",
    ],
    visibility = ["//visibility:public"],
    deps = [
        ":qt_core",
    ],
)

