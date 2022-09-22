load("@rules_cc//cc:defs.bzl", "cc_library", "cc_test")
load("//tools:cpplint.bzl", "cpplint")

package(default_visibility = ["//visibility:public"])


cc_library(
    name = "calc_include",
    hdrs = [
        "k_bus.h",
        "k_command.h",
        "k_config.h",
        "k_datatype.h",
        "k_evdata.h",
        "k_functionblock.h",
        "k_lib.h",
        "k_program.h",
        "k_module.h",
        "k_project.h",
        "k_util.h",
    ],
      deps = [
        "@opencv",
        "//cyber"

    ],  
)
