#ifndef __PND_THREAD_TASK_HPP__
#define __PND_THREAD_TASK_HPP__

#include <pndbotics/common/thread/future.hpp>

namespace pndbotics
{
namespace common
{
class ThreadTask
{
public:
    __PND_THREAD_DECL_TMPL_FUNC_ARG__
    explicit ThreadTask(__PND_THREAD_TMPL_FUNC_ARG__)
    {
        mFunc = std::bind(__PND_THREAD_BIND_FUNC_ARG__);
    }

    virtual void Execute();

    void SetEnqueueTime();
    uint64_t GetEnqueueTime() const;

protected:
    uint64_t mEnqueueTimeMicrosec;
    std::function<Any()> mFunc;
};

typedef std::shared_ptr<ThreadTask> ThreadTaskPtr;

class ThreadTaskFuture : public ThreadTask, public FutureWrapper
{
public:
    __PND_THREAD_DECL_TMPL_FUNC_ARG__
    explicit ThreadTaskFuture(__PND_THREAD_TMPL_FUNC_ARG__)
        : ThreadTask(__PND_THREAD_BIND_FUNC_ARG__)
    {}

    void Execute();
};

typedef std::shared_ptr<ThreadTaskFuture> ThreadTaskFuturePtr;

}
}

#endif//__PND_THREAD_TASK_HPP__
