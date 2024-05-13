#include "player.h"
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QTimer>
#include "apiclient.h"
#include "game.h"
#include "mainwindow.h"

Player::Player()
    : QObject()
{
    // Initializing Variables
    onlineMode = false;
    username = "New Player";
    hashedPassword = "";
    level = 1;
    gold = 1000;
    clan = "";
    rankClan = 0;
    rankGlobal = 0;

    _availableLevels = 25;

    gameTimer = new QTimer(this);
    connect(gameTimer, SIGNAL(timeout()), this, SLOT(playerWon()));

    gameTimeTimer = new QTimer(this);
    connect(gameTimeTimer, SIGNAL(timeout()), this, SLOT(updateTimer()));

    // TODO: These values should be fetched from the DB for the online game mode in Milestone 2
    cannonData = new CannonData{1, 30, 20, 500};
    fenceData = new FenceData{1, 150};
    castleData = new CastleData{1, 100};
    workerData = new WorkerData{1, 3, 30};
}

void Player::renderStats()
{
    gameDuration_ms = 120000; // Might change according to level to increase difficulty
    gameTimer->start(gameDuration_ms);
    gameTimeTimer->start(950);
    score = 0;
    goldTemp = 0;

    // A work-around to get mouse click position because View and Scene don't have the same size and position due to fullscreen
    int offsetX = gameView->width() / 2 - gameView->getSceneWidth() / 2;
    int offsetY = gameView->height() / 2 - gameView->getSceneHeight() / 2;

    // Render the in-game Stats Bar
    QGraphicsPixmapItem *statsBar = new QGraphicsPixmapItem(
        QPixmap(":/assets/imgs/stats_bar.png").scaled(934, 50, Qt::KeepAspectRatio));
    statsBar->setPos(0 - offsetX, 0 - offsetY);
    statsBar->setZValue(20);
    gameView->scene->addItem(statsBar);

    int statsPosX = 20;
    int statsPosY = -2;

    gameTimeText = new QGraphicsTextItem;
    scoreText = new QGraphicsTextItem;
    goldText = new QGraphicsTextItem;

    // GameTimeText
    gameTimeText->setFont(QFont("Bungee", 11));
    gameTimeText->setDefaultTextColor(Qt::white);
    gameTimeText->setPlainText("⏳ 00:00\t\t");
    gameTimeText->setPos(statsPosX - offsetX, statsPosY - offsetY);
    gameTimeText->setZValue(20);
    gameView->scene->addItem(gameTimeText);

    // ScoreText
    statsPosX += gameTimeText->boundingRect().width();

    scoreText->setFont(QFont("Bungee", 11));
    scoreText->setDefaultTextColor(Qt::white);
    scoreText->setPlainText("⚔️ 0\t\t");
    scoreText->setPos(statsPosX - offsetX, statsPosY - offsetY);
    scoreText->setZValue(20);
    gameView->scene->addItem(scoreText);

    // GoldText
    statsPosX += scoreText->boundingRect().width();

    goldText->setFont(QFont("Bungee", 11));
    goldText->setDefaultTextColor(Qt::white);
    goldText->setPlainText("🪙 0\t");
    goldText->setPos(statsPosX - offsetX, statsPosY - offsetY);
    goldText->setZValue(20);
    gameView->scene->addItem(goldText);
}

QString Player::displayPlayerInfo()
{
    return ("👉 " + username + " 👈\n🎚️ " + QString::number(level) + "\n🪙 " + QString::number(gold)
            + "\n🤼 " + (clan == "" ? "(No Clan)" : clan) + "\n🎖️ C#"
            + (rankClan == 0 ? "∞" : QString::number(rankClan)) + "\n🏅 G#"
            + (rankGlobal == 0 ? "∞" : QString::number(rankGlobal)));
}

// Getters
CannonData *Player::getCannonData()
{
    return cannonData;
}

FenceData *Player::getFenceData()
{
    return fenceData;
}

