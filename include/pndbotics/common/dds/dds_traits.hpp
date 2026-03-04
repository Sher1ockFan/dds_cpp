#ifndef __PND_DDS_TRAINTS_HPP__
#define __PND_DDS_TRAINTS_HPP__

namespace pndbotics
{
namespace common
{
#include <org/eclipse/cyclonedds/topic/TopicTraits.hpp>

#define DdsGetTypeName(TYPE) \
    org::eclipse::cyclonedds::topic::TopicTraits<TYPE>::getTypeName()

#define DdsIsKeyless(TYPE) \
    org::eclipse::cyclonedds::topic::TopicTraits<TYPE>::isKeyless()

}
}
#endif//__PND_DDS_TRAINTS_HPP__
