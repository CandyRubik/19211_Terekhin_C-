#ifndef GAMEFIELD_H
#define GAMEFIELD_H

#include <QWidget>
#include <QPushButton>
#include "game.h"
#include <memory>

class GameField : public QWidget
{
    Q_OBJECT
    bool moveEvent = false;
    std::pair<qreal, qreal> cursorPos = std::make_pair(0, 0);
    Game& GameR;
public:
    explicit GameField(QWidget *parent = nullptr);

    ~GameField();

    void paintEvent(QPaintEvent *);

    void mouseMoveEvent(QMouseEvent *mouseEvent);

    void drawAim();

    void drawFirstGField();

    void drawSecondGField();

    void drawFields();

    void mousePressEvent(QMouseEvent *mouseEvent);

    void drawEnemyField();
signals:
    void quitSignal();
};

#endif // GAMEFIELD_H
