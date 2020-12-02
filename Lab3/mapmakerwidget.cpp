#include "mapmakerwidget.h"
#include <QPainter>
#include <QMouseEvent>
#include <QMessageBox>
#include <QKeyEvent>
#include <cmath>


mapWidget::mapWidget(QWidget *parent) : QWidget(parent)
{
    setMouseTracking(true);
    setFocusPolicy(Qt::StrongFocus);
    for (int i = 0; i < 11; i++)
    {
        ships_status.push_back(std::make_pair(std::make_pair(QPoint(), ""), false));
    }
}

mapWidget::~mapWidget() {}

size_t mapWidget::getShipSize(std::vector<std::pair<std::pair<QPoint, std::string>, bool>>::iterator it)
{
    switch(std::distance(ships_status.begin(), it)) // getting index of vector and depends of them we install ship_size
    {
        case 0:
            return 4;
            break;
        case 1:
            return 3;
            break;
        case 2:
            return 3;
            break;
        case 3:
            return 2;
            break;
        case 4:
            return 2;
            break;
        case 5:
            return 2;
            break;
        case 6:
            return 2;
            break;
        case 7:
            return 1;
            break;
        case 8:
            return 1;
            break;
        case 9:
            return 1;
            break;
        case 10:
            return 1;
            break;
        default:
            return 0;
    }
}

bool mapWidget::restrictedAreaCheck(std::vector<std::pair<std::pair<QPoint, std::string>, bool>>::iterator iter)
{
    for (auto it = ships_status.begin(); it != iter; ++it)
    {
        int ship_size_verifiable = getShipSize(iter) - 1;
        int ship_size = getShipSize(it);
        if(cntrl) // if verifiable ship is horizontal
        {
            if( (it->first.second == "vertical") &&
                (   ((it->first.first.x() - 1 <= cursorPos.first) && (it->first.first.y() - 1 <= cursorPos.second) &&
                    (it->first.first.x() + 1 >= cursorPos.first) && (it->first.first.y() + ship_size >= cursorPos.second)) ||

                    ((it->first.first.x() - 1 <= cursorPos.first + ship_size_verifiable) && (it->first.first.y() - 1 <= cursorPos.second) &&
                    (it->first.first.x() + 1 >= cursorPos.first + ship_size_verifiable) && (it->first.first.y() + ship_size >= cursorPos.second))))
            {
                return true;
            }
            if( (it->first.second == "horizontal") &&
                (   ((it->first.first.x() - 1 <= cursorPos.first) && (it->first.first.y() - 1 <= cursorPos.second) &&
                    (it->first.first.x() + ship_size >= cursorPos.first) && (it->first.first.y() + 1 >= cursorPos.second)) ||

                    ((it->first.first.x() - 1 <= cursorPos.first + ship_size_verifiable) && (it->first.first.y() - 1 <= cursorPos.second) &&
                    (it->first.first.x() + ship_size >= cursorPos.first + ship_size_verifiable) && (it->first.first.y() + 1 >= cursorPos.second))))
            {
                return true;
            }
        }
        else // if verifiable ship is vertical
        {
            if( (it->first.second == "vertical") &&
                (    ((it->first.first.x() - 1 <= cursorPos.first) && (it->first.first.y() - 1 <= cursorPos.second) &&
                    (it->first.first.x() + 1 >= cursorPos.first) && (it->first.first.y() + ship_size >= cursorPos.second)) ||

                     ((it->first.first.x() - 1 <= cursorPos.first) && (it->first.first.y() - 1 <= cursorPos.second + ship_size_verifiable) &&
                     (it->first.first.x() + 1 >= cursorPos.first) && (it->first.first.y() + ship_size >= cursorPos.second + ship_size_verifiable))))
            {
                return true;
            }
            if( (it->first.second == "horizontal") &&
                (    ((it->first.first.x() - 1 <= cursorPos.first) && (it->first.first.y() - 1 <= cursorPos.second) &&
                    (it->first.first.x() + ship_size >= cursorPos.first) && (it->first.first.y() + 1 >= cursorPos.second)) ||

                     ((it->first.first.x() - 1 <= cursorPos.first) && (it->first.first.y() - 1 <= cursorPos.second + ship_size_verifiable) &&
                     (it->first.first.x() + ship_size >= cursorPos.first) && (it->first.first.y() + 1 >= cursorPos.second + ship_size_verifiable))))
            {
                return true;
            }
        }
    }
    return false;
}

void mapWidget::drawField()
{
    QPainter painter(this);
    painter.setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::FlatCap));
    painter.setBrush(QBrush(Qt::white, Qt::SolidPattern));
    for (size_t i = 0; i < 10; i++)
        for(size_t j = 0; j < 10; j++)
            painter.drawRect(i * Sizes::map_square_side, j * Sizes::map_square_side, Sizes::map_square_side, Sizes::map_square_side);
}

