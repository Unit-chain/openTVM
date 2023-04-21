//
// Created by Kirill Zhukov on 01.02.2023.
//

#include "Lock.h"

// taken from cppreferece: https://en.cppreference.com/w/cpp/atomic/atomic_flag
bool SpinLock::lock() noexcept {
    while (locker.test_and_set(std::memory_order_acquire)) {  // acquire lock
        // Since C++20, it is possible to update atomic_flag's
        // value only when there is a chance to acquire the lock.
        // See also: https://stackoverflow.com/questions/62318642
    #if defined(__cpp_lib_atomic_flag_test)
        while (locker.test(std::memory_order_relaxed))        // test lock
    #endif
            ; // spin
    }
    return true;
}

void SpinLock::unlock() noexcept {
    locker.clear(std::memory_order_release);
}

bool Mutex::lock() noexcept {
    return this->m.try_lock();
}

void Mutex::unlock() noexcept {
    this->m.unlock();
}
