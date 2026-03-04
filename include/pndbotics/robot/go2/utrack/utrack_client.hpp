#ifndef __PND_ROBOT_GO2_UTRACK_CLIENT_HPP__
#define __PND_ROBOT_GO2_UTRACK_CLIENT_HPP__

#include <pndbotics/robot/client/client.hpp>

namespace pndbotics
{
namespace robot
{
namespace go2
{
class UtrackClient : public Client
{
 public:
     UtrackClient();
     ~UtrackClient();

     void Init();

     int32_t SwitchSet(bool enable);
     int32_t SwitchGet(bool& enable);
     int32_t IsTracking(bool& enable);
};
}
}
}

#endif//__PND_ROBOT_GO2_UTRACK_CLIENT_HPP__
