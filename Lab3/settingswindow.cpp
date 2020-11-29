#include "settingswindow.h"
#include <QDebug>
#include <iostream>
#include "ui_settingswindow.h"
#include "mainwindow.h"
#include "mapmaker.h"
#include <QFile>
#include <QDir>
#include <QTextStream>

SettingsWindow::SettingsWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Settings");
}

SettingsWindow::~SettingsWindow()
{
    delete ui;
}


void SettingsWindow::on_goToMainWindow_clicked()
{
    QFile file1(QDir::currentPath() + "/info/MapF.txt");
    if (file1.open(QIODevice::ReadOnly)) {
        QStringList strList;
        while(!file1.atEnd())
        {
            strList << file1.readLine();
        }
        file1.close();
        if(file1.open(QIODevice::WriteOnly))
        {
            strList[10] = ui->chooseStrategyF->currentText().toStdString().c_str();
            QTextStream stream(&file1);
            foreach(QString s, strList)
            {
                stream << s;
            }
        }
        file1.close();
    }

    QFile file2(QDir::currentPath() + "/info/MapS.txt");
    if (file2.open(QIODevice::ReadOnly)) {
        QStringList strList;
        while(!file2.atEnd())
        {
            strList << file2.readLine();
        }
        file2.close();
        if(file2.open(QIODevice::WriteOnly))
        {
            strList[10] = ui->chooseStrategyS->currentText().toStdString().c_str();
            QTextStream stream(&file2);
            foreach(QString s, strList)
            {
                stream << s;
            }
        }
        file2.close();
    }
    this->close();
}

void SettingsWindow::on_chooseStrategyF_textActivated(const QString &arg1)
{
    if(arg1 == "User")
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
    if(arg2 == "User")
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
    map->setWindowTitle("Setting up the first player card");
    map->show();
}

void SettingsWindow::on_SetMapS_clicked()
{
    mapMaker *map = new mapMaker(this);
    map->setWindowTitle("Setting up the second player card");
    map->show();
}
