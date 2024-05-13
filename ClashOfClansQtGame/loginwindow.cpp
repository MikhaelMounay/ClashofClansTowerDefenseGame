#include "loginwindow.h"
#include <QCryptographicHash>
#include <QEventLoop>
#include <QInputDialog>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QLineEdit>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QSet>
#include "player.h"
#include "ui_loginwindow.h"
#include <apiclient.h>

LoginWindow::LoginWindow(Player *playerPtr, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LoginWindow)
{
    ui->setupUi(this);

    // Styling the Login window
    setWindowTitle("Clash of Clans | Login");

    QPixmap bgimg(":/assets/imgs/game_launcher/login_bg.jpg");
    bgimg.scaled(this->size(), Qt::KeepAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, bgimg);
    this->setPalette(palette);

    // Change the cursor of the game
    QPixmap cursorPixmap(":/assets/imgs/game_launcher/sword_cursor.png");
    QCursor customCursor(cursorPixmap);
    setCursor(customCursor);

    // Initializing Variables
    player = playerPtr;

    // Hiding the Error Label initially
    ui->error_label->setVisible(false);

    // Getting Available Clans from DB
    QNetworkAccessManager netManager;
    QNetworkRequest netRequest(QUrl(API_BASE_URL + "clans"));
    QNetworkReply *netReply = netManager.get(netRequest);

    QEventLoop loop;
    connect(netReply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    if (netReply->error() == QNetworkReply::NoError) {
        QByteArray _byteArr = netReply->readAll();

        QJsonParseError JSONErr;
        QJsonDocument JSONDoc = QJsonDocument::fromJson(_byteArr, &JSONErr);

        if (JSONErr.error == QJsonParseError::NoError && JSONDoc.isObject()) {
            QJsonObject objRes = JSONDoc.object();

            if (!(objRes.value("clans").toArray().isEmpty())) {
                QJsonArray JSONArr = objRes.value("clans").toArray();
                QSet<QString> clanSet;

                for (int i = 0; i < JSONArr.size(); i++) {
                    QJsonObject obj = JSONArr[i].toObject();

                    if (obj.value("clan").toString() != "") {
                        clanSet.insert(obj.value("clan").toString());
                    }
                }

                for (QSet<QString>::iterator it = clanSet.begin(); it != clanSet.end(); it++) {
                    ui->clans_comboBox->addItem(*it);
                }
            }
        }
    }
    netReply->deleteLater();

    // Set Button Click Audio
    buttonClickAudio = new ButtonClickAudio();
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

QString LoginWindow::hashString(QString input)
{
    QByteArray digest = input.toUtf8();
    digest = QCryptographicHash::hash(digest, QCryptographicHash::Sha256);
    return QString(digest.toHex());
}

bool LoginWindow::_isCredValid()
{
    if (ui->username_lineEdit->text() == "") {
        ui->error_label->setText("Username is empty ?!");
        ui->error_label->setVisible(true);
        return false;
    } else if (ui->password_lineEdit->text() == "") {
        ui->error_label->setText("Password is empty ?!");
        ui->error_label->setVisible(true);
        return false;
    } else {
        ui->error_label->setVisible(false);
        return true;
    }
}

void LoginWindow::closeEvent(QCloseEvent *event)
{
    emit windowClosed();
    close();
}

// Slots
void LoginWindow::on_login_Button_clicked()
{
    buttonClickAudio->playAudio();

    if (!_isCredValid()) {
        return;
    }

    APIClient *apiClient = new APIClient(player);
    PlayerInfo *playerInfo = new PlayerInfo;

    QJsonObject postDataObj;
    postDataObj["username"] = ui->username_lineEdit->text();
    postDataObj["hashedPassword"] = hashString(ui->password_lineEdit->text());
    QJsonDocument postDataDoc(postDataObj);
    QByteArray postDataByteArr = postDataDoc.toJson();

    apiClient->postRequest(QUrl(API_BASE_URL + "login"), postDataByteArr, playerInfo);
    if (playerInfo->username != "") {
        player->updatePlayerInfo(playerInfo);
        player->setOnlineMode(true);
        close();
    } else {
        ui->error_label->setText("Wrong name/pass!");
        ui->error_label->setVisible(true);
    }
    apiClient->deleteLater();
}

void LoginWindow::on_register_Button_clicked()
{
    buttonClickAudio->playAudio();

    if (!_isCredValid()) {
        return;
    } else {
        QString confirmPass = QInputDialog::getText(this,
                                                    "Clash of Clans | Register Online",
                                                    "Confirm Password: ",
                                                    QLineEdit::Password);

        if (ui->password_lineEdit->text() != confirmPass) {
            ui->error_label->setText("Pass not matching!");
            ui->error_label->setVisible(true);
            return;
        }
    }

    APIClient *apiClient = new APIClient(player);
    PlayerInfo *playerInfo = new PlayerInfo;

    QJsonObject postDataObj;
    postDataObj["username"] = ui->username_lineEdit->text();
    postDataObj["hashedPassword"] = hashString(ui->password_lineEdit->text());
    postDataObj["clan"] = ui->clans_comboBox->currentText();
    QJsonDocument postDataDoc(postDataObj);
    QByteArray postDataByteArr = postDataDoc.toJson();

    apiClient->postRequest(QUrl(API_BASE_URL + "newplayer"), postDataByteArr, playerInfo);
    if (playerInfo->username != "") {
        player->updatePlayerInfo(playerInfo);
        player->setOnlineMode(true);
        delete playerInfo;
        close();
    } else {
        ui->error_label->setText("Name exists!");
        ui->error_label->setVisible(true);
    }
    apiClient->deleteLater();
}
