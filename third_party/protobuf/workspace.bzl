"""Loads the protobuf library"""

# load("@com_google_protobuf//:protobuf_deps.bzl", "protobuf_deps")

# protobuf_deps()
# load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")



# def clean_dep(dep):
#     return str(Label(dep))

# def repo():
#     native.new_local_repository(
#         name = "protobuf",
#         build_file = clean_dep("//third_party/protobuf:protobuf.BUILD"),
#         path = "/usr/local/include",
#     )



"""Loads the protobuf library"""

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

def repo():
    http_archive(
        name = "com_google_protobuf",
        # sha256 = "d0f5f605d0d656007ce6c8b5a82df3037e1d8fe8b121ed42e536f569dec16113",
        strip_prefix = "protobuf-3.15.2",
        urls = [
            "https://github.com/protocolbuffers/protobuf/archive/v3.15.2.tar.gz",
        ],
    )