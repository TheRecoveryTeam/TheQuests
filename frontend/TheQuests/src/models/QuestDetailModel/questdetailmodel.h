#ifndef QUESTDETAILMODEL_H
#define QUESTDETAILMODEL_H
#include "src/models/QuestShortModel/questshortmodel.h"

class QuestDetailModel: public QuestShortModel
{
public:
    explicit QuestDetailModel(QObject* parent = nullptr);

    QuestDetailModel(
            const QString& id,
            const QString& title,
            const QString& description,
            const QString& authorNickName,
            const QString& playerCount,
            const QString& imagePath,
            const QString& currCardId,
            const QString& stage,
            QObject* parent = nullptr);

    const QString& getCurrCardId() const;
    void setCurrCardId(const QString &value);

    const QString& getStage() const;
    void setStage(const QString &value);

private:
    QString currCardId;
    QString stage;
};

#endif // QUESTDETAILMODEL_H
