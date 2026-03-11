#include <QtTest/QtTest>
#include <QtSql>

class ContactTest : public QObject
{
    Q_OBJECT

private slots:

    void testDatabaseConnection()
    {
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName(":memory:");

        QVERIFY(db.open());
    }

    void testInsertContact()
    {
        QSqlQuery query;

        query.exec("CREATE TABLE contacts ("
                   "id INTEGER PRIMARY KEY,"
                   "name TEXT,"
                   "mobile TEXT,"
                   "email TEXT,"
                   "birthday TEXT)");

        query.prepare("INSERT INTO contacts(name,mobile,email,birthday) "
                      "VALUES('John','1234567890','john@test.com','2000-01-01')");

        QVERIFY(query.exec());
    }

    void testEmailValidation()
    {
        QString email = "test@email.com";
        QVERIFY(email.contains("@"));
    }
};

QTEST_MAIN(ContactTest)
#include "test_contacts.moc"
