#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include <QGuiApplication>
#include <QDebug>

#include <src/data_structures/network/CardGetRequest/cardgetrequest.h>

#include "src/engine/App/app.h"

#include "src/models/CardModel/cardmodel.h"
#include "src/models/CardModel/controllers/abstractcardcontroller.h"
#include "src/models/CardModel/controllers/ChooseCardModel/choosecardmodel.h"
#include "src/models/CardModel/controllers/ChooseCardModel/cardlinklist.h"
#include "src/models/CardModel/controllers/ChooseCardModel/cardlink.h"
#include "src/models/UserModel/usermodel.h"
#include "src/engine/HttpRequester/httprequester.h"
#include "src/controllers/CardController/cardcontroller.h"

int main(int argc, char *argv[])
{
    qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));


    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    App application(nullptr);

    auto cardChooseController = new ChooseCardModel();
    auto cardLinksList = new CardLinkList();
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

    CardController::instance()->get("card_one_id");
    UserModel::instance()->setToken("authenticated");

    return app.exec();
}
