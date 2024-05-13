#ifndef BUTTONCLICKAUDIO_H
#define BUTTONCLICKAUDIO_H

#include <QMediaPlayer>

class ButtonClickAudio
{
private:
    // Member Variables
    QMediaPlayer *buttonClickAudio;

public:
    // Member Functions
    ButtonClickAudio(bool isPurchase = false);

    void playAudio();
};

#endif // BUTTONCLICKAUDIO_H
