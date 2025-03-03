greaterThan(QT_MAJOR_VERSION,4):QT+=multimedia

SOURCES += \
    $$PWD/fmodmedia/fmodmedia.cpp   \
    $$PWD/mydevice/mydevice.cpp \

HEADERS += \
    $$PWD/fmodmedia/fmodmedia.h \
    $$PWD/mydevice/mydevice.h   \

INCLUDEPATH += $$PWD
INCLUDEPATH += $$fmodmedia
INCLUDEPATH += $$mydevice
INCLUDEPATH += $$PWD/fmod/include
LIBS        += -L$$PWD/fmod/libs -lfmodex
