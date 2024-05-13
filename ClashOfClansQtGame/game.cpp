#include "game.h"
#include <QAudioOutput>
#include <QCursor>
#include <QFile>
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QMediaPlayer>
#include <QMouseEvent>
#include <QPixmap>
#include <QTimer>
#include "castle.h"
#include "enemy.h"
#include "fence.h"
#include "player.h"
#include "worker.h"
#include <bullet.h>
#include <cannon.h>
#include <cstdlib>
#include <ctime>

#include <QDebug>

Game::Game(Player *playerPtr, EnemyDataAdditions *EnemyDataAdditions)
{
    // Initializing Variables
    player = playerPtr;
    sceneWidth = 600;
    sceneHeight = 600;
    schemaWidth = 15;
    schemaHeight = 15;
    mapSchema.resize(schemaWidth);
    for (int i = 0; i < schemaWidth; i++) {
        mapSchema[i].resize(schemaHeight);
    }
    unitSize = 40;
    enemyDataAdditions = EnemyDataAdditions;
    enemySpawnInterval_ms = 3500 + enemyDataAdditions->enemySpawnIntervalAddition_ms;

    // Styling the Game View
    setWindowTitle("Clash of Clans | Game Client");

    setFixedSize(sceneWidth, sceneHeight);
    setWindowState(Qt::WindowFullScreen);
    setStyleSheet("background-image: url(:/assets/imgs/ingamebg/lvl_"
                  + QString::number(player->_getCyclicLevel())
                  + ".png); background-repeat: "
                    "no-repeat; background-position: center;");

    // Initialize the map with weights
    mapWeights.resize(this->height());
    for (int i = 0; i < this->height(); i++) {
        mapWeights[i].resize(this->width());
    }
    for (int i = 0; i < this->height(); i++) {
        for (int j = 0; j < this->width(); j++) {
            if (i > (height() / 2 - sceneHeight / 2) && i < (height() / 2 + sceneHeight / 2)
                && j > (width() / 2 - sceneWidth / 2) && j < (width() / 2 + sceneWidth / 2)) {
                continue;
            }
            mapWeights[i][j] = 0;
        }
    }

    // Change the cursor of the game
    QPixmap cursorPixmap(":/assets/imgs/game_launcher/sword_cursor.png");
    QCursor customCursor(cursorPixmap);
    setCursor(customCursor);

    // Creating the Scene
    scene = new QGraphicsScene(this);
    scene->setSceneRect(0, 0, sceneWidth, sceneHeight);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // Play In-game Theme Audio
    QAudioOutput *itemShopThemeAudioOutput = new QAudioOutput;
    itemShopThemeAudioOutput->setVolume(0.2);
    inGameThemeAudio = new QMediaPlayer;
    inGameThemeAudio->setAudioOutput(itemShopThemeAudioOutput);
    inGameThemeAudio->setSource(QUrl("qrc:/assets/audio/ingame_theme.mp3"));
    inGameThemeAudio->setLoops(QMediaPlayer::Infinite);
    inGameThemeAudio->play();
}

Game::~Game()
{
    inGameThemeAudio->stop();
    delete enemyDataAdditions;
}

void Game::start()
{
    setScene(scene);

    // Initialize the Player and show their score and gold
    player->renderStats();

    // Setting firing speed of the cannon
    firingTimer = new QTimer(this);

    // Spawning Enemies
    enemyTimer = new QTimer(this);
    connect(enemyTimer, &QTimer::timeout, this, &Game::spawnEnemy);
    enemyTimer->start(enemySpawnInterval_ms);

    renderMap(":/assets/mapSchema/lvl_" + QString::number(player->_getCyclicLevel()) + ".txt");

    show();
}

void Game::readMapSchema(QString path)
{
    QFile file(path);
    if (file.open(QFile::ReadOnly | QFile::Text)) {
        QTextStream stream(&file);
        for (int i = 0; i < schemaWidth; i++) {
            for (int j = 0; j < schemaHeight; j++) {
                QString letter;
                stream >> letter;
                mapSchema[i][j] = letter.toInt();
            }
        }
        file.close();
    }
}

