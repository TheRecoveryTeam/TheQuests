#ifndef PROCESSINFO_H
#define PROCESSINFO_H

#include <QList>
#include <QString>

namespace TreeFrog {


class ProcessInfo
{
public:
    ProcessInfo(qint64 pid);

    qint64 pid() const { return processId; }
    qint64 ppid() const;
    QString processName() const;
    bool exists() const;

    void terminate();  // SIGTERM
    void kill();       // SIGKILL
    void restart();    // SIGHUP
    bool waitForTerminated(int msecs = 10000);
    QList<qint64> childProcessIds() const;

    static void kill(qint64 ppid);
    static void kill(QList<qint64> pids);
    static QList<qint64> pidsOf(const QString &processName);
    static QList<qint64> allConcurrentPids();

private:
    qint64 processId;
};

}
#endif // PROCESSINFO_H
