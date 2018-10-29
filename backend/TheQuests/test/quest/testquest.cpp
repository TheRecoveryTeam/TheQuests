#include <TfTest/TfTest>
#include "../../models/questcollection.h"

class TestQuestCollection : public QObject {
    Q_OBJECT
private slots:
    void createData();
    void create();
};


void TestQuestCollection::createData() {
    QTest::addColumn<QString>("title");
    QTest::addColumn<QString>("description");
    QTest::addColumn<QString>("imagePath");
    QTest::addColumn<QString>("firstCardId");
    QTest::addColumn<QString>("anotherId");
    QTest::addColumn<QVariantMap>("resources");

    // Тестовые данные
    QVariantMap resources1;
    resources1["health"] = 50;
    resources1["stength"] = 35;
    QTest::newRow("Test1") << "Quest" << "Super quest" << "/img/img.png" << "dasdqwerqrw" << resources1;
}


void TestQuestCollection::create() {
    QFETCH(QString, title);
    QFETCH(QString, description);
    QFETCH(QString, imagePath);
    QFETCH(QString, firstCardId);
    QFETCH(QString, anotherId);
    QFETCH(QVariantMap, resources);

    Questcollection
    created = Questcollection::create(title, description, imagePath, firstCardId, anotherId, resources);
    QString id = created.id();
    Questcollection questCollection = Questcollection::get(id);
    QCOMPARE(questCollection.title(), title);
    QCOMPARE(questCollection.description(), description);
    QCOMPARE(questCollection.imagePath(), imagePath);
    QCOMPARE(questCollection.firstCardId(), firstCardId);
    QCOMPARE(questCollection.anotherId(), anotherId);
    QCOMPARE(questCollection.resources(), resources);
}


TF_TEST_MAIN(TestQuestCollection);
