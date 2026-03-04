#ifndef __PND_ROBOT_GO2_VIDEO_CLIENT_HPP__
#define __PND_ROBOT_GO2_VIDEO_CLIENT_HPP__

#include <pndbotics/robot/client/client.hpp>

namespace pndbotics
{
namespace robot
{
namespace go2
{
/*
 * VideoClient
 */
class VideoClient : public Client
{
public:
    explicit VideoClient();
    ~VideoClient();

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

#endif//__PND_ROBOT_GO2_VIDEO_CLIENT_HPP__
