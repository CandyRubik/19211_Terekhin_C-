#include "mapwidget.h"
#include <QPainter>
#include <QMouseEvent>
#include <cmath>


mapWidget::mapWidget(QWidget *parent) : QGraphicsView(parent)
{
    setSceneRect(0 , 0, 301, 301);
}

mapWidget::~mapWidget() {}

void mapWidget::drawBackground(QPainter *painter, const QRectF &rect)
{
    Q_UNUSED(rect);
    painter->setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::FlatCap));
    painter->setBrush(QBrush(Qt::white, Qt::SolidPattern));
    for (int i = 0; i < 10; i++)
        for(int j = 0; j < 10; j++)
            painter->drawRect(i * Sizes::map_square_side, j * Sizes::map_square_side, Sizes::map_square_side, Sizes::map_square_side);
}

/*void mapWidget::paintEvent(QPaintEvent *)
{
    QPainter ghostPainter(this);
    ghostPainter.setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::FlatCap));
    ghostPainter.setBrush(QBrush(Qt::red, Qt::SolidPattern));
    ghostPainter.drawRect(cursor_pos.first * Sizes::map_square_side, cursor_pos.second * Sizes::map_square_side, Sizes::map_square_side, Sizes::map_square_side);
}*/

/*void mapWidget::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    QPointF pos = mouseEvent->pos();
    std::pair<qreal, qreal> real_x_y_pos = std::make_pair(pos.x(), pos.y());
    cursor_pos = std::make_pair(ceil(real_x_y_pos.first / Sizes::map_square_side), ceil(real_x_y_pos.second / Sizes::map_square_side));
}
*/
void mapWidget::mousePressEvent(QMouseEvent *mouseEvent)
{
    qreal Rectx = floor(mouseEvent->pos().x() / Sizes::map_square_side);
    qreal Recty = floor(mouseEvent->pos().y() / Sizes::map_square_side);
    map_scene.addRect(Rectx * Sizes::map_square_side , Recty * Sizes::map_square_side, Sizes::map_square_side, Sizes::map_square_side,
            QPen(Qt::black, 1, Qt::SolidLine, Qt::FlatCap), QBrush(Qt::red, Qt::SolidPattern));

}
