#include <pndbotics/common/thread/future.hpp>

namespace pndbotics
{
namespace common
{
class FutureImpl : public Future
{
public:
    FutureImpl()
        : mState(DEFER), mValue(PND_EMPTY_ANY), mFault(PND_EMPTY_ANY)
    {}

    int32_t GetState() override
    {
        LockGuard<Mutex> lock(mMutex);
        return mState;
    }

    bool Wait(int64_t microsec = 0) override
    {
        mCond.Lock();
        if (microsec <= 0)
        {
            while (mState == DEFER)
            {
                mCond.Wait();
            }
            mCond.Unlock();
            return true;
        }

        int64_t remain = microsec;
        while (mState == DEFER && remain > 0)
        {
            const int64_t slice = (remain > 20000) ? 20000 : remain;
            const bool ok = mCond.Wait(slice);
            if (mState != DEFER)
            {
                mCond.Unlock();
                return true;
            }
            if (!ok)
            {
                remain -= slice;
            }
        }
        const bool done = (mState != DEFER);
        mCond.Unlock();
        return done;
    }

    const Any& GetValue(int64_t microsec = 0) override
    {
        Wait(microsec);
        return mValue;
    }

    const Any& GetFaultMessage() override
    {
        return mFault;
    }

    void Ready(const Any& value) override
    {
        {
            LockGuard<Mutex> lock(mMutex);
            mValue = value;
            mState = READY;
        }
        mCond.Lock();
        mCond.NotifyAll();
        mCond.Unlock();
    }

    void Fault(const Any& message) override
    {
        {
            LockGuard<Mutex> lock(mMutex);
            mFault = message;
            mState = FAULT;
        }
        mCond.Lock();
        mCond.NotifyAll();
        mCond.Unlock();
    }

private:
    int32_t mState;
    Any mValue;
    Any mFault;
    Mutex mMutex;
    MutexCond mCond;
};

FutureWrapper::FutureWrapper()
{
    mFuturePtr = std::make_shared<FutureImpl>();
}

FutureWrapper::~FutureWrapper()
{}

}
}
