#include "buttonclickaudio.h"
#include <QAudioOutput>
#include <QMediaPlayer>

ButtonClickAudio::ButtonClickAudio(bool isPurchase)
{
    // Set Button Click Audio
    QAudioOutput *buttonClickAudioOutput = new QAudioOutput;
    buttonClickAudioOutput->setVolume(1);
    buttonClickAudio = new QMediaPlayer;
    buttonClickAudio->setAudioOutput(buttonClickAudioOutput);
    if (isPurchase) {
        buttonClickAudio->setSource(QUrl("qrc:/assets/audio/purchase_click.mp3"));
    } else {
        buttonClickAudio->setSource(QUrl("qrc:/assets/audio/button_click.mp3"));
    }
}

void ButtonClickAudio::playAudio()
{
    if (buttonClickAudio->playbackState() == QMediaPlayer::PlayingState) {
        buttonClickAudio->setPosition(0);
    } else if (buttonClickAudio->playbackState() == QMediaPlayer::StoppedState) {
        buttonClickAudio->play();
    }
}
