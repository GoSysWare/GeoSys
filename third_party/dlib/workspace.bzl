
def clean_dep(dep):
    return str(Label(dep))

def repo():
    native.new_local_repository(
        name = "dlib",
        build_file = clean_dep("//third_party/dlib:dlib.BUILD"),
        path = "/home/shuimujie/Works/dlib/install/include",
    )
