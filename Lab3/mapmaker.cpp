#include "mapmaker.h"
#include "ui_mapmaker.h"
#include "mapwidget.h"
#include <QPen>
#include <QBrush>


mapMaker::mapMaker(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::mapMaker)
{
    ui->setupUi(this);
    this->setFixedSize (303, 350);
    mapWidget *map = new mapWidget(this);
    map->setScene(&map->map_scene);
    QPainter painter(this);
    map->drawBackground(&painter, QRectF(0, 0, 301, 301));
    //  QPainter --- mouse press event (QGraphicsScene)

}


mapMaker::~mapMaker()
{
    delete ui;
}
