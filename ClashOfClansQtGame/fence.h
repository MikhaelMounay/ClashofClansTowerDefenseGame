#ifndef FENCE_H
#define FENCE_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QTimer>
#include "game.h"
#include "healthbar.h"

class Game;

class Fence : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
private:
    // Member Variables
    int health;
    int maxHealth;
    int x;
    int y;
    int incomingDamage;
    int incomingRepair;
    Game *gameView;

    QMediaPlayer *repairAudio;

public:
    // Member Variables
    QTimer *damageTimer;
    QTimer *repairTimer;
    HealthBar *healthBar;
    static bool isRepairAudioPlaying;

    // Member Functions
    Fence(int X, int Y, int unitSize, Game *gameViewPtr);

    // Getters
    int getX();
    int getY();
    int getHealth();
    int getMaxHealth();

    // Setters
    void setMaxHealth(int MaxHealth);
    void setHealth(int h);
    void setIncomingDamage(int damage);
    void setIncomingRepair(int repair);

public slots:
    void decrementHealth();
    void incrementHealth();
};

#endif // FENCE_H
