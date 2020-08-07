#ifndef NETWORK_H
#define NETWORK_H

#include <QtNetwork>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
#include <QUrl>
#include <string>
#include <fstream>

#include <QtCore>

#include <cstdio>

using namespace std;

QT_USE_NAMESPACE

QT_BEGIN_NAMESPACE

QT_END_NAMESPACE

/**
 * @class Network
 * @brief Connects and retrieves data from a server
 *
 * Uses QNetworkAccessManager and QNetworkRequest for sending a request
 * @date May 2019
 */
class Network : public QObject
{
    Q_OBJECT
public:
    Network();
    void fetchData();

signals:
    void dataReady();

private:
    QNetworkAccessManager *manager = new QNetworkAccessManager();
    QNetworkRequest *request = new QNetworkRequest(QUrl("http://localhost/measurements.csv"));
    //QNetworkReply *reply;
public slots:
    void downloadFinished(QNetworkReply* reply);
};

#endif // NETWORK_H
