#ifndef SHOPITEM_H
#define SHOPITEM_H

#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include "buttonclickaudio.h"
#include "itemshopwindow.h"

class ShopItem : public QWidget
{
    Q_OBJECT

private:
    // Member Variables
    ItemShopWindow *itemShopWindow;
    QString itemType;
    int itemId;
    QString itemName;
    int price;
    int bulletDamage;
    double bulletSpeed;
    int attackSpeed_ms;
    int maxHealth;
    double workerSpeed;
    int workerHealing;

    QVBoxLayout *vLayout;
    QLabel *image;
    QLabel *name;
    QLabel *stats;
    QPushButton *buy_Button;

    ButtonClickAudio *purchaseButtonClickAudio;

public:
    // Member Functions
    ShopItem(ItemShopWindow *itemShopWindowPtr,
             QString itemType,
             int itemId,
             QString itemName,
             int price,
             int bulletDamage = 0,
             double bulletSpeed = 0,
             int attackSpeed_ms = 0,
             int maxHealth = 0,
             double workerSpeed = 0,
             int workerHealing = 0);
    void updateState(int ItemId, int availableGold);

private slots:
    void on_buy_Button_clicked();
};

#endif // SHOPITEM_H
