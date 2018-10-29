#include <TfTest/TfTest>
#include "../../models/tokencollection.h"

class TestTokenCollection : public QObject {
    Q_OBJECT
private slots:
    void createData();
    void create();
};


void TestTokenCollection::createData() {
    QTest::addColumn<QString>("key");
    QTest::addColumn<QString>("expires");

    // Тестовые данные
    QTest::newRow("Test1") << "afafafafaf" << "124124515";
}


void TestTokenCollection::create() {
    QFETCH(QString, key);
    QFETCH(QString, expires);

    Tokencollection created = Tokencollection::create(key, expires);
    QString id = created.id();
    Tokencollection tokenCollection = Tokencollection::get(id);
    QCOMPARE(tokenCollection.key(), key);
    QCOMPARE(tokenCollection.expires(), expires);
}


TF_TEST_MAIN(TestTokenCollection);
