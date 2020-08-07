#include "network.h"

QT_USE_NAMESPACE

Network::Network()
{
    connect(manager, SIGNAL(finished(QNetworkReply*)), SLOT(downloadFinished(QNetworkReply*)));
}

/**
 * @brief Sends a GET request to a hardcoded server to fetch measurements
 *
 * https://stackoverflow.com/a/46947157
 *
 * https://doc.qt.io/qt-5/qnetworkaccessmanager.html#details
 *
 * https://doc.qt.io/qt-5/qnetworkrequest.html#details
 */
void Network::fetchData()
{
    manager->get(*request);
    qDebug() << "Requested";
}

/**
 * @brief Handles the finished signal of the object manager of class type QNetworkAccessManager
 * @param reply The network reply from the manager
 */
void Network::downloadFinished(QNetworkReply *reply)
{

    qDebug() << "Finished:";
    qDebug() << reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();

    //Still a bug?
    //https://forum.qt.io/topic/50516/qnetworkreply-readall-gets-empty-data-on-finished/23
    QByteArray answerBytes = reply->readAll();

    if (!(answerBytes.isEmpty() || answerBytes.isNull()))
    {
        fstream file;
        file.open("measurements.txt", ios::out);
        if(file.is_open())
        {
            for (int i = 0; i < answerBytes.size(); i++) {
                file << answerBytes.at(i);
            }
            file.close();
        }
    }
    qDebug() << "saved";
    emit dataReady();
}
