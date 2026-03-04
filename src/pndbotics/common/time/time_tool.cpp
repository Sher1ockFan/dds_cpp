#include <chrono>
#include <cstdio>

#include <pndbotics/common/time/time_tool.hpp>

namespace pndbotics
{
namespace common
{
void GetCurrentTimeval(struct timeval& tv)
{
    ::gettimeofday(&tv, nullptr);
}

void GetCurrentTimespec(struct timespec& ts)
{
    ::clock_gettime(CLOCK_REALTIME, &ts);
}

uint64_t GetCurrentTime()
{
    return static_cast<uint64_t>(::time(nullptr));
}

uint64_t GetCurrentTimeNanosecond()
{
    struct timespec ts {};
    ::clock_gettime(CLOCK_REALTIME, &ts);
    return static_cast<uint64_t>(ts.tv_sec) * PND_NUMER_NANO + static_cast<uint64_t>(ts.tv_nsec);
}

uint64_t GetCurrentTimeMicrosecond()
{
    return GetCurrentTimeNanosecond() / 1000ULL;
}

uint64_t GetCurrentTimeMillisecond()
{
    return GetCurrentTimeNanosecond() / 1000000ULL;
}

uint64_t GetCurrentCpuTimeNanosecond()
{
    struct timespec ts {};
    ::clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &ts);
    return static_cast<uint64_t>(ts.tv_sec) * PND_NUMER_NANO + static_cast<uint64_t>(ts.tv_nsec);
}

uint64_t GetCurrentThreadCpuTimeNanosecond()
{
    struct timespec ts {};
    ::clock_gettime(CLOCK_THREAD_CPUTIME_ID, &ts);
    return static_cast<uint64_t>(ts.tv_sec) * PND_NUMER_NANO + static_cast<uint64_t>(ts.tv_nsec);
}

uint64_t GetCurrentMonotonicTimeNanosecond()
{
    struct timespec ts {};
    ::clock_gettime(CLOCK_MONOTONIC, &ts);
    return static_cast<uint64_t>(ts.tv_sec) * PND_NUMER_NANO + static_cast<uint64_t>(ts.tv_nsec);
}

uint64_t GetCurrentCpuTimeMicrosecond()
{
    return GetCurrentCpuTimeNanosecond() / 1000ULL;
}

uint64_t GetCurrentThreadCpuTimeMicrosecond()
{
    return GetCurrentThreadCpuTimeNanosecond() / 1000ULL;
}

uint64_t GetCurrentMonotonicTimeMicrosecond()
{
    return GetCurrentMonotonicTimeNanosecond() / 1000ULL;
}

uint64_t TimevalToMicrosecond(const struct timeval& tv)
{
    return static_cast<uint64_t>(tv.tv_sec) * PND_NUMER_MICRO + static_cast<uint64_t>(tv.tv_usec);
}

uint64_t TimevalToMillisecond(const struct timeval& tv)
{
    return TimevalToMicrosecond(tv) / 1000ULL;
}

uint64_t TimespecToMicrosecond(const struct timespec& ts)
{
    return static_cast<uint64_t>(ts.tv_sec) * PND_NUMER_MICRO + static_cast<uint64_t>(ts.tv_nsec) / 1000ULL;
}

uint64_t TimespecToMillisecond(const struct timespec& ts)
{
    return TimespecToMicrosecond(ts) / 1000ULL;
}

void MicrosecondToTimeval(uint64_t microsec, struct timeval& tv)
{
    tv.tv_sec = static_cast<time_t>(microsec / PND_NUMER_MICRO);
    tv.tv_usec = static_cast<suseconds_t>(microsec % PND_NUMER_MICRO);
}

void MillisecondToTimeval(uint64_t millisec, struct timeval& tv)
{
    MicrosecondToTimeval(millisec * 1000ULL, tv);
}

void MicrosecondToTimespec(uint64_t microsec, struct timespec& ts)
{
    ts.tv_sec = static_cast<time_t>(microsec / PND_NUMER_MICRO);
    ts.tv_nsec = static_cast<long>((microsec % PND_NUMER_MICRO) * 1000ULL);
}

void MillisecondToTimespec(uint64_t millisec, struct timespec& ts)
{
    MicrosecondToTimespec(millisec * 1000ULL, ts);
}

std::string TimeFormatString(struct tm* tmptr, const char* format)
{
    if (tmptr == nullptr || format == nullptr)
    {
        return std::string();
    }

    char buf[128] = {0};
    std::snprintf(buf, sizeof(buf), format,
                  tmptr->tm_year + 1900,
                  tmptr->tm_mon + 1,
                  tmptr->tm_mday,
                  tmptr->tm_hour,
                  tmptr->tm_min,
                  tmptr->tm_sec);
    return std::string(buf);
}

std::string TimeFormatString(struct tm* tmptr, uint64_t precise, const char* format)
{
    if (tmptr == nullptr || format == nullptr)
    {
        return std::string();
    }

    char buf[128] = {0};
    std::snprintf(buf, sizeof(buf), format,
                  tmptr->tm_year + 1900,
                  tmptr->tm_mon + 1,
                  tmptr->tm_mday,
                  tmptr->tm_hour,
                  tmptr->tm_min,
                  tmptr->tm_sec,
                  static_cast<unsigned int>(precise));
    return std::string(buf);
}

std::string TimeFormatString(uint64_t sec, const char* format)
{
    time_t tt = static_cast<time_t>(sec);
    struct tm tmv {};
    ::localtime_r(&tt, &tmv);
    return TimeFormatString(&tmv, format);
}

std::string TimeMicrosecondFormatString(const uint64_t& microsec, const char* format)
{
    time_t sec = static_cast<time_t>(microsec / PND_NUMER_MICRO);
    uint64_t precise = microsec % PND_NUMER_MICRO;
    struct tm tmv {};
    ::localtime_r(&sec, &tmv);
    return TimeFormatString(&tmv, precise, format);
}

std::string TimeMillisecondFormatString(const uint64_t& millisec, const char* format)
{
    time_t sec = static_cast<time_t>(millisec / PND_NUMER_MILLI);
    uint64_t precise = millisec % PND_NUMER_MILLI;
    struct tm tmv {};
    ::localtime_r(&sec, &tmv);
    return TimeFormatString(&tmv, precise, format);
}

std::string GetTimeString()
{
    return TimeFormatString(GetCurrentTime(), PND_TIME_FORMAT_STR);
}

std::string GetTimeMicrosecondString()
{
    return TimeMicrosecondFormatString(GetCurrentTimeMicrosecond(), PND_TIME_MICROSEC_FORMAT_STR);
}

std::string GetTimeMillisecondString()
{
    return TimeMillisecondFormatString(GetCurrentTimeMillisecond(), PND_TIME_MILLISEC_FORMAT_STR);
}

Timer::Timer()
    : mMicrosecond(0)
{}

Timer::~Timer()
{}

void Timer::Start()
{
    mMicrosecond = GetCurrentMonotonicTimeMicrosecond();
}

void Timer::Restart()
{
    Start();
}

uint64_t Timer::Stop()
{
    const uint64_t now = GetCurrentMonotonicTimeMicrosecond();
    return (now >= mMicrosecond) ? (now - mMicrosecond) : 0ULL;
}

}
}
