#include <pndbotics/common/dds/dds_qos_policy.hpp>
#include <pndbotics/common/dds/dds_qos_policy_parameter.hpp>

namespace pndbotics
{
namespace common
{
namespace
{
static ::dds::core::Duration ToDuration(int64_t nanoSecond)
{
    if (nanoSecond <= 0)
    {
        return ::dds::core::Duration::zero();
    }

    const int64_t sec = nanoSecond / 1000000000LL;
    const uint32_t nsec = (uint32_t)(nanoSecond % 1000000000LL);
    return ::dds::core::Duration(sec, nsec);
}
}

DdsDuration::DdsDuration(int64_t nanoSecond)
{
    mNative = ToDuration(nanoSecond);
}

DdsDuration::~DdsDuration()
{}

DdsQosDeadlinePolicy::DdsQosDeadlinePolicy(int64_t period) :
    DdsQosPolicyName(PND_DDS_QOS_POLICY_NAME_DEADLINE)
{
    mNative = ::dds::core::policy::Deadline(ToDuration(period));
}

DdsQosDeadlinePolicy::~DdsQosDeadlinePolicy()
{}

DdsQosDestinationOrderPolicy::DdsQosDestinationOrderPolicy(int32_t kind) :
    DdsQosPolicyName(PND_DDS_QOS_POLICY_NAME_DESTINATION_ORDER)
{
    auto v = (::dds::core::policy::DestinationOrderKind::Type)kind;
    mNative = ::dds::core::policy::DestinationOrder(v);
}

DdsQosDestinationOrderPolicy::~DdsQosDestinationOrderPolicy()
{}

DdsQosDurabilityPolicy::DdsQosDurabilityPolicy(int32_t kind) :
    DdsQosPolicyName(PND_DDS_QOS_POLICY_NAME_DURABILITY)
{
    auto v = (::dds::core::policy::DurabilityKind::Type)kind;
    mNative = ::dds::core::policy::Durability(v);
}

DdsQosDurabilityPolicy::~DdsQosDurabilityPolicy()
{}

DdsQosDurabilityServicePolicy::DdsQosDurabilityServicePolicy(
        int64_t cleanupDelay,
        int32_t historyKind,
        int32_t historyDepth,
        int32_t maxSamples,
        int32_t maxInstances,
        int32_t maxSamplesPerInstance) :
    DdsQosPolicyName(PND_DDS_QOS_POLICY_NAME_DURABILITY_SERVICE)
{
    auto hk = (::dds::core::policy::HistoryKind::Type)historyKind;
    mNative = ::dds::core::policy::DurabilityService(
        ToDuration(cleanupDelay), hk, historyDepth, maxSamples, maxInstances, maxSamplesPerInstance);
}

DdsQosDurabilityServicePolicy::~DdsQosDurabilityServicePolicy()
{}

DdsQosEntityFactoryPolicy::DdsQosEntityFactoryPolicy(bool autoEnable) :
    DdsQosPolicyName(PND_DDS_QOS_POLICY_NAME_ENTITY_FACTORY)
{
    mNative = ::dds::core::policy::EntityFactory(autoEnable);
}

DdsQosEntityFactoryPolicy::~DdsQosEntityFactoryPolicy()
{}

DdsQosGroupDataPolicy::DdsQosGroupDataPolicy(const std::vector<uint8_t>& value) :
    DdsQosPolicyName(PND_DDS_QOS_POLICY_NAME_GROUP_DATA)
{
    mNative = ::dds::core::policy::GroupData(value);
}

DdsQosGroupDataPolicy::~DdsQosGroupDataPolicy()
{}

DdsQosHistoryPolicy::DdsQosHistoryPolicy(int32_t kind, int32_t depth) :
    DdsQosPolicyName(PND_DDS_QOS_POLICY_NAME_HISTORY)
{
    auto v = (::dds::core::policy::HistoryKind::Type)kind;
    mNative = ::dds::core::policy::History(v, depth);
}

DdsQosHistoryPolicy::~DdsQosHistoryPolicy()
{}

DdsQosLatencyBudgetPolicy::DdsQosLatencyBudgetPolicy(int64_t duration) :
    DdsQosPolicyName(PND_DDS_QOS_POLICY_NAME_LATENCY_BUDGET)
{
    mNative = ::dds::core::policy::LatencyBudget(ToDuration(duration));
}

DdsQosLatencyBudgetPolicy::~DdsQosLatencyBudgetPolicy()
{}

DdsQosLifespanPolicy::DdsQosLifespanPolicy(int64_t duration) :
    DdsQosPolicyName(PND_DDS_QOS_POLICY_NAME_LIFESPAN)
{
    mNative = ::dds::core::policy::Lifespan(ToDuration(duration));
}

DdsQosLifespanPolicy::~DdsQosLifespanPolicy()
{}

DdsQosLivelinessPolicy::DdsQosLivelinessPolicy(int32_t kind, int64_t leaseDuration) :
    DdsQosPolicyName(PND_DDS_QOS_POLICY_NAME_LIVELINESS)
{
    auto v = (::dds::core::policy::LivelinessKind::Type)kind;
    mNative = ::dds::core::policy::Liveliness(v, ToDuration(leaseDuration));
}

DdsQosLivelinessPolicy::~DdsQosLivelinessPolicy()
{}

DdsQosOwnershipPolicy::DdsQosOwnershipPolicy(int32_t kind) :
    DdsQosPolicyName(PND_DDS_QOS_POLICY_NAME_OWNERSHIP)
{
    auto v = (::dds::core::policy::OwnershipKind::Type)kind;
    mNative = ::dds::core::policy::Ownership(v);
}

DdsQosOwnershipPolicy::~DdsQosOwnershipPolicy()
{}

DdsQosOwnershipStrengthPolicy::DdsQosOwnershipStrengthPolicy(int32_t strength) :
    DdsQosPolicyName(PND_DDS_QOS_POLICY_NAME_OWNERSHIP_STRENGTH)
{
    mNative = ::dds::core::policy::OwnershipStrength(strength);
}

DdsQosOwnershipStrengthPolicy::~DdsQosOwnershipStrengthPolicy()
{}

DdsQosPartitionPolicy::DdsQosPartitionPolicy(const std::string& name) :
    DdsQosPolicyName(PND_DDS_QOS_POLICY_NAME_PARTITION)
{
    mNative = ::dds::core::policy::Partition(name);
}

DdsQosPartitionPolicy::~DdsQosPartitionPolicy()
{}

DdsQosPresentationPolicy::DdsQosPresentationPolicy(int32_t accessScopeKind, bool coherentAccess, bool orderedAccess) :
    DdsQosPolicyName(PND_DDS_QOS_POLICY_NAME_PRESENTATION)
{
    auto v = (::dds::core::policy::PresentationAccessScopeKind::Type)accessScopeKind;
    mNative = ::dds::core::policy::Presentation(v, coherentAccess, orderedAccess);
}

DdsQosPresentationPolicy::~DdsQosPresentationPolicy()
{}

DdsQosReaderDataLifecyclePolicy::DdsQosReaderDataLifecyclePolicy(
        int64_t autopurgeNowriterSamplesDelay,
        int64_t autopurgeDisposedSamplesDelay) :
    DdsQosPolicyName(PND_DDS_QOS_POLICY_NAME_READER_DATA_LIFECYCLE)
{
    mNative = ::dds::core::policy::ReaderDataLifecycle(
        ToDuration(autopurgeNowriterSamplesDelay),
        ToDuration(autopurgeDisposedSamplesDelay));
}

DdsQosReaderDataLifecyclePolicy::~DdsQosReaderDataLifecyclePolicy()
{}

DdsQosReliabilityPolicy::DdsQosReliabilityPolicy(int32_t kind, int64_t maxBlockingTime) :
    DdsQosPolicyName(PND_DDS_QOS_POLICY_NAME_RELIABILITY)
{
    auto v = (::dds::core::policy::ReliabilityKind::Type)kind;
    mNative = ::dds::core::policy::Reliability(v, ToDuration(maxBlockingTime));
}

DdsQosReliabilityPolicy::~DdsQosReliabilityPolicy()
{}

DdsQosResourceLimitsPolicy::DdsQosResourceLimitsPolicy(int32_t maxSamples, int32_t maxInstances, int32_t maxSamplesPerInstance) :
    DdsQosPolicyName(PND_DDS_QOS_POLICY_NAME_RESOURCE_LIMITS)
{
    mNative = ::dds::core::policy::ResourceLimits(maxSamples, maxInstances, maxSamplesPerInstance);
}

DdsQosResourceLimitsPolicy::~DdsQosResourceLimitsPolicy()
{}

DdsQosTimeBasedFilterPolicy::DdsQosTimeBasedFilterPolicy(int64_t minSep) :
    DdsQosPolicyName(PND_DDS_QOS_POLICY_NAME_TIME_BASED_FILTER)
{
    mNative = ::dds::core::policy::TimeBasedFilter(ToDuration(minSep));
}

DdsQosTimeBasedFilterPolicy::~DdsQosTimeBasedFilterPolicy()
{}

DdsQosTopicDataPolicy::DdsQosTopicDataPolicy(const std::vector<uint8_t>& value) :
    DdsQosPolicyName(PND_DDS_QOS_POLICY_NAME_TOPIC_DATA)
{
    mNative = ::dds::core::policy::TopicData(value);
}

DdsQosTopicDataPolicy::~DdsQosTopicDataPolicy()
{}

DdsQosTransportPriorityPolicy::DdsQosTransportPriorityPolicy(int32_t value) :
    DdsQosPolicyName(PND_DDS_QOS_POLICY_NAME_TRANSPORT_PRIORITY)
{
    mNative = ::dds::core::policy::TransportPriority(value);
}

DdsQosTransportPriorityPolicy::~DdsQosTransportPriorityPolicy()
{}

DdsQosWriterDataLifecyclePolicy::DdsQosWriterDataLifecyclePolicy(bool autodisposeUnregisteredInstances) :
    DdsQosPolicyName(PND_DDS_QOS_POLICY_NAME_WRITER_DATA_LIFECYCLE)
{
    mNative = ::dds::core::policy::WriterDataLifecycle(autodisposeUnregisteredInstances);
}

DdsQosWriterDataLifecyclePolicy::~DdsQosWriterDataLifecyclePolicy()
{}

DdsQosUserDataPolicy::DdsQosUserDataPolicy(const std::vector<uint8_t>& value) :
    DdsQosPolicyName(PND_DDS_QOS_POLICY_NAME_USER_DATA)
{
    mNative = ::dds::core::policy::UserData(value);
}

DdsQosUserDataPolicy::~DdsQosUserDataPolicy()
{}

}
}
