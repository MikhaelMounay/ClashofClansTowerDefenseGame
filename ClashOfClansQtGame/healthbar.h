#ifndef HEALTHBAR_H
#define HEALTHBAR_H

#include <QGraphicsRectItem>
#include "game.h"

class HealthBar : public QGraphicsRectItem
{
private:
    // Member Variables
    Game *gameView;
    double maxHealth;
    double currentHealth;
    int width;
    QGraphicsRectItem *progressBar;

public:
    // Member Functions
    HealthBar(Game *gameViewPtr, int X, int Y, int Width, int MaxHealth, int Health, bool isFriend);
    void show();
    void hide();
    void move(int newX, int newY);

    // Getters
    int getCurrentHealth();
    QGraphicsRectItem *getProgressBar();

    // Setters
    void setCurrentHealth(int value);
    void decrementCurrentHealth(int value);
    void incrementCurrentHealth(int value);
};

#endif // HEALTHBAR_H
