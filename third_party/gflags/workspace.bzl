"""Loads the gflags library"""

# def clean_dep(dep):
#     return str(Label(dep))

# def repo():
#     # gflags
#     native.new_local_repository(
#         name = "com_github_gflags_gflags",
#         build_file = clean_dep("//third_party/gflags:gflags.BUILD"),
#         path = "/usr/include/gflags",
#     )


load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
def repo():
    http_archive(
    name = "com_google_gflags_gflags",
    strip_prefix = "gflags-2.2.2",
    url = "https://github.com/gflags/gflags/archive/v2.2.2.tar.gz",
    )

