#include <pndbotics/common/dds/dds_callback.hpp>

namespace pndbotics
{
namespace common
{
DdsReaderCallback::DdsReaderCallback()
{}

DdsReaderCallback::DdsReaderCallback(const DdsMessageHandler& handler) :
    mMessageHandler(handler)
{}

DdsReaderCallback::DdsReaderCallback(const DdsReaderCallback& cb) :
    mMessageHandler(cb.mMessageHandler)
{}

DdsReaderCallback& DdsReaderCallback::operator=(const DdsReaderCallback& cb)
{
    if (this != &cb)
    {
        mMessageHandler = cb.mMessageHandler;
    }
    return *this;
}

DdsReaderCallback::~DdsReaderCallback()
{}

bool DdsReaderCallback::HasMessageHandler() const
{
    return (bool)mMessageHandler;
}

void DdsReaderCallback::OnDataAvailable(const void* message)
{
    if (mMessageHandler)
    {
        mMessageHandler(message);
    }
}

}
}
