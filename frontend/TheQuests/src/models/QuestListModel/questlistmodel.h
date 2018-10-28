#ifndef QUESTLISTMODEL_H
#define QUESTLISTMODEL_H
#include <QAbstractListModel>
#include "src/models/QuestShortModel/questshortmodel.h"
#include <vector>

class QuestListModel: public QAbstractListModel
{
public:

    explicit QuestListModel(QObject* parent = nullptr);

    QuestListModel();
private:
    std::vector<QuestShortModel> listQuests;
};

#endif // QUESTLISTMODEL_H
