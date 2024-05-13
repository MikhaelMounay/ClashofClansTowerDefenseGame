#include "mainwindow.h"
#include "player.h"

#include <QApplication>
#include <QFontDatabase>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Including Custom Font
    QFontDatabase::addApplicationFont(":/assets/fonts/Bungee.ttf");
    QFontDatabase::addApplicationFont(":/assets/fonts/RollingNoOne.ttf");

    // Initializing the Player
    Player *player = new Player;

    // Showing the game as full screen
    MainWindow window(player);
    window.resizeLayout();

    window.show();

    return a.exec();
}
