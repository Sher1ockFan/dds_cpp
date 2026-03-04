#include <pndbotics/common/lock/lock.hpp>

namespace pndbotics
{
namespace common
{
Spinlock::Spinlock()
{
    ::pthread_spin_init(&mNative, PTHREAD_PROCESS_PRIVATE);
}

Spinlock::~Spinlock()
{
    ::pthread_spin_destroy(&mNative);
}

void Spinlock::Lock()
{
    ::pthread_spin_lock(&mNative);
}

void Spinlock::Unlock()
{
    ::pthread_spin_unlock(&mNative);
}

bool Spinlock::Trylock()
{
    return ::pthread_spin_trylock(&mNative) == 0;
}

pthread_spinlock_t& Spinlock::GetNative()
{
    return mNative;
}

CaspinLock::CaspinLock()
    : mData(0)
{}

CaspinLock::~CaspinLock()
{}

void CaspinLock::Lock()
{
    while (!Trylock())
    {
        ::sched_yield();
    }
}

void CaspinLock::Unlock()
{
    __sync_lock_release(&mData);
}

bool CaspinLock::Trylock()
{
    return __sync_lock_test_and_set(&mData, 1) == 0;
}

Mutex::Mutex()
{
    ::pthread_mutex_init(&mNative, nullptr);
}

Mutex::~Mutex()
{
    ::pthread_mutex_destroy(&mNative);
}

void Mutex::Lock()
{
    ::pthread_mutex_lock(&mNative);
}

void Mutex::Unlock()
{
    ::pthread_mutex_unlock(&mNative);
}

bool Mutex::Trylock()
{
    return ::pthread_mutex_trylock(&mNative) == 0;
}

pthread_mutex_t& Mutex::GetNative()
{
    return mNative;
}

Cond::Cond()
{
    ::pthread_cond_init(&mNative, nullptr);
}

Cond::~Cond()
{
    ::pthread_cond_destroy(&mNative);
}

void Cond::Wait(Mutex& mutex)
{
    ::pthread_cond_wait(&mNative, &mutex.GetNative());
}

bool Cond::Wait(Mutex& mutex, uint64_t microsec)
{
    struct timespec ts {};
    ::clock_gettime(CLOCK_REALTIME, &ts);
    ts.tv_sec += static_cast<time_t>(microsec / 1000000ULL);
    ts.tv_nsec += static_cast<long>((microsec % 1000000ULL) * 1000ULL);
    if (ts.tv_nsec >= 1000000000L)
    {
        ts.tv_sec += 1;
        ts.tv_nsec -= 1000000000L;
    }
    const int ret = ::pthread_cond_timedwait(&mNative, &mutex.GetNative(), &ts);
    return ret == 0;
}

void Cond::Notify()
{
    ::pthread_cond_signal(&mNative);
}

void Cond::NotifyAll()
{
    ::pthread_cond_broadcast(&mNative);
}

MutexCond::MutexCond()
{}

MutexCond::~MutexCond()
{}

void MutexCond::Lock()
{
    mMutex.Lock();
}

void MutexCond::Unlock()
{
    mMutex.Unlock();
}

bool MutexCond::Wait(int64_t microsec)
{
    if (microsec <= 0)
    {
        mCond.Wait(mMutex);
        return true;
    }
    return mCond.Wait(mMutex, static_cast<uint64_t>(microsec));
}

void MutexCond::Notify()
{
    mCond.Notify();
}

void MutexCond::NotifyAll()
{
    mCond.NotifyAll();
}

Rwlock::Rwlock()
{
    ::pthread_rwlock_init(&mNative, nullptr);
}

Rwlock::~Rwlock()
{
    ::pthread_rwlock_destroy(&mNative);
}

void Rwlock::Lock(int32_t mode)
{
    if (mode == PND_LOCK_MODE_READ)
    {
        ::pthread_rwlock_rdlock(&mNative);
    }
    else
    {
        ::pthread_rwlock_wrlock(&mNative);
    }
}

void Rwlock::Unlock()
{
    ::pthread_rwlock_unlock(&mNative);
}

bool Rwlock::Trylock(int32_t mode)
{
    if (mode == PND_LOCK_MODE_READ)
    {
        return ::pthread_rwlock_tryrdlock(&mNative) == 0;
    }
    return ::pthread_rwlock_trywrlock(&mNative) == 0;
}

pthread_rwlock_t& Rwlock::GetNative()
{
    return mNative;
}

Filelock::Filelock(const std::string& fileName)
    : mFd(-1), mCloseFd(true)
{
    mFd = ::open(fileName.c_str(), O_CREAT | O_RDWR, 0666);
    std::memset(&mLock, 0, sizeof(mLock));
}

Filelock::Filelock(int32_t fd)
    : mFd(fd), mCloseFd(false)
{
    std::memset(&mLock, 0, sizeof(mLock));
}

Filelock::~Filelock()
{
    if (mCloseFd && mFd >= 0)
    {
        ::close(mFd);
    }
}

void Filelock::SetLockMode(int32_t mode)
{
    switch (mode)
    {
    case PND_LOCK_MODE_READ:
        mLock.l_type = F_RDLCK;
        break;
    case PND_LOCK_MODE_WRITE:
        mLock.l_type = F_WRLCK;
        break;
    default:
        mLock.l_type = F_UNLCK;
        break;
    }
}

void Filelock::SetLockMember(int32_t mode, int64_t start, int64_t len)
{
    SetLockMode(mode);
    mLock.l_whence = SEEK_SET;
    mLock.l_start = start;
    mLock.l_len = len;
}

void Filelock::Lock(int32_t mode, int64_t start, int64_t len)
{
    if (mFd < 0)
    {
        return;
    }
    SetLockMember(mode, start, len);
    ::fcntl(mFd, F_SETLKW, &mLock);
}

void Filelock::Unlock()
{
    if (mFd < 0)
    {
        return;
    }
    SetLockMember(PND_LOCK_MODE_UNLCK, 0, 0);
    ::fcntl(mFd, F_SETLK, &mLock);
}

bool Filelock::Trylock(int32_t mode, int64_t start, int64_t len)
{
    if (mFd < 0)
    {
        return false;
    }
    SetLockMember(mode, start, len);
    return ::fcntl(mFd, F_SETLK, &mLock) == 0;
}

}
}
