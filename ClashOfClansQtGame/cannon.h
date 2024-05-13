#ifndef CANNON_H
#define CANNON_H

#include <QGraphicsPixmapItem>
#include <QMediaPlayer>
#include <QObject>
#include "game.h"

class Cannon : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
private:
    // Member Variables
    int x;
    int y;
    int bulletDamage;
    double bulletSize;
    double bulletSpeed;
    int attackSpeed_ms;
    Game *gameView;

    QMediaPlayer *bulletAudio;

public:
    // Member Functions
    Cannon(int X, int Y, int unitSize, Game *gameViewPtr);

    // Getters
    int getX();
    int getY();
    int getBulletDamage();
    int getBulletSize();
    int getBulletSpeed();
    int getAttackSpeed_ms();

    // Setters
    void setBulletDamage(int BulletDamage);
    void setBulletSpeed(double BulletSpeed);
    void setAttackSpeed_ms(int AttackSpeed_ms);

public slots:
    void fireBullet();
};

#endif // CANNON_H
