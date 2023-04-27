def clean_dep(dep):
    return str(Label(dep))

def repo():
    native.new_local_repository(
        name = "cuda",
        build_file = clean_dep("//third_party/cuda:cuda.BUILD"),
        path = "/usr/local/cuda/include",
    )
