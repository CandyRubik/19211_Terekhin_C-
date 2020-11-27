#include "gamefield.h"
#include <QPainter>
#include <QMouseEvent>
#include <QMessageBox>
#include <cmath>
#include <QPoint>
#include <QEvent>

namespace Sizes {
    constexpr std::pair<int, int> kFirstFieldBegin = {180, 270};
    constexpr std::pair<int, int> kFirstFieldEnd = {kFirstFieldBegin.first + 300, kFirstFieldBegin.second + 300};
    constexpr std::pair<int, int> kSecondFieldBegin = {810, 270};
    constexpr std::pair<int, int> kSecondFieldEnd = {kSecondFieldBegin.first + 300, kSecondFieldBegin.second + 300};
    constexpr qreal kMapSquareSide = 30;
}

GameField::GameField(QWidget *parent) : QWidget(parent)
{
    setMouseTracking(true);
    setMinimumSize(1280, 720);
    GameP = std::make_unique<Game>();
}

GameField::~GameField() {}

void GameField::paintEvent(QPaintEvent *)
{
    drawFields();
    if(GameP->getNextSecond() && !GameP->getGamerUserStatus(1))
    {
        std::pair<int, int> shotPos = GameP->getFirstGamer()->makeMove(*GameP);
        QMouseEvent *event = new QMouseEvent(QEvent::MouseButtonPress, QPoint(shotPos.first, shotPos.second), Qt::LeftButton, Qt::LeftButton, Qt::NoModifier);
        mousePressEvent(event);
    }
    else if(!GameP->getGamerUserStatus(2) && !GameP->getNextSecond())
    {
        std::pair<int, int> shotPos = GameP->getSecondGamer()->makeMove(*GameP);
        QMouseEvent *event = new QMouseEvent(QEvent::MouseButtonPress, QPoint(shotPos.first, shotPos.second), Qt::LeftButton, Qt::LeftButton, Qt::NoModifier);
        mousePressEvent(event);
    }
    if(moveEvent)
    {
        drawAim();
    }
    if(GameP->getNextSecond())
    {
        drawFirstGField();
        drawEnemyField();
    }
    else
    {
        drawSecondGField();
        drawEnemyField();
    }

}

void GameField::drawEnemyField()
{
    std::vector<std::string> field;
    if(GameP->getNextSecond())
    {
        field = GameP->getSecondGamer()->getField();
    }
    else
    {
        field = GameP->getFirstGamer()->getField();
    }

    for(int i = 0; i < 10; i++)
    {
        for(int j = 0; j < 10; j++)
        {
            if(field[i][j] == '.')
            {
                QPainter shipPainter(this);
                shipPainter.setPen(QPen(Qt::blue, 5, Qt::SolidLine, Qt::FlatCap));
                shipPainter.drawPoint(Sizes::kSecondFieldBegin.first + (j * Sizes::kMapSquareSide) + Sizes::kMapSquareSide / 2, Sizes::kSecondFieldBegin.second + (i * Sizes::kMapSquareSide) + Sizes::kMapSquareSide / 2);
            }
            if(field[i][j] == 'X')
            {
                QPainter shipPainter(this);
                shipPainter.setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::FlatCap));
                shipPainter.setBrush(QBrush(Qt::black, Qt::SolidPattern));
                shipPainter.drawRect(Sizes::kSecondFieldBegin.first + (j * Sizes::kMapSquareSide), Sizes::kSecondFieldBegin.second + (i * Sizes::kMapSquareSide), Sizes::kMapSquareSide, Sizes::kMapSquareSide);
            }
        }
    }
}

void GameField::drawAim()
{
    using namespace Sizes;
    if(cursorPos.first >= kSecondFieldBegin.first && cursorPos.second >= kSecondFieldBegin.second &&
         cursorPos.first < kSecondFieldEnd.first && cursorPos.second < kSecondFieldEnd.second)
    {
        QPainter aim(this);
        aim.setPen(QPen(Qt::blue, 2, Qt::SolidLine, Qt::FlatCap));
        aim.drawRect(cursorPos.first, cursorPos.second, kMapSquareSide, kMapSquareSide);
    }
    moveEvent = false;
}

void GameField::drawFirstGField()
{
    std::vector<std::string> field = GameP->getFirstGamer()->getField();
    for(int i = 0; i < 10; i++)
    {
        for(int j = 0; j < 10; j++)
        {
            if(field[i][j] == '*')
            {
                QPainter shipPainter(this);
                shipPainter.setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::FlatCap));
                shipPainter.setBrush(QBrush(Qt::red, Qt::SolidPattern));
                shipPainter.drawRect(Sizes::kFirstFieldBegin.first + (j * Sizes::kMapSquareSide), Sizes::kFirstFieldBegin.second + (i * Sizes::kMapSquareSide), Sizes::kMapSquareSide, Sizes::kMapSquareSide);
            }
            if(field[i][j] == '.')
            {
                QPainter shipPainter(this);
                shipPainter.setPen(QPen(Qt::blue, 5, Qt::SolidLine, Qt::FlatCap));
                shipPainter.drawPoint(Sizes::kFirstFieldBegin.first + (j * Sizes::kMapSquareSide) + Sizes::kMapSquareSide / 2, Sizes::kFirstFieldBegin.second + (i * Sizes::kMapSquareSide) + Sizes::kMapSquareSide / 2);
            }
            if(field[i][j] == 'X')
            {
                QPainter shipPainter(this);
                shipPainter.setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::FlatCap));
                shipPainter.setBrush(QBrush(Qt::black, Qt::SolidPattern));
                shipPainter.drawRect(Sizes::kFirstFieldBegin.first + (j * Sizes::kMapSquareSide), Sizes::kFirstFieldBegin.second + (i * Sizes::kMapSquareSide), Sizes::kMapSquareSide, Sizes::kMapSquareSide);
            }
        }
    }
}

