#include "mapmaker.h"
#include "ui_mapmaker.h"
#include <QGraphicsView>
#include <QPen>
#include <QBrush>


mapMaker::mapMaker(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::mapMaker)
{
    ui->setupUi(this);
    QBrush brush;
    this->setFixedSize (400, 320);
    QGraphicsView *emptyMap = new QGraphicsView(this);
    QGraphicsScene *map = new QGraphicsScene(this);
    map->setSceneRect(0 , 0, 301, 301);
    emptyMap->setScene(map);
    for (int i = 0; i < 10; i++)
        for(int j = 0; j < 10; j++)
            map->addRect(i * 30, j * 30, 30, 30);

}

mapMaker::~mapMaker()
{
    delete ui;
}
