#include "network.h"

Network::Network()
{
}

/**
 * @brief Sends a GET request to a hardcoded server
 * @param temperature The temperature value to send to the server
 * @param relative_humidity The relative humidity value to send to the server
 *
 * Inserts the given parameters temperature and relative_humidity into the URL to send a GET request to and sends the request
 *
 * https://stackoverflow.com/a/46947157
 *
 * https://doc.qt.io/qt-5/qnetworkaccessmanager.html#details
 *
 * https://doc.qt.io/qt-5/qnetworkrequest.html#details
 */
void Network::send(QString temperature, QString relative_humidity)
{
    string urlString = string("http://localhost/input.php?password=123456&station_id=1&temperature=") + string(temperature.toStdString()) + string("&relative_humidity=") + string(relative_humidity.toStdString());
    request->setUrl(QUrl(urlString.c_str()));
    manager->get(*request);
}
