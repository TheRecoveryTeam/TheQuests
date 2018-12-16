//
// Created by dpudov on 12.11.18.
//

#ifndef __USER_INTERRUPT_HANDLER__
#define __USER_INTERRUPT_HANDLER__

#include <iostream>
#include <mutex>
#include <condition_variable>
#include <signal.h>

static std::condition_variable _condition;
static std::mutex _mutex;

namespace networkhelper {
    class InterruptHandler {
    public:
        static void hookSIGINT() {
            signal(SIGINT, handleUserInterrupt);
        }

        static void handleUserInterrupt(int signal) {
            if (signal == SIGINT) {
                std::cout << "SIGINT trapped ..." << '\n';
                _condition.notify_one();
            }
        }

        static void waitForUserInterrupt() {
            std::unique_lock<std::mutex> lock{_mutex};
            _condition.wait(lock);
            std::cout << "user has signaled to interrupt program..." << '\n';
            lock.unlock();
        }
    };
}

#endif