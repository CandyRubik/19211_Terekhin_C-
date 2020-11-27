#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QDialog>
#include "gamefield.h"

namespace Ui {
class GameWindow;
}


class GameWindow : public QDialog
{
    Q_OBJECT
    GameField* field;
public:
    explicit GameWindow(QWidget *parent = nullptr);
    ~GameWindow();

private:
    Ui::GameWindow *ui;

private slots:
        void quitSlot();

};

#endif // GAMEWINDOW_H
