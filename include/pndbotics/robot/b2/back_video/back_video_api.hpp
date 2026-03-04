#ifndef __PND_ROBOT_B2_BACK_VIDEO_API_HPP__
#define __PND_ROBOT_B2_BACK_VIDEO_API_HPP__

#include <pndbotics/common/json/jsonize.hpp>

namespace pndbotics
{
namespace robot
{
namespace b2
{
/*service name*/
const std::string ROBOT_BACK_VIDEO_SERVICE_NAME = "back_videohub";

/*api version*/
const std::string ROBOT_BACK_VIDEO_API_VERSION = "1.0.0.0";

/*api id*/
const int32_t ROBOT_BACK_VIDEO_API_ID_GETIMAGESAMPLE       = 1001;
}
}
}

#endif //__PND_ROBOT_B2_BACK_VIDEO_API_HPP__
