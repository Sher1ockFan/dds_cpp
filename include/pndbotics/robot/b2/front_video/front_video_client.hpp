#ifndef __PND_ROBOT_B2_FRONT_VIDEO_CLIENT_HPP__
#define __PND_ROBOT_B2_FRONT_VIDEO_CLIENT_HPP__

#include <pndbotics/robot/client/client.hpp>

namespace pndbotics
{
namespace robot
{
namespace b2
{
/*
 * FrontVideoClient
 */
class FrontVideoClient : public Client
{
public:
    explicit FrontVideoClient();
    ~FrontVideoClient();

    void Init();

    /*
     * @brief GetImageSample
     * @api: 1001
     */
    int32_t GetImageSample(std::vector<uint8_t>&);

};
}
}
}

#endif//__PND_ROBOT_B2_FRONT_VIDEO_CLIENT_HPP__
