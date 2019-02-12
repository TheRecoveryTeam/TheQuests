//
// Created by dpudov on 12.11.18.
//

#ifndef __RUNTIME_UTILS__
#define __RUNTIME_UTILS__

#include <execinfo.h>
#include <unistd.h>

namespace networkhelper {
    class RuntimeUtils {
    public:
        static void printStackTrace() {
            const int MAX_CALLSTACK = 100;
            void *callstack[MAX_CALLSTACK];
            int frames;

            // get void*'s for all entries on the stack...
            frames = backtrace(callstack, MAX_CALLSTACK);

            // print out all the frames to stderr...
            backtrace_symbols_fd(callstack, frames, STDERR_FILENO);
        }
    };
}

#endif // __RUNTIME_UTILS__