#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsTextItem>
#include <QObject>
#include <QTimer>
#include "game.h"

class APIClient;
struct PlayerInfo;

struct CannonData
{
    int cannonId;
    int bulletDamage;
    double bulletSpeed;
    int attackSpeed_ms;
};

struct FenceData
{
    int fenceId;
    int maxHealth;
};

struct CastleData
{
    int castleId;
    int maxHealth;
};

struct WorkerData
{
    int workerId;
    double workerSpeed;
    int workerHealing;
};

class Player : public QObject
{
    Q_OBJECT
private:
    // Member Variables
    bool onlineMode;
    QString username;
    QString hashedPassword;
    int level;
    int gold;
    QString clan;
    int rankClan;
    int rankGlobal;

    int _availableLevels;
    Game *gameView;
    int score;
    int goldTemp;
    CannonData *cannonData;
    FenceData *fenceData;
    CastleData *castleData;
    WorkerData *workerData;

    QGraphicsTextItem *gameTimeText;
    QGraphicsTextItem *scoreText;
    QGraphicsTextItem *goldText;
    QTimer *gameTimer;
    QTimer *gameTimeTimer;
    int gameDuration_ms;

public:
    // Member Functions
    Player();
    void renderStats();
    QString displayPlayerInfo();

    // Getters
    CannonData *getCannonData();
    FenceData *getFenceData();
    CastleData *getCastleData();
    WorkerData *getWorkerData();

    bool isOnlineMode();
    QString getUsername();
    QString getHashedPassword();
    int getLevel();
    int getGold();
    QString getClan();
    int getRankClan();
    int getRankGlobal();

    int _getAvailableLevels();
    int _getCyclicLevel();
    int getScore();
    int getGoldTemp();
    QTimer *getGameTimer();
    QTimer *getGameTimeTimer();

    // Setters
    void setItemData(QString ItemType, int ItemId);
    void setCannonData(CannonData *CannonData);
    void setFenceData(FenceData *FenceData);
    void setCastleData(CastleData *CastleData);
    void setWorkerData(WorkerData *WorkerData);

    void setOnlineMode(bool IsOnlineMode);
    void updatePlayerInfo(PlayerInfo *PlayerInfo);
    void setUsername(QString Username);
    void setHashedPassword(QString HashedPassword);
    void setLevel(int Level);
    void setGold(int Gold);
    void setClan(QString Clan);
    void setRankClan(int rank);
    void setRankGlobal(int rank);

    void setGame(Game *gameViewPtr);
    void levelUp();
    void resetLevel();
    void incrementScore();
    void incrementGoldTemp();
    void increaseGold(int amount);

public slots:
    void playerWon();
    void updateTimer();
};

#endif // PLAYER_H