void mapWidget::drawStableShip(std::vector<std::pair<std::pair<QPoint, std::string>, bool>>::iterator it)
{
    QPainter shipPainter(this);
    shipPainter.setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::FlatCap));
    shipPainter.setBrush(QBrush(Qt::red, Qt::SolidPattern));
    size_t ship_size = getShipSize(it);
    if(it->first.second == "vertical")  // ship should be drawn vertical
    {
        for(size_t i = 0; i < ship_size; i++)
        {
            shipPainter.drawRect(it->first.first.x() * Sizes::map_square_side, (it->first.first.y() + i) * Sizes::map_square_side, Sizes::map_square_side, Sizes::map_square_side);
        }
    }
    else    // ship should be drawn horizontal
    {
        for(size_t i = 0; i < ship_size; i++)
        {
            shipPainter.drawRect((it->first.first.x() + i) * Sizes::map_square_side, it->first.first.y() * Sizes::map_square_side, Sizes::map_square_side, Sizes::map_square_side);
        }
    }
}

void mapWidget::drawUnstableShip(std::vector<std::pair<std::pair<QPoint, std::string>, bool>>::iterator it)
{
    QPainter shipPainter(this);
    shipPainter.setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::FlatCap));
    shipPainter.setBrush(QBrush(Qt::red, Qt::SolidPattern));
    size_t ship_size = getShipSize(it);
    if(cntrl)  // ship should be drawn vertical
    {
        for(size_t i = 0; i < ship_size; i++)
        {
            shipPainter.drawRect((cursorPos.first + i) * Sizes::map_square_side, cursorPos.second * Sizes::map_square_side, Sizes::map_square_side, Sizes::map_square_side);
        }
    }
    else    // ship should be drawn horizontal
    {
        for(size_t i = 0; i < ship_size; i++)
        {
            shipPainter.drawRect(cursorPos.first * Sizes::map_square_side, (cursorPos.second + i) * Sizes::map_square_side, Sizes::map_square_side, Sizes::map_square_side);
        }
    }
}

void mapWidget::addShipToFlotilla(std::vector<std::pair<std::pair<QPoint, std::string>, bool>>::iterator it, std::string pos)
{
    int ship_size = getShipSize(it);
    it->second = true;
    it->first.first = QPoint(cursorPos.first, cursorPos.second);
    it->first.second = pos;
    if(pos == "horizontal")
    {
        for(qreal j = cursorPos.first + (11 * cursorPos.second); j < cursorPos.first + (11 * cursorPos.second) + ship_size; j++)
        {
            flotilla[(int)j] = '*';
        }
    }
    else
    {
        for(qreal j = cursorPos.first + (11 * cursorPos.second); j < cursorPos.first + (11 * cursorPos.second) + (11* ship_size); j+=11)
        {
            flotilla[(int)j] = '*';
        }
    }
}

void mapWidget::paintEvent(QPaintEvent *)
{
    drawField();
    // start painting ships
    for(auto it = ships_status.begin(); it != ships_status.end(); ++it)
    {
        if(it->second) // if ship is on map => paint him
        {
            drawStableShip(it);
        }
        else
        {
            if(pressEvent)
            {
                if(cntrl)   // if cntrl pressed
                {
                    if(cursorPos.first > (10 - getShipSize(it)) || restrictedAreaCheck(it)) // if click in unacceptable place
                    {
                        QMessageBox::warning(this, "Warning", "Your ship cannot be placed on the board this way, try placing it differently");
                    }
                    else
                    {
                        addShipToFlotilla(it, "horizontal");
                    }
                }
                else    // if cntrl !pressed
                {
                    if(cursorPos.second > (10 - getShipSize(it)) || restrictedAreaCheck(it)) // if click in unacceptable place
                    {
                        QMessageBox::warning(this, "Warning", "Your ship cannot be placed on the board this way, try placing it differently");
                    }
                    else
                    {
                        addShipToFlotilla(it, "vertical");
                    }
                }
                pressEvent = false;
            }
            if(moveEvent)
            {
                drawUnstableShip(it);
                moveEvent = false;
            }
            break;
        }
    }
}

void mapWidget::mouseMoveEvent(QMouseEvent *mouseEvent)
{
    moveEvent = true;
    cursorPos = std::make_pair(floor(mouseEvent->pos().x() / Sizes::map_square_side), floor(mouseEvent->pos().y() / Sizes::map_square_side));
    QWidget::update();
}

void mapWidget::mousePressEvent(QMouseEvent *mouseEvent)
{
    pressEvent = true;
    cursorPos = std::make_pair(floor(mouseEvent->pos().x() / Sizes::map_square_side), floor(mouseEvent->pos().y() / Sizes::map_square_side));
    QWidget::update();
}

void mapWidget::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Control)
    {
        cntrl = !cntrl;
    }
}

std::string& mapWidget::getFlotilla()
{
    return flotilla;
}

std::vector<std::pair<std::pair<QPoint, std::string>, bool>>& mapWidget::getShipsStatus()
{
    return ships_status;
}
