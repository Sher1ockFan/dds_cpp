#ifndef __PND_ROBOT_H1_LOCO_ERROR_HPP__
#define __PND_ROBOT_H1_LOCO_ERROR_HPP__

#include <pndbotics/common/decl.hpp>

namespace pndbotics {
namespace robot {
namespace h1 {
PND_DECL_ERR(PND_ROBOT_LOCO_ERR_LOCOSTATE_NOT_AVAILABLE, 8301, "LocoState not available.")
PND_DECL_ERR(PND_ROBOT_LOCO_ERR_INVALID_FSM_ID, 8302, "Invalid fsm id.")
PND_DECL_ERR(PND_ROBOT_LOCO_ERR_ODOMSTATE_NOT_AVAILABLE, 8303, "OdomState not available.")
PND_DECL_ERR(PND_ROBOT_LOCO_ERR_INVALID_TASK_ID, 8304, "Invalid task id.")
}  // namespace h1
}  // namespace robot
}  // namespace pndbotics

#endif // __PND_ROBOT_H1_LOCO_ERROR_HPP__
