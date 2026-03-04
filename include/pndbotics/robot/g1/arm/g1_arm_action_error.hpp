#pragma once

#include <pndbotics/common/decl.hpp>

namespace pndbotics {
namespace robot {
namespace g1 {

PND_DECL_ERR(PND_ROBOT_ARM_ACTION_ERR_ARMSDK, 7400, "The topic rt/armsdk is occupied.")
PND_DECL_ERR(PND_ROBOT_ARM_ACTION_ERR_HOLDING, 7401, "The arm is holding. Expecting release action(99) or the same last action id.")
PND_DECL_ERR(PND_ROBOT_ARM_ACTION_ERR_INVALID_ACTION_ID, 7402, "Invalid action id.")
// The actions are only supported in fsm id {500, 501, 801};
// You can subscribe the topic rt/sportmodestate to check the fsm id.
// And in the state 801, the actions are only supported in the fsm mode {0, 3}.
// See https://support.pndbotics.com/home/en/G1_developer/sport_services_interface#Expert%20interface
PND_DECL_ERR(PND_ROBOT_ARM_ACTION_ERR_INVALID_FSM_ID, 7404, "Invalid fsm id.")

}  // namespace g1
}  // namespace robot
}  // namespace pndbotics