#include "apiclient.h"
#include <QDebug>
#include <QEventLoop>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include "player.h"

QString API_BASE_URL = "https://clashofclanstowerdefensegame.onrender.com/";

APIClient::APIClient(Player *playerPtr, QObject *parent)
    : QObject()
{
    // Initializing Variables
    player = playerPtr;
    netManager = new QNetworkAccessManager(this);
}

APIClient::~APIClient()
{
    delete netManager;
}

void APIClient::readNetReply(QNetworkReply *netReply, PlayerInfo *playerInfo)
{
    if (netReply->error() == QNetworkReply::NoError) {
        QByteArray _byteArr = netReply->readAll();

        QJsonParseError JSONErr;
        QJsonDocument JSONDoc = QJsonDocument::fromJson(_byteArr, &JSONErr);
        if (JSONErr.error == QJsonParseError::NoError && JSONDoc.isObject()) {
            QJsonObject objRes = JSONDoc.object();

            if (objRes.value("playerInfo").toObject().isEmpty()) {
                playerInfo->username = "";
            } else {
                playerInfo->username
                    = objRes.value("playerInfo").toObject().value("username").toString();
                playerInfo->hashedPassword
                    = objRes.value("playerInfo").toObject().value("hashedpassword").toString();
                playerInfo->level = objRes.value("playerInfo").toObject().value("level").toInt();
                playerInfo->gold = objRes.value("playerInfo").toObject().value("gold").toInt();
                playerInfo->clan = objRes.value("playerInfo").toObject().value("clan").toString();
                playerInfo->cannon_id
                    = objRes.value("playerInfo").toObject().value("cannon_id").toInt();
                playerInfo->fence_id
                    = objRes.value("playerInfo").toObject().value("fence_id").toInt();
                playerInfo->castle_id
                    = objRes.value("playerInfo").toObject().value("castle_id").toInt();
                playerInfo->worker_id
                    = objRes.value("playerInfo").toObject().value("worker_id").toInt();
                playerInfo->rankGlobal
                    = objRes.value("playerInfo").toObject().value("global_rank").toString().toInt();
                if (playerInfo->clan != "") {
                    playerInfo->rankClan
                        = objRes.value("playerInfo").toObject().value("clan_rank").toString().toInt();
                } else {
                    playerInfo->rankClan = 0;
                }
            }
        }
    } else {
        qDebug() << "APIClient::readNetReply => " << netReply->errorString();
    }
}

void APIClient::getRequest(QUrl Url, PlayerInfo *playerInfo)
{
    QNetworkRequest netRequest(Url);
    QNetworkReply *netReply = netManager->get(netRequest);

    QEventLoop loop;
    connect(netReply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    readNetReply(netReply, playerInfo);
}

void APIClient::postRequest(QUrl Url, QByteArray _byteArr, PlayerInfo *playerInfo)
{
    QNetworkRequest netRequest(Url);
    netRequest.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QNetworkReply *netReply = netManager->post(netRequest, _byteArr);

    QEventLoop loop;
    connect(netReply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    readNetReply(netReply, playerInfo);
}

void APIClient::putRequest(QUrl Url, QByteArray _byteArr, PlayerInfo *playerInfo)
{
    QNetworkRequest netRequest(Url);
    netRequest.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QNetworkReply *netReply = netManager->put(netRequest, _byteArr);

    QEventLoop loop;
    connect(netReply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    readNetReply(netReply, playerInfo);
}
