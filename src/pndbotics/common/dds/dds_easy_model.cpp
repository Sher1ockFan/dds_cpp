#include <pndbotics/common/dds/dds_easy_model.hpp>

namespace pndbotics
{
namespace common
{
DdsEasyModel::DdsEasyModel()
{
    mLogger = nullptr;
}

DdsEasyModel::~DdsEasyModel()
{}

void DdsEasyModel::Init(uint32_t domainId)
{
    mDdsParameter = DdsParameter();
    mChannelMap.clear();
    mPublisherList.clear();
    mSubscriberList.clear();
    mPublisherDefault.reset();
    mSubscriberDefault.reset();

    mParticipant.reset(new DdsParticipant(domainId, DdsParticipantQos(), ""));
}

void DdsEasyModel::Init(const std::string& ddsParameterFileName)
{
    std::string fileName = ddsParameterFileName.empty() ? PND_DDS_PARAMETER_CONFIG_FILENAME : ddsParameterFileName;
    PND_THROW(CommonException, std::string("Init from file is not supported in source-only mode. file:") + fileName);
}

void DdsEasyModel::Init(const JsonMap& param)
{
    mDdsParameter.Init(param);

    mChannelMap.clear();
    mPublisherList.clear();
    mSubscriberList.clear();
    mPublisherDefault.reset();
    mSubscriberDefault.reset();

    DdsParticipantQos participantQos;
    Realize(mDdsParameter.GetParticipantQos(), participantQos);
    mParticipant.reset(new DdsParticipant(mDdsParameter.GetDomainId(), participantQos, mDdsParameter.GetConfig()));

    for (const auto& publisherParam : mDdsParameter.GetPublisher())
    {
        DdsPublisherQos publisherQos;
        Realize(mDdsParameter.GetPublisherQos(), publisherQos);
        Realize(publisherParam.GetQos(), publisherQos);
        mPublisherList.push_back(DdsPublisherPtr(new DdsPublisher(mParticipant, publisherQos)));
    }

    for (const auto& subscriberParam : mDdsParameter.GetSubscriber())
    {
        DdsSubscriberQos subscriberQos;
        Realize(mDdsParameter.GetSubscriberQos(), subscriberQos);
        Realize(subscriberParam.GetQos(), subscriberQos);
        mSubscriberList.push_back(DdsSubscriberPtr(new DdsSubscriber(mParticipant, subscriberQos)));
    }
}

bool DdsEasyModel::WriteMessage(const std::string topic, const void* message, int64_t waitMicrosec)
{
    DdsTopicChannelAbstractPtr channel = GetChannel(topic);
    if (!channel)
    {
        return false;
    }

    return channel->Write(message, waitMicrosec);
}

int64_t DdsEasyModel::GetLastDataAvailableTime(const std::string topic)
{
    DdsTopicChannelAbstractPtr channel = GetChannel(topic);
    if (!channel)
    {
        return -1;
    }

    return channel->GetLastDataAvailableTime();
}

void DdsEasyModel::GetTopicQos(const std::string& topic, DdsTopicQos& qos)
{
    Realize(mDdsParameter.GetTopicQos(), qos);

    const auto& topicMap = mDdsParameter.GetTopic();
    auto it = topicMap.find(topic);
    if (it != topicMap.end())
    {
        Realize(it->second.GetQos(), qos);
    }
}

void DdsEasyModel::GetWriterQos(const std::string& topic, DdsWriterQos& qos)
{
    Realize(mDdsParameter.GetWriterQos(), qos);

    for (const auto& publisherParam : mDdsParameter.GetPublisher())
    {
        for (const auto& writerParam : publisherParam.GetWriter())
        {
            if (writerParam.GetTopicName() == topic)
            {
                Realize(writerParam.GetQos(), qos);
            }
        }
    }
}

void DdsEasyModel::GetReaderQos(const std::string& topic, DdsReaderQos& qos)
{
    Realize(mDdsParameter.GetReaderQos(), qos);

    for (const auto& subscriberParam : mDdsParameter.GetSubscriber())
    {
        for (const auto& readerParam : subscriberParam.GetReader())
        {
            if (readerParam.GetTopicName() == topic)
            {
                Realize(readerParam.GetQos(), qos);
            }
        }
    }
}

DdsTopicChannelAbstractPtr DdsEasyModel::GetChannel(const std::string& topic)
{
    auto it = mChannelMap.find(topic);
    if (it == mChannelMap.end())
    {
        return DdsTopicChannelAbstractPtr();
    }

    return it->second;
}

DdsSubscriberPtr DdsEasyModel::GetSubscriber(const std::string& topic)
{
    const auto& subscribers = mDdsParameter.GetSubscriber();
    for (size_t i = 0; i < subscribers.size() && i < mSubscriberList.size(); ++i)
    {
        for (const auto& readerParam : subscribers[i].GetReader())
        {
            if (readerParam.GetTopicName() == topic)
            {
                return mSubscriberList[i];
            }
        }
    }

    return GetSubscriberDefault();
}

DdsSubscriberPtr DdsEasyModel::GetSubscriberDefault()
{
    if (!mSubscriberDefault)
    {
        DdsSubscriberQos qos;
        Realize(mDdsParameter.GetSubscriberQos(), qos);
        mSubscriberDefault.reset(new DdsSubscriber(mParticipant, qos));
    }

    return mSubscriberDefault;
}

DdsPublisherPtr DdsEasyModel::GetPublisher(const std::string& topic)
{
    const auto& publishers = mDdsParameter.GetPublisher();
    for (size_t i = 0; i < publishers.size() && i < mPublisherList.size(); ++i)
    {
        for (const auto& writerParam : publishers[i].GetWriter())
        {
            if (writerParam.GetTopicName() == topic)
            {
                return mPublisherList[i];
            }
        }
    }

    return GetPublisherDefault();
}

DdsPublisherPtr DdsEasyModel::GetPublisherDefault()
{
    if (!mPublisherDefault)
    {
        DdsPublisherQos qos;
        Realize(mDdsParameter.GetPublisherQos(), qos);
        mPublisherDefault.reset(new DdsPublisher(mParticipant, qos));
    }

    return mPublisherDefault;
}

}
}
