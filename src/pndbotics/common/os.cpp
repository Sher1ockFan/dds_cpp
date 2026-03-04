#include <algorithm>
#include <fstream>
#include <sstream>

#include <pndbotics/common/os.hpp>

namespace pndbotics
{
namespace common
{
OsHelper::OsHelper()
    : mUID(0), mPasswd{}, mProcessorNumber(1), mProcessorNumberConf(1), mPageSize(4096)
{
    __Getpwuid();
    __GetProcessor();
    __GetPageSize();
    __GetProcessFileName();
    __GetHostname();
}

void OsHelper::__Getpwuid()
{
    mUID = ::getuid();
    struct passwd* pwd = nullptr;
    struct passwd buf {};
    char tmp[4096] = {0};
    if (::getpwuid_r(mUID, &buf, tmp, sizeof(tmp), &pwd) == 0 && pwd != nullptr)
    {
        mPasswd = *pwd;
    }
}

void OsHelper::__GetProcessor()
{
    mProcessorNumber = static_cast<int32_t>(::get_nprocs());
    mProcessorNumberConf = static_cast<int32_t>(::get_nprocs_conf());
}

void OsHelper::__GetPageSize()
{
    mPageSize = static_cast<int32_t>(::sysconf(_SC_PAGESIZE));
}

void OsHelper::__GetProcessFileName()
{
    char path[PATH_MAX] = {0};
    const ssize_t n = ::readlink("/proc/self/exe", path, sizeof(path) - 1);
    if (n > 0)
    {
        path[n] = '\0';
        mProcessFileName = std::string(path);
    }
}

void OsHelper::__GetHostname()
{
    char host[256] = {0};
    if (::gethostname(host, sizeof(host) - 1) == 0)
    {
        mHostname = std::string(host);
    }
}

uid_t OsHelper::GetUID() const
{
    return mUID;
}

gid_t OsHelper::GetGID() const
{
    return mPasswd.pw_gid;
}

std::string OsHelper::GetUser() const
{
    return mPasswd.pw_name ? std::string(mPasswd.pw_name) : std::string();
}

const struct passwd& OsHelper::GetPasswd() const
{
    return mPasswd;
}

bool OsHelper::GetPasswd(const std::string& name, struct passwd& pwd)
{
    struct passwd* out = nullptr;
    char tmp[4096] = {0};
    struct passwd local {};
    if (::getpwnam_r(name.c_str(), &local, tmp, sizeof(tmp), &out) == 0 && out != nullptr)
    {
        pwd = *out;
        return true;
    }
    return false;
}

bool OsHelper::GetUIDAndGID(const std::string& name, uid_t& uid, gid_t& gid)
{
    struct passwd pwd {};
    if (!GetPasswd(name, pwd))
    {
        return false;
    }
    uid = pwd.pw_uid;
    gid = pwd.pw_gid;
    return true;
}

int32_t OsHelper::GetProcessorNumber() const
{
    return mProcessorNumber;
}

int32_t OsHelper::GetProcessorNumberConf() const
{
    return mProcessorNumberConf;
}

int32_t OsHelper::GetPageSize() const
{
    return mPageSize;
}

int64_t OsHelper::Align(int64_t len) const
{
    if (mPageSize <= 0)
    {
        return len;
    }
    return ((len + mPageSize - 1) / mPageSize) * mPageSize;
}

bool OsHelper::IsAligned(int64_t len) const
{
    return (mPageSize > 0) ? (len % mPageSize == 0) : true;
}

const std::string& OsHelper::GetHostname() const
{
    return mHostname;
}

uint32_t OsHelper::GetProcessId()
{
    return static_cast<uint32_t>(::getpid());
}

const std::string& OsHelper::GetProcessFileName()
{
    return mProcessFileName;
}

std::string OsHelper::GetProcessName()
{
    if (mProcessFileName.empty())
    {
        return std::string();
    }
    const size_t pos = mProcessFileName.find_last_of('/');
    return (pos == std::string::npos) ? mProcessFileName : mProcessFileName.substr(pos + 1);
}

std::string OsHelper::GetProcessDirectory(bool withEndDelim)
{
    if (mProcessFileName.empty())
    {
        return std::string();
    }
    const size_t pos = mProcessFileName.find_last_of('/');
    if (pos == std::string::npos)
    {
        return std::string();
    }
    std::string dir = mProcessFileName.substr(0, pos);
    if (withEndDelim)
    {
        dir.push_back('/');
    }
    return dir;
}

uint64_t OsHelper::GetThreadId()
{
    return static_cast<uint64_t>(GetTid());
}

int32_t OsHelper::GetTid()
{
    return static_cast<int32_t>(::syscall(SYS_gettid));
}

bool OsHelper::GetNetworkInterfaceIps(std::map<std::string, std::string>& networkInterfaceIpMap)
{
    networkInterfaceIpMap.clear();
    struct ifaddrs* ifaddr = nullptr;
    if (::getifaddrs(&ifaddr) != 0)
    {
        return false;
    }
    for (struct ifaddrs* it = ifaddr; it != nullptr; it = it->ifa_next)
    {
        if (it->ifa_addr == nullptr || it->ifa_addr->sa_family != AF_INET)
        {
            continue;
        }
        char ip[INET_ADDRSTRLEN] = {0};
        auto* sa = reinterpret_cast<struct sockaddr_in*>(it->ifa_addr);
        if (::inet_ntop(AF_INET, &sa->sin_addr, ip, sizeof(ip)) != nullptr)
        {
            networkInterfaceIpMap[it->ifa_name] = std::string(ip);
        }
    }
    ::freeifaddrs(ifaddr);
    return true;
}

bool OsHelper::GetIps(std::set<std::string>& ips)
{
    ips.clear();
    std::map<std::string, std::string> nicMap;
    if (!GetNetworkInterfaceIps(nicMap))
    {
        return false;
    }
    for (const auto& kv : nicMap)
    {
        ips.insert(kv.second);
    }
    return true;
}

void OsHelper::CpuSet(const std::string& cpuIds)
{
    cpu_set_t set;
    CPU_ZERO(&set);

    std::stringstream ss(cpuIds);
    std::string token;
    while (std::getline(ss, token, ','))
    {
        if (token.empty())
        {
            continue;
        }
        const int id = std::stoi(token);
        if (id >= 0)
        {
            CPU_SET(static_cast<size_t>(id), &set);
        }
    }
    ::sched_setaffinity(0, sizeof(set), &set);
}

void OsHelper::CpuSet(uint64_t threadId, size_t cpuId)
{
    cpu_set_t set;
    CPU_ZERO(&set);
    CPU_SET(cpuId, &set);
    ::pthread_setaffinity_np(static_cast<pthread_t>(threadId), sizeof(set), &set);
}

void OsHelper::SetThreadName(uint64_t threadId, const std::string& name)
{
    std::string n = name.substr(0, PND_THREAD_NAME_MAX_LEN - 1);
    if (threadId == 0)
    {
        ::pthread_setname_np(::pthread_self(), n.c_str());
    }
    else
    {
        ::pthread_setname_np(static_cast<pthread_t>(threadId), n.c_str());
    }
}

void OsHelper::SetScheduler(int32_t policy, int32_t priority)
{
    sched_param param {};
    param.sched_priority = priority;
    ::pthread_setschedparam(::pthread_self(), policy, &param);
}

void OsHelper::SetScheduler(uint64_t threadId, int32_t policy, int32_t priority)
{
    sched_param param {};
    param.sched_priority = priority;
    ::pthread_setschedparam(static_cast<pthread_t>(threadId), policy, &param);
}

void OsHelper::SingletonProcessInstance()
{
    if (!mInstanceLockPtr)
    {
        const std::string lockFile = "/tmp/" + GetProcessName() + ".lock";
        mInstanceLockPtr = std::make_shared<Filelock>(lockFile);
    }
    mInstanceLockPtr->Trylock(PND_LOCK_MODE_WRITE);
}

}
}
