//
// Created by Kirill Zhukov on 01.02.2023.
//

#ifndef VM_WITH_HEAP_LOCK_H
#define VM_WITH_HEAP_LOCK_H

#include <mutex>
#include "atomic"
#include "pthread.h"

///  @brief abstract lock
/// @class Lock
class Lock {
public:
    virtual bool lock()  = 0;
    virtual void unlock() = 0;
};

/// @brief spinlock implementation of lock
/// @class SpinLock
class SpinLock : public Lock {
public:
    SpinLock() = default;

    /// @brief locking atomic_flag
    /// @return true if lock is ok, otherwise false.
    bool lock() noexcept override;
    /// @brief unlocking atomic_flag
    /// @return void
    void unlock() noexcept override;
protected:
    std::atomic_flag locker = ATOMIC_FLAG_INIT;
};

/// @brief basic mutex lock implementation
/// @class Mutex
class Mutex : public Lock {
public:
    /// @brief locking mutex
    /// @return true if lock is ok, otherwise false - lock exists.
    bool lock() noexcept override; // if false - then lock exists
    /// @brief unlocking atomic_flag
    /// @return void
    void unlock() noexcept override;
protected:
#if 0
    // for future usage
    void lockWaiting();
    std::condition_variable cv;
#endif
    std::mutex m;
};

/// @brief universal lock but only one type at the same time
/// @union uLock
/// @var uLock::sl - SpinLock, should be used for short-time locks
/// @var uLock::ml - Mutex, should be used for long-time locks
union uLock {
    SpinLock sl;
    Mutex ml;
};

#endif //VM_WITH_HEAP_LOCK_H