CastleData *Player::getCastleData()
{
    return castleData;
}

WorkerData *Player::getWorkerData()
{
    return workerData;
}

bool Player::isOnlineMode()
{
    return onlineMode;
}

QString Player::getUsername()
{
    return username;
}

QString Player::getHashedPassword()
{
    return hashedPassword;
}

int Player::getLevel()
{
    return level;
}

int Player::getGold()
{
    return gold;
}

QString Player::getClan()
{
    return clan;
}

int Player::getRankClan()
{
    return rankClan;
}

int Player::getRankGlobal()
{
    return rankGlobal;
}

int Player::_getAvailableLevels()
{
    return _availableLevels;
}

int Player::_getCyclicLevel()
{
    return ((level % _availableLevels) == 0 ? _availableLevels : (level % _availableLevels));
}

int Player::getScore()
{
    return score;
}

QTimer *Player::getGameTimer()
{
    return gameTimer;
}

QTimer *Player::getGameTimeTimer()
{
    return gameTimeTimer;
}

// Setters
void Player::setItemData(QString ItemType, int ItemId)
{
    QFile file(":/assets/shopItems/" + ItemType + "s.json");
    if (file.open(QFile::ReadOnly)) {
        QByteArray _byteArr = file.readAll();
        file.close();

        QJsonParseError JSONErr;
        QJsonDocument JSONDoc = QJsonDocument::fromJson(_byteArr, &JSONErr);

        if (JSONErr.error == QJsonParseError::NoError && JSONDoc.isObject()) {
            QJsonObject JSONObj = JSONDoc.object();
            QJsonArray JSONArr = JSONObj.value(ItemType + "s").toArray();
            QJsonObject obj = JSONArr[ItemId - 1].toObject();

            if (ItemType == "cannon") {
                CannonData *cannonData = new CannonData{obj.value("id").toInt(),
                                                        obj.value("bulletDamage").toInt(),
                                                        obj.value("bulletSpeed").toDouble(),
                                                        obj.value("attackSpeed_ms").toInt()};
                setCannonData(cannonData);
                delete cannonData;
            } else if (ItemType == "fence") {
                FenceData *fenceData = new FenceData{obj.value("id").toInt(),
                                                     obj.value("maxHealth").toInt()};
                setFenceData(fenceData);
                delete fenceData;
            } else if (ItemType == "castle") {
                CastleData *castleData = new CastleData{obj.value("id").toInt(),
                                                        obj.value("maxHealth").toInt()};
                setCastleData(castleData);
                delete castleData;
            } else if (ItemType == "worker") {
                WorkerData *workerData = new WorkerData{obj.value("id").toInt(),
                                                        obj.value("workerSpeed").toDouble(),
                                                        obj.value("workerHealing").toInt()};
                setWorkerData(workerData);
                delete workerData;
            }
        }
    }
}

void Player::setCannonData(CannonData *CannonData)
{
    cannonData->cannonId = CannonData->cannonId;
    cannonData->bulletDamage = CannonData->bulletDamage;
    cannonData->bulletSpeed = CannonData->bulletSpeed;
    cannonData->attackSpeed_ms = CannonData->attackSpeed_ms;
}

void Player::setFenceData(FenceData *FenceData)
{
    fenceData->fenceId = FenceData->fenceId;
    fenceData->maxHealth = FenceData->maxHealth;
}

void Player::setCastleData(CastleData *CastleData)
{
    castleData->castleId = CastleData->castleId;
    castleData->maxHealth = CastleData->maxHealth;
}

void Player::setWorkerData(WorkerData *WorkerData)
{
    workerData->workerId = WorkerData->workerId;
    workerData->workerSpeed = WorkerData->workerSpeed;
    workerData->workerHealing = WorkerData->workerHealing;
}

void Player::setOnlineMode(bool IsOnlineMode)
{
    onlineMode = IsOnlineMode;
}

