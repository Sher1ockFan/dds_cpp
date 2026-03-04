#ifndef __PND_ROBOT_G1_LOCO_ERROR_HPP__
#define __PND_ROBOT_G1_LOCO_ERROR_HPP__

#include <pndbotics/common/decl.hpp>

namespace pndbotics {
namespace robot {
namespace g1 {
PND_DECL_ERR(PND_ROBOT_LOCO_ERR_LOCOSTATE_NOT_AVAILABLE, 7301,
            "LocoState not available.")
PND_DECL_ERR(PND_ROBOT_LOCO_ERR_INVALID_FSM_ID, 7302, "Invalid fsm id.")
PND_DECL_ERR(PND_ROBOT_LOCO_ERR_INVALID_TASK_ID, 7303, "Invalid task id.")
} // namespace g1
} // namespace robot
} // namespace pndbotics

#endif // __PND_ROBOT_G1_LOCO_ERROR_HPP__
