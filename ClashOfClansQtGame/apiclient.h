#ifndef APICLIENT_H
#define APICLIENT_H

#include <QObject>
#include <QtNetwork/QNetworkAccessManager>
#include "player.h"

extern QString API_BASE_URL;

struct PlayerInfo
{
    QString username = "";
    QString hashedPassword = "";
    int level = -1;
    int gold = -1;
    QString clan = "";
    int cannon_id = 1;
    int fence_id = 1;
    int castle_id = 1;
    int worker_id = 1;
    int rankClan = 0;
    int rankGlobal = 0;
};

class APIClient : public QObject
{
    Q_OBJECT

private:
    // Member Variables
    QNetworkAccessManager *netManager;

public:
    // Member Variables
    Player *player;

    // Member Functions
    explicit APIClient(Player *playerPtr, QObject *parent = nullptr);
    ~APIClient();

    void getRequest(QUrl Url, PlayerInfo *playerInfo);
    void postRequest(QUrl Url, QByteArray _byteArr, PlayerInfo *playerInfo);
    void putRequest(QUrl Url, QByteArray _byteArr, PlayerInfo *playerInfo);
    void deleteRequest(QUrl Url);

    void readNetReply(QNetworkReply *netReply, PlayerInfo *playerInfo);
};

#endif // APICLIENT_H
