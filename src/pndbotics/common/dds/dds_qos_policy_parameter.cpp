#include <pndbotics/common/dds/dds_qos_policy_parameter.hpp>

namespace pndbotics
{
namespace common
{
namespace
{
static bool GetMapField(const JsonMap& in, const std::string& key, JsonMap& out)
{
    auto it = in.find(key);
    if (it == in.end() || it->second.Empty() || !IsJsonMap(it->second))
    {
        return false;
    }

    out = AnyCast<JsonMap>(it->second);
    return true;
}

static bool GetArrayField(const JsonMap& in, const std::string& key, JsonArray& out)
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
static bool GetNumberField(const JsonMap& in, const std::string& key, T& out)
{
    auto it = in.find(key);
    if (it == in.end() || it->second.Empty())
    {
        return false;
    }

    out = AnyNumberCast<T>(it->second);
    return true;
}

template<typename T>
static bool GetField(const JsonMap& in, const std::string& key, T& out)
{
    auto it = in.find(key);
    if (it == in.end() || it->second.Empty())
    {
        return false;
    }

    out = AnyCast<T>(it->second);
    return true;
}

static std::vector<uint8_t> ToByteVector(const Any& value)
{
    std::vector<uint8_t> ret;

    if (!IsJsonArray(value))
    {
        return ret;
    }

    const JsonArray& arr = AnyCast<JsonArray>(value);
    for (const auto& item : arr)
    {
        ret.push_back((uint8_t)AnyNumberCast<int32_t>(item));
    }

    return ret;
}
}

DdsQosPolicyParameter::DdsQosPolicyParameter() :
    mDefault(true)
{}

DdsQosPolicyParameter::~DdsQosPolicyParameter()
{}

void DdsQosPolicyParameter::Update()
{
    mDefault = false;
}

bool DdsQosPolicyParameter::Default() const
{
    return mDefault;
}

DdsQosDeadlinePolicyParameter::DdsQosDeadlinePolicyParameter() :
    mPeriod(0)
{}

DdsQosDeadlinePolicyParameter::~DdsQosDeadlinePolicyParameter()
{}

void DdsQosDeadlinePolicyParameter::Init(const JsonMap& data)
{
    GetNumberField<int64_t>(data, PND_DDS_QOS_POLICY_MEMBER_NAME_PEROID, mPeriod);
    Update();
}

int64_t DdsQosDeadlinePolicyParameter::GetPeriod() const
{
    return mPeriod;
}

DdsQosDestinationOrderPolicyParameter::DdsQosDestinationOrderPolicyParameter() :
    mKind(0)
{}

DdsQosDestinationOrderPolicyParameter::~DdsQosDestinationOrderPolicyParameter()
{}

void DdsQosDestinationOrderPolicyParameter::Init(const JsonMap& data)
{
    GetNumberField<int32_t>(data, PND_DDS_QOS_POLICY_MEMBER_NAME_KIND, mKind);
    Update();
}

int32_t DdsQosDestinationOrderPolicyParameter::GetKind() const
{
    return mKind;
}

DdsQosDurabilityPolicyParameter::DdsQosDurabilityPolicyParameter() :
    mKind(0)
{}

DdsQosDurabilityPolicyParameter::~DdsQosDurabilityPolicyParameter()
{}

void DdsQosDurabilityPolicyParameter::Init(const JsonMap& data)
{
    GetNumberField<int32_t>(data, PND_DDS_QOS_POLICY_MEMBER_NAME_KIND, mKind);
    Update();
}

int32_t DdsQosDurabilityPolicyParameter::GetKind() const
{
    return mKind;
}

DdsQosDurabilityServicePolicyParameter::DdsQosDurabilityServicePolicyParameter() :
    mCleanupDelay(0), mHistoryKind(0), mHistoryDepth(0), mMaxSamples(0), mMaxInstances(0), mMaxSamplesPerInstance(0)
{}

DdsQosDurabilityServicePolicyParameter::~DdsQosDurabilityServicePolicyParameter()
{}

void DdsQosDurabilityServicePolicyParameter::Init(const JsonMap& data)
{
    GetNumberField<int64_t>(data, PND_DDS_QOS_POLICY_MEMBER_NAME_CLEANUP_DELAY, mCleanupDelay);
    GetNumberField<int32_t>(data, PND_DDS_QOS_POLICY_MEMBER_NAME_HISTORY_KIND, mHistoryKind);
    GetNumberField<int32_t>(data, PND_DDS_QOS_POLICY_MEMBER_NAME_HISTORY_DEPTH, mHistoryDepth);
    GetNumberField<int32_t>(data, PND_DDS_QOS_POLICY_MEMBER_NAME_MAX_SAMPLES, mMaxSamples);
    GetNumberField<int32_t>(data, PND_DDS_QOS_POLICY_MEMBER_NAME_MAX_INSTANCES, mMaxInstances);
    GetNumberField<int32_t>(data, PND_DDS_QOS_POLICY_MEMBER_NAME_MAX_SAMPLES_PER_INSTANCE, mMaxSamplesPerInstance);
    Update();
}

int64_t DdsQosDurabilityServicePolicyParameter::GetCleanupDelay() const
{
    return mCleanupDelay;
}

int32_t DdsQosDurabilityServicePolicyParameter::GetHistoryKind() const
{
    return mHistoryKind;
}

int32_t DdsQosDurabilityServicePolicyParameter::GetHistoryDepth() const
{
    return mHistoryDepth;
}

int32_t DdsQosDurabilityServicePolicyParameter::GetMaxSamples() const
{
    return mMaxSamples;
}

int32_t DdsQosDurabilityServicePolicyParameter::GetMaxInstances() const
{
    return mMaxInstances;
}

int32_t DdsQosDurabilityServicePolicyParameter::GetMaxSamplesPerInstance() const
{
    return mMaxSamplesPerInstance;
}

DdsQosEntityFactoryPolicyParameter::DdsQosEntityFactoryPolicyParameter() :
    mAutoEnable(false)
{}

DdsQosEntityFactoryPolicyParameter::~DdsQosEntityFactoryPolicyParameter()
{}

void DdsQosEntityFactoryPolicyParameter::Init(const JsonMap& data)
{
    GetField<bool>(data, PND_DDS_QOS_POLICY_MEMBER_NAME_AUTO_ENABLE, mAutoEnable);
    Update();
}

int64_t DdsQosEntityFactoryPolicyParameter::GetAutoEnable() const
{
    return mAutoEnable;
}

DdsQosGroupDataPolicyParameter::DdsQosGroupDataPolicyParameter()
{}

DdsQosGroupDataPolicyParameter::~DdsQosGroupDataPolicyParameter()
{}

void DdsQosGroupDataPolicyParameter::Init(const JsonMap& data)
{
    auto it = data.find(PND_DDS_QOS_POLICY_MEMBER_NAME_VALUE);
    if (it != data.end() && !it->second.Empty())
    {
        mValue = ToByteVector(it->second);
    }
    Update();
}

const std::vector<uint8_t>& DdsQosGroupDataPolicyParameter::GetValue() const
{
    return mValue;
}

DdsQosHistoryPolicyParameter::DdsQosHistoryPolicyParameter() :
    mKind(0), mDepth(1)
{}

DdsQosHistoryPolicyParameter::~DdsQosHistoryPolicyParameter()
{}

void DdsQosHistoryPolicyParameter::Init(const JsonMap& data)
{
    GetNumberField<int32_t>(data, PND_DDS_QOS_POLICY_MEMBER_NAME_KIND, mKind);
    GetNumberField<int32_t>(data, PND_DDS_QOS_POLICY_MEMBER_NAME_DEPTH, mDepth);
    Update();
}

int32_t DdsQosHistoryPolicyParameter::GetKind() const
{
    return mKind;
}

int32_t DdsQosHistoryPolicyParameter::GetDepth() const
{
    return mDepth;
}

DdsQosLatencyBudgetPolicyParameter::DdsQosLatencyBudgetPolicyParameter() :
    mDuration(0)
{}

DdsQosLatencyBudgetPolicyParameter::~DdsQosLatencyBudgetPolicyParameter()
{}

void DdsQosLatencyBudgetPolicyParameter::Init(const JsonMap& data)
{
    GetNumberField<int64_t>(data, PND_DDS_QOS_POLICY_MEMBER_NAME_DURATION, mDuration);
    Update();
}

int64_t DdsQosLatencyBudgetPolicyParameter::GetDuration() const
{
    return mDuration;
}

DdsQosLifespanPolicyParameter::DdsQosLifespanPolicyParameter() :
    mDuration(0)
{}

DdsQosLifespanPolicyParameter::~DdsQosLifespanPolicyParameter()
{}

void DdsQosLifespanPolicyParameter::Init(const JsonMap& data)
{
    GetNumberField<int64_t>(data, PND_DDS_QOS_POLICY_MEMBER_NAME_DURATION, mDuration);
    Update();
}

int64_t DdsQosLifespanPolicyParameter::GetDuration() const
{
    return mDuration;
}

DdsQosLivelinessPolicyParameter::DdsQosLivelinessPolicyParameter() :
    mKind(0), mLeaseDuration(0)
{}

DdsQosLivelinessPolicyParameter::~DdsQosLivelinessPolicyParameter()
{}

void DdsQosLivelinessPolicyParameter::Init(const JsonMap& data)
{
    GetNumberField<int32_t>(data, PND_DDS_QOS_POLICY_MEMBER_NAME_KIND, mKind);
    GetNumberField<int64_t>(data, PND_DDS_QOS_POLICY_MEMBER_NAME_LEASE_DURATION, mLeaseDuration);
    Update();
}

int32_t DdsQosLivelinessPolicyParameter::GetKind() const
{
    return mKind;
}

int64_t DdsQosLivelinessPolicyParameter::GetLeaseDuration() const
{
    return mLeaseDuration;
}

DdsQosOwnershipPolicyParameter::DdsQosOwnershipPolicyParameter() :
    mKind(0)
{}

DdsQosOwnershipPolicyParameter::~DdsQosOwnershipPolicyParameter()
{}

void DdsQosOwnershipPolicyParameter::Init(const JsonMap& data)
{
    GetNumberField<int32_t>(data, PND_DDS_QOS_POLICY_MEMBER_NAME_KIND, mKind);
    Update();
}

int32_t DdsQosOwnershipPolicyParameter::GetKind() const
{
    return mKind;
}

DdsQosOwnershipStrengthPolicyParameter::DdsQosOwnershipStrengthPolicyParameter() :
    mValue(0)
{}

DdsQosOwnershipStrengthPolicyParameter::~DdsQosOwnershipStrengthPolicyParameter()
{}

void DdsQosOwnershipStrengthPolicyParameter::Init(const JsonMap& data)
{
    GetNumberField<int32_t>(data, PND_DDS_QOS_POLICY_MEMBER_NAME_VALUE, mValue);
    Update();
}

int32_t DdsQosOwnershipStrengthPolicyParameter::GetValue() const
{
    return mValue;
}

DdsQosPartitionPolicyParameter::DdsQosPartitionPolicyParameter()
{}

DdsQosPartitionPolicyParameter::~DdsQosPartitionPolicyParameter()
{}

void DdsQosPartitionPolicyParameter::Init(const JsonMap& data)
{
    GetField<std::string>(data, PND_DDS_QOS_POLICY_MEMBER_NAME_NAME, mName);
    Update();
}

const std::string& DdsQosPartitionPolicyParameter::GetName() const
{
    return mName;
}

DdsQosPresentationPolicyParameter::DdsQosPresentationPolicyParameter() :
    mAccessScopeKind(0), mCoherentAccess(false), mOrderedAccess(false)
{}

DdsQosPresentationPolicyParameter::~DdsQosPresentationPolicyParameter()
{}

void DdsQosPresentationPolicyParameter::Init(const JsonMap& data)
{
    GetNumberField<int32_t>(data, PND_DDS_QOS_POLICY_MEMBER_NAME_ACCESS_SCOPE, mAccessScopeKind);
    GetField<bool>(data, PND_DDS_QOS_POLICY_MEMBER_NAME_COHERENT_ACCESS, mCoherentAccess);
    GetField<bool>(data, PND_DDS_QOS_POLICY_MEMBER_NAME_ORDERED_ACCESS, mOrderedAccess);
    Update();
}

int32_t DdsQosPresentationPolicyParameter::GetAccessScopeKind() const
{
    return mAccessScopeKind;
}

bool DdsQosPresentationPolicyParameter::GetCoherentAccess() const
{
    return mCoherentAccess;
}

bool DdsQosPresentationPolicyParameter::GetOrderedAccess() const
{
    return mOrderedAccess;
}

DdsQosReaderDataLifecyclePolicyParameter::DdsQosReaderDataLifecyclePolicyParameter() :
    mAutopurgeNowriterSamplesDelay(0), mAutopurgeDisposedSamplesDelay(0)
{}

DdsQosReaderDataLifecyclePolicyParameter::~DdsQosReaderDataLifecyclePolicyParameter()
{}

void DdsQosReaderDataLifecyclePolicyParameter::Init(const JsonMap& data)
{
    GetNumberField<int64_t>(data, PND_DDS_QOS_POLICY_MEMBER_NAME_AUTOPURGE_NOWRITER_SAMPLES_DELAY, mAutopurgeNowriterSamplesDelay);
    GetNumberField<int64_t>(data, PND_DDS_QOS_POLICY_MEMBER_NAME_AUTOPURGE_DISPOSED_SAMPLES_DELAY, mAutopurgeDisposedSamplesDelay);
    Update();
}

int64_t DdsQosReaderDataLifecyclePolicyParameter::GetAutopurgeNowriterSamplesDelay() const
{
    return mAutopurgeNowriterSamplesDelay;
}

int64_t DdsQosReaderDataLifecyclePolicyParameter::GetAutopurgeDisposedSamplesDelay() const
{
    return mAutopurgeDisposedSamplesDelay;
}

DdsQosReliabilityPolicyParameter::DdsQosReliabilityPolicyParameter() :
    mKind(0), mMaxBlockingTime(0)
{}

DdsQosReliabilityPolicyParameter::~DdsQosReliabilityPolicyParameter()
{}

void DdsQosReliabilityPolicyParameter::Init(const JsonMap& data)
{
    GetNumberField<int32_t>(data, PND_DDS_QOS_POLICY_MEMBER_NAME_KIND, mKind);
    GetNumberField<int64_t>(data, PND_DDS_QOS_POLICY_MEMBER_NAME_MAX_BLOCKING_TIME, mMaxBlockingTime);
    Update();
}

int32_t DdsQosReliabilityPolicyParameter::GetKind() const
{
    return mKind;
}

int64_t DdsQosReliabilityPolicyParameter::GetMaxBlockingTime() const
{
    return mMaxBlockingTime;
}

DdsQosResourceLimitsPolicyParameter::DdsQosResourceLimitsPolicyParameter() :
    mMaxSamples(0), mMaxInstances(0), mMaxSamplesPerInstance(0)
{}

DdsQosResourceLimitsPolicyParameter::~DdsQosResourceLimitsPolicyParameter()
{}

void DdsQosResourceLimitsPolicyParameter::Init(const JsonMap& data)
{
    GetNumberField<int32_t>(data, PND_DDS_QOS_POLICY_MEMBER_NAME_MAX_SAMPLES, mMaxSamples);
    GetNumberField<int32_t>(data, PND_DDS_QOS_POLICY_MEMBER_NAME_MAX_INSTANCES, mMaxInstances);
    GetNumberField<int32_t>(data, PND_DDS_QOS_POLICY_MEMBER_NAME_MAX_SAMPLES_PER_INSTANCE, mMaxSamplesPerInstance);
    Update();
}

int32_t DdsQosResourceLimitsPolicyParameter::GetMaxSamples() const
{
    return mMaxSamples;
}

int32_t DdsQosResourceLimitsPolicyParameter::GetMaxInstances() const
{
    return mMaxInstances;
}

int32_t DdsQosResourceLimitsPolicyParameter::GetMaxSamplesPerInstance() const
{
    return mMaxSamplesPerInstance;
}

DdsQosTimeBasedFilterPolicyParameter::DdsQosTimeBasedFilterPolicyParameter() :
    mMinSep(0)
{}

DdsQosTimeBasedFilterPolicyParameter::~DdsQosTimeBasedFilterPolicyParameter()
{}

void DdsQosTimeBasedFilterPolicyParameter::Init(const JsonMap& data)
{
    GetNumberField<int64_t>(data, PND_DDS_QOS_POLICY_MEMBER_NAME_MIN_SEP, mMinSep);
    Update();
}

int64_t DdsQosTimeBasedFilterPolicyParameter::GetMinSep() const
{
    return mMinSep;
}

DdsQosTopicDataPolicyParameter::DdsQosTopicDataPolicyParameter()
{}

DdsQosTopicDataPolicyParameter::~DdsQosTopicDataPolicyParameter()
{}

void DdsQosTopicDataPolicyParameter::Init(const JsonMap& data)
{
    auto it = data.find(PND_DDS_QOS_POLICY_MEMBER_NAME_VALUE);
    if (it != data.end() && !it->second.Empty())
    {
        mValue = ToByteVector(it->second);
    }
    Update();
}

const std::vector<uint8_t>& DdsQosTopicDataPolicyParameter::GetValue() const
{
    return mValue;
}

DdsQosTransportPriorityPolicyParameter::DdsQosTransportPriorityPolicyParameter() :
    mValue(0)
{}

DdsQosTransportPriorityPolicyParameter::~DdsQosTransportPriorityPolicyParameter()
{}

void DdsQosTransportPriorityPolicyParameter::Init(const JsonMap& data)
{
    GetNumberField<int32_t>(data, PND_DDS_QOS_POLICY_MEMBER_NAME_VALUE, mValue);
    Update();
}

int32_t DdsQosTransportPriorityPolicyParameter::GetValue() const
{
    return mValue;
}

DdsQosWriterDataLifecyclePolicyParameter::DdsQosWriterDataLifecyclePolicyParameter() :
    mAutodisposeUnregisteredInstances(false)
{}

DdsQosWriterDataLifecyclePolicyParameter::~DdsQosWriterDataLifecyclePolicyParameter()
{}

void DdsQosWriterDataLifecyclePolicyParameter::Init(const JsonMap& data)
{
    GetField<bool>(data, PND_DDS_QOS_POLICY_MEMBER_NAME_AUTODISPOSE_UNREGISETED_INSTANCES, mAutodisposeUnregisteredInstances);
    Update();
}

bool DdsQosWriterDataLifecyclePolicyParameter::GetAutodisposeUnregisteredInstances() const
{
    return mAutodisposeUnregisteredInstances;
}

DdsQosUserDataPolicyParameter::DdsQosUserDataPolicyParameter()
{}

DdsQosUserDataPolicyParameter::~DdsQosUserDataPolicyParameter()
{}

void DdsQosUserDataPolicyParameter::Init(const JsonMap& data)
{
    auto it = data.find(PND_DDS_QOS_POLICY_MEMBER_NAME_VALUE);
    if (it != data.end() && !it->second.Empty())
    {
        mValue = ToByteVector(it->second);
    }
    Update();
}

const std::vector<uint8_t>& DdsQosUserDataPolicyParameter::GetValue() const
{
    return mValue;
}

}
}
