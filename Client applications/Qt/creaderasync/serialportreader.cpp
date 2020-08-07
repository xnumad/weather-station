/****************************************************************************
**
** Copyright (C) 2013 Laszlo Papp <lpapp@kde.org>
** Contact: http://www.qt-project.org/legal
**
** This file is part of the QtSerialPort module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "serialportreader.h"

QT_USE_NAMESPACE

/**
 * @brief Constructor method
 * @param serialPort The serial interface to read data from
 *
 * Initializes attributes, connects signals with slots and starts the timer with an interval of 5 seconds
 */
SerialPortReader::SerialPortReader(QSerialPort *serialPort)
    : QObject()
    , serialPort(serialPort)
    , standardOutput(stdout)
{
    connect(serialPort, SIGNAL(readyRead()), SLOT(handleReadyRead()));
    connect(&timer, SIGNAL(timeout()), SLOT(handleTimeout()));
    connect(serialPort, SIGNAL(error(QSerialPort::SerialPortError)), SLOT(handleError(QSerialPort::SerialPortError)));

    timer.start(5000);
}

/**
 * @brief Method to handle the emitted signal readyRead() from serialPort
 */
void SerialPortReader::handleReadyRead()
{
    readData.append(serialPort->readAll());

    if (!timer.isActive())
        timer.start(5000);
}

/**
 * @brief Method to handle the emitted signal timeout() from serialPort
 */
void SerialPortReader::handleTimeout()
{
    if (readData.isEmpty()) {
        //m_standardOutput << "" << endl;
        return;
    }

    standardOutput << readData << endl; //print all received data
    QString output = readData;
    readData = NULL;

    handleData(output);
}

/**
 * @brief Method to handle processing of received data
 *
 * Only called by handleTimeout() if usable data was received
 */
void SerialPortReader::handleData(QString receivedData)
{
    receivedData.chop(1); //remove last char (\n) for proper parsing

    Parser parser;
    Network network;

    //Parse and send measurement
    network.send(parser.parseTemperature(receivedData), parser.parseHumidity(receivedData));

    //OR use array to parse measurement (but it takes more lines!)
    //QString *measurement = parser.parseBoth(receivedData);
    //network.send(QString(measurement[0]), QString(measurement[1]));
    //delete measurement;
}

/**
 * @brief Method to handle the emitted signal error(QSerialPort::SerialPortError) from serialPort
 * @param serialPortError The error to be read
 */
void SerialPortReader::handleError(QSerialPort::SerialPortError serialPortError)
{
    qDebug() << QSerialPort::ReadError;
    if (serialPortError == QSerialPort::ReadError) {
        standardOutput << QObject::tr("An I/O error occurred while reading the data from port %1, error: %2").arg(serialPort->portName()).arg(serialPort->errorString()) << endl;
        //QCoreApplication::exit(1);
    }
}

SerialPortReader::~SerialPortReader()
{
}