void Game::renderMap(QString path)
{
    readMapSchema(path);

    for (int i = 0; i < schemaWidth; i++) {
        for (int j = 0; j < schemaHeight; j++) {
            int x = j * unitSize;
            int y = i * unitSize;

            // A work-around because View and Scene don't have the same size and position due to fullscreen
            int offsetX = this->width() / 2 - sceneWidth / 2;
            int offsetY = this->height() / 2 - sceneHeight / 2;

            if (mapSchema[i][j] == 1) {
                castle = new Castle(x, y, unitSize * 3, this);
                scene->addItem(castle);
                castle->setZValue(2);
                castle->healthBar->show();

                // for (int k = castle->getY() - 10 + offsetY; k < (castle->getY() - 10 + offsetY) + unitSize * 3.2; k++) {
                //     for (int l = castle->getX() - 10 + offsetX; l < (castle->getX() - 10 + offsetX) + unitSize * 3.2; l++) {
                //         mapWeights[k][l] = player->getCastleData()->maxHealth
                //                            / (30 + enemyDataAdditions->enemyDamageAddition);
                //     }
                // }

                // Change Item properties according to the purchased item from the Item Shop
                castle->setMaxHealth(player->getCastleData()->maxHealth);
            } else if (mapSchema[i][j] == 2) {
                cannon = new Cannon(x, y, unitSize * 3, this);
                scene->addItem(cannon);
                cannon->setZValue(3);

                // for (int k = cannon->getY() - 10 + offsetY; k < (cannon->getY() - 10 + offsetY) + unitSize * 3.2; k++) {
                //     for (int l = cannon->getY() - 10 + offsetX; l < (cannon->getY() - 10 + offsetX) + unitSize * 3.2; l++) {
                //         mapWeights[k][l] = INT_MAX;
                //     }
                // }

                cannon->setBulletDamage(player->getCannonData()->bulletDamage);
                cannon->setBulletSpeed(player->getCannonData()->bulletSpeed);
                cannon->setAttackSpeed_ms(player->getCannonData()->attackSpeed_ms);

                // Change the attack speed according to the Cannon
                connect(firingTimer, SIGNAL(timeout()), cannon, SLOT(fireBullet()));
                firingTimer->setInterval(cannon->getAttackSpeed_ms());
            } else if (mapSchema[i][j] == 3) {
                Fence *fenceUnit = new Fence(x * 1.1, y * 1.1, unitSize * 2, this);
                scene->addItem(fenceUnit);
                fenceUnit->setZValue(1);

                // for (int k = fenceUnit->getY() - 10 + offsetY; k < (fenceUnit->getY() - 10 + offsetY) + unitSize * 2.2; k++) {
                //     for (int l = fenceUnit->getX() - 10 + offsetX; l < (fenceUnit->getX() - 10 + offsetX) + unitSize * 2.2; l++) {
                //         mapWeights[k][l] = player->getFenceData()->maxHealth
                //                            / (30 + enemyDataAdditions->enemyDamageAddition);
                //         // mapWeights[k][l] = 10;
                //     }
                // }

                fenceUnit->setMaxHealth(player->getFenceData()->maxHealth);
            } else if (mapSchema[i][j] == 4) {
                Worker *workerUnit = new Worker(this);
                workerUnit->setPos(x, y);
                scene->addItem(workerUnit);

                workerUnit->setWorkerSpeed(player->getWorkerData()->workerSpeed);
                workerUnit->setWorkerHealing(player->getWorkerData()->workerHealing);
            }
        }
    }

    // Testing
    // QDebug dbg(QtDebugMsg);
    // for (int i = 0; i < mapWeights.size(); i++) {
    //     for (int j = 0; j < mapWeights[0].size(); j++) {
    //         if (mapWeights[i][j] != 0) {
    //             dbg << mapWeights[i][j] << " ";
    //         }
    //     }
    // }
}

