#include "mapwidget.h"
#include <QPainter>
#include <QMouseEvent>
#include <QMessageBox>
#include <QKeyEvent>
#include <cmath>


mapWidget::mapWidget(QWidget *parent) : QWidget(parent)
{
    this->setMouseTracking(true);
    setFocusPolicy(Qt::StrongFocus);
    for (int i = 0; i < 10; i++)
    {
        ships_status.push_back(std::make_pair(std::make_pair(QPoint(), ""), false));
    }
}

mapWidget::~mapWidget() {}

int mapWidget::getShipSize(std::vector<std::pair<std::pair<QPoint, std::string>, bool>>::iterator it)
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
            return 1;
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
                (   ((it->first.first.x() - 1 <= cursor_pos.first) && (it->first.first.y() - 1 <= cursor_pos.second) &&
                    (it->first.first.x() + 1 >= cursor_pos.first) && (it->first.first.y() + ship_size >= cursor_pos.second)) ||

                    ((it->first.first.x() - 1 <= cursor_pos.first + ship_size_verifiable) && (it->first.first.y() - 1 <= cursor_pos.second) &&
                    (it->first.first.x() + 1 >= cursor_pos.first + ship_size_verifiable) && (it->first.first.y() + ship_size >= cursor_pos.second))))
            {
                return true;
            }
            if( (it->first.second == "horizontal") &&
                (   ((it->first.first.x() - 1 <= cursor_pos.first) && (it->first.first.y() - 1 <= cursor_pos.second) &&
                    (it->first.first.x() + ship_size >= cursor_pos.first) && (it->first.first.y() + 1 >= cursor_pos.second)) ||

                    ((it->first.first.x() - 1 <= cursor_pos.first + ship_size_verifiable) && (it->first.first.y() - 1 <= cursor_pos.second) &&
                    (it->first.first.x() + ship_size >= cursor_pos.first + ship_size_verifiable) && (it->first.first.y() + 1 >= cursor_pos.second))))
            {
                return true;
            }
        }
        else // if verifiable ship is vertical
        {
            if( (it->first.second == "vertical") &&
                (    ((it->first.first.x() - 1 <= cursor_pos.first) && (it->first.first.y() - 1 <= cursor_pos.second) &&
                    (it->first.first.x() + 1 >= cursor_pos.first) && (it->first.first.y() + ship_size >= cursor_pos.second)) ||

                     ((it->first.first.x() - 1 <= cursor_pos.first) && (it->first.first.y() - 1 <= cursor_pos.second + ship_size_verifiable) &&
                     (it->first.first.x() + 1 >= cursor_pos.first) && (it->first.first.y() + ship_size >= cursor_pos.second + ship_size_verifiable))))
            {
                return true;
            }
            if( (it->first.second == "horizontal") &&
                (    ((it->first.first.x() - 1 <= cursor_pos.first) && (it->first.first.y() - 1 <= cursor_pos.second) &&
                    (it->first.first.x() + ship_size >= cursor_pos.first) && (it->first.first.y() + 1 >= cursor_pos.second)) ||

                     ((it->first.first.x() - 1 <= cursor_pos.first) && (it->first.first.y() - 1 <= cursor_pos.second + ship_size_verifiable) &&
                     (it->first.first.x() + ship_size >= cursor_pos.first) && (it->first.first.y() + 1 >= cursor_pos.second + ship_size_verifiable))))
            {
                return true;
            }
        }
    }
    return false;
}

void mapWidget::drawBackground(QPainter *painter, const QRectF &rect)
{
    Q_UNUSED(rect);
    painter->setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::FlatCap));
    painter->setBrush(QBrush(Qt::white, Qt::SolidPattern));
    for (int i = 0; i < 10; i++)
        for(int j = 0; j < 10; j++)
            painter->drawRect(i * Sizes::map_square_side, j * Sizes::map_square_side, Sizes::map_square_side, Sizes::map_square_side);
}

void mapWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::FlatCap));
    painter.setBrush(QBrush(Qt::white, Qt::SolidPattern));
    for (int i = 0; i < 10; i++)
        for(int j = 0; j < 10; j++)
            painter.drawRect(i * Sizes::map_square_side, j * Sizes::map_square_side, Sizes::map_square_side, Sizes::map_square_side);
    QPainter shipPainter(this);
    shipPainter.setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::FlatCap));
    shipPainter.setBrush(QBrush(Qt::red, Qt::SolidPattern));
    for(auto it = ships_status.begin(); it != ships_status.end(); ++it)
    {
        int ship_size = getShipSize(it);
        if(it->second) // if ship is on map => paint him
        {
            if(it->first.second == "vertical")  // ship should be drawn vertical
            {
                for(int i = 0; i < ship_size; i++)
                {
                    shipPainter.drawRect(it->first.first.x() * Sizes::map_square_side, (it->first.first.y() + i) * Sizes::map_square_side, Sizes::map_square_side, Sizes::map_square_side);
                }
            }
            else    // ship should be drawn horizontal
            {
                for(int i = 0; i < ship_size; i++)
                {
                    shipPainter.drawRect((it->first.first.x() + i) * Sizes::map_square_side, it->first.first.y() * Sizes::map_square_side, Sizes::map_square_side, Sizes::map_square_side);
                }
            }
        }
        else
        {
            switch(std::distance(ships_status.begin(), it)) // getting index of vector and depends of them we install ship_size
            {
                case 0:
                    ship_size = 4;
                    break;
                case 1:
                    ship_size = 3;
                    break;
                case 2:
                    ship_size = 3;
                    break;
                case 3:
                    ship_size = 2;
                    break;
                case 4:
                    ship_size = 2;
                    break;
                case 5:
                    ship_size = 2;
                    break;
                case 6:
                    ship_size = 1;
                    break;
                case 7:
                    ship_size = 1;
                    break;
                case 8:
                    ship_size = 1;
                    break;
                case 9:
                    ship_size = 1;
                    break;
            }
            if(pressEvent)
            {
                if(cntrl)   // if cntrl pressed
                {
                    if(cursor_pos.first > (10 - ship_size) || restrictedAreaCheck(it))
                    {
                        QMessageBox::warning(this, "Внимание", "Ваш корабль не может быть размещен на поле таким образом, попробуйте разместить его по-другому");
                    }
                    else
                    {
                        it->second = true;
                        it->first.first = QPoint(cursor_pos.first, cursor_pos.second);
                        it->first.second = "horizontal";
                        for(qreal j = cursor_pos.first + (11 * cursor_pos.second); j < cursor_pos.first + (11 * cursor_pos.second) + ship_size; j++)
                        {
                            flotilla[(int)j] = '*';
                        }
                    }
                }
                else    // if cntrl !pressed
                {
                    if(cursor_pos.second > (10 - ship_size) || restrictedAreaCheck(it))
                    {
                        QMessageBox::warning(this, "Внимание", "Ваш корабль не может быть размещен на поле таким образом, попробуйте разместить его по-другому");
                    }
                    else
                    {
                        it->second = true;
                        it->first.first = QPoint(cursor_pos.first, cursor_pos.second);
                        it->first.second = "vertical";
                        for(qreal j = cursor_pos.first + (11 * cursor_pos.second); j < cursor_pos.first + (11 * cursor_pos.second) + (11* ship_size); j+=11)
                        {
                            flotilla[(int)j] = '*';
                        }
                    }
                }
                pressEvent = false;
            }

            if(moveEvent)
            {
                if(cntrl) // if cntrl pressed
                {
                    for(int i = 0; i < ship_size; i++)
                    {
                        shipPainter.drawRect((cursor_pos.first + i) * Sizes::map_square_side, cursor_pos.second * Sizes::map_square_side, Sizes::map_square_side, Sizes::map_square_side);
                    }
                }
                else
                {
                    for(int i = 0; i < ship_size; i++)
                    {
                        shipPainter.drawRect(cursor_pos.first * Sizes::map_square_side, (cursor_pos.second + i) * Sizes::map_square_side, Sizes::map_square_side, Sizes::map_square_side);
                    }
                }
                moveEvent = false;
            }
            break;
        }
    }
}

void mapWidget::mouseMoveEvent(QMouseEvent *mouseEvent)
{
    moveEvent = true;
    cursor_pos = std::make_pair(floor(mouseEvent->pos().x() / Sizes::map_square_side), floor(mouseEvent->pos().y() / Sizes::map_square_side));
    /*QGraphicsRectItem * Rect = map_scene.addRect(Rectx * Sizes::map_square_side , Recty * Sizes::map_square_side, Sizes::map_square_side, Sizes::map_square_side,
            QPen(Qt::black, 1, Qt::SolidLine, Qt::FlatCap), QBrush(Qt::red, Qt::SolidPattern));*/
    QWidget::update();
}

void mapWidget::mousePressEvent(QMouseEvent *mouseEvent)
{
    pressEvent = true;
    cursor_pos = std::make_pair(floor(mouseEvent->pos().x() / Sizes::map_square_side), floor(mouseEvent->pos().y() / Sizes::map_square_side));
    /*QGraphicsRectItem * Rect = map_scene.addRect(Rectx * Sizes::map_square_side , Recty * Sizes::map_square_side, Sizes::map_square_side, Sizes::map_square_side,
            QPen(Qt::black, 1, Qt::SolidLine, Qt::FlatCap), QBrush(Qt::red, Qt::SolidPattern));*/
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
