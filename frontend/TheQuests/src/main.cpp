#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml>

#include "src/models/CardModel/cardmodel.h"

int main(int argc, char *argv[])
{
    qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    CardModel currentCard(
                "id_12345",
                "questId_12345",
                "Card title from C++",
                "http://localhost:3000",
                "Very long description aa bb cc dd kek lol azaza, Lorem Ipsum dolor sit amet",
                "choose");

    engine.rootContext()->setContextProperty("currentCard", &currentCard);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
