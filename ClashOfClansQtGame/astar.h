#ifndef ASTAR_H
#define ASTAR_H

#include <QHash>
#include <QPair>
#include <QPoint>
#include <QSet>
#include <Qvector>
#include "game.h"

class Astar
{
private:
    // Member Variables
    QVector<QVector<int>> map;
    QPoint start;
    QPoint end;
    Game *gameView;

public:
    // Member Functions
    Astar(QVector<QVector<int>> Map, QPoint Start, QPoint End, Game *gameViewPtr);
    int calculateH(QPoint a, QPoint b);
    QPoint getLowestFScore(const QSet<QPoint> &openSet, const QHash<QPoint, int> &fScore);
    QVector<QPoint> redefinePath(QHash<QPoint, QPoint> parent, QPoint end);
    QVector<QPoint> findPath();
};

#endif // ASTAR_H
