#ifndef NETWORK_H
#define NETWORK_H

#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
#include <QUrl>
#include <string>

using namespace std;

/**
 * @class Network
 * @brief Connects and sends data to a server
 *
 * Uses QNetworkAccessManager and QNetworkRequest for sending a request
 * @date May 2019
 */
class Network
{
public:
    Network();
    void send(QString temperature, QString relative_humidity);

private:
    QNetworkAccessManager *manager = new QNetworkAccessManager();
    QNetworkRequest *request = new QNetworkRequest();
    string urlString;
};

#endif // NETWORK_H
