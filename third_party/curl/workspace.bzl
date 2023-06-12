def clean_dep(dep):
    return str(Label(dep))

def repo():
    native.new_local_repository(
        name = "curl",
        build_file = clean_dep("//third_party/curl:curl.BUILD"),
        path = "/usr/include/x86_64-linux-gnu",
    )
