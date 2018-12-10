#include <QtQml>
#include "app.h"

#include "src/models/CardModel/cardmodel.h"
#include "src/models/QuestShortModel/questshortmodel.h"
#include "src/models/QuestDetailModel/questdetailmodel.h"
#include "src/models/ResourceListModel/resourcelistmodel.h"
#include "src/models/UserModel/usermodel.h"

#include "src/models/CardModel/controllers/abstractcardcontroller.h"
#include "src/models/CardModel/controllers/ChooseCardModel/choosecardmodel.h"
#include "src/models/CardModel/controllers/ChooseCardModel/cardlinklist.h"

#include "src/controllers/CardController/cardcontroller.h"
#include "src/controllers/UserController/usercontroller.h"
#include "src/controllers/UserController/LoginForm/loginform.h"
#include "src/controllers/UserController/SignUpForm/signupform.h"
#include "src/controllers/UserController/SignUpFinishForm/signupfinishform.h"

#include "src/controllers/QuestController/questcontroller.h"

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


    qmlRegisterSingletonType<CardController>("controllers", 1, 0, "CardController",
                                        reinterpret_cast<QObject*(*)(QQmlEngine*, QJSEngine*)>(CardController::instance));


    qmlRegisterType<ChooseCardModel>("application", 1, 0, "ChooseCardModel");
    qmlRegisterType<CardLinkList>("application", 1, 0, "CardLinkList");
    qmlRegisterType<AbstractCardController>("application", 1, 0, "AbstractCardController");
    qmlRegisterType<ResourceListModel>("application", 1, 0, "ResourceListModel");



    qmlRegisterSingletonType<UserController>("controllers", 1, 0, "UserController",
                                        reinterpret_cast<QObject*(*)(QQmlEngine*, QJSEngine*)>(UserController::instance));
    qmlRegisterType<LoginForm>("application", 1, 0, "LoginForm");
    qmlRegisterType<SignUpForm>("application", 1, 0, "SignUpForm");
    qmlRegisterType<SignUpFinishForm>("application", 1, 0, "SignUpFinishFrom");

    qmlRegisterSingletonType<QuestController>("controllers", 1, 0, "QuestController",
                                     reinterpret_cast<QObject*(*)(QQmlEngine*, QJSEngine*)>(QuestController::instance));

}
