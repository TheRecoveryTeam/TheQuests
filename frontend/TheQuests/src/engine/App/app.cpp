#include <QtQml>
#include "app.h"

#include "src/models/CardModel/cardmodel.h"
#include "src/models/QuestShortModel/questshortmodel.h"
#include "src/models/QuestDetailModel/questdetailmodel.h"
#include "src/models/UserModel/usermodel.h"

#include "src/models/CardModel/controllers/abstractcardcontroller.h"
#include "src/models/CardModel/controllers/ChooseCardModel/choosecardmodel.h"
#include "src/models/CardModel/controllers/ChooseCardModel/cardlinklist.h"
#include "src/models/CardModel/controllers/ChooseCardModel/cardlink.h"
#include "src/data_structures/network/CardGetResponse/cardgetresponse.h"

App::App(QObject *parent):
    QObject(parent)
{
    registerTypes();
}

void App::registerTypes() const
{
    qmlRegisterType<QObject>("application", 1, 0, "QObject");

    qmlRegisterSingletonType<CardModel>("models", 1, 0, "CardModel",
                                        reinterpret_cast<QObject*(*)(QQmlEngine*, QJSEngine*)>(CardModel::instance));
    qmlRegisterSingletonType<QuestDetailModel>("models", 1, 0, "QuestDetailModel",
                                               reinterpret_cast<QObject*(*)(QQmlEngine*, QJSEngine*)>(QuestDetailModel::instance));
    qmlRegisterSingletonType<UserModel>("models", 1, 0, "UserModel",
                                        reinterpret_cast<QObject*(*)(QQmlEngine*, QJSEngine*)>(UserModel::instance));

    qmlRegisterType<ChooseCardModel>("application", 1, 0, "ChooseCardModel");
    qmlRegisterType<CardLinkList>("application", 1, 0, "CardLinkList");
    qmlRegisterType<CardLink>("application", 1, 0, "CardLink");
    qmlRegisterType<AbstractCardController>("application", 1, 0, "AbstractCardController");
}
