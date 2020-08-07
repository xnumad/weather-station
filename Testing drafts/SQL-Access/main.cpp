#include <QCoreApplication>

#include <QtSql/QSqlDatabase>
#include <QtSql/QSql>
#include <QtSql/QSqlQuery>

#include <QDebug>
#include <QtDebug>
#include <QCoreApplication>
#include <QStringList>

//#include <sql.h>
#include <QLibrary>
#include <QSql>
#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlDriverCreator>
#include <QSqlDriverCreatorBase>
#include <QSqlDriverPlugin>
#include <QSqlQuery>
#include <QSqlResult>
#include <QtSql>
#include <QtSqlDepends>
#include <QtSql/QSql>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");

    //Or as a pointer
    //QSqlDatabase *db = new QSqlDatabase();
    //db->addDatabase("QMYSQL");

    db.setHostName("localhost");
    db.setPort(3306);
    db.setDatabaseName("weatherStation");
    db.setUserName("root");
    db.setPassword("pw");
    qDebug() << db.open();

    //QSqlError err = db.lastError();
    //qDebug() << "type: " << err.type();
    //qDebug() << "valid: " << err.isValid();
    //qDebug() << "text: " << err.text();
    //qDebug() << "native-error-code: " << err.nativeErrorCode();
    //qDebug() << "db-text: " << err.databaseText();
    //qDebug() << "drv-text: " << err.driverText();

    db.close();
    db.removeDatabase("default");

    return a.exec();
}
