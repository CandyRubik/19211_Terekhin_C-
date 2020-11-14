#ifndef MAPMAKER_H
#define MAPMAKER_H

#include <QDialog>
#include <QVector>
#include <QGraphicsScene>

namespace Ui {
class mapMaker;
}

class mapMaker : public QDialog
{
    Q_OBJECT

public:
    explicit mapMaker(QWidget *parent = nullptr);
    ~mapMaker();

private:
    Ui::mapMaker *ui;
    QVector<QGraphicsRectItem *> array;
};

#endif // MAPMAKER_H
