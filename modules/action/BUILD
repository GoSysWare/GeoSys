load("@rules_cc//cc:defs.bzl", "cc_library")
load("//tools:cpplint.bzl", "cpplint")

package(default_visibility = ["//visibility:public"])

cc_library(
    name = "action_server",
    srcs = [


    ],
    hdrs = [
        "server/status_tracker.h",
        "server/server_goal_handle.h",
        "server/action_server_base.h",
        "server/action_server.h",
        "server/handle_tracker_deleter.h",
        "server/simple_action_server.h",


    ],
    deps = [
        "//cyber",
        "//modules/common/proto:action_cc_proto",
        ":action",
    ],
)

cc_library(
    name = "action_client",
    srcs = [
        
    ],
    hdrs = [
        "client/terminal_state.h",
        "client/client_helpers.h",
        "client/comm_state.h",
        "client/connection_monitor.h",
        "client/action_client.h",
        "client/simple_action_client.h",
        "client/simple_goal_state.h",
        "client/simple_client_goal_state.h",
    ],
    deps = [
        "//cyber",
        "//modules/common/proto:action_cc_proto",
        ":action",
    ],
)
cc_library(
    name = "action",
    srcs = [
        "goal_id_generator.cc",
    ],
    hdrs = [
        "client_goal_status.h",
        "destruction_guard.h",
        "enclosure_deleter.h",
        "goal_id_generator.h",
        "action_definition.h",
        "managed_list.h",


    ],
    deps = [
        "//cyber",
        "//modules/common/proto:action_cc_proto",
    ],
)

# cpplint()
