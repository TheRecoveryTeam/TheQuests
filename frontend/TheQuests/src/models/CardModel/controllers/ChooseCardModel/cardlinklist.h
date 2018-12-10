#ifndef CARDLINKLIST_H
#define CARDLINKLIST_H

#include <QAbstractListModel>
#include <QString>

class CardLinkList: public QAbstractListModel
{
    Q_OBJECT
public:
    enum {
        linkRole = Qt::UserRole + 1
    };

    CardLinkList(QObject* parent = nullptr);
    CardLinkList(const QVector<QString>& links, QObject* parent = nullptr);
    ~CardLinkList() = default;

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

    bool appendLink(const QString& link);

protected:
    QHash <int, QByteArray> roleNames() const;

private:
    QVector<QString> links;
};

#endif // CARDLINKLIST_H
