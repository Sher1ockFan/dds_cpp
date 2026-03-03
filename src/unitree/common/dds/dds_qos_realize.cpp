#include <unitree/common/dds/dds_qos_realize.hpp>

namespace unitree
{
namespace common
{
static void SetDeadline(const DdsQosParameter& parameter, DdsTopicQos& qos)
{
    if (!parameter.GetDeadline().Default())
    {
        qos.SetPolicy(DdsQosDeadlinePolicy(parameter.GetDeadline().GetPeriod()));
    }
}

static void SetDestinationOrder(const DdsQosParameter& parameter, DdsTopicQos& qos)
{
    if (!parameter.GetDestinationOrder().Default())
    {
        qos.SetPolicy(DdsQosDestinationOrderPolicy(parameter.GetDestinationOrder().GetKind()));
    }
}

static void SetDurability(const DdsQosParameter& parameter, DdsTopicQos& qos)
{
    if (!parameter.GetDurability().Default())
    {
        qos.SetPolicy(DdsQosDurabilityPolicy(parameter.GetDurability().GetKind()));
    }
}

void Realize(const DdsQosParameter& parameter, DdsParticipantQos& qos)
{
    if (!parameter.GetEntityFactory().Default())
    {
        qos.SetPolicy(DdsQosEntityFactoryPolicy((bool)parameter.GetEntityFactory().GetAutoEnable()));
    }

    if (!parameter.GetUserData().Default())
    {
        qos.SetPolicy(DdsQosUserDataPolicy(parameter.GetUserData().GetValue()));
    }
}

void Realize(const DdsQosParameter& parameter, DdsTopicQos& qos)
{
    SetDeadline(parameter, qos);
    SetDestinationOrder(parameter, qos);
    SetDurability(parameter, qos);

    if (!parameter.GetDurabilityService().Default())
    {
        qos.SetPolicy(DdsQosDurabilityServicePolicy(
            parameter.GetDurabilityService().GetCleanupDelay(),
            parameter.GetDurabilityService().GetHistoryKind(),
            parameter.GetDurabilityService().GetHistoryDepth(),
            parameter.GetDurabilityService().GetMaxSamples(),
            parameter.GetDurabilityService().GetMaxInstances(),
            parameter.GetDurabilityService().GetMaxSamplesPerInstance()));
    }

    if (!parameter.GetHistory().Default())
    {
        qos.SetPolicy(DdsQosHistoryPolicy(parameter.GetHistory().GetKind(), parameter.GetHistory().GetDepth()));
    }

    if (!parameter.GetLatencyBudget().Default())
    {
        qos.SetPolicy(DdsQosLatencyBudgetPolicy(parameter.GetLatencyBudget().GetDuration()));
    }

    if (!parameter.GetLifespan().Default())
    {
        qos.SetPolicy(DdsQosLifespanPolicy(parameter.GetLifespan().GetDuration()));
    }

    if (!parameter.GetLiveliness().Default())
    {
        qos.SetPolicy(DdsQosLivelinessPolicy(parameter.GetLiveliness().GetKind(), parameter.GetLiveliness().GetLeaseDuration()));
    }

    if (!parameter.GetOwnership().Default())
    {
        qos.SetPolicy(DdsQosOwnershipPolicy(parameter.GetOwnership().GetKind()));
    }

    if (!parameter.GetReliability().Default())
    {
        qos.SetPolicy(DdsQosReliabilityPolicy(parameter.GetReliability().GetKind(), parameter.GetReliability().GetMaxBlockingTime()));
    }

    if (!parameter.GetResourceLimits().Default())
    {
        qos.SetPolicy(DdsQosResourceLimitsPolicy(
            parameter.GetResourceLimits().GetMaxSamples(),
            parameter.GetResourceLimits().GetMaxInstances(),
            parameter.GetResourceLimits().GetMaxSamplesPerInstance()));
    }

    if (!parameter.GetTopicData().Default())
    {
        qos.SetPolicy(DdsQosTopicDataPolicy(parameter.GetTopicData().GetValue()));
    }

    if (!parameter.GetTransportPriority().Default())
    {
        qos.SetPolicy(DdsQosTransportPriorityPolicy(parameter.GetTransportPriority().GetValue()));
    }
}

void Realize(const DdsQosParameter& parameter, DdsPublisherQos& qos)
{
    if (!parameter.GetEntityFactory().Default())
    {
        qos.SetPolicy(DdsQosEntityFactoryPolicy((bool)parameter.GetEntityFactory().GetAutoEnable()));
    }

    if (!parameter.GetGroupData().Default())
    {
        qos.SetPolicy(DdsQosGroupDataPolicy(parameter.GetGroupData().GetValue()));
    }

    if (!parameter.GetPartition().Default())
    {
        qos.SetPolicy(DdsQosPartitionPolicy(parameter.GetPartition().GetName()));
    }

    if (!parameter.GetPresentation().Default())
    {
        qos.SetPolicy(DdsQosPresentationPolicy(
            parameter.GetPresentation().GetAccessScopeKind(),
            parameter.GetPresentation().GetCoherentAccess(),
            parameter.GetPresentation().GetOrderedAccess()));
    }
}

void Realize(const DdsQosParameter& parameter, DdsSubscriberQos& qos)
{
    if (!parameter.GetEntityFactory().Default())
    {
        qos.SetPolicy(DdsQosEntityFactoryPolicy((bool)parameter.GetEntityFactory().GetAutoEnable()));
    }

    if (!parameter.GetGroupData().Default())
    {
        qos.SetPolicy(DdsQosGroupDataPolicy(parameter.GetGroupData().GetValue()));
    }

    if (!parameter.GetPartition().Default())
    {
        qos.SetPolicy(DdsQosPartitionPolicy(parameter.GetPartition().GetName()));
    }

    if (!parameter.GetPresentation().Default())
    {
        qos.SetPolicy(DdsQosPresentationPolicy(
            parameter.GetPresentation().GetAccessScopeKind(),
            parameter.GetPresentation().GetCoherentAccess(),
            parameter.GetPresentation().GetOrderedAccess()));
    }
}

void Realize(const DdsQosParameter& parameter, DdsWriterQos& qos)
{
    if (!parameter.GetDeadline().Default())
    {
        qos.SetPolicy(DdsQosDeadlinePolicy(parameter.GetDeadline().GetPeriod()));
    }

    if (!parameter.GetDestinationOrder().Default())
    {
        qos.SetPolicy(DdsQosDestinationOrderPolicy(parameter.GetDestinationOrder().GetKind()));
    }

    if (!parameter.GetDurability().Default())
    {
        qos.SetPolicy(DdsQosDurabilityPolicy(parameter.GetDurability().GetKind()));
    }

    if (!parameter.GetHistory().Default())
    {
        qos.SetPolicy(DdsQosHistoryPolicy(parameter.GetHistory().GetKind(), parameter.GetHistory().GetDepth()));
    }

    if (!parameter.GetLatencyBudget().Default())
    {
        qos.SetPolicy(DdsQosLatencyBudgetPolicy(parameter.GetLatencyBudget().GetDuration()));
    }

    if (!parameter.GetLifespan().Default())
    {
        qos.SetPolicy(DdsQosLifespanPolicy(parameter.GetLifespan().GetDuration()));
    }

    if (!parameter.GetLiveliness().Default())
    {
        qos.SetPolicy(DdsQosLivelinessPolicy(parameter.GetLiveliness().GetKind(), parameter.GetLiveliness().GetLeaseDuration()));
    }

    if (!parameter.GetOwnership().Default())
    {
        qos.SetPolicy(DdsQosOwnershipPolicy(parameter.GetOwnership().GetKind()));
    }

    if (!parameter.GetOwnershipStrength().Default())
    {
        qos.SetPolicy(DdsQosOwnershipStrengthPolicy(parameter.GetOwnershipStrength().GetValue()));
    }

    if (!parameter.GetReliability().Default())
    {
        qos.SetPolicy(DdsQosReliabilityPolicy(parameter.GetReliability().GetKind(), parameter.GetReliability().GetMaxBlockingTime()));
    }

    if (!parameter.GetResourceLimits().Default())
    {
        qos.SetPolicy(DdsQosResourceLimitsPolicy(
            parameter.GetResourceLimits().GetMaxSamples(),
            parameter.GetResourceLimits().GetMaxInstances(),
            parameter.GetResourceLimits().GetMaxSamplesPerInstance()));
    }

    if (!parameter.GetTransportPriority().Default())
    {
        qos.SetPolicy(DdsQosTransportPriorityPolicy(parameter.GetTransportPriority().GetValue()));
    }

    if (!parameter.GetUserData().Default())
    {
        qos.SetPolicy(DdsQosUserDataPolicy(parameter.GetUserData().GetValue()));
    }

    if (!parameter.GetWriterDataLifecycle().Default())
    {
        qos.SetPolicy(DdsQosWriterDataLifecyclePolicy(parameter.GetWriterDataLifecycle().GetAutodisposeUnregisteredInstances()));
    }
}

void Realize(const DdsQosParameter& parameter, DdsReaderQos& qos)
{
    if (!parameter.GetDeadline().Default())
    {
        qos.SetPolicy(DdsQosDeadlinePolicy(parameter.GetDeadline().GetPeriod()));
    }

    if (!parameter.GetDestinationOrder().Default())
    {
        qos.SetPolicy(DdsQosDestinationOrderPolicy(parameter.GetDestinationOrder().GetKind()));
    }

    if (!parameter.GetDurability().Default())
    {
        qos.SetPolicy(DdsQosDurabilityPolicy(parameter.GetDurability().GetKind()));
    }

    if (!parameter.GetHistory().Default())
    {
        qos.SetPolicy(DdsQosHistoryPolicy(parameter.GetHistory().GetKind(), parameter.GetHistory().GetDepth()));
    }

    if (!parameter.GetLatencyBudget().Default())
    {
        qos.SetPolicy(DdsQosLatencyBudgetPolicy(parameter.GetLatencyBudget().GetDuration()));
    }

    if (!parameter.GetLiveliness().Default())
    {
        qos.SetPolicy(DdsQosLivelinessPolicy(parameter.GetLiveliness().GetKind(), parameter.GetLiveliness().GetLeaseDuration()));
    }

    if (!parameter.GetOwnership().Default())
    {
        qos.SetPolicy(DdsQosOwnershipPolicy(parameter.GetOwnership().GetKind()));
    }

    if (!parameter.GetReliability().Default())
    {
        qos.SetPolicy(DdsQosReliabilityPolicy(parameter.GetReliability().GetKind(), parameter.GetReliability().GetMaxBlockingTime()));
    }

    if (!parameter.GetReaderDataLifecycle().Default())
    {
        qos.SetPolicy(DdsQosReaderDataLifecyclePolicy(
            parameter.GetReaderDataLifecycle().GetAutopurgeNowriterSamplesDelay(),
            parameter.GetReaderDataLifecycle().GetAutopurgeDisposedSamplesDelay()));
    }

    if (!parameter.GetResourceLimits().Default())
    {
        qos.SetPolicy(DdsQosResourceLimitsPolicy(
            parameter.GetResourceLimits().GetMaxSamples(),
            parameter.GetResourceLimits().GetMaxInstances(),
            parameter.GetResourceLimits().GetMaxSamplesPerInstance()));
    }

    if (!parameter.GetTimeBasedFilter().Default())
    {
        qos.SetPolicy(DdsQosTimeBasedFilterPolicy(parameter.GetTimeBasedFilter().GetMinSep()));
    }

    if (!parameter.GetUserData().Default())
    {
        qos.SetPolicy(DdsQosUserDataPolicy(parameter.GetUserData().GetValue()));
    }
}

}
}
