#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QDialog>
#include "buttonclickaudio.h"
#include "player.h"

namespace Ui {
class LoginWindow;
}

class LoginWindow : public QDialog
{
    Q_OBJECT

private:
    Ui::LoginWindow *ui;

    ButtonClickAudio *buttonClickAudio;

    // Member Functions
    QString hashString(QString input);
    bool _isCredValid();

public:
    // Member Variables
    Player *player;

    // Member Functions
    explicit LoginWindow(Player *playerPtr, QWidget *parent = nullptr);
    ~LoginWindow();

    void closeEvent(QCloseEvent *event);

private slots:
    void on_login_Button_clicked();
    void on_register_Button_clicked();

signals:
    void windowClosed();
};

#endif // LOGINWINDOW_H
