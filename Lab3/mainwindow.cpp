#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "settingswindow.h"
#include <QIcon>
#include <QKeyEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Морской бой");
    this->setWindowIcon(QIcon(":/resources/img/icon.png"));
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

void MainWindow::resizeEvent(QResizeEvent *evt)
{
    QPixmap bkgnd(":/resources/img/background.jpg");
    bkgnd = bkgnd.scaled(size(), Qt::IgnoreAspectRatio);
    QPalette p = palette(); //copy current, not create new
    p.setBrush(QPalette::Background, bkgnd);
    setPalette(p);

    QMainWindow::resizeEvent(evt); //call base implementation
}

void MainWindow::keyPressEvent(QKeyEvent *evt)
{
    if (evt->key() == Qt::Key_Escape) {
           qApp->quit();
     }
}
