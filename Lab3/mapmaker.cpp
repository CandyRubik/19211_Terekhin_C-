#include "mapmaker.h"
#include "ui_mapmaker.h"

mapMaker::mapMaker(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::mapMaker)
{
    ui->setupUi(this);
}

mapMaker::~mapMaker()
{
    delete ui;
}
