#include <pndbotics/common/os.hpp>
#include <pndbotics/common/thread/thread.hpp>

namespace pndbotics
{
namespace common
{
Thread::~Thread()
{
    if (mThreadId != 0 && !::pthread_equal(mThreadId, ::pthread_self()))
    {
        ::pthread_join(mThreadId, nullptr);
    }
    mThreadId = 0;
}

uint64_t Thread::GetThreadId() const
{
    return static_cast<uint64_t>(mThreadId);
}

void Thread::SetCpu()
{
    if (mCpuId >= 0)
    {
        OsHelper::Instance()->CpuSet(GetThreadId(), static_cast<size_t>(mCpuId));
    }
}

void Thread::SetName()
{
    if (!mName.empty())
    {
        OsHelper::Instance()->SetThreadName(GetThreadId(), mName);
    }
}

void Thread::SetPriority(int32_t priority)
{
    OsHelper::Instance()->SetScheduler(GetThreadId(), PND_SCHED_POLICY_FIFO, priority);
}

void Thread::Wrap()
{
    SetName();
    SetCpu();
    try
    {
        if (mFunc)
        {
            Ready(mFunc());
        }
        else
        {
            Ready(PND_EMPTY_ANY);
        }
    }
    catch (const std::exception& e)
    {
        Fault(std::string(e.what()));
    }
    catch (...)
    {
        Fault(std::string("thread execution unknown exception"));
    }
}

void Thread::CreateThreadNative()
{
    auto entry = [](void* arg) -> void* {
        Thread* self = static_cast<Thread*>(arg);
        self->Wrap();
        return nullptr;
    };
    ::pthread_create(&mThreadId, nullptr, entry, this);
}

}
}
