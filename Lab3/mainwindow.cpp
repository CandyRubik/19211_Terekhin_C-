#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "settingswindow.h"
#include "gamewindow.h"
#include <QIcon>
#include <QKeyEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPalette Pal(palette());
    QImage background(":/resources/img/background.jpg");
    Pal.setBrush(QPalette::Window, background);
    setAutoFillBackground(true);
    setPalette(Pal);
    setWindowTitle("Sea Battle");
    setWindowIcon(QIcon(":/resources/img/icon.png"));
    connect(ui->Quit, &QPushButton::clicked, qApp, &QApplication::quit);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_Settings_clicked()
{
    SettingsWindow settings;
    settings.setModal(true);
    settings.exec();
}


void MainWindow::keyPressEvent(QKeyEvent *evt)
{
    if (evt->key() == Qt::Key_Escape) {
           qApp->quit();
     }
}

void MainWindow::on_Game_clicked()
{
    GameWindow* Game = new GameWindow(this);
    Game->setMinimumSize(1280, 720);
    Game->show();
}
