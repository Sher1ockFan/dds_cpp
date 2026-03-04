#ifndef __PND_ROBOT_G1_AGV_ERROR_HPP__
#define __PND_ROBOT_G1_AGV_ERROR_HPP__

#include <pndbotics/common/decl.hpp>

namespace pndbotics
{
namespace robot
{
namespace g1
{

PND_DECL_ERR(PND_ROBOT_G1_AGV_ERR_NOT_INIT,   9101,   "Module not initialized.")
PND_DECL_ERR(PND_ROBOT_G1_AGV_ERR_EXEC_MOVE,   9102,   "Failed to execute move command.")
PND_DECL_ERR(PND_ROBOT_G1_AGV_ERR_EXEC_HEIGHT_ADJUST,   9103,   "Failed to execute height adjust command.")

}
}
}

#endif // __PND_ROBOT_G1_AGV_ERROR_HPP__
