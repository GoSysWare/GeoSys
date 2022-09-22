

#include <iostream>
#include "cyber/cyber.h"
#include "modules/action/server/simple_action_server.h"

#include "test/test_modules/LiftAction.pb.h"
          
using namespace apollo::cyber;

using namespace apollo::cyber::proto;

using namespace apollo::actionlib;

using user::proto::LiftAction;

typedef std::shared_ptr<LiftAction::Goal const> LiftActionGoalConstPtr;

std::shared_ptr<SimpleActionServer<LiftAction>> server;


void doAction(const LiftActionGoalConstPtr & g)
{
    std::cout << "doAction"<<std::endl;
    LiftAction::Feedback  p;
    p.set_c(11);

    server->publishFeedback(p);
    Rate rate(Duration(1.0));
    rate.Sleep();
    server->setSucceeded();
    // server->setAborted();
    // server->setPreempted();
  
    std::cout << "doAction done"<<std::endl;



    return ;

}
void doCancel()
{
    std::cout << "doCancel"<<std::endl;
}

int main(int argc, char *argv[])
{
    apollo::cyber::Init(argv[0]);
    FLAGS_v =4;
    std::shared_ptr<apollo::cyber::Node> node(apollo::cyber::CreateNode("lift_node"));

    std::function<void (const LiftActionGoalConstPtr &)> fun = doAction;

    server = std::make_shared<SimpleActionServer<LiftAction>>(node,"/lift/server",fun,false);
    server->registerPreemptCallback(doCancel);
    server->start();

     apollo::cyber::WaitForShutdown();

    return 0;
}