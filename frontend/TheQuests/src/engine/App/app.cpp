#include <QtQml>
#include <QtWebView/QtWebView>
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

#include "src/config/network.h"

App::App() {
    QtWebView::initialize();
    registerTypes();
    addConstantsToContext();
}

bool App::init()
{
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return !engine.rootObjects().isEmpty();
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


    qmlRegisterType<ChooseCardModel>("models", 1, 0, "ChooseCardModel");
    qmlRegisterType<CardLinkList>("models", 1, 0, "CardLinkList");
    qmlRegisterType<AbstractCardController>("models", 1, 0, "AbstractCardController");
    qmlRegisterType<ResourceListModel>("models", 1, 0, "ResourceListModel");



    qmlRegisterSingletonType<UserController>("controllers", 1, 0, "UserController",
                                        reinterpret_cast<QObject*(*)(QQmlEngine*, QJSEngine*)>(UserController::instance));
    qmlRegisterType<LoginForm>("controllers", 1, 0, "LoginForm");
    qmlRegisterType<SignUpForm>("controllers", 1, 0, "SignUpForm");
    qmlRegisterType<SignUpFinishForm>("controllers", 1, 0, "SignUpFinishFrom");

    qmlRegisterSingletonType<QuestController>("controllers", 1, 0, "QuestController",
                                     reinterpret_cast<QObject*(*)(QQmlEngine*, QJSEngine*)>(QuestController::instance));

}

void App::addConstantsToContext() const
{
    engine.rootContext()->setContextProperty("oauthPath", config::network::oauth::getOauthUrl(
        config::network::oauth::VK_BASE,
        config::network::oauth::VK_CLIENT_ID,
        config::network::oauth::VK_REDIRECT_PATH,
        config::network::oauth::VK_API_V
    ));
}