void GameField::drawSecondGField()
{
    std::vector<std::string> field = GameP->getSecondGamer()->getField();
    for(int i = 0; i < 10; i++)
    {
        for(int j = 0; j < 10; j++)
        {
            if(field[i][j] == '*')
            {
                QPainter shipPainter(this);
                shipPainter.setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::FlatCap));
                shipPainter.setBrush(QBrush(Qt::red, Qt::SolidPattern));
                shipPainter.drawRect(Sizes::kFirstFieldBegin.first + (j * Sizes::kMapSquareSide), Sizes::kFirstFieldBegin.second + (i * Sizes::kMapSquareSide), Sizes::kMapSquareSide, Sizes::kMapSquareSide);
            }
            if(field[i][j] == '.')
            {
                QPainter shipPainter(this);
                shipPainter.setPen(QPen(Qt::blue, 5, Qt::SolidLine, Qt::FlatCap));
                shipPainter.drawPoint(Sizes::kFirstFieldBegin.first + (j * Sizes::kMapSquareSide) + Sizes::kMapSquareSide / 2, Sizes::kFirstFieldBegin.second + (i * Sizes::kMapSquareSide) + Sizes::kMapSquareSide / 2);
            }
            if(field[i][j] == 'X')
            {
                QPainter shipPainter(this);
                shipPainter.setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::FlatCap));
                shipPainter.setBrush(QBrush(Qt::black, Qt::SolidPattern));
                shipPainter.drawRect(Sizes::kFirstFieldBegin.first + (j * Sizes::kMapSquareSide), Sizes::kFirstFieldBegin.second + (i * Sizes::kMapSquareSide), Sizes::kMapSquareSide, Sizes::kMapSquareSide);
            }
        }
    }
}

void GameField::drawFields()
{
    QPainter painter(this);
    painter.setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::FlatCap));
    painter.setBrush(QBrush(Qt::white, Qt::SolidPattern));
    using namespace Sizes;
    for (int i = kFirstFieldBegin.first; i < kFirstFieldEnd.first; i += kMapSquareSide)
        for(int j = kFirstFieldBegin.second; j < kFirstFieldEnd.second; j += kMapSquareSide)
        {
            painter.drawRect(i, j, kMapSquareSide, kMapSquareSide);
        }

    for (int i = kSecondFieldBegin.first; i < kSecondFieldEnd.first; i += kMapSquareSide)
        for(int j = kSecondFieldBegin.second; j < kSecondFieldEnd.second; j += kMapSquareSide)
        {
            painter.drawRect(i, j, kMapSquareSide, kMapSquareSide);
        }
}

void GameField::mouseMoveEvent(QMouseEvent *mouseEvent)
{
    moveEvent = true;
    cursorPos = std::make_pair(floor(mouseEvent->pos().x() / Sizes::kMapSquareSide) * Sizes::kMapSquareSide, floor(mouseEvent->pos().y() / Sizes::kMapSquareSide) * Sizes::kMapSquareSide);
    QWidget::update();
}

void GameField::mousePressEvent(QMouseEvent *mouseEvent)
{
    using namespace Sizes;
    cursorPos = std::make_pair(floor(mouseEvent->pos().x() / kMapSquareSide) * kMapSquareSide, floor(mouseEvent->pos().y() / kMapSquareSide) * kMapSquareSide);
    if(cursorPos.first >= kSecondFieldBegin.first && cursorPos.second >= kSecondFieldBegin.second &&
            cursorPos.first < kSecondFieldEnd.first && cursorPos.second < kSecondFieldEnd.second)
    {
        GameP->setUserShot({true, {(cursorPos.second - kSecondFieldBegin.second) / kMapSquareSide, (cursorPos.first - kSecondFieldBegin.first) / kMapSquareSide}});
    }
    if(GameP->move() && GameP->getFirstGamer()->getAffectedCells() == 22)
    {
        QMessageBox::information(this, "Congratulations", "First Player wins");
        emit quitSignal();
    }
    else if(GameP->getSecondGamer()->getAffectedCells() == 22)
    {
        QMessageBox::information(this, "Congratulations", "Second Player wins");
        emit quitSignal();
    }
    else if((!GameP->getNextSecond() && GameP->getGamerUserStatus(2)) && (GameP->getNextSecond() && GameP->getGamerUserStatus(1)))
    {
        QMessageBox::information(this, "Swap", "Pass control to the next player");
    }
    QWidget::update();
}

