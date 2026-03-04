#ifndef __PND_SERVICE_CONFIG_HPP__
#define __PND_SERVICE_CONFIG_HPP__

#include <pndbotics/common/service/base/service_decl.hpp>

namespace pndbotics
{
namespace common
{
class ServiceConfig : public common::JsonConfig
{
public:
    ServiceConfig();
    virtual ~ServiceConfig();

    ServiceConfig(const std::string& configFileName);

    virtual void Parse(const std::string& configFileName);
    virtual void ParseContent(const std::string& content);

    //top-level field: ServiceName
    const std::string& GetServiceName() const;

    //top-level field: CpuIds
    const std::string& GetCpuIds() const;

protected:
    std::string mCpuIds;
    std::string mServiceName;
};

typedef std::shared_ptr<ServiceConfig> ServiceConfigPtr;

}
}

#endif//__PND_SERVICE_CONFIG_HPP__
