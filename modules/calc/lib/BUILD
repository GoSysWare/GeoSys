load("@rules_cc//cc:defs.bzl", "cc_library", "cc_test")
load("//tools:cpplint.bzl", "cpplint")

package(default_visibility = ["//visibility:public"])


cc_library(
    name = "calc_library",
    deps = [
        "//modules/calc/lib/Arithmetic:Arithmetic",
        "//modules/calc/lib/Comparison:Comparison",        
        "//modules/calc/lib/Converter:Converter",
        "//modules/calc/lib/Counter:Counter",
        "//modules/calc/lib/Devices:Devices",
        "//modules/calc/lib/Fsm:Fsm",
        "//modules/calc/lib/Geometry:Geometry",

        "//modules/calc/lib/Task:Task",
        "//modules/calc/lib/Logic:Logic",
        # "//modules/calc/lib/Maths:Maths",
        # "//modules/calc/lib/Opencv:Opencv",
        "//modules/calc/lib/System:System",  
        "//modules/calc/lib/Timer:Timer",
        "//modules/calc/lib/Trigger:Trigger",  
        "//modules/calc/lib/String:String",  

    ],
)
