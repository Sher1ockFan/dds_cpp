#ifndef __PND_ROBOT_B2_ROBOT_STATE_CLIENT_ERROR_HPP__
#define __PND_ROBOT_B2_ROBOT_STATE_CLIENT_ERROR_HPP__

#include <pndbotics/common/decl.hpp>

namespace pndbotics
{
namespace robot
{
namespace b2
{
PND_DECL_ERR(PND_ROBOT_STATE_CLIENT_ERR_SERVICE_SWITCH,      5201,   "service switch error.")
PND_DECL_ERR(PND_ROBOT_STATE_CLIENT_ERR_SERVICE_PROTECTED,   5202,   "service is protected.")
PND_DECL_ERR(PND_ROBOT_STATE_CLIENT_ERR_LOWPOWER_SWITCH,     5203,   "low power switch error.")
PND_DECL_ERR(PND_ROBOT_STATE_CLIENT_ERR_LOWPOWER_STATE,      5204,   "low power state error.")
}
}
}

#endif//__PND_ROBOT_B2_ROBOT_STATE_CLIENT_ERROR_HPP__
