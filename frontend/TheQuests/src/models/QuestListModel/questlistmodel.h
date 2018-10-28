#ifndef QUESTLISTMODEL_H
#define QUESTLISTMODEL_H
#include <QAbstractListModel>
#include "src/models/QuestShortModel/questshortmodel.h"

class QuestListModel: public QAbstractListModel
{
    Q_OBJECT
public:

    explicit QuestListModel(QObject* parent = nullptr);
    QuestListModel(QVector<QuestShortModel*> listQuests,
                   QObject* parent = nullptr);

    enum Roles{
        questRole = Qt::UserRole + 1
    };

    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QHash<int, QByteArray> roleNames() const;
    void add(QuestShortModel* quest);

    const QVector<QuestShortModel*>& getListQuests() const;
    void setListQuests(const QVector<QuestShortModel*> &value);

private:
    QVector<QuestShortModel*> listQuests;
};

#endif // QUESTLISTMODEL_H
