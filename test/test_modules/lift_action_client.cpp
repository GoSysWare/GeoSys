

#include "modules/action/client/simple_action_client.h"
#include "cyber/cyber.h"
#include <iostream>

#include "test/test_modules/LiftAction.pb.h"

using namespace apollo::cyber;

using namespace apollo::cyber::proto;
using namespace apollo::actionlib;
using user::proto::LiftAction;

typedef std::shared_ptr<LiftAction::Result const> ResultConstPtr;
typedef std::shared_ptr<LiftAction::Feedback const> FeedbackConstPtr;

void done_cb(const SimpleClientGoalState &state, const ResultConstPtr &result) {
  std::cout << "done_cb" << std::endl;
}

void active_cb() { std::cout << "active_cb" << std::endl; }
void feedback_cb(const FeedbackConstPtr &feedback) {
  std::cout << "feedback_cb" << std::endl;
}

int main(int argc, char *argv[]) {
  apollo::cyber::Init(argv[0]);
  FLAGS_v =4;

  std::shared_ptr<apollo::cyber::Node> node(
      apollo::cyber::CreateNode("lift_node_client"));

  auto client =
      std::make_shared<SimpleActionClient<LiftAction>>(node, "/lift/server");
  LiftAction::Goal g;
  g.set_a(10);

  bool c =  client->waitForServer(apollo::cyber::Duration(5.0));

  // SimpleClientGoalState f = client->sendGoalAndWait(g, apollo::cyber::Duration(5.0),
  //                                  apollo::cyber::Duration(3.0));

  client->sendGoal(g,done_cb,active_cb,feedback_cb);
  std::cout << "sendGoal" << std::endl;
   Rate rate(Duration(2.0));
    rate.Sleep();
  std::cout << "waitForResult " << client->waitForResult(Duration(3.0)) << std::endl;
  client->cancelAllGoals();
  std::cout << "cancelGoal" << std::endl;

  apollo::cyber::WaitForShutdown();

  return 0;
}