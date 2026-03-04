#ifndef __PND_DDS_CALLBACK_HPP__
#define __PND_DDS_CALLBACK_HPP__

#include <pndbotics/common/decl.hpp>

using DdsMessageHandler = std::function<void(const void*)>;

namespace pndbotics
{
namespace common
{
class DdsReaderCallback
{
public:
    DdsReaderCallback();
    DdsReaderCallback(const DdsMessageHandler& handler);
    DdsReaderCallback(const DdsReaderCallback& cb);
    DdsReaderCallback& operator=(const DdsReaderCallback& cb);

    ~DdsReaderCallback();

public:
    bool HasMessageHandler() const;
    void OnDataAvailable(const void* message);

private:
    DdsMessageHandler mMessageHandler;
};

using DdsReaderCallbackPtr = std::shared_ptr<DdsReaderCallback>;

}
}

#endif//__PND_DDS_CALLBACK_HPP__
