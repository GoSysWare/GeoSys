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
load("//third_party/gtest:workspace.bzl", gtest = "repo")
load("//third_party/gflags:workspace.bzl", gflags = "repo")
load("//third_party/cpplint:workspace.bzl", cpplint = "repo")


#########################################################################################
# 开发应用的功能基础库、框架、中间件
#########################################################################################
load("//third_party/boost:workspace.bzl", boost = "repo")
load("//third_party/civetweb:workspace.bzl", civetweb = "repo")
load("//third_party/fastrtps:workspace.bzl", fastrtps = "repo")

load("//third_party/nlohmann_json:workspace.bzl", nlohmann_json = "repo")
load("//third_party/poco:workspace.bzl", poco = "repo")
load("//third_party/sqlite3:workspace.bzl", sqlite3 = "repo")
load("//third_party/tinyxml2:workspace.bzl", tinyxml2 = "repo")
load("//third_party/uuid:workspace.bzl", uuid = "repo")
load("//third_party/yaml_cpp:workspace.bzl", yaml_cpp = "repo")
load("//third_party/mq:workspace.bzl", mq = "repo")
load("//third_party/behaviortree:workspace.bzl", bt = "repo")



#########################################################################################
# 图像处理、点云、地图功能库
#########################################################################################

load("//third_party/opencv:workspace.bzl", opencv = "repo")
load("//third_party/geos:workspace.bzl", geos = "repo")
load("//third_party/gdal:workspace.bzl", gdal = "repo")
load("//third_party/spatialite:workspace.bzl", spatialite = "repo")
# load("//third_party/vtk:vtk_configure.bzl", "vtk_configure")
# load("//third_party/pcl:pcl_configure.bzl", "pcl_configure")

#########################################################################################
# 数学计算库
#########################################################################################
# load("//third_party/osqp:workspace.bzl", osqp = "repo")
load("//third_party/proj4:workspace.bzl", proj4 = "repo")
# load("//third_party/qpOASES:workspace.bzl", qpOASES = "repo")
# load("//third_party/tf2:workspace.bzl", tf2 = "repo")


#########################################################################################
# 人工智能框架和工具
#########################################################################################
load("//third_party/gpus:cuda_configure.bzl", "cuda_configure")
# load("//third_party/tensorrt:tensorrt_configure.bzl", "tensorrt_configure")


#########################################################################################
# 硬件 协议 驱动
#########################################################################################
load("//third_party/mqtt:workspace.bzl", mqtt = "repo")
load("//third_party/bluez:workspace.bzl", bluez = "repo")

#########################################################################################
# 其他工具和框架
#########################################################################################

load("//third_party/ffmpeg:workspace.bzl", ffmpeg = "repo")






def initialize_third_party():
    """ Load third party repositories.  See above load() statements. """

    # boost()
    # bluez()
    # geos()
    # gdal()
    # spatialite()
    # mqtt()
    # mq()
    cpplint()
    # civetweb()
    fastrtps()
    ffmpeg()
    gflags()
    glog()
    # gtest()
    # nlohmann_json()
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