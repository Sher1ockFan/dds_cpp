#include <pndbotics/common/dds/dds_qos.hpp>

namespace pndbotics
{
namespace common
{
#define PND_DDS_QOS_IMPL(QosType) \
void QosType::CopyToNativeQos(NativeQosType& qos) const \
{ \
    qos = mNative; \
} \
 \
void QosType::InitPolicyDefault() \
{ \
    mNative = NativeQosType(); \
    mPolicyNameSet.clear(); \
}

PND_DDS_QOS_IMPL(DdsParticipantQos)
PND_DDS_QOS_IMPL(DdsTopicQos)
PND_DDS_QOS_IMPL(DdsPublisherQos)
PND_DDS_QOS_IMPL(DdsSubscriberQos)
PND_DDS_QOS_IMPL(DdsWriterQos)
PND_DDS_QOS_IMPL(DdsReaderQos)

#undef PND_DDS_QOS_IMPL

}
}
