#ifndef FMODMEDIA_H
#define FMODMEDIA_H

#include <QObject>
#include "media/fmod/include/fmod.h"

class FmodMedia : public QObject
{
private:
    FmodMedia(QObject *parent = 0);
    static FmodMedia *self;

    //Fmod
    FMOD_SYSTEM *system;    //声音系统
    FMOD_SOUND *sound;      //声音
    FMOD_CHANNEL *channel;  //通道

    //初始化Fmod
    void initFmod();

    void stopWav();

public:
    static FmodMedia *getInstance()
    {
        return self;
    }

    void playWav(QString strFileName);

};

#endif // FMODMEDIA_H
