#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include <QGuiApplication>
#include <QDebug>

#include "src/engine/App/app.h"
#include "src/engine/Store/store.h"
#include "src/models/CardModel/cardmodel.h"
#include "src/models/QuestShortModel/questshortmodel.h"
#include "src/models/QuestDetailModel/questdetailmodel.h"
#include"src/models/UserModel/usermodel.h"

#include "src/models/CardModel/controllers/abstractcardcontroller.h"
#include "src/models/CardModel/controllers/ChooseCardModel/choosecardmodel.h"
#include "src/models/CardModel/controllers/ChooseCardModel/cardlinklist.h"
#include "src/models/CardModel/controllers/ChooseCardModel/cardlink.h"
#include "src/data_structures/network/CardGetResponse/cardgetresponse.h"

static QObject *singletonCardModelProvider(QQmlEngine *, QJSEngine *)
{
    return CardModel::instance();
}

static QObject *singletonQuestDetailModelProvider(QQmlEngine *, QJSEngine *)
{
    return QuestDetailModel::instance();
}

static QObject *singletonUserModelProvider(QQmlEngine *, QJSEngine *)
{
    return UserModel::instance();
}

int main(int argc, char *argv[])
{
    data_structures::CardGetResponse card_get;
    QJsonDocument doc(card_get.toJSON());
    qDebug() << doc.toJson(QJsonDocument::Compact);

    qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));
    qmlRegisterType<QObject>("application", 1, 0, "QObject");
    qmlRegisterType<Store>("application", 1, 0, "Store");
    qmlRegisterSingletonType<CardModel>("models", 1, 0, "CardModel", singletonCardModelProvider);
    qmlRegisterSingletonType<QuestDetailModel>("models", 1, 0, "QuestDetailModel", singletonQuestDetailModelProvider);
    qmlRegisterSingletonType<UserModel>("models", 1, 0, "UserModel", singletonUserModelProvider);
    qmlRegisterType<ChooseCardModel>("application", 1, 0, "ChooseCardModel");
    qmlRegisterType<CardLinkList>("application", 1, 0, "CardLinkList");
    qmlRegisterType<CardLink>("application", 1, 0, "CardLink");
    qmlRegisterType<AbstractCardController>("application", 1, 0, "AbstractCardController");

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    App application(nullptr);
    auto store = new Store(&application);
    application.setStore(store);

    auto cardChooseController = new ChooseCardModel();
    auto cardLinksList = new CardLinkList();
    CardModel::instance()->setController(cardChooseController);
    cardChooseController->setLinksList(cardLinksList);

    for (int i = 0; i < 3; i++) {
        auto newLink = new CardLink();
        newLink->setAnswer(QString("Answer %1").arg(i + 1));
        cardLinksList->appendLink(newLink);
    }

    CardModel::instance()->setAll("id_12345",
                                  "questId_12345",
                                  "Card title from C++",
                                  "http://img.uduba.com/uduba.com/user_data/b6/ae/b6aeede60c86ad480eec162b3de65ec7_783x0.jpg?uduba_pid=6232881",
                                  "Very long description aa bb cc dd kek lol azaza, Lorem Ipsum dolor sit amet",
                                   "choose",
                                   cardChooseController
                                  );

    engine.rootContext()->setContextProperty("application", &application);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
