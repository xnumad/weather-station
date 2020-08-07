#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    connect(network, &Network::dataReady, this, &Widget::readData);
    ui->tbl_measurements->setColumnCount(5);
    //ui->tbl_measurements->setRowCount(1); //would be used in conjunction with method "insertRow"

    //Initialize a QStringList for the column headers
    QStringList labels = { "station_id", "time_measured", "temperature", "humidity", "relative_humidity"};
    ui->tbl_measurements->setHorizontalHeaderLabels(labels);

    //Alternatively:
    //ui->tbl_measurements->setHorizontalHeaderItem(0, new QTableWidgetItem("station_id"));

    network->fetchData();
}

void Widget::readData()
{
    qDebug() << "readData()";
    //https://stackoverflow.com/a/9166851
    QFile importedCSV("measurements.txt");
    QString data;
    QStringList lines;
    QStringList lineData;

    if (importedCSV.open(QFile::ReadOnly))
    {
        qDebug() << "opened";
        data = importedCSV.readAll();
        lines = data.split("\n");
        lines.removeFirst(); //remove first line (header names for columns)
        lines.removeLast(); //is an empty line we don't want to parse
        importedCSV.close();
    }

    ui->tbl_measurements->setRowCount(lines.size());

    for (int x = 0; x < lines.size(); x++)
    {
        lineData = lines.at(x).split(";");

        for (int y = 0; y < lineData.size(); y++)
        {
            if (y == 1) { //column time_measured (unixtime)
                //Don't display unixtime but convert and then display
                //https://stackoverflow.com/a/2935123
                QDateTime timestamp;
                timestamp.setTime_t(lineData.at(y).toUInt());
                ui->tbl_measurements->setItem(x, y, new QTableWidgetItem(timestamp.toString(Qt::SystemLocaleLongDate))); //Qt::SystemLocaleLongDate displays second which is helpful when a measurement is taken every 5 seconds
                continue;
            }
            //ui->tbl_measurements->insertRow(ui->tbl_measurements->rowCount()); //somehow adds empty rows //https://stackoverflow.com/a/6958211
            ui->tbl_measurements->setItem(x, y, new QTableWidgetItem(lineData.at(y)));
            //ui->tbl_measurements->item(x,y)->setText(rowData[y]);
        }
    }

    ui->tbl_measurements->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_chk_manual_resize_stateChanged()
{
    //https://stackoverflow.com/a/34190094
    if (ui->chk_manual_resize->isChecked())
        ui->tbl_measurements->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
    else
        ui->tbl_measurements->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}
