load("@rules_cc//cc:defs.bzl", "cc_library", "cc_test")
load("//tools:cpplint.bzl", "cpplint")

package(default_visibility = ["//visibility:public"])




cc_library(
    name = "task",
    hdrs = ["task.h"],
    deps = [
        ":task_manager",
    ],
)

cc_test(
    name = "task_test",
    size = "small",
    srcs = ["task_test.cc"],
    deps = [
        "//cyber:cyber_core",
        "@com_google_googletest//:gtest_main",
    ],
)

cc_library(
    name = "task_manager",
    srcs = ["task_manager.cc"],
    hdrs = ["task_manager.h"],
    copts = ["-faligned-new"],
    deps = [
        "//cyber/scheduler:scheduler_factory",
    ],
)


cc_library(
    name = "async_task_client",
    hdrs = ["async_task_client.h"],
    deps = [
        ":async_task_client_base",
    ],
)

cc_library(
    name = "async_task_client_base",
    hdrs = ["async_task_client_base.h"],
)

cc_library(
    name = "async_task",
    hdrs = ["async_task.h"],
    deps = [
        ":async_task_base",
        "//cyber/scheduler",
    ],
)

cc_library(
    name = "async_task_base",
    hdrs = ["async_task_base.h"],
)


cpplint()
