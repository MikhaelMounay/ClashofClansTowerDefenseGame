#include "healthbar.h"
#include <QGraphicsRectItem>

HealthBar::HealthBar(
    Game *gameViewPtr, int X, int Y, int Width, int MaxHealth, int Health, bool isFriend)
{
    // Initializing Variables
    gameView = gameViewPtr;
    maxHealth = MaxHealth;
    currentHealth = Health;
    width = Width;

    // int offset = 8;
    int height = 5;

    setRect(X - 10, Y - 10, width, height);
    setZValue(10);
    setBrush(Qt::gray);

    progressBar = new QGraphicsRectItem(X - 10, Y - 10, width, height, this);
    progressBar->setZValue(11);
    if (isFriend) {
        progressBar->setBrush(Qt::green);
    } else {
        progressBar->setBrush(Qt::red);
    }
}

void HealthBar::show()
{
    gameView->scene->addItem(this);
}

void HealthBar::hide()
{
    gameView->scene->removeItem(this);
}

void HealthBar::move(int newX, int newY)
{
    int dx = newX - x();
    int dy = newY - y();
    setPos(x() + dx, y() + dy);
    // progressBar->setPos(x() + dx, y() + dy);
}

// Getters
int HealthBar::getCurrentHealth()
{
    return currentHealth;
}

QGraphicsRectItem *HealthBar::getProgressBar()
{
    return progressBar;
}

// Setters
void HealthBar::setCurrentHealth(int value)
{
    currentHealth = value;

    double percent = currentHealth / maxHealth;
    int newWidth = percent * width;

    QRectF rect = progressBar->rect();
    rect.setWidth(newWidth);
    progressBar->setRect(rect);
}

void HealthBar::decrementCurrentHealth(int value)
{
    currentHealth -= value;
    if (currentHealth < 0) {
        currentHealth = 0;
    }

    double percent = currentHealth / maxHealth;
    int newWidth = percent * width;

    QRectF rect = progressBar->rect();
    rect.setWidth(newWidth);
    progressBar->setRect(rect);
}

void HealthBar::incrementCurrentHealth(int value)
{
    currentHealth += value;
    if (currentHealth > maxHealth) {
        currentHealth = maxHealth;
    }

    double percent = currentHealth / maxHealth;
    int newWidth = percent * width;

    QRectF rect = progressBar->rect();
    rect.setWidth(newWidth);
    progressBar->setRect(rect);
}
