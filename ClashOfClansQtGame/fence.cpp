#include "fence.h"
#include <QAudioOutput>
#include <QMediaPlayer>
#include "game.h"
#include "player.h"
#include "worker.h"
#include <enemy.h>

bool Fence::isRepairAudioPlaying = false;

Fence::Fence(int X, int Y, int unitSize, Game *gameViewPtr)
    : QObject()
    , QGraphicsPixmapItem()
{
    // Initializing Variables
    x = X;
    y = Y;
    gameView = gameViewPtr;
    maxHealth = 90;
    health = maxHealth;
    damageTimer = new QTimer(this);
    repairTimer = new QTimer(this);

    healthBar = new HealthBar(gameView, x, y, gameView->getUnitSize() * 2, maxHealth, health, true);

    connect(damageTimer, SIGNAL(timeout()), this, SLOT(decrementHealth()));
    connect(repairTimer, SIGNAL(timeout()), this, SLOT(incrementHealth()));

    QPixmap fenceImg(":/assets/imgs/fence/lvl_"
                     + QString::number(gameView->player->getFenceData()->fenceId) + ".png");
    fenceImg = fenceImg.scaled(unitSize, unitSize);
    setPixmap(fenceImg);
    setPos(x, y);

    // Set Repair Audio
    QAudioOutput *repairAudioOutput = new QAudioOutput;
    repairAudioOutput->setVolume(1);
    repairAudio = new QMediaPlayer;
    repairAudio->setAudioOutput(repairAudioOutput);
    repairAudio->setSource(QUrl("qrc:/assets/audio/worker.mp3"));
}

// Getters
int Fence::getX()
{
    return x;
}

int Fence::getY()
{
    return y;
}

int Fence::getHealth()
{
    return health;
}

int Fence::getMaxHealth()
{
    return maxHealth;
}

// Setters
void Fence::setMaxHealth(int MaxHealth)
{
    maxHealth = MaxHealth;
}

void Fence::setHealth(int h)
{
    health = h;
    healthBar->setCurrentHealth(health);
}

void Fence::setIncomingDamage(int damage)
{
    incomingDamage = damage;
}

void Fence::setIncomingRepair(int repair)
{
    incomingRepair = repair;
}

void Fence::decrementHealth()
{
    health -= incomingDamage;
    healthBar->setCurrentHealth(health);
    healthBar->show();

    if (health <= 0) {
        damageTimer->stop();
        if (gameView->damagedFenceUnits.indexOf(this)
            != -1) { // for the interaction with Worker class
            gameView->damagedFenceUnits.removeAt(gameView->damagedFenceUnits.indexOf(this));
        }

        // Change the map to redefine Enemy paths
        int offsetX = gameView->width() / 2 - gameView->getSceneWidth() / 2;
        int offsetY = gameView->height() / 2 - gameView->getSceneHeight() / 2;
        QVector<QVector<int>> *mapWeights = gameView->getMapWeights();
        for (int i = pos().y() + offsetY; i < gameView->getUnitSize() * 2; i++) {
            for (int j = pos().x() + offsetX; j < gameView->getUnitSize() * 2; j++) {
                (*mapWeights)[i][j] = 0;
            }
        }
        for (int i = 0; i < gameView->enemyUnits.size(); i++) {
            gameView->enemyUnits[i]->definePath();
        }

        gameView->scene->removeItem(healthBar);
        delete healthBar;
        gameView->scene->removeItem(this);
        delete this;

        return;
    }
    if (gameView->damagedFenceUnits.indexOf(this) == -1) { // for the interaction with Worker class
        gameView->damagedFenceUnits.push_back(this);
    }

    // Stop the damage if the Enemy is killed
    bool enemyExist = false;
    QList<QGraphicsItem *> collidingItemsList = collidingItems();
    for (int i = 0; i < collidingItemsList.size(); i++) {
        if (typeid(*(collidingItemsList[i])) == typeid(Enemy)) {
            enemyExist = true;
            break;
        }
    }
    if (!enemyExist) {
        damageTimer->stop();
    }
}

void Fence::incrementHealth()
{
    health += incomingRepair;
    healthBar->setCurrentHealth(health);

    // Play Repair Audio
    if (!isRepairAudioPlaying) {
        repairAudio->play();
        isRepairAudioPlaying = true;
        connect(repairAudio,
                &QMediaPlayer::playbackStateChanged,
                this,
                [this](QMediaPlayer::PlaybackState state) {
                    if (state == QMediaPlayer::StoppedState) {
                        isRepairAudioPlaying = false;
                    }
                });
    }

    if (health >= maxHealth) {
        healthBar->hide();

        repairAudio->stop();
        isRepairAudioPlaying = false;

        if (gameView->damagedFenceUnits.indexOf(this) != -1) {
            gameView->damagedFenceUnits.removeAt(gameView->damagedFenceUnits.indexOf(this));
        }
    }

    // Stop repairing if the Worker is killed
    bool workerExist = false;
    QList<QGraphicsItem *> collidingItemsList = collidingItems();
    for (int i = 0; i < collidingItemsList.size(); i++) {
        if (typeid(*(collidingItemsList[i])) == typeid(Worker)) {
            workerExist = true;
            break;
        }
    }
    if (!workerExist) {
        repairTimer->stop();
        repairAudio->stop();
        isRepairAudioPlaying = false;
    }
}
