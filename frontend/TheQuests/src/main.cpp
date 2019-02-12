#include <QGuiApplication>
#include <QtQml>
#include <QGuiApplication>

#include "src/engine/App/app.h"
#include "src/engine/HttpRequester/httprequester.h"

int main(int argc, char *argv[])
{
    qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    App application;
    if (!application.init()) {
        return -1;
    }

    return app.exec();
}
