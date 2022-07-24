"""Loads the GOES library"""

def clean_dep(dep):
    return str(Label(dep))

def repo():
    # geos
    native.new_local_repository(
        name = "geos",
        build_file = clean_dep("//third_party/geos:geos.BUILD"),
        path = "/usr/local/include/geos",
    )
