#include "castle.h"
#include <QTimer>
#include "enemy.h"
#include "game.h"
#include "mainwindow.h"
#include "player.h"

Castle::Castle(int X, int Y, int unitSize, Game *gameViewPtr)
    : QObject()
    , QGraphicsPixmapItem()
{
    // Initializing Variables
    gameView = gameViewPtr;
    x = X;
    y = Y;
    maxHealth = 100;
    health = maxHealth;
    damageTimer = new QTimer(this);

    healthBar = new HealthBar(gameView, x, y, gameView->getUnitSize() * 3, maxHealth, health, true);

    connect(damageTimer, SIGNAL(timeout()), this, SLOT(decrementHealth()));

    QPixmap castleImg(":/assets/imgs/castle/lvl_"
                      + QString::number(gameView->player->getCastleData()->castleId) + ".png");
    castleImg = castleImg.scaled(unitSize, unitSize);
    setPixmap(castleImg);
    setPos(x, y);
}

// Getters
int Castle::getX()
{
    return x;
}

int Castle::getY()
{
    return y;
}

int Castle::getHealth()
{
    return health;
}

int Castle::getMaxHealth()
{
    return maxHealth;
}

// Setters
void Castle::setMaxHealth(int MaxHealth)
{
    maxHealth = MaxHealth;
}

void Castle::setHealth(int h)
{
    health = h;
    healthBar->setCurrentHealth(health);
}

void Castle::setIncomingDamage(int damage)
{
    incomingDamage = damage;
}

// Slots
void Castle::decrementHealth()
{
    health -= incomingDamage;
    healthBar->setCurrentHealth(health);

    if (health <= 0) {
        damageTimer->stop();

        // Game Over
        gameView->player->getGameTimeTimer()->stop();
        gameView->player->getGameTimer()->stop();

        // Reset Stats for Offline Mode
        if (!gameView->player->isOnlineMode()) {
            gameView->player->resetLevel();
            gameView->player->setGold(0);
            gameView->player->setItemData("cannon", 1);
            gameView->player->setItemData("fence", 1);
            gameView->player->setItemData("castle", 1);
            gameView->player->setItemData("worker", 1);
        }

        MainWindow *window = new MainWindow(gameView->player);
        window->setWindowState(Qt::WindowFullScreen);
        window->resizeLayout();
        window->setGameOverText(
            "<p style='line-height:60%; color: red;'>Game Over!<br>Repeat Level "
            + QString::number(gameView->player->getLevel()) + " ➡️<br></p>");
        window->show();
        if (gameView->getFiringTimer()->isActive()) {
            gameView->getFiringTimer()->stop();
        }
        if (gameView->scene->items().size() > 0) {
            gameView->scene->clear();
        }
        gameView->close();
        delete gameView;
        return;
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
