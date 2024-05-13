#include "enemy.h"
#include <QAudioOutput>
#include <QMediaPlayer>
#include <QTimer>
#include "astar.h"
#include "cannon.h"
#include "castle.h"
#include "fence.h"
#include "game.h"
#include "player.h"
#include "worker.h"

bool Enemy::isAttackAudioPlaying = false;

Enemy::Enemy(Game *gameViewPtr, QVector<QVector<int>> *mapWeightsPtr)
    : QObject()
    , QGraphicsPixmapItem()
{
    // Initializing Variables
    gameView = gameViewPtr;
    mapWeights = mapWeightsPtr;

    maxHealth = 90;
    health = maxHealth;
    enemyDamage = 30;
    enemySizeMultiplier = 1.5;
    enemySpeed = 1.5;

    enemySize = gameView->getUnitSize() * enemySizeMultiplier;

    healthBar = new HealthBar(gameView, x(), y(), enemySize, maxHealth, health, false);

    QPixmap enemyImg(":/assets/imgs/enemy/lvl_"
                     + QString::number(gameView->player->_getCyclicLevel()) + ".png");
    enemyImg = enemyImg.scaled(enemySize, enemySize);
    setPixmap(enemyImg);
    setZValue(4);

    // Setting Timer for Enemy movement
    QTimer *moveTimer = new QTimer(this);
    connect(moveTimer, SIGNAL(timeout()), this, SLOT(moveToCastle()));
    moveTimer->start(20);

    // Set Enemy Killed & Enemy Attack Audio
    QAudioOutput *killedAudioOutput = new QAudioOutput;
    killedAudioOutput->setVolume(1);
    killedAudio = new QMediaPlayer;
    killedAudio->setAudioOutput(killedAudioOutput);
    killedAudio->setSource(QUrl("qrc:/assets/audio/enemy_kill.mp3"));

    QAudioOutput *attackAudioOutput = new QAudioOutput;
    attackAudioOutput->setVolume(1);
    attackAudio = new QMediaPlayer;
    attackAudio->setAudioOutput(attackAudioOutput);
    attackAudio->setSource(QUrl("qrc:/assets/audio/enemy_attack.mp3"));
}

void Enemy::definePath()
{
    // Defining Shortest Path
    int offsetX = (gameView->width() / 2 - gameView->getSceneWidth() / 2);
    int offsetY = (gameView->height() / 2 - gameView->getSceneHeight() / 2);

    QPoint start(x() + offsetX, y() + offsetY);
    QPoint end(gameView->castle->getX() + offsetX, gameView->castle->getY() + offsetY);

    Astar astar(*mapWeights, start, end, gameView);
    path = astar.findPath();

    for (int i = 0; i < path.size(); i++) {
        path[i].setX(path[i].x() - offsetX);
        path[i].setY(path[i].y() - offsetY);
    }
}

// Getters
int Enemy::getHealth()
{
    return health;
}

int Enemy::getMaxHealth()
{
    return maxHealth;
}

// Setters
void Enemy::setMaxHealth(int MaxHealth)
{
    maxHealth = MaxHealth;
}

void Enemy::setEnemyDamage(int EnemyDamage)
{
    enemyDamage = EnemyDamage;
}

void Enemy::setEnemySpeed(double EnemySpeed)
{
    enemySpeed = EnemySpeed;
}

void Enemy::setHealth(int h)
{
    health = h;
    healthBar->setCurrentHealth(health);
}

void Enemy::decrementHealth(int damage)
{
    health -= damage;
    healthBar->setCurrentHealth(health);

    if (health <= 0) {
        gameView->player->incrementScore();
        gameView->player->incrementGoldTemp();
        gameView->enemyUnits.removeAt(gameView->enemyUnits.indexOf(this));

        // Play Enemy Killed Audio
        if (killedAudio->playbackState() == QMediaPlayer::PlayingState) {
            killedAudio->setPosition(0);
        } else if (killedAudio->playbackState() == QMediaPlayer::StoppedState) {
            killedAudio->play();
        }
        attackAudio->stop();
        isAttackAudioPlaying = false;

        gameView->scene->removeItem(healthBar);
        delete healthBar;
        gameView->scene->removeItem(this);
        delete this;
    }
}

void Enemy::moveToCastle()
{
    // Interactions with other elements
    QList<QGraphicsItem *> collidingItemsList = collidingItems();
    for (int i = 0; i < collidingItemsList.size(); i++) {
        if (typeid(*(collidingItemsList[i])) == typeid(Fence)) {
            Fence *fenceUnit = dynamic_cast<Fence *>(collidingItemsList[i]);
            fenceUnit->setIncomingDamage(enemyDamage);
            if (!fenceUnit->damageTimer->isActive()) {
                fenceUnit->damageTimer->start(1000);
            }

            // Play Enemy Attack Audio
            if (!isAttackAudioPlaying) {
                attackAudio->play();
                isAttackAudioPlaying = true;
                connect(attackAudio,
                        &QMediaPlayer::playbackStateChanged,
                        this,
                        [this](QMediaPlayer::PlaybackState state) {
                            if (state == QMediaPlayer::StoppedState) {
                                isAttackAudioPlaying = false;
                            }
                        });
            }

            return;
        } else if (typeid(*(collidingItemsList[i])) == typeid(Castle)) {
            Castle *castleUnit = dynamic_cast<Castle *>(collidingItemsList[i]);
            castleUnit->setIncomingDamage(enemyDamage);
            if (!castleUnit->damageTimer->isActive()) {
                castleUnit->damageTimer->start(1000);
            }

            // Play Enemy Attack Audio
            if (!isAttackAudioPlaying) {
                attackAudio->play();
                isAttackAudioPlaying = true;
                connect(attackAudio,
                        &QMediaPlayer::playbackStateChanged,
                        this,
                        [this](QMediaPlayer::PlaybackState state) {
                            if (state == QMediaPlayer::StoppedState) {
                                isAttackAudioPlaying = false;
                            }
                        });
            }

            return;
        } else if (typeid(*(collidingItemsList[i])) == typeid(Worker)) {
            Worker *workerUnit = dynamic_cast<Worker *>(collidingItemsList[i]);
            // Workers encountering Enemy troops result in their instant death.
            gameView->scene->removeItem(workerUnit);
            delete workerUnit;
            return;
        }
    }

    // Moving the Enemy (STRAIGHT LINE)
    // QLineF line(QPointF(x(), y()), QPointF(gameView->castle->getX(), gameView->castle->getY()));
    // qreal angle = -1 * line.angle();
    // this->setRotation(angle);
    // double dy = enemySpeed * qSin(qDegreesToRadians(angle));
    // double dx = enemySpeed * qCos(qDegreesToRadians(angle));
    // setPos(x() + dx, y() + dy);

    // Moving the Enemy (SHORTEST PATH)
    if (!path.isEmpty()) {
        QPoint nextPos = path.first();
        setPos(nextPos);
        healthBar->move(x(), y());
        path.removeFirst();
    }
}
