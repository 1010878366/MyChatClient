#包含一个目录
INCLUDEPATH += $$PWD
#如果DEPENDPATH目录里的头文件发生了变化，所有的cpp都会重新编译
DEPENDPATH += $$PWD

#$$PWD  当前目录  D:\work\workspace\qtstudyspace\MyChatClient\basewidget

HEADERS += \
    $$PWD/animationstackedwidget.h \
    $$PWD/clineedit.h \
    $$PWD/customwidget.h \
    $$PWD/chatstackedwidget.h \
    $$PWD/qqlist/qqlistviewchild.h \
    $$PWD/qqlist/qqlistviewgroup.h \
    $$PWD/qqlist/qqlistwidget.h \
    $$PWD/qqlist/qqpopmenuwidget.h \
    $$PWD/chatbubble.h

SOURCES += \
    $$PWD/animationstackedwidget.cpp \
    $$PWD/clineedit.cpp \
    $$PWD/customwidget.cpp \
    $$PWD/chatstackedwidget.cpp \
    $$PWD/qqlist/qqlistviewchild.cpp \
    $$PWD/qqlist/qqlistviewgroup.cpp \
    $$PWD/qqlist/qqlistwidget.cpp \
    $$PWD/qqlist/qqpopmenuwidget.cpp \
    $$PWD/chatbubble.cpp

FORMS += \
    $$PWD/qqlist/qqlistviewgroup.ui
