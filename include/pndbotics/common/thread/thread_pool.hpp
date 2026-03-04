#ifndef __PND_THREAD_POOL_HPP__
#define __PND_THREAD_POOL_HPP__

#include <pndbotics/common/log/log.hpp>
#include <pndbotics/common/thread/thread.hpp>
#include <pndbotics/common/thread/thread_task.hpp>
#include <pndbotics/common/block_queue.hpp>

namespace pndbotics
{
namespace common
{
class ThreadPool
{
public:
    enum
    {
        /*
         * minimum threads can be created.
         */
        MIN_THREAD_NUMBER = 1,
        /*
         * maximum threads can be created.
         */
        MAX_THREAD_NUMBER = 1000,
        /*
         * default timeout get task from blockqueue.
         * 1 second
         */
        QUEUE_GET_TIMEOUT_MICROSEC = 1000000,
        /*
         * default max queue size.
         * as PND_QUEUE_MAX_LEN
         */
        MAX_QUEUE_SIZE = PND_QUEUE_MAX_LEN,
        /*
         * default in queue time in microsecond.
         * 7 days
         */
        MAX_QUEUE_MICROSEC = 25200000000
    };

    explicit ThreadPool(uint32_t threadNumber = MIN_THREAD_NUMBER,
        uint32_t queueMaxSize = PND_QUEUE_MAX_LEN,
        uint64_t taskMaxQueueMicrosec = MAX_QUEUE_MICROSEC);

    __PND_THREAD_DECL_TMPL_FUNC_ARG__
    bool AddTask(__PND_THREAD_TMPL_FUNC_ARG__)
    {
        return AddTaskInner(ThreadTaskPtr(new ThreadTask(__PND_THREAD_BIND_FUNC_ARG__)));
    }

    __PND_THREAD_DECL_TMPL_FUNC_ARG__
    FuturePtr AddTaskFuture(__PND_THREAD_TMPL_FUNC_ARG__)
    {
        ThreadTaskFuturePtr taskPtr = ThreadTaskFuturePtr(
            new ThreadTaskFuture(__PND_THREAD_BIND_FUNC_ARG__));

        if (AddTaskInner(std::dynamic_pointer_cast<ThreadTask>(taskPtr)))
        {
            return taskPtr->GetFuture();
        }

        return FuturePtr();
    }

    int32_t DoTask();
    uint64_t GetTaskSize();

    bool IsQuit();
    void Quit(bool waitThreadExit = true);

    bool IsTaskOverdue(uint64_t enqueueTime);

private:
    bool AddTaskInner(ThreadTaskPtr taskptr);

    void InitCreateThread();
    void WaitThreadExit();

private:
    volatile bool mQuit;

    uint32_t mThreadNumber;
    uint32_t mTaskQueueMaxSize;
    uint64_t mTaskMaxQueueTime;

    BlockQueue<ThreadTaskPtr> mTaskQueue;
    std::vector<ThreadPtr> mThreadList;

    Logger* mLogger;
};

typedef std::shared_ptr<ThreadPool> ThreadPoolPtr;

}
}
#endif//__PND_THREAD_POOL_HPP__
