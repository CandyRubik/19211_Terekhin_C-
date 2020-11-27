#ifndef MAPMAKER_H
#define MAPMAKER_H

#include <QDialog>
#include <QGraphicsScene>
#include "mapmakerwidget.h"

namespace Ui {
class mapMaker;
}

class mapMaker : public QDialog
{
    Q_OBJECT
    mapWidget *map;
public:
    explicit mapMaker(QWidget *parent = nullptr);
    ~mapMaker();
private slots:
    void on_okButton_clicked();

private:
    Ui::mapMaker *ui;

};

#endif // MAPMAKER_H
