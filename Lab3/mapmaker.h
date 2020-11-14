#ifndef MAPMAKER_H
#define MAPMAKER_H

#include <QDialog>

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
};

#endif // MAPMAKER_H
