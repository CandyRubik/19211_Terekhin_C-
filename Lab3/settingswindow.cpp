#include "settingswindow.h"
#include "ui_settingswindow.h"
#include "mainwindow.h"
#include "mapmaker.h"
#include <QFile>

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
    QFile file1("D:\\LabsC++\\Lab3\\info\\MapF.txt");
    if (file1.open(QIODevice::Append)) {
        file1.write(ui->chooseStrategyF->currentText().toStdString().c_str());
    }
    file1.close();
    QFile file2("D:\\LabsC++\\Lab3\\info\\MapS.txt");
    if (file2.open(QIODevice::Append)) {
        file2.write(ui->chooseStrategyS->currentText().toStdString().c_str());
    }
    file2.close();
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
    mapMaker *map = new mapMaker(this);
    map->setWindowTitle("Настройка карты игрока 1");
    map->show();
}

void SettingsWindow::on_SetMapS_clicked()
{
    mapMaker *map = new mapMaker(this);
    map->setWindowTitle("Настройка карты игрока 2");
    map->show();
}
