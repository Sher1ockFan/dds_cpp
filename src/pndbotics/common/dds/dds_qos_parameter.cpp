#include <pndbotics/common/dds/dds_qos_parameter.hpp>

namespace pndbotics
{
namespace common
{
namespace
{
template<typename POLICY>
static bool InitPolicyIfExists(const JsonMap& data, const std::string& key, POLICY& policy)
{
    auto it = data.find(key);
    if (it == data.end() || it->second.Empty() || !IsJsonMap(it->second))
    {
        return false;
    }

    policy.Init(AnyCast<JsonMap>(it->second));
    return !policy.Default();
}
}

DdsQosParameter::DdsQosParameter() :
    mDefault(true)
{}

DdsQosParameter::~DdsQosParameter()
{}

void DdsQosParameter::Init(const JsonMap& data)
{
    mDefault = true;

    bool changed = false;
    changed |= InitPolicyIfExists(data, PND_DDS_QOS_POLICY_NAME_DEADLINE, mDeadline);
    changed |= InitPolicyIfExists(data, PND_DDS_QOS_POLICY_NAME_DESTINATION_ORDER, mDestinationOrder);
    changed |= InitPolicyIfExists(data, PND_DDS_QOS_POLICY_NAME_DURABILITY, mDurability);
    changed |= InitPolicyIfExists(data, PND_DDS_QOS_POLICY_NAME_DURABILITY_SERVICE, mDurabilityService);
    changed |= InitPolicyIfExists(data, PND_DDS_QOS_POLICY_NAME_ENTITY_FACTORY, mEntityFactory);
    changed |= InitPolicyIfExists(data, PND_DDS_QOS_POLICY_NAME_GROUP_DATA, mGroupData);
    changed |= InitPolicyIfExists(data, PND_DDS_QOS_POLICY_NAME_HISTORY, mHistory);
    changed |= InitPolicyIfExists(data, PND_DDS_QOS_POLICY_NAME_LATENCY_BUDGET, mLatencyBudget);
    changed |= InitPolicyIfExists(data, PND_DDS_QOS_POLICY_NAME_LIFESPAN, mLifespan);
    changed |= InitPolicyIfExists(data, PND_DDS_QOS_POLICY_NAME_LIVELINESS, mLiveliness);
    changed |= InitPolicyIfExists(data, PND_DDS_QOS_POLICY_NAME_OWNERSHIP, mOwnership);
    changed |= InitPolicyIfExists(data, PND_DDS_QOS_POLICY_NAME_OWNERSHIP_STRENGTH, mOwnershipStrength);
    changed |= InitPolicyIfExists(data, PND_DDS_QOS_POLICY_NAME_PARTITION, mPartition);
    changed |= InitPolicyIfExists(data, PND_DDS_QOS_POLICY_NAME_PRESENTATION, mPresentation);
    changed |= InitPolicyIfExists(data, PND_DDS_QOS_POLICY_NAME_READER_DATA_LIFECYCLE, mReaderDataLifecycle);
    changed |= InitPolicyIfExists(data, PND_DDS_QOS_POLICY_NAME_RELIABILITY, mReliability);
    changed |= InitPolicyIfExists(data, PND_DDS_QOS_POLICY_NAME_RESOURCE_LIMITS, mResourceLimits);
    changed |= InitPolicyIfExists(data, PND_DDS_QOS_POLICY_NAME_TIME_BASED_FILTER, mTimeBasedFilter);
    changed |= InitPolicyIfExists(data, PND_DDS_QOS_POLICY_NAME_TOPIC_DATA, mTopicData);
    changed |= InitPolicyIfExists(data, PND_DDS_QOS_POLICY_NAME_TRANSPORT_PRIORITY, mTransportPriority);
    changed |= InitPolicyIfExists(data, PND_DDS_QOS_POLICY_NAME_WRITER_DATA_LIFECYCLE, mWriterDataLifecycle);
    changed |= InitPolicyIfExists(data, PND_DDS_QOS_POLICY_NAME_USER_DATA, mUserData);

    mDefault = !changed;
}

bool DdsQosParameter::Default() const
{
    return mDefault;
}

}
}
