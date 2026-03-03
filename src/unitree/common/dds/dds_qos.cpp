#include <unitree/common/dds/dds_qos.hpp>

namespace unitree
{
namespace common
{
#define UT_DDS_QOS_IMPL(QosType) \
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

UT_DDS_QOS_IMPL(DdsParticipantQos)
UT_DDS_QOS_IMPL(DdsTopicQos)
UT_DDS_QOS_IMPL(DdsPublisherQos)
UT_DDS_QOS_IMPL(DdsSubscriberQos)
UT_DDS_QOS_IMPL(DdsWriterQos)
UT_DDS_QOS_IMPL(DdsReaderQos)

#undef UT_DDS_QOS_IMPL

}
}
