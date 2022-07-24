"""Loads the glog library"""

# Sanitize a dependency so that it works correctly from code that includes

# def clean_dep(dep):
#     return str(Label(dep))

# def repo():
#     # glog
#     native.new_local_repository(
#         name = "com_google_glog",
#         build_file = clean_dep("//third_party/glog:glog.BUILD"),
#         path = "/usr/include/glog",
#     )
load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
def repo():
    http_archive(
    name = "com_google_glog",
    sha256 = "f28359aeba12f30d73d9e4711ef356dc842886968112162bc73002645139c39c",
    strip_prefix = "glog-0.4.0",
    url = "https://github.com/google/glog/archive/v0.4.0.tar.gz",
    )
