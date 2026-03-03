#include <unitree/common/dds/dds_entity.hpp>

namespace unitree
{
namespace common
{
DdsLogger::DdsLogger()
{
    mLogger = nullptr;
}

DdsLogger::~DdsLogger()
{}

DdsParticipant::DdsParticipant(uint32_t domainId, const DdsParticipantQos& qos, const std::string& config) :
    mNative(__UT_DDS_NULL__)
{
    UT_DDS_EXCEPTION_TRY

    auto participantQos = ::dds::domain::qos::DomainParticipantQos();
    qos.CopyToNativeQos(participantQos);

    if (config.empty())
    {
        mNative = NATIVE_TYPE(domainId, participantQos);
    }
    else
    {
        mNative = NATIVE_TYPE(
            domainId,
            participantQos,
            nullptr,
            ::dds::core::status::StatusMask::none(),
            config);
    }

    UT_DDS_EXCEPTION_CATCH(mLogger, true)
}

DdsParticipant::~DdsParticipant()
{
    mNative = __UT_DDS_NULL__;
}

const DdsParticipant::NATIVE_TYPE& DdsParticipant::GetNative() const
{
    return mNative;
}

DdsPublisher::DdsPublisher(const DdsParticipantPtr& participant, const DdsPublisherQos& qos) :
    mNative(__UT_DDS_NULL__)
{
    UT_DDS_EXCEPTION_TRY

    auto publisherQos = participant->GetNative().default_publisher_qos();
    qos.CopyToNativeQos(publisherQos);

    mNative = NATIVE_TYPE(participant->GetNative(), publisherQos);

    UT_DDS_EXCEPTION_CATCH(mLogger, true)
}

DdsPublisher::~DdsPublisher()
{
    mNative = __UT_DDS_NULL__;
}

const DdsPublisher::NATIVE_TYPE& DdsPublisher::GetNative() const
{
    return mNative;
}

DdsSubscriber::DdsSubscriber(const DdsParticipantPtr& participant, const DdsSubscriberQos& qos) :
    mNative(__UT_DDS_NULL__)
{
    UT_DDS_EXCEPTION_TRY

    auto subscriberQos = participant->GetNative().default_subscriber_qos();
    qos.CopyToNativeQos(subscriberQos);

    mNative = NATIVE_TYPE(participant->GetNative(), subscriberQos);

    UT_DDS_EXCEPTION_CATCH(mLogger, true)
}

DdsSubscriber::~DdsSubscriber()
{
    mNative = __UT_DDS_NULL__;
}

const DdsSubscriber::NATIVE_TYPE& DdsSubscriber::GetNative() const
{
    return mNative;
}

}
}
