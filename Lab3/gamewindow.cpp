#include "gamewindow.h"
#include "ui_gamewindow.h"

GameWindow::GameWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GameWindow)
{
    ui->setupUi(this);
    setFixedSize (1280, 720);
    QPalette Pal(palette());
    QImage background(":/resources/img/background.jpg");
    Pal.setBrush(QPalette::Window, background);
    setAutoFillBackground(true);
    setPalette(Pal);
    field = new GameField(this);
    connect(field, &GameField::quitSignal, this, &GameWindow::quitSlot);
}

GameWindow::~GameWindow()
{
    delete ui;
    delete field;
}

void GameWindow::quitSlot()
{
    this->close();
}

