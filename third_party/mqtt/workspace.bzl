"""Loads the GOES library"""

def clean_dep(dep):
    return str(Label(dep))

def repo():
    # mqtt
    native.new_local_repository(
        name = "paho",
        build_file = clean_dep("//third_party/mqtt:paho.BUILD"),
        path = "/usr/local/include",
    )
