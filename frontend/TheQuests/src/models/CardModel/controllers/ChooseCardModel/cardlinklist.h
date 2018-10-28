#ifndef CARDLINKLIST_H
#define CARDLINKLIST_H

#include <QAbstractListModel>
#include "./cardlink.h"

class CardLinkList: public QAbstractListModel
{
    Q_OBJECT
public:
    enum {
        linkRole = Qt::UserRole + 1,
    };

    explicit CardLinkList(QObject* parent = nullptr);
    CardLinkList(const QVector<CardLink*>& links, QObject* parent = nullptr);
    ~CardLinkList() = default;

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;

private:
    QHash <int, QByteArray> rolenames() const;

    QVector<CardLink*> links;
};

#endif // CARDLINKLIST_H
