"""Loads the GOES library"""

def clean_dep(dep):
    return str(Label(dep))

def repo():
    # gdal
    native.new_local_repository(
        name = "gdal",
        build_file = clean_dep("//third_party/gdal:gdal.BUILD"),
        path = "/usr/local/include",
    )
