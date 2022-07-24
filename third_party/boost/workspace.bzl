"""Loads the boost library"""


def clean_dep(dep):
    return str(Label(dep))

def repo():
    native.new_local_repository(
        name = "boost",
        build_file = clean_dep("//third_party/boost:boost.BUILD"),
        path = "/usr/include",
    )
