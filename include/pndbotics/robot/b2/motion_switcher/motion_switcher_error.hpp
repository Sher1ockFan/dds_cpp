#ifndef __PND_ROBOT_B2_MOTION_SWITCHER_ERROR_HPP__
#define __PND_ROBOT_B2_MOTION_SWITCHER_ERROR_HPP__

#include <pndbotics/common/decl.hpp>

namespace pndbotics
{
namespace robot
{
namespace b2
{
    PND_DECL_ERR(PND_SWITCH_ERR_PARAMETR,         7001,  "parameter is invalid.")
    PND_DECL_ERR(PND_SWITCH_ERR_BUSY,             7002,  "switcher is busy.")
    PND_DECL_ERR(PND_SWITCH_ERR_EVENT,            7003,  "event is invalid.")
    PND_DECL_ERR(PND_SWITCH_ERR_NAME,             7004,  "name or alias is invalid.")
    PND_DECL_ERR(PND_SWITCH_ERR_CMD,              7005,  "name or alias is invalid.")
    PND_DECL_ERR(PND_SWITCH_ERR_EXEC_CHECK,       7006,  "check cmd execute error.")
    PND_DECL_ERR(PND_SWITCH_ERR_EXEC_SELECT,      7007,  "select cmd execute error.")
    PND_DECL_ERR(PND_SWITCH_ERR_EXEC_RELEASE,     7008,  "release cmd execute error.")
    PND_DECL_ERR(PND_SWITCH_ERR_CUSTOMIZE,        7009,  "save customize data error.")
}
}
}

#endif//__PND_ROBOT_B2_MOTION_SWITCHER_ERROR_HPP__
