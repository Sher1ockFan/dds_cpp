#include <unitree/common/dds/dds_factory_model.hpp>
#include <unitree/common/dds/dds_qos_realize.hpp>

namespace unitree
{
namespace common
{
DdsFactoryModel::DdsFactoryModel()
{
    mLogger = nullptr;
}

DdsFactoryModel::~DdsFactoryModel()
{}

void DdsFactoryModel::Init(uint32_t domainId, const std::string& ddsConfig)
{
    mParticipantQos = DdsParticipantQos();
    mTopicQos = DdsTopicQos();
    mPublisherQos = DdsPublisherQos();
    mSubscriberQos = DdsSubscriberQos();
    mWriterQos = DdsWriterQos();
    mReaderQos = DdsReaderQos();

    mParticipant.reset(new DdsParticipant(domainId, mParticipantQos, ddsConfig));
    mPublisher.reset(new DdsPublisher(mParticipant, mPublisherQos));
    mSubscriber.reset(new DdsSubscriber(mParticipant, mSubscriberQos));
}

void DdsFactoryModel::Init(const std::string& ddsParameterFileName)
{
    UT_THROW(CommonException, std::string("Init from file is not supported in source-only mode. file:") + ddsParameterFileName);
}

void DdsFactoryModel::Init(const JsonMap& param)
{
    DdsParameter ddsParameter(param);

    mParticipantQos = DdsParticipantQos();
    mTopicQos = DdsTopicQos();
    mPublisherQos = DdsPublisherQos();
    mSubscriberQos = DdsSubscriberQos();
    mWriterQos = DdsWriterQos();
    mReaderQos = DdsReaderQos();

    Realize(ddsParameter.GetParticipantQos(), mParticipantQos);
    Realize(ddsParameter.GetTopicQos(), mTopicQos);
    Realize(ddsParameter.GetPublisherQos(), mPublisherQos);
    Realize(ddsParameter.GetSubscriberQos(), mSubscriberQos);
    Realize(ddsParameter.GetWriterQos(), mWriterQos);
    Realize(ddsParameter.GetReaderQos(), mReaderQos);

    mParticipant.reset(new DdsParticipant(ddsParameter.GetDomainId(), mParticipantQos, ddsParameter.GetConfig()));
    mPublisher.reset(new DdsPublisher(mParticipant, mPublisherQos));
    mSubscriber.reset(new DdsSubscriber(mParticipant, mSubscriberQos));
}

}
}
