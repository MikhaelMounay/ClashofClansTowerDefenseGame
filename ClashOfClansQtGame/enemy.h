#ifndef ENEMY_H
#define ENEMY_H

#include <QGraphicsPixmapItem>
#include <QMediaPlayer>
#include <QObject>
#include <QVector>
#include "game.h"
#include "healthbar.h"

class Enemy : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
private:
    // Member Variables
    Game *gameView;
    int health;
    int maxHealth;
    int enemyDamage;
    double enemySize;
    double enemySpeed;
    double enemySizeMultiplier;

    QMediaPlayer *killedAudio;
    QMediaPlayer *attackAudio;

    QVector<QVector<int>> *mapWeights;
    QVector<QPoint> path;

public:
    HealthBar *healthBar;
    static bool isAttackAudioPlaying;

    // Member Functions
    Enemy(Game *gameViewPtr, QVector<QVector<int>> *mapWeightsPtr);
    void definePath();

    // Getters
    int getHealth();
    int getMaxHealth();

    // Setters
    void setMaxHealth(int MaxHealth);
    void setEnemyDamage(int EnemyDamage);
    void setEnemySpeed(double EnemySpeed);
    void setHealth(int h);
    void decrementHealth(int damage);

public slots:
    void moveToCastle();
};

#endif // ENEMY_H
