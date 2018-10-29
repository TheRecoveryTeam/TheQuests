#ifndef MONGOCOMMAND_H
#define MONGOCOMMAND_H

#include <TGlobal>
#include <QStringList>

class TMongoDriver;


class MongoCommand
{
public:
    MongoCommand(const QString &path);
    ~MongoCommand();

    bool open(const QString &env);
    void close();
    QStringList getCollectionNames() const;

private:
    TMongoDriver *driver {nullptr};
    QString settingsPath;
    QString databaseName;

    T_DISABLE_COPY(MongoCommand)
    T_DISABLE_MOVE(MongoCommand)
};

#endif // MONGOCOMMAND_H
