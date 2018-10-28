#ifndef CARDLINK_H
#define CARDLINK_H

#include <QAbstractListModel>
#include <QVector>
#include "src/config/resourcetypes.h"
#include "src/models/structures/resourceitem.h"

class CardLink : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(const QString& answer READ getAnswer NOTIFY answerChanged)

public:
    enum {
        typeRole = Qt::UserRole + 1,
        valueRole
    };

    explicit CardLink(QObject* parent = nullptr);
    CardLink(const QString& answer,
             const QVector<structures::ResourceItem>& resources,
             QObject* parent = nullptr);
    ~CardLink() = default;

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;

    const QString& getAnswer() const;
    void setAnswer(const QString& value);

signals:
    void answerChanged(const QString& newAnswer);

private:
    QHash <int, QByteArray> rolenames() const;

    QString answer;
    QVector<structures::ResourceItem> resources;
};

#endif // CARDLINK_H
