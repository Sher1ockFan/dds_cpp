#ifndef __PND_LOG_DECL_HPP__
#define __PND_LOG_DECL_HPP__

#include <pndbotics/common/exception.hpp>
#include <pndbotics/common/os.hpp>
#include <pndbotics/common/lock/lock.hpp>
#include <pndbotics/common/thread/thread.hpp>
#include <pndbotics/common/thread/recurrent_thread.hpp>
#include <pndbotics/common/filesystem/file.hpp>

/*
 * log buffer size
 */
#define PND_LOG_BUFFER_SIZE          65535           //64K-1
#define PND_LOG_CRT_BUFFER_SIZE      64512           //63K
#define PND_LOG_MAX_BUFFER_SIZE      4194303         //4M-1
/*
 * log file size
 */
#define PND_LOG_FILE_SIZE            104857600       //100M
#define PND_LOG_MAX_FILE_SIZE        10737418240     //10G
#define PND_LOG_MIN_FILE_SIZE        PND_LOG_MAX_BUFFER_SIZE

/*
 * log write interval(micro second)
 */
#define PND_LOG_WRITE_INTER          100000          //100ms
#define PND_LOG_MAX_WRITE_INTER      1000000         //1s
#define PND_LOG_MIN_WRITE_INTER      2000            //2ms

/*
 * log file number
 */
#define PND_LOG_FILE_NUMBER          2
#define PND_LOG_MAX_FILE_NUMBER      100
#define PND_LOG_MIN_FILE_NUMBER      PND_LOG_FILE_NUMBER

#define PND_LOG_FILE_EXT             ".LOG"

//write log macro wrapper
#define __PND_LOG(logger, level, ...)\
    do {                            \
        if (logger != NULL)         \
        {                           \
            logger->Log(level, __VA_ARGS__);    \
        }                           \
    } while (0)

#define __PND_CRIT_LOG(logger, key, code, ...)   \
    do {                            \
        if (logger != NULL)         \
        {                           \
            logger->CritLog(PND_LOG_CRIT, key, code, __VA_ARGS__);\
        }                           \
    } while (0)


//debug
#define LOG_DEBUG(logger, ...)      \
    __PND_LOG(logger, PND_LOG_DEBUG, __VA_ARGS__)

//info
#define LOG_INFO(logger, ...)       \
    __PND_LOG(logger, PND_LOG_INFO, __VA_ARGS__)

//warning
#define LOG_WARNING(logger, ...)    \
    __PND_LOG(logger, PND_LOG_WARNING, __VA_ARGS__)

//error
#define LOG_ERROR(logger, ...)      \
    __PND_LOG(logger, PND_LOG_ERROR, __VA_ARGS__)

//fatal
#define LOG_FATAL(logger, ...)      \
    __PND_LOG(logger, PND_LOG_FATAL, __VA_ARGS__)

//critical log. the 1st args is CRITICAL KEY 
#define CRIT_LOG(logger, ...)       \
    __PND_CRIT_LOG(logger, __VA_ARGS__)

#define CRIT_LOG(logger, ...)       \
    __PND_CRIT_LOG(logger, __VA_ARGS__)

//write log format macro wrapper
/*
 * FMT_DEBUG(logger, ("key1", val1)("key2", val2)("keyn", ""));
 */
#define __PND_LOG_FMT(logger, level, keyvalues)  \
    do {                                        \
        if (logger != NULL)                     \
        {                                       \
            logger->LogFormat(level, pndbotics::common::LogBuilder() keyvalues);    \
        }                                       \
    } while (0)

#define __PND_CRIT_LOG_FMT(logger, key, code, keyvalues)    \
    do {                                        \
        if (logger != NULL)                     \
        {                                       \
            logger->CritLogFormat(PND_LOG_CRIT, key, code, pndbotics::common::LogBuilder() keyvalues);   \
        }                                       \
    } while (0)

//debug
#define FMT_DEBUG(logger, keyvalues)            \
    __PND_LOG_FMT(logger, PND_LOG_DEBUG, keyvalues)

//info
#define FMT_INFO(logger, keyvalues)             \
    __PND_LOG_FMT(logger, PND_LOG_INFO, keyvalues)

//warning
#define FMT_WARNING(logger, keyvalues)          \
    __PND_LOG_FMT(logger, PND_LOG_WARNING, keyvalues)

//error
#define FMT_ERROR(logger, keyvalues)            \
    __PND_LOG_FMT(logger, PND_LOG_ERROR, keyvalues)

//fatal
#define FMT_FATAL(logger, keyvalues)            \
    __PND_LOG_FMT(logger, PND_LOG_FATAL, keyvalues)

#define CRIT_FMT(logger, critkey, keyvalues)    \
    __PND_CRIT_LOG_FMT(logger, critkey, keyvalues)


/*
//declare and define log level
#define PND_LOG_DECL_LEVEL(name, level, desc)    \
    const int32_t name = level;                 \
    const std::string name##_DESC = desc;
#define PND_LOG_DESC_LEVEL(name) name##_DESC
*/

