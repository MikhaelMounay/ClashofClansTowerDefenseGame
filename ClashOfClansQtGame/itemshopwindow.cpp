#include "itemshopwindow.h"
#include <QAudioOutput>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QKeyEvent>
#include <QMediaPlayer>
#include "game.h"
#include "player.h"
#include "shopitem.h"
#include "ui_itemshopwindow.h"

ItemShopWindow::ItemShopWindow(Player *playerPtr, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ItemShopWindow)
{
    ui->setupUi(this);

    // Styling the ItemShop window
    setWindowTitle("Clash of Clans | Item Shop");
    setWindowState(Qt::WindowFullScreen);

    QPixmap bgimg(":/assets/imgs/game_launcher/itemshop_bg.png");
    bgimg.scaled(this->size(), Qt::KeepAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, bgimg);
    this->setPalette(palette);

    QPalette palette2;
    palette2.setBrush(QPalette::Window, QBrush(Qt::transparent));
    ui->container_scrollArea->setPalette(palette2);
    ui->cannon_scrollArea->setPalette(palette2);
    ui->fence_scrollArea->setPalette(palette2);
    ui->castle_scrollArea->setPalette(palette2);
    ui->worker_scrollArea->setPalette(palette2);

    // Change the cursor of the game
    QPixmap cursorPixmap(":/assets/imgs/game_launcher/sword_cursor.png");
    QCursor customCursor(cursorPixmap);
    setCursor(customCursor);

    // Initializing player
    player = playerPtr;

    // Rendering Player Stats
    ui->stats_label->setText("🎚️ " + QString::number(player->getLevel()) + "\t 🪙 "
                             + QString::number(player->getGold()));
    ui->stats_label->setStyleSheet("color: white;");

    // Rendering Items into ScrollView
    fetchItemsFromJSON("cannon");
    fetchItemsFromJSON("fence");
    fetchItemsFromJSON("castle");
    fetchItemsFromJSON("worker");

    // Update Next Enemy Label
    enemyDataAdditions = new EnemyDataAdditions;
    enemyDataAdditions->maxHealthAddition = player->getLevel() * 10;
    enemyDataAdditions->enemyDamageAddition = player->getLevel() * 10;
    enemyDataAdditions->enemySpeedAddition = player->getLevel() * 0.05;
    enemyDataAdditions->enemySpawnIntervalAddition_ms = player->getLevel() * -50;

    // (Just for display; actual effective values are stored in Game class)
    ui->nextEnemy_label->setText(
        "Next Enemy : 💥 " + QString::number(30 + enemyDataAdditions->enemyDamageAddition) + " 🛡️ "
        + QString::number(90 + enemyDataAdditions->maxHealthAddition) + " 🏃 "
        + QString::number(1.5 + enemyDataAdditions->enemySpeedAddition) + " ⏱️ "
        + QString::number((3500 + enemyDataAdditions->enemySpawnIntervalAddition_ms) / 1000.0)
        + " eps");

    // Update Items State for owned items
    this->updateItemsState(player->getCannonData()->cannonId,
                           player->getFenceData()->fenceId,
                           player->getCastleData()->castleId,
                           player->getWorkerData()->workerId);

    // Play Item Shop Theme Audio
    QAudioOutput *itemShopThemeAudioOutput = new QAudioOutput;
    itemShopThemeAudioOutput->setVolume(0.8);
    itemShopThemeAudio = new QMediaPlayer;
    itemShopThemeAudio->setAudioOutput(itemShopThemeAudioOutput);
    itemShopThemeAudio->setSource(QUrl("qrc:/assets/audio/itemshop_theme.mp3"));
    itemShopThemeAudio->setLoops(QMediaPlayer::Infinite);
    itemShopThemeAudio->play();

    // Set Button Click Audio
    buttonClickAudio = new ButtonClickAudio();
}

ItemShopWindow::~ItemShopWindow()
{
    delete ui;
}

void ItemShopWindow::hideEvent(QHideEvent *event)
{
    itemShopThemeAudio->stop();
    hide();
}

