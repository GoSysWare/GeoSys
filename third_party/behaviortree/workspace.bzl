"""Loads the boost library"""


def clean_dep(dep):
    return str(Label(dep))

def repo():
    native.new_local_repository(
        name = "behaviortree",
        build_file = clean_dep("//third_party/behaviortree:behaviortree.BUILD"),
        path = "/usr/include",
    )
