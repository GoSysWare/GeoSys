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
    urls = [
        "https://github.com/bazelbuild/bazel-skylib/releases/download/1.4.2/bazel-skylib-1.4.2.tar.gz",
    ],
)

load("@bazel_skylib//:workspace.bzl", "bazel_skylib_workspace")

bazel_skylib_workspace()


#rules_python
http_archive(
    name = "rules_python",
    sha256 = "863ba0fa944319f7e3d695711427d9ad80ba92c6edd0b7c7443b84e904689539",
    strip_prefix = "rules_python-0.22.0",
    url = "https://github.com/bazelbuild/rules_python/releases/download/0.22.0/rules_python-0.22.0.tar.gz",
)

load("@rules_python//python:repositories.bzl", "py_repositories")

py_repositories()


# grpc
http_archive(
    name = "com_github_grpc_grpc",
    strip_prefix = "grpc-1.55.1",
    urls = [
        "https://github.com/grpc/grpc/archive/v1.55.1.tar.gz",
    ],
)

load("@com_github_grpc_grpc//bazel:grpc_deps.bzl", "grpc_deps")

grpc_deps()

load("@com_github_grpc_grpc//bazel:grpc_extra_deps.bzl", "grpc_extra_deps")

grpc_extra_deps()


