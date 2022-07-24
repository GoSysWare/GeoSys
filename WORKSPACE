workspace(name = "GEOSYS")

#########################################################################################
#bazel 编译的基础工具链
#########################################################################################
#加载bazel自带的工具链,这样可以运行http_archive，git_repository等函数
#对自带可以bazel构建的开源包，压缩文件就可以，使用时直接调用http_archive/local_repository规则即可
# strip_prefix 关键字可以解决解压时会发生两层文件名情况
# 本地非bazel构建的库，需要自己定义BUILD文件，然后利用bazel规则，像make文件一样去编写
# 注意new_local_repository 是当地文件夹，不是tar.gz压缩文件
#load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive","http_file","http_jar")
#  load('@bazel_tools//tools/build_defs/repo:git.bzl', 'git_repository',"new_git_repository")
#########################################################################################
#第三方库引用
#########################################################################################
load("//tools:workspace.bzl", "apollo_repositories")
apollo_repositories()

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

#########################################################################################
#bazel 内部支持
#########################################################################################
#bazel_skylib
http_archive(
    name = "bazel_skylib",
    sha256 = "1c531376ac7e5a180e0237938a2536de0c54d93f5c278634818e0efc952dd56c",
    urls = [
        "https://apollo-system.cdn.bcebos.com/archive/6.0/bazel-skylib-1.0.3.tar.gz",
        "https://github.com/bazelbuild/bazel-skylib/releases/download/1.0.3/bazel-skylib-1.0.3.tar.gz",
    ],
)

load("@bazel_skylib//:workspace.bzl", "bazel_skylib_workspace")

bazel_skylib_workspace()

http_archive(
    name = "zlib",
    build_file = "@com_google_protobuf//:third_party/zlib.BUILD",
    sha256 = "629380c90a77b964d896ed37163f5c3a34f6e6d897311f1df2a7016355c45eff",
    strip_prefix = "zlib-1.2.11",
    urls = ["https://github.com/madler/zlib/archive/v1.2.11.tar.gz"],
)

#rules_proto
http_archive(
    name = "rules_proto",
    sha256 = "602e7161d9195e50246177e7c55b2f39950a9cf7366f74ed5f22fd45750cd208",
    strip_prefix = "rules_proto-97d8af4dc474595af3900dd85cb3a29ad28cc313",
    urls = [
        "https://github.com/bazelbuild/rules_proto/archive/97d8af4dc474595af3900dd85cb3a29ad28cc313.tar.gz",
    ],
)

load("@rules_proto//proto:repositories.bzl", "rules_proto_dependencies", "rules_proto_toolchains")

rules_proto_dependencies()

rules_proto_toolchains()


#rules_python
http_archive(
    name = "rules_python",
    url = "https://github.com/bazelbuild/rules_python/releases/download/0.1.0/rules_python-0.1.0.tar.gz",
    sha256 = "b6d46438523a3ec0f3cead544190ee13223a52f6a6765a29eae7b7cc24cc83a0",
)

load("@rules_python//python:repositories.bzl", "py_repositories")

py_repositories()

# grpc
http_archive(
    name = "com_github_grpc_grpc",
    sha256 = "419dba362eaf8f1d36849ceee17c3e2ff8ff12ac666b42d3ff02a164ebe090e9",
    strip_prefix = "grpc-1.30.0",
    urls = [
        "https://apollo-system.cdn.bcebos.com/archive/6.0/v1.30.0.tar.gz",
        "https://github.com/grpc/grpc/archive/v1.30.0.tar.gz",
    ],
)
load("@com_github_grpc_grpc//bazel:grpc_deps.bzl", "grpc_deps")

grpc_deps()

load("@com_github_grpc_grpc//bazel:grpc_extra_deps.bzl", "grpc_extra_deps")

grpc_extra_deps()


