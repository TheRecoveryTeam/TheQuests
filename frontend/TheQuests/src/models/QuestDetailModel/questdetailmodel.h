#ifndef QUESTDETAILMODEL_H
#define QUESTDETAILMODEL_H

#include <QObject>
#include "src/models/QuestShortModel/questshortmodel.h"

class QQmlEngine;
class QJSEngine;

namespace structures {
struct QuestDetail;
}
class QuestDetailModel: public QuestShortModel
{
    Q_OBJECT
    Q_PROPERTY(const QString& currCardId READ getCurrCardId NOTIFY currCardIdChanged)
    Q_PROPERTY(const QString& stage READ getStage NOTIFY stageChanged)

public:
    ~QuestDetailModel() = default;

    static QuestDetailModel* instance(QQmlEngine* qqmle = nullptr, QJSEngine* qjse = nullptr);

    const QString& getCurrCardId() const;
    void setCurrCardId(const QString &value);

    const QString& getStage() const;
    void setStage(const QString &value);

    void setAll(const QString& id,
                const QString& title,
                const QString& description,
                const QString& authorNickName,
                const QString& playerCount,
                const QString& imagePath,
                const QString& currCardId,
                const QString& stage);

    void setQuestDetail(structures::QuestDetail& questDetail);

signals:
    void currCardIdChanged (const QString&);
    void stageChanged (const QString&);

private:
    static QuestDetailModel* createInstance();
    explicit QuestDetailModel(QObject* parent = nullptr);

    QString currCardId;
    QString stage;
};

#endif // QUESTDETAILMODEL_H
