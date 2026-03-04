#include <pndbotics/common/thread/recurrent_thread.hpp>
#include <pndbotics/common/time/sleep.hpp>
#include <pndbotics/common/time/time_tool.hpp>

namespace pndbotics
{
namespace common
{
RecurrentThread::~RecurrentThread()
{
    mQuit = true;
}

int32_t RecurrentThread::ThreadFunc()
{
    while (!mQuit)
    {
        const uint64_t begin = GetCurrentMonotonicTimeMicrosecond();
        if (mFunc)
        {
            mFunc();
        }
        const uint64_t end = GetCurrentMonotonicTimeMicrosecond();
        const uint64_t elapsed = (end >= begin) ? (end - begin) : 0ULL;
        if (elapsed < mIntervalMicrosec)
        {
            MicroSleep(mIntervalMicrosec - elapsed);
        }
    }
    return 0;
}

int32_t RecurrentThread::ThreadFunc_0()
{
    while (!mQuit)
    {
        if (mFunc)
        {
            mFunc();
        }
        else
        {
            break;
        }
    }
    return 0;
}

bool RecurrentThread::Wait(int64_t microsec)
{
    return FutureWrapper::Wait(microsec);
}

}
}
