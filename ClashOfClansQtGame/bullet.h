#ifndef BULLET_H
#define BULLET_H

#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include <QObject>
#include "game.h"
#include <cannon.h>

class Bullet : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

private:
    // Member Variables
    Cannon *cannon;
    Game *gameView;
    int bulletDamage;
    int bulletSize;
    int bulletSpeed;

public:
    // Member Functions
    Bullet(Cannon *cannonPtr, Game *gameViewPtr);

    // Getters
    int getBulletDamage();

public slots:
    void move();
};

#endif // BULLET_H
