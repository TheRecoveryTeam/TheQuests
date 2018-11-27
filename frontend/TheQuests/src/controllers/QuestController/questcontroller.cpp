#include <QDebug>
#include <QJsonObject>

#include "questcontroller.h"

#include "src/utils/singleton.h"
#include "src/engine/HttpRequester/httprequester.h"
#include "src/models/QuestDetailModel/questdetailmodel.h"
#include "src/config/apiurls.h"
#include "src/data_structures/network/QuestGetRequest/questgetrequest.h"
#include "src/mappers/CardMapper/questmapper.h"
#include "src/models/structures/questdetail.h"

QuestController *QuestController::instance()
{
    return Singleton<QuestController>::instance(QuestController::createInstance);
}

void QuestController::get(const QString &questId) const
{
    httpRequester->doGet(
                config::apiUrls::quest::GET,
                data_structures::QuestGetRequest(questId),
    [this](QJsonObject obj) {

        QuestMapper mapper;
        auto questDetail = mapper.convertQuestDetail(obj);
        questDetailModel->setQuestDetail(questDetail);
    },
    [](QJsonObject obj){
        qDebug() << "error" << obj;
    });
}

QuestController *QuestController::createInstance()
{
    return new QuestController();
}

QuestController::QuestController(QObject* parent):
    AbstractContoller(parent, HttpRequester::instance()),
    questDetailModel(QuestDetailModel::instance())
{}
