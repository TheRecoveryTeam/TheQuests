#ifndef QUESTDETAILMODEL_H
#define QUESTDETAILMODEL_H
#include "src/models/QuestShortModel/questshortmodel.h"

class QuestDetailModel: public QuestShortModel
{
    Q_OBJECT
    Q_PROPERTY(const QString& currCardId READ getCurrCardId NOTIFY currCardIdChanged)
    Q_PROPERTY(const QString& stage READ getStage NOTIFY stageChanged)

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

signals:
    void currCardIdChanged (const QString&);
    void stageChanged (const QString&);

private:
    QString currCardId;
    QString stage;
};

#endif // QUESTDETAILMODEL_H
