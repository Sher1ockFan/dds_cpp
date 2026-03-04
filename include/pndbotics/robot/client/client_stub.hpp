#ifndef __PND_ROBOT_SDK_CLIENT_STUB_HPP__
#define __PND_ROBOT_SDK_CLIENT_STUB_HPP__

#include <pndbotics/robot/future/request_future.hpp>
#include <pndbotics/robot/channel/channel_labor.hpp>
#include <pndbotics/common/block_queue.hpp>

namespace pndbotics
{
namespace robot
{
class ClientStub
{
public:
    explicit ClientStub();
    ~ClientStub();

    void Init(const std::string& name);

    bool Send(const Request& req, int64_t waitTimeout);
    RequestFuturePtr SendRequest(const Request& req, int64_t waitTimeout);

private:
    void ResponseFunc(const void* message);

private:
    ChannelLaborPtr<Request,Response> mChannelLaborPtr;
    RequestFutureQueuePtr mFutureQueuePtr;
};

using ClientStubPtr = std::shared_ptr<ClientStub>;

}
}

#endif//__PND_ROBOT_SDK_CLIENT_STUB_HPP__
