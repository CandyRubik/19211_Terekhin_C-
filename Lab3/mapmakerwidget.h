#ifndef MAPWIDGET_H
#define MAPWIDGET_H

#include <QWidget>
#include <QPoint>
#include <string>
#include <vector>

namespace Sizes {
    constexpr qreal map_square_side = 30;
}

class mapWidget : public QWidget
{
    std::string flotilla = "          \n          \n          \n          \n          \n          \n          \n          \n          \n          \n";
    std::pair<qreal, qreal> cursorPos = std::make_pair(0, 0);
    bool moveEvent = false;
    bool pressEvent = false;
    bool cntrl = false;
    std::vector<std::pair<std::pair<QPoint, std::string>, bool>> ships_status;
    bool restrictedAreaCheck(std::vector<std::pair<std::pair<QPoint, std::string>, bool>>::iterator iter); // true - if we try to put ship in restricted area, and false - else
public:
    mapWidget(QWidget *parent = nullptr);

    ~mapWidget();

    void mousePressEvent(QMouseEvent *mouseEvent);

    void paintEvent(QPaintEvent *);

    void mouseMoveEvent(QMouseEvent *mouseEvent);

    void keyPressEvent(QKeyEvent *event);

    std::string& getFlotilla();

    std::vector<std::pair<std::pair<QPoint, std::string>, bool>>& getShipsStatus();

    int getShipSize(std::vector<std::pair<std::pair<QPoint, std::string>, bool>>::iterator it);

    void drawField();

    void drawStableShip(std::vector<std::pair<std::pair<QPoint, std::string>, bool>>::iterator it);

    void addShipToFlotilla(std::vector<std::pair<std::pair<QPoint, std::string>, bool>>::iterator it, std::string pos);

    void drawUnstableShip(std::vector<std::pair<std::pair<QPoint, std::string>, bool>>::iterator it);
};

#endif // MAPWIDGET_H
