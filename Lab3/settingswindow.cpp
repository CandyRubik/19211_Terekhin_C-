#include "settingswindow.h"
#include "ui_settingswindow.h"
#include "mainwindow.h"
#include "mapmaker.h"

SettingsWindow::SettingsWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Настройки");
}

SettingsWindow::~SettingsWindow()
{
    delete ui;
}


void SettingsWindow::on_goToMainWindow_clicked()
{
    this->close();
}

void SettingsWindow::on_chooseStrategyF_textActivated(const QString &arg1)
{
    if(arg1 == "Пользователь")
    {
        ui->SetMapF->setEnabled(true);
    }
    else
    {
        ui->SetMapF->setEnabled(false);
    }
}

void SettingsWindow::on_chooseStrategyS_textActivated(const QString &arg2)
{
    if(arg2 == "Пользователь")
    {
        ui->SetMapS->setEnabled(true);
    }
    else
    {
        ui->SetMapS->setEnabled(false);
    }
}

void SettingsWindow::on_SetMapF_clicked()
{
    mapMaker map;
    map.setModal(true);
    map.setWindowTitle("Настройка карты игрока 1");
    map.exec();
}

void SettingsWindow::on_SetMapS_clicked()
{
    mapMaker map;
    map.setModal(true);
    map.setWindowTitle("Настройка карты игрока 2");
    map.exec();
}
