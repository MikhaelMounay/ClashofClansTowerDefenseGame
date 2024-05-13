#ifndef WORKER_H
#define WORKER_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include "game.h"

class Worker : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
private:
    // Member Variables
    Game *gameView;
    int workerHealing;
    double workerSize;
    double workerSizeMultiplier;
    double workerSpeed;

public:
    // Member Functions
    Worker(Game *gameViewPtr);

    // Setters
    void setWorkerSpeed(double WorkerSpeed);
    void setWorkerHealing(int WorkerHealing);

public slots:
    void moveToFence();
};

#endif // WORKER_H