void Player::updatePlayerInfo(PlayerInfo *playerInfo)
{
    setUsername(playerInfo->username);
    setHashedPassword(playerInfo->hashedPassword);
    setLevel(playerInfo->level);
    setGold(playerInfo->gold);
    setClan(playerInfo->clan);
    setRankClan(playerInfo->rankClan);
    setRankGlobal(playerInfo->rankGlobal);
    setItemData("cannon", playerInfo->cannon_id);
    setItemData("fence", playerInfo->fence_id);
    setItemData("castle", playerInfo->castle_id);
    setItemData("worker", playerInfo->worker_id);
}

void Player::setUsername(QString Username)
{
    username = Username;
}

void Player::setHashedPassword(QString HashedPassword)
{
    hashedPassword = HashedPassword;
}

void Player::setLevel(int Level)
{
    level = Level;
}

void Player::setGold(int Gold)
{
    gold = Gold;
}

void Player::setClan(QString Clan)
{
    clan = Clan;
}

void Player::setRankClan(int rank)
{
    rankClan = rank;
}

void Player::setRankGlobal(int rank)
{
    rankGlobal = rank;
}

void Player::setGame(Game *gameViewPtr)
{
    gameView = gameViewPtr;
}

void Player::levelUp()
{
    level++;
    gold += goldTemp;

    if (onlineMode) {
        APIClient *apiClient = new APIClient(this);
        PlayerInfo *playerInfo = new PlayerInfo;
        playerInfo->username = username;
        playerInfo->hashedPassword = hashedPassword;

        QJsonObject postDataObj;
        postDataObj["level"] = level;
        postDataObj["gold"] = gold;
        postDataObj["clan"] = clan;
        postDataObj["cannon_id"] = cannonData->cannonId;
        postDataObj["fence_id"] = fenceData->fenceId;
        postDataObj["castle_id"] = castleData->castleId;
        postDataObj["worker_id"] = workerData->workerId;
        QJsonDocument postDataDoc(postDataObj);
        QByteArray postDataByteArr = postDataDoc.toJson();

        apiClient->putRequest(QUrl(API_BASE_URL + "player/" + username + "/" + hashedPassword),
                              postDataByteArr,
                              playerInfo);
        if (playerInfo->username != "") {
            updatePlayerInfo(playerInfo);
        }
        apiClient->deleteLater();
    }
}

void Player::resetLevel()
{
    level = 1;
}

void Player::incrementScore()
{
    score++;
    scoreText->setPlainText("⚔️ " + QString::number(score) + "\t\t");
}

void Player::incrementGoldTemp()
{
    goldTemp += 20;
    goldText->setPlainText("🪙 " + QString::number(goldTemp) + "\t");
}

void Player::increaseGold(int amount)
{
    gold += amount;
}

// Slots
void Player::playerWon()
{
    this->levelUp();

    // Game Over & Player Won
    gameTimeTimer->stop();
    gameTimer->stop();
    MainWindow *window = new MainWindow(this);
    window->setWindowState(Qt::WindowFullScreen);
    window->resizeLayout();
    window->setGameOverText("<p style='line-height:60%; color: blue;'>You Won!<br>Score: "
                            + QString::number(score) + "<br>To Level " + QString::number(level)
                            + " ➡️<br></p>");
    window->show();
    if (gameView->getFiringTimer()->isActive()) {
        gameView->getFiringTimer()->stop();
    }
    gameView->scene->clear();
    gameView->close();
    delete gameView;
}

void Player::updateTimer()
{
    int min = (gameDuration_ms / 1000) / 60;
    int sec = (gameDuration_ms / 1000) % 60;
    gameTimeText->setPlainText(
        "⏳ " + QString("%1:%2").arg(min, 2, 10, QLatin1Char('0')).arg(sec, 2, 10, QLatin1Char('0'))
        + "\t\t");
    gameDuration_ms -= 950;
}
