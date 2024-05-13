#include "mainwindow.h"
#include <QAudioOutput>
#include <QCursor>
#include <QMediaPlayer>
#include <QMessageBox>
#include <QPixmap>
#include "game.h"
#include "itemshopwindow.h"
#include "loginwindow.h"
#include "player.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(Player *playerPtr, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Styling the main window
    setWindowTitle("Clash of Clans | Game Launcher");
    setWindowState(Qt::WindowFullScreen);

    QPixmap bgimg(":/assets/imgs/game_launcher/background.jpg");
    bgimg.scaled(this->size(), Qt::KeepAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, bgimg);
    this->setPalette(palette);

    // Change the cursor of the game
    QPixmap cursorPixmap(":/assets/imgs/game_launcher/sword_cursor.png");
    QCursor customCursor(cursorPixmap);
    setCursor(customCursor);

    // Initializing player
    player = playerPtr;
    setPlayerInfoText(player->displayPlayerInfo());
    setGameOverText("To Level " + QString::number(player->getLevel()) + " ➡️");

    // Preparing LoginWindow
    loginWindow = new LoginWindow(player);
    connect(loginWindow, &LoginWindow::windowClosed, this, &MainWindow::onLoginWindowClosed);
    loginWindow->setModal(true);

    // Play Intro Audio
    QAudioOutput *introAudioOutput = new QAudioOutput;
    introAudioOutput->setVolume(1);
    introAudio = new QMediaPlayer;
    introAudio->setAudioOutput(introAudioOutput);
    introAudio->setSource(QUrl("qrc:/assets/audio/intro.mp3"));
    introAudio->play();

    // Set Button Click Audio
    buttonClickAudio = new ButtonClickAudio();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::hideEvent(QHideEvent *event)
{
    introAudio->stop();
    hide();
}

// Setters
void MainWindow::setGameOverText(QString text)
{
    ui->gameOver_label->setText(text);
}

void MainWindow::setPlayerInfoText(QString text)
{
    ui->playerInfo_label->setText(text);
}

void MainWindow::resizeLayout()
{
    ui->sizeController_Button->setMinimumWidth(this->width() * 0.25);
}

// Slots
void MainWindow::onLoginWindowClosed()
{
    setPlayerInfoText(player->displayPlayerInfo());
    setGameOverText("To Level " + QString::number(player->getLevel()) + " ➡️");
}

void MainWindow::on_quit_Button_clicked()
{
    buttonClickAudio->playAudio();

    QMessageBox::StandardButton reply = QMessageBox::question(this,
                                                              "Quit?",
                                                              "One last game :) ?!",
                                                              QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::No) {
        close();
    }
}

void MainWindow::on_start_Button_clicked()
{
    buttonClickAudio->playAudio();

    ItemShopWindow *itemShopWindow = new ItemShopWindow(player);
    itemShopWindow->show();
    this->hide();
}

void MainWindow::on_online_Button_clicked()
{
    buttonClickAudio->playAudio();

    loginWindow->show();
}
