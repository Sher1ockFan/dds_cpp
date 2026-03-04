#ifndef __PND_DECL_HPP__
#define __PND_DECL_HPP__

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <errno.h>
#include <exception>
#include <execinfo.h>
#include <sched.h>
#include <signal.h>
#include <string.h>
#include <strings.h>
#include <arpa/inet.h>
#include <ifaddrs.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/statvfs.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/sysinfo.h>
#include <sys/syscall.h>
#include <sys/resource.h>
#include <sys/timerfd.h>
#include <net/if.h>
#include <netinet/in.h>
#include <netdb.h>
#include <time.h>
#include <poll.h>
#include <pthread.h>
#include <pwd.h>
#include <limits.h>
#include <fcntl.h>
#include <dirent.h>
#include <utime.h>
#include <atomic>
#include <string>
#include <iostream>
#include <sstream>
#include <typeinfo>
#include <list>
#include <vector>
#include <set>
#include <map>
#include <unordered_map>
#include <functional>
#include <iomanip>
#include <memory>
#include <regex>

#ifdef __GLIBC__
#define PND_UNLIKELY(x)  __builtin_expect(!!(x), 0)
#define PND_LIKELY(x)    __builtin_expect(!!(x), 1)
#else
#define PND_UNLIKELY(x)  (x)
#define PND_LIKELY(x)    (x)
#endif//__GLIBC__

#define __PND_CAT(x, y)  x##y
#define PND_CAT(x, y)    __PND_CAT(x, y)

#define __PND_STR(x)     #x
#define PND_STR(x)       __PND_STR(x)

#define PND_QUEUE_MAX_LEN        INT_MAX
#define PND_PATH_MAX_LEN         1024
#define PND_THREAD_NAME_MAX_LEN  16

#define PND_DECL_ERR(name, code, desc)   \
    const int32_t name = code; const std::string name##_DESC = desc;

#define PND_DESC_ERR(name) name##_DESC

#ifndef SYS_gettid
#define SYS_gettid __NR_gettid
#endif//SYS_gettid

#define PND_SAFE_DEL(x)  \
    if ((x) != NULL) { delete (x); (x) = NULL; }

namespace pndbotics
{
namespace common
{
static const std::string PND_EMPTY_STR = "";
}
}

#endif//__PND_DECL_HPP__
