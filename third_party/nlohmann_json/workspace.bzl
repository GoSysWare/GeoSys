"""Loads the nlohmann_json library"""

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

# Sanitize a dependency so that it works correctly from code that includes
# Apollo as a submodule.
def clean_dep(dep):
    return str(Label(dep))

def repo():
    http_archive(
        name = "nlohmann_json",
        strip_prefix = "json-3.10.5",
        build_file = clean_dep("//third_party/nlohmann_json:json.BUILD"),
        urls = [
            "https://github.com/nlohmann/json/archive/v3.10.5.tar.gz",
        ],
    )