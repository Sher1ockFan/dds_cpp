#ifndef __PND_RECURRENT_THREAD_HPP__
#define __PND_RECURRENT_THREAD_HPP__

#include <pndbotics/common/thread/thread.hpp>

#define PND_THREAD_TIME_INTERVAL_MICROSEC 1000000

namespace pndbotics
{
namespace common
{
class RecurrentThread : public Thread
{
public:
    __PND_THREAD_DECL_TMPL_FUNC_ARG__
    explicit RecurrentThread(uint64_t intervalMicrosec, __PND_THREAD_TMPL_FUNC_ARG__)
        : mQuit(false), mIntervalMicrosec(intervalMicrosec)
    {
        //recurrent function
        mFunc = std::bind(__PND_THREAD_BIND_FUNC_ARG__);

        //Call Thread::Run for runing thread
        if (mIntervalMicrosec == 0)
        {
            Run(&RecurrentThread::ThreadFunc_0, this);
        }
        else
        {
            Run(&RecurrentThread::ThreadFunc, this);
        }
    }

    __PND_THREAD_DECL_TMPL_FUNC_ARG__
    explicit RecurrentThread(const std::string& name, int32_t cpuId, uint64_t intervalMicrosec,
        __PND_THREAD_TMPL_FUNC_ARG__)
        : Thread(name, cpuId), mQuit(false), mIntervalMicrosec(intervalMicrosec)
    {
        //recurrent function
        mFunc = std::bind(__PND_THREAD_BIND_FUNC_ARG__);

        //Call Thread::Run for runing thread
        if (mIntervalMicrosec == 0)
        {
            Run(&RecurrentThread::ThreadFunc_0, this);
        }
        else
        {
            Run(&RecurrentThread::ThreadFunc, this);
        }
    }

    virtual ~RecurrentThread();

    int32_t ThreadFunc();
    int32_t ThreadFunc_0();

    bool Wait(int64_t microsec = 0);

private:
    volatile bool mQuit;
    uint64_t mIntervalMicrosec;
    std::function<void()> mFunc;
};

typedef std::shared_ptr<RecurrentThread> RecurrentThreadPtr;

__PND_THREAD_DECL_TMPL_FUNC_ARG__
ThreadPtr CreateRecurrentThread(uint64_t intervalMicrosec, __PND_THREAD_TMPL_FUNC_ARG__)
{
    return ThreadPtr(new RecurrentThread(intervalMicrosec, __PND_THREAD_BIND_FUNC_ARG__));
}

__PND_THREAD_DECL_TMPL_FUNC_ARG__
ThreadPtr CreateRecurrentThreadEx(const std::string& name, int32_t cpuId, uint64_t intervalMicrosec,
    __PND_THREAD_TMPL_FUNC_ARG__)
{
    return ThreadPtr(new RecurrentThread(name, cpuId, intervalMicrosec,
        __PND_THREAD_BIND_FUNC_ARG__));
}

}
}

#endif//__PND_RECURRENT_THREAD_HPP__
