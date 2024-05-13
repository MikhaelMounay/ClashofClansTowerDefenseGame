#ifndef ITEMSHOPWINDOW_H
#define ITEMSHOPWINDOW_H

#include <QDialog>
#include <QList>
#include <QMediaPlayer>
#include <QStack>
#include "buttonclickaudio.h"
#include "game.h"
#include "player.h"

class ShopItem;

struct Purchase
{
    QString itemType;
    int itemId;
    int price;
    int bulletDamage = 0;
    double bulletSpeed = 0;
    int attackSpeed_ms = 0;
    int maxHealth = 0;
    double workerSpeed = 0;
    int workerHealing = 0;
};

namespace Ui {
class ItemShopWindow;
}

class ItemShopWindow : public QDialog
{
    Q_OBJECT

private:
    Ui::ItemShopWindow *ui;

    // Member Variables
    QList<ShopItem *> cannonList;
    QList<ShopItem *> fenceList;
    QList<ShopItem *> castleList;
    QList<ShopItem *> workerList;
    EnemyDataAdditions *enemyDataAdditions;

    QMediaPlayer *itemShopThemeAudio;
    ButtonClickAudio *buttonClickAudio;

    // Member Functions
    void fetchItemsFromJSON(QString itemType);

public:
    // Member Variables
    Player *player;
    Game *game;
    QStack<Purchase *> purchaseStack;

    // Member Functions
    explicit ItemShopWindow(Player *playerPtr, QWidget *parent = nullptr);
    ~ItemShopWindow();

    void updateItemsState(int cannonId, int fenceId, int castleId, int workerId);
    void makePurchase(Purchase *purchase);

    void keyPressEvent(QKeyEvent *event); // To prevent program exiting whole game using "escape"
    void hideEvent(QHideEvent *event);

private slots:
    void on_undo_Button_clicked();
    void on_lockin_Button_clicked();
};

#endif // ITEMSHOPWINDOW_H
