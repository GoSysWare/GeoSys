
#ifndef CYBER_ACTIONLIB__GOAL_ID_GENERATOR_H_
#define CYBER_ACTIONLIB__GOAL_ID_GENERATOR_H_

#include "modules/common/proto/action.pb.h"


using apollo::common::proto::GoalID;

namespace apollo {
namespace actionlib
{

class  GoalIDGenerator
{
public:
  /**
   * Create a generator that prepends the fully qualified node name to the Goal ID
   */
  GoalIDGenerator();

  /**
   * \param name Unique name to prepend to the goal id. This will
   *             generally be a fully qualified node name.
   */
  GoalIDGenerator(const std::string & name);

  /**
   * \param name Set the name to prepend to the goal id. This will
   *             generally be a fully qualified node name.
   */
  void setName(const std::string & name);

  /**
   * \brief Generates a unique ID
   * \return A unique GoalID for this action
   */
  GoalID generateID();

private:
  std::string name_;
};

}  // namespace actionlib
}

#endif  // ACTIONLIB__GOAL_ID_GENERATOR_H_
