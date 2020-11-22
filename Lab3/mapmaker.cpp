#include "mapmaker.h"
#include "ui_mapmaker.h"
#include "mapwidget.h"
#include <QPen>
#include <QBrush>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

mapMaker::mapMaker(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::mapMaker)
{
    ui->setupUi(this);
    this->setFixedSize (302, 350);
    map = new mapWidget(this);
    map->setMinimumSize(301, 301);
}


mapMaker::~mapMaker()
{
    delete map;
    delete ui;
}

void mapMaker::on_okButton_clicked()
{
    if(this->windowTitle() == "Настройка карты игрока 1")
    {
        std::vector<std::pair<std::pair<QPoint, std::string>, bool>>& ships = map->getShipsStatus();
        for(auto it = ships.begin(); it != ships.end(); ++it)
        {
            if(it->second == false)
            {
                QMessageBox::warning(this, "Внимание", "Вы разместили не все корабли, поэтому карта не может быть изменета!");
                return;
            }
        }
        QFile file("D:\\LabsC++\\Lab3\\info\\MapF.txt");
        if (file.open(QIODevice::WriteOnly))
        {
            QTextStream out(&file);
            out << map->getFlotilla().c_str();
        }
    }
    else
    {
        std::vector<std::pair<std::pair<QPoint, std::string>, bool>>& ships = map->getShipsStatus();
        for(auto it = ships.begin(); it != ships.end(); ++it)
        {
            if(it->second == false)
            {
                QMessageBox::warning(this, "Внимание", "Вы разместили не все корабли, поэтому карта не может быть изменета!");
                return;
            }
        }
        QFile file("D:\\LabsC++\\Lab3\\info\\MapS.txt");
        if (file.open(QIODevice::WriteOnly))
        {
            QTextStream out(&file);
            out << map->getFlotilla().c_str();
        }
    }
    close();
}