//declare and define log store type 
#define PND_LOG_DECL_STORE_TYPE(name, type, desc)\
    const int32_t name = type;                  \
    const std::string name##_DESC = desc;
#define PND_LOG_DESC_STORE_TYPE(name) name##_DESC

//define log level
#define PND_LOG_NONE                     0
#define PND_LOG_CRIT                     1
#define PND_LOG_FATAL                    2
#define PND_LOG_ERROR                    3
#define PND_LOG_WARNING                  4
#define PND_LOG_INFO                     5
#define PND_LOG_DEBUG                    6
#define PND_LOG_ALL                      7

#define PND_LOG_DESC_NONE                "NONE"
#define PND_LOG_DESC_CRIT                "CRIT"
#define PND_LOG_DESC_FATAL               "FATAL"
#define PND_LOG_DESC_ERROR               "ERROR"
#define PND_LOG_DESC_WARNING             "WARNING"
#define PND_LOG_DESC_INFO                "INFO"
#define PND_LOG_DESC_DEBUG               "DEBUG"
#define PND_LOG_DESC_ALL                 "ALL"

//define log store type
#define PND_LOG_STORE_FILE_ASYNC         0
#define PND_LOG_STORE_FILE               1
#define PND_LOG_STORE_STDOUT             2
#define PND_LOG_STORE_STDERR             3

#define PND_LOG_STORE_DESC_FILE_ASYNC    "FILEASYNC"
#define PND_LOG_STORE_DESC_ASYNC_FILE    "ASYNCFILE"
#define PND_LOG_STORE_DESC_ASYNC         "ASYNC"
#define PND_LOG_STORE_DESC_FILE          "FILE"
#define PND_LOG_STORE_DESC_STDOUT        "STDOUT"
#define PND_LOG_STORE_DESC_STDERR        "STDERR"

namespace pndbotics
{
namespace common
{
static inline int32_t GetLogLevel(const std::string& desc)
{
    if (desc == PND_LOG_DESC_NONE)           {
        return PND_LOG_NONE;     }
    else if (desc == PND_LOG_DESC_CRIT)      {
        return PND_LOG_CRIT;     }
    else if (desc == PND_LOG_DESC_FATAL)     {
        return PND_LOG_FATAL;    }
    else if (desc == PND_LOG_DESC_ERROR)     {
        return PND_LOG_ERROR;    }
    else if (desc == PND_LOG_DESC_WARNING)   {
        return PND_LOG_WARNING;  }
    else if (desc == PND_LOG_DESC_INFO)      {
        return PND_LOG_INFO;     }
    else if (desc == PND_LOG_DESC_DEBUG)     {
        return PND_LOG_DEBUG;    }
    else if (desc == PND_LOG_DESC_ALL)       {
        return PND_LOG_ALL;      }

    PND_THROW(CommonException, std::string("unknown log level desc:") + desc);
}

static inline const char* GetLogLevelDesc(int32_t level)
{
    switch (level)
    {
    case PND_LOG_NONE:
        return PND_LOG_DESC_NONE;
    case PND_LOG_CRIT:
        return PND_LOG_DESC_CRIT;
    case PND_LOG_FATAL:
        return PND_LOG_DESC_FATAL;
    case PND_LOG_ERROR:
        return PND_LOG_DESC_ERROR;
    case PND_LOG_WARNING:
        return PND_LOG_DESC_WARNING;
    case PND_LOG_INFO:
        return PND_LOG_DESC_INFO;
    case PND_LOG_DEBUG:
        return PND_LOG_DESC_DEBUG;
    case PND_LOG_ALL:
        return PND_LOG_DESC_ALL;
    }

    PND_THROW(CommonException, "unknown log level");
}

static inline int32_t GetLogStoreType(const std::string& desc)
{
    if (desc == PND_LOG_STORE_DESC_FILE_ASYNC ||
        desc == PND_LOG_STORE_DESC_ASYNC_FILE ||
        desc == PND_LOG_STORE_DESC_ASYNC)      {
        return PND_LOG_STORE_FILE_ASYNC;  }
    else if (desc == PND_LOG_STORE_DESC_FILE)  {
        return PND_LOG_STORE_FILE;        }
    else if (desc == PND_LOG_STORE_DESC_STDOUT){
        return PND_LOG_STORE_STDOUT;      }
    else if (desc == PND_LOG_STORE_DESC_STDERR){
        return PND_LOG_STORE_STDERR;      }

    PND_THROW(CommonException, std::string("unknown log store type desc:") + desc);
}

static inline const char* GetLogStoreTypeDesc(int32_t type)
{
    switch (type)
    {
    case PND_LOG_STORE_FILE_ASYNC:
        return PND_LOG_STORE_DESC_FILE_ASYNC;
    case PND_LOG_STORE_FILE:
        return PND_LOG_STORE_DESC_FILE;
    case PND_LOG_STORE_STDOUT:
        return PND_LOG_STORE_DESC_STDOUT;
    case PND_LOG_STORE_STDERR:
        return PND_LOG_STORE_DESC_STDERR;
    }

    PND_THROW(CommonException, "unknown log store type");
}
}
}

#endif//__PND_LOG_DECL_HPP__
