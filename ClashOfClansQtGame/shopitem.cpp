#include "shopitem.h"
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include "itemshopwindow.h"

ShopItem::ShopItem(ItemShopWindow *itemShopWindowPtr,
                   QString ItemType,
                   int ItemId,
                   QString ItemName,
                   int Price,
                   int BulletDamage,
                   double BulletSpeed,
                   int AttackSpeed_ms,
                   int MaxHealth,
                   double WorkerSpeed,
                   int WorkerHealing)
    : QWidget()
{
    // Initializing Variables
    itemShopWindow = itemShopWindowPtr;
    itemType = ItemType;
    itemId = ItemId;
    itemName = ItemName;
    price = Price;
    bulletDamage = BulletDamage;
    bulletSpeed = BulletSpeed;
    attackSpeed_ms = AttackSpeed_ms;
    maxHealth = MaxHealth;
    workerSpeed = WorkerSpeed;
    workerHealing = WorkerHealing;

    // Designing the Shop Item
    this->setFixedWidth(225);
    this->setFont(QFont("Bungee", 11));

    // Adding a Vertical Layout
    vLayout = new QVBoxLayout(this);
    vLayout->setAlignment(Qt::AlignCenter);

    // Adding the image of the item
    QString imagePath = ":/assets/imgs/" + itemType + "/lvl_" + QString::number(itemId) + ".png";
    image = new QLabel(this);
    image->setPixmap(QPixmap(imagePath).scaled(75, 75, Qt::KeepAspectRatio));
    image->setAlignment(Qt::AlignCenter);
    vLayout->addWidget(image);

    // Adding the name of the item
    name = new QLabel(this);
    name->setText(itemName);
    name->setAlignment(Qt::AlignCenter);
    vLayout->addWidget(name);
    name->setFont(QFont("Bungee", 12));

    // Adding the stats of the item
    stats = new QLabel(this);
    stats->setText(
        (bulletDamage == 0 ? "" : (" 💥 " + QString::number(bulletDamage)))
        + (bulletSpeed == 0 ? "" : (" 💨 " + QString::number(bulletSpeed)))
        + (attackSpeed_ms == 0 ? "" : (" 🚀 " + QString::number(attackSpeed_ms / 1000.0) + " bps"))
        + (maxHealth == 0 ? "" : (" 🛡️ " + QString::number(maxHealth)))
        + (workerSpeed == 0 ? "" : (" 🏃 " + QString::number(workerSpeed)))
        + (workerHealing == 0 ? "" : (" 🛠️ " + QString::number(workerHealing))));
    stats->setAlignment(Qt::AlignCenter);
    vLayout->addWidget(stats);

    // Adding the Buy button
    buy_Button = new QPushButton(this);
    buy_Button->setText("🪙 " + QString::number(price));
    buy_Button->setObjectName("buy_Button");
    buy_Button->setStyleSheet("QPushButton#buy_Button {background-color: #30ed45; color: black; "
                              "border-style: solid; border-width: 2px; border-radius: 10px; "
                              "border-color: black; padding: 10px; font: 11pt Bungee"
                              ";} QPushButton#buy_Button:hover { background-color: #0ccb21;} "
                              "QPushButton#buy_Button:focus { border-width: 4px;}");
    buy_Button->setFixedHeight(50);
    vLayout->addWidget(buy_Button);
    connect(buy_Button, &QPushButton::clicked, this, &ShopItem::on_buy_Button_clicked);

    // Set Purchase Button Click Audio
    purchaseButtonClickAudio = new ButtonClickAudio(true);
}

void ShopItem::updateState(int ItemId, int availableGold)
{
    if (itemId == ItemId) {
        buy_Button->setStyleSheet("background-color: #efad46; color: black; "
                                  "border-style: solid; border-width: 2px; border-radius: 10px; "
                                  "border-color: black; padding: 10px; font: 11pt Bungee;");
        buy_Button->setDisabled(true);
    } else if (price > availableGold) {
        buy_Button->setStyleSheet("background-color: #ef4646; color: black; "
                                  "border-style: solid; border-width: 2px; border-radius: 10px; "
                                  "border-color: black; padding: 10px; font: 11pt Bungee;");
        buy_Button->setDisabled(true);
    } else {
        buy_Button->setStyleSheet(
            "QPushButton#buy_Button {background-color: #30ed45; color: black; "
            "border-style: solid; border-width: 2px; border-radius: 10px; "
            "border-color: black; padding: 10px; font: 11pt Bungee"
            ";} QPushButton#buy_Button:hover { background-color: #0ccb21;} "
            "QPushButton#buy_Button:focus { border-width: 4px;}");
        buy_Button->setDisabled(false);
    }
}

// Slots
void ShopItem::on_buy_Button_clicked()
{
    purchaseButtonClickAudio->playAudio();

    // If it's pressed, this means the btn is not disabled. i.e., there's enough gold to buy. No need to check

    Purchase *purchase = new Purchase{itemType, itemId, price};
    Purchase *purchaseUndo;

    if (itemType == "cannon") {
        purchase->bulletDamage = bulletDamage;
        purchase->bulletSpeed = bulletSpeed;
        purchase->attackSpeed_ms = attackSpeed_ms;

        purchaseUndo = new Purchase{"cannon",
                                    itemShopWindow->player->getCannonData()->cannonId,
                                    price};
        purchaseUndo->bulletDamage = itemShopWindow->player->getCannonData()->bulletDamage;
        purchaseUndo->bulletSpeed = itemShopWindow->player->getCannonData()->bulletSpeed;
        purchaseUndo->attackSpeed_ms = itemShopWindow->player->getCannonData()->attackSpeed_ms;
    } else if (itemType == "fence") {
        purchase->maxHealth = maxHealth;

        purchaseUndo = new Purchase{"fence", itemShopWindow->player->getFenceData()->fenceId, price};
        purchaseUndo->maxHealth = itemShopWindow->player->getFenceData()->maxHealth;
    } else if (itemType == "castle") {
        purchase->maxHealth = maxHealth;

        purchaseUndo = new Purchase{"castle",
                                    itemShopWindow->player->getCastleData()->castleId,
                                    price};
        purchaseUndo->maxHealth = itemShopWindow->player->getCastleData()->maxHealth;
    } else if (itemType == "worker") {
        purchase->workerSpeed = workerSpeed;
        purchase->workerHealing = workerHealing;

        purchaseUndo = new Purchase{"worker",
                                    itemShopWindow->player->getWorkerData()->workerId,
                                    price};
        purchaseUndo->workerSpeed = itemShopWindow->player->getWorkerData()->workerSpeed;
        purchaseUndo->workerHealing = itemShopWindow->player->getWorkerData()->workerHealing;
    }

    itemShopWindow->purchaseStack.push(purchaseUndo);
    itemShopWindow->makePurchase(purchase);
    delete purchase;
}
