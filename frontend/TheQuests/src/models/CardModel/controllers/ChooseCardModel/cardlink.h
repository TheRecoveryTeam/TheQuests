#ifndef CARDLINK_H
#define CARDLINK_H

#include <QObject>
#include <map>
#include <src/config/resourcetypes.h>

class CardLink : public QObject
{
    Q_OBJECT
public:
    explicit CardLink(QObject *parent = nullptr);
    CardLink(const QString& answer,
             const std::map<config::ResourceTypes, int>& influenceMap,
             QObject* parent = nullptr);

    const QString& getAnswer() const;
    void setAnswer(const QString& value);

    Q_INVOKABLE int getInfluence(const config::ResourceTypes& rt) const;

    void setInfluenceMap(const std::map<config::ResourceTypes, int>& value);
    void rewriteInfluence(const config::ResourceTypes& rt, int magnitude);

signals:

private:
    QString answer;
    std::map<config::ResourceTypes, int> influenceMap;
};

#endif // CARDLINK_H
