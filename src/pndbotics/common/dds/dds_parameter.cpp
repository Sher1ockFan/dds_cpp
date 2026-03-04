#include <pndbotics/common/dds/dds_parameter.hpp>

namespace pndbotics
{
namespace common
{
namespace
{
static bool GetMap(const JsonMap& in, const std::string& key, JsonMap& out)
{
    auto it = in.find(key);
    if (it == in.end() || it->second.Empty() || !IsJsonMap(it->second))
    {
        return false;
    }

    out = AnyCast<JsonMap>(it->second);
    return true;
}

static bool GetArray(const JsonMap& in, const std::string& key, JsonArray& out)
{
    auto it = in.find(key);
    if (it == in.end() || it->second.Empty() || !IsJsonArray(it->second))
    {
        return false;
    }

    out = AnyCast<JsonArray>(it->second);
    return true;
}

template<typename T>
static bool GetValue(const JsonMap& in, const std::string& key, T& out)
{
    auto it = in.find(key);
    if (it == in.end() || it->second.Empty())
    {
        return false;
    }

    out = AnyCast<T>(it->second);
    return true;
}

template<typename T>
static bool GetNumberValue(const JsonMap& in, const std::string& key, T& out)
{
    auto it = in.find(key);
    if (it == in.end() || it->second.Empty())
    {
        return false;
    }

    out = AnyNumberCast<T>(it->second);
    return true;
}
}

DdsQosParameterHolder::DdsQosParameterHolder()
{}

DdsQosParameterHolder::~DdsQosParameterHolder()
{}

void DdsQosParameterHolder::SetQos(const DdsQosParameter& qos)
{
    mQos = qos;
}

const DdsQosParameter& DdsQosParameterHolder::GetQos() const
{
    return mQos;
}

DdsParticipantParameter::DdsParticipantParameter() :
    mDomainId(0)
{}

DdsParticipantParameter::DdsParticipantParameter(uint32_t domainId, const std::string& config) :
    mDomainId(domainId), mConfig(config)
{}

DdsParticipantParameter::~DdsParticipantParameter()
{}

void DdsParticipantParameter::SetDomainId(int32_t domainId)
{
    mDomainId = (uint32_t)domainId;
}

uint32_t DdsParticipantParameter::GetDomainId() const
{
    return mDomainId;
}

void DdsParticipantParameter::SetConfig(const std::string& config)
{
    mConfig = config;
}

const std::string& DdsParticipantParameter::GetConfig() const
{
    return mConfig;
}

DdsTopicParameter::DdsTopicParameter()
{}

DdsTopicParameter::DdsTopicParameter(const std::string& name) :
    mName(name)
{}

DdsTopicParameter::~DdsTopicParameter()
{}

void DdsTopicParameter::SetName(const std::string& name)
{
    mName = name;
}

const std::string& DdsTopicParameter::GetName() const
{
    return mName;
}

DdsTopicParameterHolder::DdsTopicParameterHolder()
{}

DdsTopicParameterHolder::DdsTopicParameterHolder(const std::string& topicName) :
    mTopicName(topicName)
{}

DdsTopicParameterHolder::~DdsTopicParameterHolder()
{}

void DdsTopicParameterHolder::SetTopicName(const std::string& topicName)
{
    mTopicName = topicName;
}

const std::string& DdsTopicParameterHolder::GetTopicName() const
{
    return mTopicName;
}

DdsWriterParameter::DdsWriterParameter()
{}

DdsWriterParameter::DdsWriterParameter(const std::string& topicName) :
    DdsTopicParameterHolder(topicName)
{}

DdsWriterParameter::~DdsWriterParameter()
{}

DdsWriterParameterHolder::DdsWriterParameterHolder()
{}

DdsWriterParameterHolder::~DdsWriterParameterHolder()
{}

void DdsWriterParameterHolder::SetWriter(const DdsWriterParameter& writer)
{
    mWriter = writer;
}

const DdsWriterParameter& DdsWriterParameterHolder::GetWriter() const
{
    return mWriter;
}

DdsReaderParameter::DdsReaderParameter()
{}

DdsReaderParameter::DdsReaderParameter(const std::string& topicName) :
    DdsTopicParameterHolder(topicName)
{}

DdsReaderParameter::~DdsReaderParameter()
{}

DdsReaderParameterHolder::DdsReaderParameterHolder()
{}

DdsReaderParameterHolder::~DdsReaderParameterHolder()
{}

void DdsReaderParameterHolder::SetReader(const DdsReaderParameter& reader)
{
    mReader = reader;
}

const DdsReaderParameter& DdsReaderParameterHolder::GetReader() const
{
    return mReader;
}

DdsPublisherParameter::DdsPublisherParameter()
{}

DdsPublisherParameter::~DdsPublisherParameter()
{}

void DdsPublisherParameter::AppendWriter(const DdsWriterParameter& writer)
{
    mWriter.push_back(writer);
}

void DdsPublisherParameter::SetWriter(const std::vector<DdsWriterParameter>& writer)
{
    mWriter = writer;
}

const std::vector<DdsWriterParameter>& DdsPublisherParameter::GetWriter() const
{
    return mWriter;
}

DdsSubscriberParameter::DdsSubscriberParameter()
{}

DdsSubscriberParameter::~DdsSubscriberParameter()
{}

void DdsSubscriberParameter::AppendReader(const DdsReaderParameter& reader)
{
    mReader.push_back(reader);
}

void DdsSubscriberParameter::SetReader(const std::vector<DdsReaderParameter>& reader)
{
    mReader = reader;
}

const std::vector<DdsReaderParameter>& DdsSubscriberParameter::GetReader() const
{
    return mReader;
}

DdsParameter::DdsParameter() :
    mDomainId(0)
{}

DdsParameter::DdsParameter(const JsonMap& param) :
    DdsParameter()
{
    Init(param);
}

DdsParameter::~DdsParameter()
{}

void DdsParameter::Init(const JsonMap& param)
{
    mTopic.clear();
    mPublisher.clear();
    mSubscriber.clear();

    JsonMap participantMap;
    if (GetMap(param, PND_DDS_PARAM_KEY_PARTICIPANT, participantMap))
    {
        int32_t domainId = 0;
        GetNumberValue<int32_t>(participantMap, PND_DDS_PARAM_KEY_DOMAINID, domainId);
        mDomainId = (uint32_t)domainId;
        mParticipant.SetDomainId(domainId);

        std::string config;
        GetValue<std::string>(participantMap, PND_DDS_PARAM_KEY_CONFIG, config);
        mConfig = config;
        mParticipant.SetConfig(config);

        JsonMap qosMap;
        if (GetMap(participantMap, PND_DDS_PARAM_KEY_QOS, qosMap))
        {
            mParticipantQos.Init(qosMap);
            mParticipant.SetQos(mParticipantQos);
        }
    }

    JsonMap topicMap;
    if (GetMap(param, PND_DDS_PARAM_KEY_TOPIC, topicMap))
    {
        for (const auto& kv : topicMap)
        {
            if (kv.second.Empty() || !IsJsonMap(kv.second))
            {
                continue;
            }

            const JsonMap& oneTopicMap = AnyCast<JsonMap>(kv.second);
            DdsTopicParameter topicParam(kv.first);
            std::string name;
            if (GetValue<std::string>(oneTopicMap, PND_DDS_PARAM_KEY_NAME, name))
            {
                topicParam.SetName(name);
            }

            JsonMap qosMap;
            if (GetMap(oneTopicMap, PND_DDS_PARAM_KEY_QOS, qosMap))
            {
                DdsQosParameter qos;
                qos.Init(qosMap);
                topicParam.SetQos(qos);
                mTopicQos = qos;
            }

            mTopic[topicParam.GetName()] = topicParam;
        }
    }

    JsonArray publisherArray;
    if (GetArray(param, PND_DDS_PARAM_KEY_PUBLISHER, publisherArray))
    {
        for (const auto& pubAny : publisherArray)
        {
            if (pubAny.Empty() || !IsJsonMap(pubAny))
            {
                continue;
            }

            DdsPublisherParameter publisherParam;
            JsonMap onePubMap = AnyCast<JsonMap>(pubAny);

            JsonMap qosMap;
            if (GetMap(onePubMap, PND_DDS_PARAM_KEY_QOS, qosMap))
            {
                DdsQosParameter qos;
                qos.Init(qosMap);
                publisherParam.SetQos(qos);
                mPublisherQos = qos;
            }

            JsonArray writerArray;
            if (GetArray(onePubMap, PND_DDS_PARAM_KEY_WRITER, writerArray))
            {
                for (const auto& writerAny : writerArray)
                {
                    if (writerAny.Empty() || !IsJsonMap(writerAny))
                    {
                        continue;
                    }

                    JsonMap writerMap = AnyCast<JsonMap>(writerAny);
                    std::string topicName;
                    GetValue<std::string>(writerMap, PND_DDS_PARAM_KEY_TOPICNAME, topicName);

                    DdsWriterParameter writerParam(topicName);
                    JsonMap writerQosMap;
                    if (GetMap(writerMap, PND_DDS_PARAM_KEY_QOS, writerQosMap))
                    {
                        DdsQosParameter writerQos;
                        writerQos.Init(writerQosMap);
                        writerParam.SetQos(writerQos);
                        mWriterQos = writerQos;
                    }

                    publisherParam.AppendWriter(writerParam);
                }
            }

            mPublisher.push_back(publisherParam);
        }
    }

    JsonArray subscriberArray;
    if (GetArray(param, PND_DDS_PARAM_KEY_SUBSCRIBER, subscriberArray))
    {
        for (const auto& subAny : subscriberArray)
        {
            if (subAny.Empty() || !IsJsonMap(subAny))
            {
                continue;
            }

            DdsSubscriberParameter subscriberParam;
            JsonMap oneSubMap = AnyCast<JsonMap>(subAny);

            JsonMap qosMap;
            if (GetMap(oneSubMap, PND_DDS_PARAM_KEY_QOS, qosMap))
            {
                DdsQosParameter qos;
                qos.Init(qosMap);
                subscriberParam.SetQos(qos);
                mSubscriberQos = qos;
            }

            JsonArray readerArray;
            if (GetArray(oneSubMap, PND_DDS_PARAM_KEY_READER, readerArray))
            {
                for (const auto& readerAny : readerArray)
                {
                    if (readerAny.Empty() || !IsJsonMap(readerAny))
                    {
                        continue;
                    }

                    JsonMap readerMap = AnyCast<JsonMap>(readerAny);
                    std::string topicName;
                    GetValue<std::string>(readerMap, PND_DDS_PARAM_KEY_TOPICNAME, topicName);

                    DdsReaderParameter readerParam(topicName);
                    JsonMap readerQosMap;
                    if (GetMap(readerMap, PND_DDS_PARAM_KEY_QOS, readerQosMap))
                    {
                        DdsQosParameter readerQos;
                        readerQos.Init(readerQosMap);
                        readerParam.SetQos(readerQos);
                        mReaderQos = readerQos;
                    }

                    subscriberParam.AppendReader(readerParam);
                }
            }

            mSubscriber.push_back(subscriberParam);
        }
    }
}

uint32_t DdsParameter::GetDomainId()
{
    return mDomainId;
}

const std::string& DdsParameter::GetConfig() const
{
    return mConfig;
}

const DdsParticipantParameter& DdsParameter::GetParticipant()
{
    return mParticipant;
}

void DdsParameter::AppendTopic(const DdsTopicParameter& topic)
{
    mTopic[topic.GetName()] = topic;
}

const std::map<std::string,DdsTopicParameter>& DdsParameter::GetTopic() const
{
    return mTopic;
}

void DdsParameter::AppendPublisher(const DdsPublisherParameter& publisher)
{
    mPublisher.push_back(publisher);
}

void DdsParameter::SetPublisher(const std::vector<DdsPublisherParameter>& publisher)
{
    mPublisher = publisher;
}

const std::vector<DdsPublisherParameter>& DdsParameter::GetPublisher() const
{
    return mPublisher;
}

void DdsParameter::AppendSubscriber(const DdsSubscriberParameter& subscriber)
{
    mSubscriber.push_back(subscriber);
}

void DdsParameter::SetSubscriber(const std::vector<DdsSubscriberParameter>& subscriber)
{
    mSubscriber = subscriber;
}

const std::vector<DdsSubscriberParameter>& DdsParameter::GetSubscriber() const
{
    return mSubscriber;
}

const DdsQosParameter& DdsParameter::GetParticipantQos() const
{
    return mParticipantQos;
}

const DdsQosParameter& DdsParameter::GetTopicQos() const
{
    return mTopicQos;
}

const DdsQosParameter& DdsParameter::GetPublisherQos() const
{
    return mPublisherQos;
}

const DdsQosParameter& DdsParameter::GetSubscriberQos() const
{
    return mSubscriberQos;
}

const DdsQosParameter& DdsParameter::GetWriterQos() const
{
    return mWriterQos;
}

const DdsQosParameter& DdsParameter::GetReaderQos() const
{
    return mReaderQos;
}

}
}
