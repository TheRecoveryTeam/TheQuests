#include <TfTest/TfTest>
#include "../../models/userscollection.h"

class TestUsersCollection : public QObject {
    Q_OBJECT
private slots:
    void createData();
    void create();
    void remove();
};


void TestUsersCollection::createData() {
    QTest::addColumn<QString>("username");
    QTest::addColumn<QString>("email");
    QTest::addColumn<QString>("password");

    // Тестовые данные
    QTest::newRow("Test1") << "admin" << "admin@mail.ru" << "admin";
}


void TestUsersCollection::create() {
    QFETCH(QString, username);
    QFETCH(QString, email);
    QFETCH(QString, password);

    Userscollection created = Userscollection::create(username, email, password);
    QString id = created.id();
    Userscollection usersCollection = Userscollection::get(id);
    QCOMPARE(usersCollection.username(), username);
    QCOMPARE(usersCollection.email(), email);
    QCOMPARE(usersCollection.password(), password);
}


TF_TEST_MAIN(TestUsersCollection);
