#########################################################################################
# 开发语言
#########################################################################################

load("//third_party/qt5:workspace.bzl", qt5 = "repo")
# load("//third_party/py:python_configure.bzl", "python_configure")

#########################################################################################
# 开发应用的通用基础库如glog gflag gtest protobuf
#########################################################################################
load("//third_party/protobuf:workspace.bzl", protobuf = "repo")
load("//third_party/glog:workspace.bzl", glog = "repo")
load("//third_party/gflags:workspace.bzl", gflags = "repo")
load("//third_party/cpplint:workspace.bzl", cpplint = "repo")
load("//third_party/fastrtps:workspace.bzl", fastrtps = "repo")
load("//third_party/poco:workspace.bzl", poco = "repo")
load("//third_party/uuid:workspace.bzl", uuid = "repo")
load("//third_party/nlohmann_json:workspace.bzl", nlohmann_json = "repo")
load("//third_party/curl:workspace.bzl", curl = "repo")

#########################################################################################
# 图像处理、点云、地图功能库
#########################################################################################

load("//third_party/opencv:workspace.bzl", opencv = "repo")

#########################################################################################
# 人工智能框架和工具
#########################################################################################
load("//third_party/gpus:cuda_configure.bzl", "cuda_configure")
load("//third_party/cuda:workspace.bzl", cuda = "repo")

# load("//third_party/tensorrt:tensorrt_configure.bzl", "tensorrt_configure")
load("//third_party/dlib:workspace.bzl", dlib = "repo")

#########################################################################################
# 其他工具和框架
#########################################################################################

load("//third_party/ffmpeg:workspace.bzl", ffmpeg = "repo")

def initialize_third_party():
    """ Load third party repositories.  See above load() statements. """

    # boost()
    # bluez()
    curl()
    # geos()
    # gdal()
    # spatialite()
    # mqtt()
    # mq()
    cpplint()
    cuda()

    # civetweb()
    dlib()
    fastrtps()
    ffmpeg()
    gflags()
    glog()

    # gtest()
    nlohmann_json()
    opencv()
    poco()

    # proj4()
    protobuf()
    qt5()

    # sqlite3()
    # tinyxml2()
    uuid()
    # yaml_cpp()
    # bt()

# Define all external repositories required by
def apollo_repositories():
    cuda_configure(name = "local_config_cuda")
    # tensorrt_configure(name = "local_config_tensorrt")
    # python_configure(name = "local_config_python")
    # vtk_configure(name = "local_config_vtk")
    # pcl_configure(name = "local_config_pcl")

    initialize_third_party()