void ItemShopWindow::fetchItemsFromJSON(QString itemType)
{
    QFile file(":/assets/shopItems/" + itemType + "s.json");
    if (file.open(QFile::ReadOnly)) {
        QByteArray _byteArr = file.readAll();
        file.close();

        QJsonParseError JSONErr;
        QJsonDocument JSONDoc = QJsonDocument::fromJson(_byteArr, &JSONErr);
        if (JSONErr.error == QJsonParseError::NoError && JSONDoc.isObject()) {
            QJsonObject JSONObj = JSONDoc.object();

            QJsonArray JSONArr = JSONObj.value(itemType + "s").toArray();
            for (int i = 0; i < JSONArr.size(); i++) {
                QJsonObject obj = JSONArr[i].toObject();

                // Initializing the ShopItem Widget with the data from JSON
                ShopItem *item
                    = new ShopItem(this,
                                   itemType,
                                   obj.value("id").toInt(),
                                   obj.value("name").toString(),
                                   obj.value("price").toInt(),
                                   (itemType == "cannon" ? obj.value("bulletDamage").toInt() : 0),
                                   (itemType == "cannon" ? obj.value("bulletSpeed").toDouble() : 0),
                                   (itemType == "cannon" ? obj.value("attackSpeed_ms").toInt() : 0),
                                   (itemType == "castle" || "fence" ? obj.value("maxHealth").toInt()
                                                                    : 0),
                                   (itemType == "worker" ? obj.value("workerSpeed").toDouble() : 0),
                                   (itemType == "worker" ? obj.value("workerHealing").toInt() : 0));

                if (itemType == "cannon") {
                    ui->cannon_horizontalLayout->addWidget(item);
                    cannonList.push_back(item);
                } else if (itemType == "fence") {
                    ui->fence_horizontalLayout->addWidget(item);
                    fenceList.push_back(item);
                } else if (itemType == "castle") {
                    ui->castle_horizontalLayout->addWidget(item);
                    castleList.push_back(item);
                } else if (itemType == "worker") {
                    ui->worker_horizontalLayout->addWidget(item);
                    workerList.push_back(item);
                }
            }
        }
    }
}

void ItemShopWindow::updateItemsState(int cannonId, int fenceId, int castleId, int workerId)
{
    for (int i = 0; i < cannonList.size(); i++) {
        cannonList[i]->updateState(cannonId, player->getGold());
    }
    for (int i = 0; i < fenceList.size(); i++) {
        fenceList[i]->updateState(fenceId, player->getGold());
    }
    for (int i = 0; i < castleList.size(); i++) {
        castleList[i]->updateState(castleId, player->getGold());
    }
    for (int i = 0; i < workerList.size(); i++) {
        workerList[i]->updateState(workerId, player->getGold());
    }

    if (purchaseStack.isEmpty()) {
        ui->undo_Button->setDisabled(true);
        ui->undo_Button->setVisible(false);
    } else {
        ui->undo_Button->setDisabled(false);
        ui->undo_Button->setVisible(true);
    }
}

void ItemShopWindow::makePurchase(Purchase *purchase)
{
    if (purchase->itemType == "cannon") {
        CannonData *cannonData = new CannonData{purchase->itemId,
                                                purchase->bulletDamage,
                                                purchase->bulletSpeed,
                                                purchase->attackSpeed_ms};
        player->setCannonData(cannonData);
        delete cannonData;
    } else if (purchase->itemType == "fence") {
        FenceData *fenceData = new FenceData{purchase->itemId, purchase->maxHealth};
        player->setFenceData(fenceData);
        delete fenceData;
    } else if (purchase->itemType == "castle") {
        CastleData *castleData = new CastleData{purchase->itemId, purchase->maxHealth};
        player->setCastleData(castleData);
        delete castleData;
    } else if (purchase->itemType == "worker") {
        WorkerData *workerData = new WorkerData{purchase->itemId,
                                                purchase->workerSpeed,
                                                purchase->workerHealing};
        player->setWorkerData(workerData);
        delete workerData;
    }

    player->setGold(player->getGold() - purchase->price);

    ui->stats_label->setText("🎚️ " + QString::number(player->getLevel()) + "\t 🪙 "
                             + QString::number(player->getGold()));
    updateItemsState(player->getCannonData()->cannonId,
                     player->getFenceData()->fenceId,
                     player->getCastleData()->castleId,
                     player->getWorkerData()->workerId);
}

// Slots
void ItemShopWindow::on_undo_Button_clicked()
{
    buttonClickAudio->playAudio();

    if (!purchaseStack.isEmpty()) {
        Purchase *purchase = purchaseStack.pop();
        purchase->price *= -1;
        makePurchase(purchase);
        delete purchase;
    }
}

void ItemShopWindow::on_lockin_Button_clicked()
{
    buttonClickAudio->playAudio();

    game = new Game(player, enemyDataAdditions);
    player->setGame(game);
    game->start();
    hide();
}

void ItemShopWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape) {
        // Simply do nothing :)
    }
}
