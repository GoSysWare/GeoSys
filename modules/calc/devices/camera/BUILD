load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library")
load("//tools:cpplint.bzl", "cpplint")

package(default_visibility = ["//visibility:public"])


cc_binary(
    name = "libusb_camera.so",
    linkshared = True,
    linkstatic = False,
    deps = [":usb_camera_lib"],
)


cc_library(
    name = "usb_camera_lib",
    includes = [
    ],
    hdrs = [
        "usb_cam.h",
        "camera_component.h",
        "util.h"
    ],
    srcs = [
        "usb_cam.cc",
        "camera_component.cc",
        "device.cpp",
        "util.cc"
    ],
    linkopts = [
        "-lpthread",
        "-ldl",
        "-lavcodec",
        "-lswscale",
        "-lavformat",
        "-lavutil",
        # "-lprotobuf",
        # "-L/home/shuimujie/Works/GeoSys/bazel-bin/external/com_google_protobuf/",
        # "-lprotobuf",
        # "-lprotobuf_lite",
    ],

    deps = [
        "//modules/calc/ioss:ioss",
        "//modules/calc/devices/camera/proto:config_cc_proto",
        "//cyber",
        "@opencv",

    ],
)


cpplint()
