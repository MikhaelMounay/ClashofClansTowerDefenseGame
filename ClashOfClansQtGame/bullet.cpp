#include "bullet.h"
#include <QGraphicsScene>
#include <QPointF>
#include <QRectF>
#include <QTimer>
#include "enemy.h"
#include "player.h"

Bullet::Bullet(Cannon *cannonPtr, Game *gameViewPtr)
    : QObject()
    , QGraphicsPixmapItem()
{
    // Initializing Variables
    cannon = cannonPtr;
    gameView = gameViewPtr;
    bulletDamage = cannon->getBulletDamage();
    bulletSize = cannon->getBulletSize();
    bulletSpeed = cannon->getBulletSpeed();

    QPixmap bulletImg(":/assets/imgs/bullet/lvl_"
                      + QString::number(gameView->player->getCannonData()->cannonId) + ".png");
    bulletImg = bulletImg.scaled(bulletSize, bulletSize);
    setPixmap(bulletImg);
    setZValue(10);

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));
    timer->start(50);
}

void Bullet::move()
{
    // Check if it hits an Enemy
    QList<QGraphicsItem *> collidingItemsList = collidingItems();
    for (int i = 0; i < collidingItemsList.size(); i++) {
        if (typeid(*(collidingItemsList[i])) == typeid(Enemy)) {
            dynamic_cast<Enemy *>(collidingItemsList[i])->decrementHealth(bulletDamage);

            gameView->scene->removeItem(this);
            delete this;
            return;
        }
    }

    // Moving the Bullet
    double angle = rotation();
    double dy = bulletSpeed * qSin(qDegreesToRadians(angle));
    double dx = bulletSpeed * qCos(qDegreesToRadians(angle));
    setPos(x() + dx, y() + dy);

    // Delete the bullet if it goes beyond the view
    QRectF viewRect = gameView->viewport()->rect();
    QPointF bulletViewPos = gameView->mapFromScene(this->scenePos());
    if (!viewRect.contains(bulletViewPos)) {
        gameView->scene->removeItem(this);
        delete this;
    }
}

// Getters
int Bullet::getBulletDamage()
{
    return bulletDamage;
}
