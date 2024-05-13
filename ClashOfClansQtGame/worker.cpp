#include "worker.h"
#include "castle.h"
#include "fence.h"
#include "game.h"
#include "player.h"

Worker::Worker(Game *gameViewPtr)
    : QObject()
    , QGraphicsPixmapItem()
{
    // Initializing Variables
    gameView = gameViewPtr;

    workerHealing = 30;
    workerSizeMultiplier = 1.75;
    workerSpeed = 3;

    workerSize = gameView->getUnitSize() * workerSizeMultiplier;

    QPixmap workerImg(":/assets/imgs/worker/lvl_"
                      + QString::number(gameView->player->getWorkerData()->workerId) + ".png");
    workerImg = workerImg.scaled(workerSize, workerSize);
    setPixmap(workerImg);
    setZValue(4);

    QTimer *moveTimer = new QTimer(this);
    connect(moveTimer, SIGNAL(timeout()), this, SLOT(moveToFence()));
    moveTimer->start(30);
}

void Worker::moveToFence()
{
    // TODO: each Worker should move towards the *closest* damaged Fence instead of moving to the *first* damaged Fence
    if (gameView->damagedFenceUnits.size() != 0) {
        QList<QGraphicsItem *> collidingItemsList = collidingItems();
        for (int i = 0; i < collidingItemsList.size(); i++) {
            if (typeid(*(collidingItemsList[i])) == typeid(Fence)) {
                Fence *fenceUnit = dynamic_cast<Fence *>(collidingItemsList[i]);
                if (gameView->damagedFenceUnits.indexOf(fenceUnit) != -1) {
                    fenceUnit->setIncomingRepair(workerHealing);
                    if (!fenceUnit->repairTimer->isActive()) {
                        fenceUnit->repairTimer->start(700);
                    }
                    return;
                }
            }
        }

        // Moving the Worker
        QLineF line(QPointF(x(), y()),
                    QPointF(gameView->damagedFenceUnits[0]->getX(),
                            gameView->damagedFenceUnits[0]->getY()));
        qreal angle = -1 * line.angle();
        // this->setRotation(angle); // TODO: the logic of rotation should be edited to just flip the image going left or right
        double dy = workerSpeed * qSin(qDegreesToRadians(angle));
        double dx = workerSpeed * qCos(qDegreesToRadians(angle));
        setPos(x() + dx, y() + dy);
    }
}

// Setters
void Worker::setWorkerSpeed(double WorkerSpeed)
{
    workerSpeed = WorkerSpeed;
}

void Worker::setWorkerHealing(int WorkerHealing)
{
    workerHealing = WorkerHealing;
}
