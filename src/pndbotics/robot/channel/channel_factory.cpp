#include <pndbotics/robot/channel/channel_factory.hpp>

namespace pndbotics
{
namespace robot
{
ChannelFactory::ChannelFactory()
    : mInited(false), mDdsFactoryPtr(nullptr)
{}

ChannelFactory::~ChannelFactory()
{
    Release();
}

void ChannelFactory::Init(int32_t domainId, const std::string& networkInterface)
{
    (void)networkInterface;
    common::LockGuard<common::Mutex> lock(mMutex);
    if (mInited && mDdsFactoryPtr)
    {
        return;
    }

    mDdsFactoryPtr = std::make_shared<common::DdsFactoryModel>();
    mDdsFactoryPtr->Init(static_cast<uint32_t>(domainId));
    mInited = true;
}

void ChannelFactory::Init(const std::string& configFileName)
{
    common::LockGuard<common::Mutex> lock(mMutex);
    if (mInited && mDdsFactoryPtr)
    {
        return;
    }

    mDdsFactoryPtr = std::make_shared<common::DdsFactoryModel>();
    mDdsFactoryPtr->Init(configFileName);
    mInited = true;
}

void ChannelFactory::Init(const common::JsonMap& jsonMap)
{
    common::LockGuard<common::Mutex> lock(mMutex);
    if (mInited && mDdsFactoryPtr)
    {
        return;
    }

    mDdsFactoryPtr = std::make_shared<common::DdsFactoryModel>();
    mDdsFactoryPtr->Init(jsonMap);
    mInited = true;
}

void ChannelFactory::Release()
{
    common::LockGuard<common::Mutex> lock(mMutex);
    mDdsFactoryPtr.reset();
    mInited = false;
}

}
}
