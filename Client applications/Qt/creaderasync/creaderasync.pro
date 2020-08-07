QT = core

greaterThan(QT_MAJOR_VERSION, 4) {
    QT       += serialport network
} else {
    include($$QTSERIALPORT_PROJECT_ROOT/src/serialport/qt4support/serialport.prf)
}

CONFIG += console
CONFIG -= app_bundle

TARGET = creaderasync
TEMPLATE = app

HEADERS += \
    serialportreader.h \
    parser.h \
    network.h

SOURCES += \
    main.cpp \
    serialportreader.cpp \
    parser.cpp \
    network.cpp
