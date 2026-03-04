#ifndef __PND_LOG_INITOR_HPP__
#define __PND_LOG_INITOR_HPP__

#include <pndbotics/common/log/log_policy.hpp>
#include <pndbotics/common/log/log_store.hpp>
#include <pndbotics/common/log/log_logger.hpp>

namespace pndbotics
{
namespace common
{
class LogInitor
{
public:
    explicit LogInitor();
    ~LogInitor();

    void Init(const std::string& configFileName, bool stdoutDefault = false);
    Logger* GetLogger(const std::string& tag);

    void Final();

    void ParseConf(Any json);
    void SetStdoutPolicy();
    void InitLogger();

private:
    std::set<std::string> mStoreNames;
    std::vector<LogPolicyPtr> mPolicis;
    std::vector<LogStorePolicyPtr> mStorePolicis;
    std::map<std::string, LoggerPtr> mLoggerMap;
};

using LogInitorPtr = std::shared_ptr<LogInitor>;

void LogInit(const std::string& configFileName = "", bool stdoutDefault = false);
void LogFinal();

Logger* GetLogger(const std::string& tag);

}
}

#endif//__PND_LOG_INITOR_HPP__
