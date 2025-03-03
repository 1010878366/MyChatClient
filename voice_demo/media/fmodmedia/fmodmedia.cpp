#include "fmodmedia.h"

FmodMedia *FmodMedia::self = new FmodMedia;

FmodMedia::FmodMedia(QObject *parent)
    :QObject(parent)
{
    initFmod();
}

void FmodMedia::initFmod()
{
    //定义声音系统
    FMOD_System_Create(&system);
    //初始化
    FMOD_System_Init(system,32,FMOD_INIT_NORMAL,0);

    sound = nullptr;
    channel = nullptr;

}

//播放声音
void FmodMedia::playWav(QString strFileName)
{
    stopWav();

    //
    FMOD_System_CreateSound(system,
                            strFileName.toLocal8Bit().data(),
                            FMOD_SOFTWARE | FMOD_CREATESAMPLE,
                            0,
                            &sound);

    FMOD_Sound_SetMode(sound, FMOD_LOOP_OFF);

    FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, sound, false, &channel);
}

void FmodMedia::stopWav()
{
    if (NULL != channel) {
        FMOD_Channel_Stop(channel);
        channel = NULL;
    }
}
