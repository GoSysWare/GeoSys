"""Loads the bluez library"""

# 蓝牙模块
def clean_dep(dep):
    return str(Label(dep))

def repo():
    native.new_local_repository(
        name = "bluez",
        build_file = clean_dep("//third_party/bluez:bluez.BUILD"),
        path = "/usr/include",
    )
