#include <QDebug>
#include <QJsonObject>
#include <QJsonArray>
#include "questcontroller.h"

#include "src/utils/singleton.h"
#include "src/engine/HttpRequester/httprequester.h"
#include "src/models/QuestDetailModel/questdetailmodel.h"
#include "src/config/apiurls.h"
#include "src/data_structures/network/QuestGetRequest/questgetrequest.h"
#include "src/data_structures/network/QuestCreate/questcreate.h"
#include "src/data_structures/network/QuestGetResources/questgetresources.h"
#include "src/data_structures/network/QuestGetQuestList/questgetquestlist.h"
#include "src/mappers/CardMapper/cardmapper.h"
#include "src/mappers/QuestMapper/questmapper.h"
#include "src/mappers/QuestMapper/questlistmapper.h"
#include "src/mappers/ResourcesMapper/resourcesmapper.h"
#include "src/models/structures/questdetail.h"
#include "src/models/structures/resourceitem.h"
#include "src/models/structures/questlist.h"
#include "src/models/QuestListsContainerModel/questlistscontainermodel.h"
#include "src/models/QuestListModel/questlistmodel.h"

QuestController *QuestController::instance()
{
    return Singleton<QuestController>::instance(QuestController::createInstance);
}

void QuestController::getQuestDetail(const QString &questId) const
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

void QuestController::getResources(const QString &questId) const
{
    httpRequester->doGet(
                config::apiUrls::quest::GET_RESOURCES,
                data_structures::QuestGetResources(questId),
    [this](QJsonObject obj) {
            ResourcesMapper mapper;
            auto resources = mapper.convertResources(obj);
    },
    [](QJsonObject obj){
        qDebug() << "error" << obj;
    });
}

void QuestController::getQuestList(const QString &page,
                                   const QString &limit,
                                   const QString &authorId,
                                   const QString &asc,
                                   const QString &stage)
{
    httpRequester->doGet(
                config::apiUrls::quest::GET_QUEST_LIST,
                data_structures::QuestGetQuestList(page, limit, authorId, asc, stage),
    [this, stage](QJsonObject obj) {
            QuestListMapper mapper;
            auto questList = mapper.convertQuestList(obj);
            if (stage == "end")
                questListsContainerModel->getCompletedQuestListModel()->setListQuests(questList);
            else if (stage == "progress")
                questListsContainerModel->getInProgressQuestListModel()->setListQuests(questList);
            else {
                // TODO :
            }

    },
    [](QJsonObject obj){
        qDebug() << "error" << obj;
    });
}

void QuestController::create(const QString &title,
                             const QString &description,
                             const QString &image)
{
    httpRequester->doPost(
                config::apiUrls::quest::CREATE,
                data_structures::QuestCreate(title, description, image),
    [this](QJsonObject obj){
        if(
                obj["id"].isString()
                && obj["title"].isString()
                && obj["description"].isString()
                && obj["imagePath"].isString()
                && obj["firstCardId"].isString()
                && obj["authorNickname"].isString()
                && obj["playerCount"].isString()) {
            // TODO :
        }
        else {
            // TODO :
        }


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
    questDetailModel(QuestDetailModel::instance()),
    questListsContainerModel(QuestListsContainerModel::instance())
{}
