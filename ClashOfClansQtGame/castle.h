#ifndef CASTLE_H
#define CASTLE_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QTimer>
#include "game.h"
#include "healthbar.h"

class Castle : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
private:
    // Member Variables
    Game *gameView;
    int health;
    int maxHealth;
    int x;
    int y;
    int incomingDamage;

public:
    // Member Variables
    QTimer *damageTimer;
    HealthBar *healthBar;

    // Member Functions
    Castle(int X, int Y, int unitSize, Game *gameViewPtr);

    // Getters
    int getX();
    int getY();
    int getHealth();
    int getMaxHealth();

    // Setters
    void setMaxHealth(int MaxHealth);
    void setHealth(int h);
    void setIncomingDamage(int damage);

public slots:
    void decrementHealth();
};

#endif // CASTLE_H
