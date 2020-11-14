#include "settingswindow.h"
#include "ui_settingswindow.h"
#include "mainwindow.h"

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
