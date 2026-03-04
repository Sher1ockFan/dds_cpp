#ifndef __PND_SERVICE_APPLICATION_HPP__
#define __PND_SERVICE_APPLICATION_HPP__

#include <pndbotics/common/service/base/service_base.hpp>

#define SERVICE_REGISTER(SERVICE)       \
class SERVICE##Register                 \
{                                       \
public:                                 \
    SERVICE##Register()                 \
    {                                   \
        pndbotics::common::ServiceApplication::Instance()->RegistService<SERVICE>(); \
    }                                   \
    static SERVICE##Register mRegister; \
};                                      \
SERVICE##Register SERVICE##Register::mRegister = SERVICE##Register();

namespace pndbotics
{
namespace common
{
class ServiceApplication
{
public:
    static ServiceApplication* Instance()
    {
        static ServiceApplication inst;
        return &inst;
    }

    template<typename SERVICE>
    void RegistService()
    {
        mServicePtr = ServicePtr(new SERVICE());
    }

    void Init(const std::string& configFileName);
    void Start();
    void Stop();

private:
    ServiceApplication();

protected:
    ServicePtr mServicePtr;
};

}
}

#endif//__PND_SERVICE_APPLICATION_HPP__
