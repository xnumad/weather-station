#ifndef WIDGET_H
#define WIDGET_H

#include "network.h"
#include <QWidget>
#include <QAbstractItemModel>

namespace Ui {
class Widget;
}

/**
 * @class Widget
 * @brief The user interface
 *
 * @date May 2019
 */
class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_chk_manual_resize_stateChanged();

    void readData();
private:
    Ui::Widget *ui;
    Network *network = new Network();
};

#endif // WIDGET_H
