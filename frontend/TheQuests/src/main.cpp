#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include <QGuiApplication>

#include "src/engine/App/app.h"
#include "src/engine/Store/store.h"
#include "src/models/CardModel/cardmodel.h"
#include "src/models/QuestShortModel/questshortmodel.h"

#define MyClassInstance Singleton<MyClass>::instance()

static QObject *singletonTypeProvider(QQmlEngine *, QJSEngine *)
{

    return CardModel::instance();
}

int main(int argc, char *argv[])
{
    qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));

    qmlRegisterType<QObject>("application", 1, 0, "QObject");
    qmlRegisterType<Store>("application", 1, 0, "Store");
    qmlRegisterSingletonType<CardModel>("models", 1, 0, "CardModel", singletonTypeProvider);

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    App application(nullptr);
    auto store = new Store(&application);
    application.setStore(store);

//    CardModel *obj = qobject_cast<CardModel*>(CardModel::instance());
    CardModel::instance()->setAll("id_12345", "questId_12345", "Card title from C++", "http://localhost:3000",
                                  "Very long description aa bb cc dd kek lol azaza, Lorem Ipsum dolor sit amet",
                                   "choose",
                                   nullptr);
//    store->addModel("loadedCard", CardModel::instance());

    engine.rootContext()->setContextProperty("application", &application);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
