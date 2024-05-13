#include "cannon.h"
#include <QAudioOutput>
#include <QMediaPlayer>
#include "player.h"
#include <bullet.h>

Cannon::Cannon(int X, int Y, int unitSize, Game *gameViewPtr)
    : QObject()
    , QGraphicsPixmapItem()
{
    // Initializing Variables
    x = X;
    y = Y;
    bulletDamage = 30;
    bulletSize = 50;
    bulletSpeed = 20;
    attackSpeed_ms = 500;
    gameView = gameViewPtr;

    QPixmap cannonImg(":/assets/imgs/cannon/lvl_"
                      + QString::number(gameView->player->getCannonData()->cannonId) + ".png");
    cannonImg = cannonImg.scaled(unitSize, unitSize);
    setPixmap(cannonImg);
    setPos(x, y);
    setTransformOriginPoint(unitSize / 2, unitSize / 2);

    // Set Bullet Audio
    QAudioOutput *bulletAudioOutput = new QAudioOutput;
    bulletAudioOutput->setVolume(0.9);
    bulletAudio = new QMediaPlayer;
    bulletAudio->setAudioOutput(bulletAudioOutput);
    bulletAudio->setSource(QUrl("qrc:/assets/audio/bullet.mp3"));
}

// Getters
int Cannon::getX()
{
    return x;
}

int Cannon::getY()
{
    return y;
}

int Cannon::getBulletDamage()
{
    return bulletDamage;
}

int Cannon::getBulletSize()
{
    return bulletSize;
}

int Cannon::getBulletSpeed()
{
    return bulletSpeed;
}

int Cannon::getAttackSpeed_ms()
{
    return attackSpeed_ms;
}

// Setters
void Cannon::setBulletDamage(int BulletDamage)
{
    bulletDamage = BulletDamage;
}

void Cannon::setBulletSpeed(double BulletSpeed)
{
    bulletSpeed = BulletSpeed;
}

void Cannon::setAttackSpeed_ms(int AttackSpeed_ms)
{
    attackSpeed_ms = AttackSpeed_ms;
}

// Slots
void Cannon::fireBullet()
{
    Bullet *bullet = new Bullet(this, gameView);

    // Set Bullet position to the center of the Cannon
    QRectF cannonRect = this->boundingRect();
    int cannonWidth = static_cast<int>(cannonRect.width());
    int cannonX = this->getX() + cannonWidth / 2;
    int cannonY = this->getY() + cannonWidth / 2;
    bullet->setPos(cannonX, cannonY);

    // A work-around to get mouse click position because View and Scene don't have the same size and position due to fullscreen
    int mouseX = gameView->_getEventX() - (gameView->width() / 2 - gameView->getSceneWidth() / 2);
    int mouseY = gameView->_getEventY() - (gameView->height() / 2 - gameView->getSceneHeight() / 2);

    // Rotate the Bullet according to mouse position
    QLineF line(QPointF(cannonX, cannonY), QPointF(mouseX, mouseY));
    qreal angle = -1 * line.angle();
    bullet->setRotation(angle);

    gameView->scene->addItem(bullet);

    // Play Bullet Audio
    if (bulletAudio->playbackState() == QMediaPlayer::PlayingState) {
        bulletAudio->setPosition(0);
    } else if (bulletAudio->playbackState() == QMediaPlayer::StoppedState) {
        bulletAudio->play();
    }
}
