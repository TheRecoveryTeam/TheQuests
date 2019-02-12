#ifndef CALL_ONCE_H
#define CALL_ONCE_H

#include <QtGlobal>
#include <QAtomicInt>
#include <QMutex>
#include <QWaitCondition>
#include <QThreadStorage>
#include <QThread>

namespace CallOnce {
    enum ECallOnce {
        CO_Request,
        CO_InProgress,
        CO_Finished
    };

    Q_GLOBAL_STATIC(QThreadStorage<QAtomicInt*>, once_flag)
}

template <class Function>
inline static void qCallOnce(Function func, QBasicAtomicInt& flag)
{
    int protectFlag = flag.fetchAndStoreAcquire(flag.load());

    if (protectFlag == CallOnce::CO_Finished)
        return;

    if (protectFlag == CallOnce::CO_Request && flag.testAndSetRelaxed(protectFlag,
                                                           CallOnce::CO_InProgress)) {
        func();
        flag.fetchAndStoreRelease(CallOnce::CO_Finished);
    }
    else {
        do {
            QThread::yieldCurrentThread();
        }
        while (!flag.testAndSetAcquire(CallOnce::CO_Finished, CallOnce::CO_Finished));
    }
}

template <class Function>
inline static void qCallOncePerThread(Function func)
{
    using namespace CallOnce;
    if (!once_flag()->hasLocalData()) {
        once_flag()->setLocalData(new QAtomicInt(CO_Request));
        qCallOnce(func, *once_flag()->localData());
    }
}

#endif // CALL_ONCE_H
