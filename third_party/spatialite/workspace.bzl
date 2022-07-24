"""Loads the Spatialite library"""

def clean_dep(dep):
    return str(Label(dep))

def repo():
    # spatialite
    native.new_local_repository(
        name = "spatialite",
        build_file = clean_dep("//third_party/spatialite:spatialite.BUILD"),
        path = "/usr/local/include",
    )
