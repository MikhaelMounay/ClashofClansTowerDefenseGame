#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QMediaPlayer>
#include <QTimer>
#include <QVector>

class Player;
class Cannon;
class Castle;
class Fence;
class Enemy;

struct EnemyDataAdditions
{
    int maxHealthAddition;
    int enemyDamageAddition;
    double enemySpeedAddition;
    int enemySpawnIntervalAddition_ms;
};

class Game : public QGraphicsView
{
private:
    // Member Variables
    int sceneWidth;
    int sceneHeight;
    int schemaWidth;
    int schemaHeight;
    QVector<QVector<int>> mapSchema;
    QVector<QVector<int>> mapWeights;
    int unitSize;
    int enemySpawnInterval_ms;
    QTimer *enemyTimer;
    QTimer *firingTimer;
    int _eventX;
    int _eventY;
    EnemyDataAdditions *enemyDataAdditions;

    QMediaPlayer *inGameThemeAudio;

    // Member Functions
    void readMapSchema(QString path);
    void renderMap(QString path);

public:
    // Member Variables
    QGraphicsScene *scene;
    Player *player;
    Castle *castle;
    Cannon *cannon;
    QList<Fence *> damagedFenceUnits;
    QList<Enemy *> enemyUnits;

    // Member Functions
    Game(Player *playerPtr, EnemyDataAdditions *EnemyDataAdditions);
    ~Game();
    void start();
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

    // Getters
    int getSceneWidth();
    int getSceneHeight();
    int getUnitSize();
    int _getEventX();
    int _getEventY();
    QTimer *getFiringTimer();
    QTimer *getEnemyTimer();
    QVector<QVector<int>> *getMapWeights();

    // Setters
    void setPlayer(Player *playerPtr);

public slots:
    void spawnEnemy();
};

#endif // GAME_H
