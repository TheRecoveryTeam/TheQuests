#ifndef TJSMODULE_H
#define TJSMODULE_H

#include <QString>
#include <QObject>
#include <QStringList>
#include <QJSValue>
#include <QDir>
#include <QMap>
#include <QMutex>
#include <TGlobal>

class QJSEngine;
class TJSInstance;


class T_CORE_EXPORT TJSModule : public QObject
{
public:
    TJSModule(QObject *parent = nullptr);
    virtual ~TJSModule();

    QJSValue evaluate(const QString &program, const QString &fileName = QString(), int lineNumber = 1);
    QJSValue call(const QString &func, const QJSValue &arg);
    QJSValue call(const QString &func, const QJSValueList &args = QJSValueList());
    TJSInstance callAsConstructor(const QString &constructorName, const QJSValue &arg);
    TJSInstance callAsConstructor(const QString &constructorName, const QJSValueList &args = QJSValueList());
    QString modulePath() const { return moduleFilePath; }

    QJSValue import(const QString &moduleName);
    QJSValue import(const QString &defaultMember, const QString &moduleName);

private:
    QJSEngine *jsEngine;
    QMap<QString, QString> loadedFiles;
    QJSValue *funcObj;
    QString lastFunc;
    QString moduleFilePath;
    QMutex mutex;

    T_DISABLE_COPY(TJSModule)
    T_DISABLE_MOVE(TJSModule);

    friend class TJSLoader;
    friend class TReactComponent;
};

#endif // TJSMODULE_H