void Game::mousePressEvent(QMouseEvent *event)
{
    if (player->getGameTimer()->isActive()) {
        if (event->button() == Qt::LeftButton) {
            _eventX = event->pos().x();
            _eventY = event->pos().y();
            if (!firingTimer->isActive()) {
                cannon->fireBullet();
                firingTimer->start();
            }
        }
    }
}

void Game::mouseReleaseEvent(QMouseEvent *event)
{
    if (firingTimer->isActive() && firingTimer->remainingTime() > 50
        && player->getGameTimer()->remainingTime() > firingTimer->remainingTime() - 50) {
        QTimer::singleShot(firingTimer->remainingTime() - 50, firingTimer, &QTimer::stop);
    }
}

void Game::mouseMoveEvent(QMouseEvent *event)
{
    if (player->getGameTimer()->isActive()) {
        _eventX = event->pos().x();
        _eventY = event->pos().y();

        // Set Bullet position to the center of the Cannon
        QRectF cannonRect = cannon->boundingRect();
        int cannonWidth = static_cast<int>(cannonRect.width());
        int cannonX = cannon->getX() + cannonWidth / 2;
        int cannonY = cannon->getY() + cannonWidth / 2;

        // A work-around to get mouse click position because View and Scene don't have the same size and position due to fullscreen
        int mouseX = _eventX - (this->width() / 2 - sceneWidth / 2);
        int mouseY = _eventY - (this->height() / 2 - sceneHeight / 2);

        // Rotate the Cannon & Bullet according to mouse position
        QLineF line(QPointF(cannonX, cannonY), QPointF(mouseX, mouseY));
        qreal angle = -1 * line.angle();
        cannon->setRotation(angle);
    }
}

// Getters
int Game::getSceneWidth()
{
    return sceneWidth;
}

int Game::getSceneHeight()
{
    return sceneHeight;
}

int Game::getUnitSize()
{
    return unitSize;
}

int Game::_getEventX()
{
    return _eventX;
}

int Game::_getEventY()
{
    return _eventY;
}

QTimer *Game::getFiringTimer()
{
    return firingTimer;
}

QTimer *Game::getEnemyTimer()
{
    return enemyTimer;
}

QVector<QVector<int>> *Game::getMapWeights()
{
    return &mapWeights;
}

// Setters
void Game::setPlayer(Player *playerPtr)
{
    player = playerPtr;
}

// Slots
void Game::spawnEnemy()
{
    srand(time(0));

    int i = rand() % 4;
    int randomX = rand() % viewport()->width();
    int randomY = rand() % viewport()->height();

    // A work-around to get mouse click position because View and Scene don't have the same size and position due to fullscreen
    int offsetX = this->width() / 2 - sceneWidth / 2;
    int offsetY = this->height() / 2 - sceneHeight / 2;

    Enemy *enemy = new Enemy(this, &mapWeights);
    enemy->setMaxHealth(90 + enemyDataAdditions->maxHealthAddition);
    enemy->setEnemyDamage(30 + enemyDataAdditions->enemyDamageAddition);
    enemy->setEnemySpeed(1.5 + enemyDataAdditions->enemySpeedAddition);

    if (i == 0) { // Top
        enemy->setPos(randomX - offsetX, 0 - offsetY);
        enemy->definePath();
    } else if (i == 1) {
        // Right
        enemy->setPos(viewport()->width() - offsetX, randomY - offsetY);
        enemy->definePath();
    } else if (i == 2) {
        // Bottom
        enemy->setPos(randomX - offsetX, viewport()->height() - offsetY);
        enemy->definePath();
    } else {
        // Left
        enemy->setPos(0 - offsetX, randomY - offsetY);
        enemy->definePath();
    }

    enemyUnits.push_back(enemy);
    scene->addItem(enemy);
    enemy->healthBar->show();
}
