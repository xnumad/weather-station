#include "widget.h"
#include <QApplication>

QT_USE_NAMESPACE

/**
 * @mainpage tableViewer
 * Reads measurement data from the server and displays it in a table
 */

/**
 * @brief main
 * @param argc
 * @param argv
 * @return
 *
 * Opens the widget
 */
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();

    return a.exec();
}
