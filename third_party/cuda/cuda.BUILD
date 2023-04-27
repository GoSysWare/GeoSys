load("@rules_cc//cc:defs.bzl", "cc_library")

package(default_visibility = ["//visibility:public"])

licenses(["notice"])

cc_library(
    name = "cuda",
    includes = [
        ".",
    ],
    linkopts = [
        "-L/usr/local/cuda-12.1/lib64",
        "-lOpenCL",
        "-lcudart",
        "-lcublas",
        "-lcuda",
        "-lcufft",
        "-lcufftw",
        "-lcurand",
        "-lcusolver",
        "-lcusparse",
        "-lnppc",
        "-lnppial",
        "-lnppicc",
        "-lnppidei",
        "-lnppif",
        "-lnppig",
        "-lnppim",
        "-lnppist",
        "-lnppisu",
        "-lnppitc",
        "-lnpps",
        "-lnvidia-ml",
        "-lnvrtc",
        "-lopenblas",
    ],

)
