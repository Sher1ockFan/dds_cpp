#ifndef __PND_ROBOT_SDK_INERNAL_HPP__
#define __PND_ROBOT_SDK_INERNAL_HPP__

#include <pndbotics/robot/internal/internal_api.hpp>
#include <pndbotics/robot/internal/internal_error.hpp>
#include <pndbotics/robot/internal/internal_request_response.hpp>

namespace pndbotics
{
namespace robot
{
using RequestPtr = std::shared_ptr<Request>;
using ResponsePtr = std::shared_ptr<Response>;
}
}

#endif//__PND_ROBOT_SDK_INERNAL_HPP__
