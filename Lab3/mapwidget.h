#ifndef MAPWIDGET_H
#define MAPWIDGET_H

#include <QGraphicsView>
#include <string>


namespace Sizes {
    constexpr qreal map_square_side = 30;
}

class mapWidget : public QGraphicsView
{
    std::string flotilla = "          \n          \n          \n          \n          \n          \n          \n          \n          \n          \n";
public:
    QGraphicsScene map_scene;
    mapWidget(QWidget *parent = nullptr);
    ~mapWidget();
    //void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void drawBackground(QPainter *painter, const QRectF &rect);
    void mousePressEvent(QMouseEvent *mouseEvent);
};

#endif // MAPWIDGET_H
