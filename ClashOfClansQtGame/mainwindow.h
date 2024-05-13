#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>
#include "buttonclickaudio.h"
#include "game.h"
#include "player.h"
#include <loginwindow.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    Ui::MainWindow *ui;

    LoginWindow *loginWindow;
    QMediaPlayer *introAudio;
    ButtonClickAudio *buttonClickAudio;

public:
    explicit MainWindow(Player *playerPtr, QWidget *parent = nullptr);
    ~MainWindow();

    Player *player;

    // Setters
    void setGameOverText(QString text);
    void setPlayerInfoText(QString text);
    void resizeLayout();

    void hideEvent(QHideEvent *event);

public slots:
    void onLoginWindowClosed();

private slots:
    void on_quit_Button_clicked();
    void on_start_Button_clicked();
    void on_online_Button_clicked();
};

#endif // MAINWINDOW_H
