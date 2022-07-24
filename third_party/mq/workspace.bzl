"""Loads the rabbitmq library"""


def clean_dep(dep):
    return str(Label(dep))

def repo():
    native.new_local_repository(
        name = "rabbitmq",
        build_file = clean_dep("//third_party/mq:rabbitmq.BUILD"),
        path = "/usr/local/include",
    )
