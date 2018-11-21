#include <TfTest/TfTest>
#include "../../models/cardcollection.h"

class TestCardCollection : public QObject {
    Q_OBJECT
private slots:
    void createData();
    void create();
};


void TestCardCollection::createData() {
    QTest::addColumn<QString>("questId");
    QTest::addColumn<QString>("title");
    QTest::addColumn<QString>("imagePath");
    QTest::addColumn<QString>("description");
    QTest::addColumn<QVariantMap>("links");
    QTest::addColumn<QString>("type");

    // Тестовые данные
    QVariantMap links1;
    links1["yes"] = "ababcacabaa";
    links1["no"] = "bcababababa";
    QTest::newRow("Test1") << "ababababab" << "Super card" << "/img/img.png" << "Best description" << links1 << "finish";
}


void TestCardCollection::create() {
    QFETCH(QString, questId);
    QFETCH(QString, title);
    QFETCH(QString, imagePath);
    QFETCH(QString, description);
    QFETCH(QVariantMap, links);
    QFETCH(QString, type);

    Cardcollection created = Cardcollection::create(questId, title, imagePath, description, links, type);
    QString id = created.id();
    Cardcollection cardCollection = Cardcollection::get(id);
    QCOMPARE(cardCollection.questId(), questId);
    QCOMPARE(cardCollection.title(), title);
    QCOMPARE(cardCollection.imagePath(), imagePath);
    QCOMPARE(cardCollection.description(), description);
    QCOMPARE(cardCollection.links(), links);
    QCOMPARE(cardCollection.type(), type);
}


TF_TEST_MAIN(TestCardCollection);
