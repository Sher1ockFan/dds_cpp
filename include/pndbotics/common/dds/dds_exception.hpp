#ifndef __PND_DDS_EXCEPTION_HPP__
#define __PND_DDS_EXCEPTION_HPP__

#include <pndbotics/common/exception.hpp>
#include <pndbotics/common/dds/dds_error.hpp>

#define __PND_DDS_EXCEPTION_MESSAGE(e, d)        \
    std::string("Catch dds::core exception. Class:") + __PND_STR(d) + ", Message:" + e.what();

#define __PND_DDS_EXCEPTION_CATCH(except, l, t)  \
catch (const except & e)                        \
{                                               \
    if (l || t)                                 \
    {                                           \
        std::string __t9b78e5r = __PND_DDS_EXCEPTION_MESSAGE(e, except);  \
        if (l)                                  \
        {                                       \
            LOG_ERROR(l, __t9b78e5r);           \
        }                                       \
        if (t)                                  \
        {                                       \
            PND_THROW(DdsException, __t9b78e5r); \
        }                                       \
    }                                           \
}

#define PND_DDS_EXCEPTION_TRY                    \
try                                             \
{

#define PND_DDS_EXCEPTION_CATCH(l, t)            \
}                                               \
__PND_DDS_EXCEPTION_CATCH(::dds::core::Error, l, t)                    \
__PND_DDS_EXCEPTION_CATCH(::dds::core::InvalidArgumentError, l, t)     \
__PND_DDS_EXCEPTION_CATCH(::dds::core::TimeoutError, l, t)             \
__PND_DDS_EXCEPTION_CATCH(::dds::core::UnsupportedError, l, t)         \
__PND_DDS_EXCEPTION_CATCH(::dds::core::AlreadyClosedError, l, t)       \
__PND_DDS_EXCEPTION_CATCH(::dds::core::IllegalOperationError, l, t)    \
__PND_DDS_EXCEPTION_CATCH(::dds::core::NotEnabledError, l, t)          \
__PND_DDS_EXCEPTION_CATCH(::dds::core::PreconditionNotMetError, l, t)  \
__PND_DDS_EXCEPTION_CATCH(::dds::core::ImmutablePolicyError, l, t)     \
__PND_DDS_EXCEPTION_CATCH(::dds::core::InconsistentPolicyError, l, t)  \
__PND_DDS_EXCEPTION_CATCH(::dds::core::OutOfResourcesError, l, t)      \
__PND_DDS_EXCEPTION_CATCH(::dds::core::InvalidDowncastError, l, t)     \
__PND_DDS_EXCEPTION_CATCH(::dds::core::NullReferenceError, l, t)       \
__PND_DDS_EXCEPTION_CATCH(::dds::core::InvalidDataError, l, t)         \
__PND_DDS_EXCEPTION_CATCH(::dds::core::Exception, l, t)                \
__PND_DDS_EXCEPTION_CATCH(std::exception, l, t)

namespace pndbotics
{
namespace common
{
PND_DECL_EXCEPTION(DdsException, PND_ERR_DDS, PND_DESC_ERR(PND_ERR_DDS))
}
}

#endif//__PND_DDS_EXCEPTION_HPP__
