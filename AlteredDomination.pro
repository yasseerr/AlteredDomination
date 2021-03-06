#-------------------------------------------------
#
# Project created by QtCreator 2018-07-24T12:00:21
#
#-------------------------------------------------

QT       += core multimedia network gui svg quick quickwidgets xml


CONFIG += resources_big
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AlteredDomination
TEMPLATE = app
RC_FILE = icon.rc
#ICON = adicon.svg
# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainmenu.cpp \
        domain/map.cpp \
    domain/city.cpp \
    domain/country.cpp \
    graphics/mapview.cpp \
    graphics/citygraphics.cpp \
    domain/unit.cpp \
    graphics/unitgraphics.cpp \
    graphics/linkgraphics.cpp \
    domain/linkn.cpp \
    domain/player.cpp \
    domain/battlemap.cpp \
    domain/unittype.cpp \
    domain/umove.cpp \
    domain/uattack.cpp \
    graphics/bmapscene.cpp \
    graphics/bframe.cpp \
    battleform.cpp \
    AI/mapai.cpp \
    AI/battleai.cpp \
    graphics/animations.cpp \
    graphics/homemenu.cpp \
    multiplayer/multiplayergame.cpp \
    multiplayer/serverengin.cpp \
    graphics/animationhandlerbattle.cpp \
    graphics/mapgraphics.cpp \
    graphics/unitpupup.cpp \
    graphics/battleborderitem.cpp

HEADERS += \
        mainmenu.h \
        domain/map.h \
    domain/city.h \
    domain/country.h \
    graphics/mapview.h \
    graphics/citygraphics.h \
    domain/unit.h \
    graphics/unitgraphics.h \
    graphics/linkgraphics.h \
    domain/linkn.h \
    domain/player.h \
    domain/battlemap.h \
    domain/unittype.h \
    domain/umove.h \
    domain/uattack.h \
    graphics/bmapscene.h \
    graphics/bframe.h \
    battleform.h \
    AI/mapai.h \
    AI/battleai.h \
    graphics/animations.h \
    graphics/homemenu.h \
    multiplayer/multiplayergame.h \
    multiplayer/serverengin.h \
    graphics/animationhandlerbattle.h \
    graphics/mapgraphics.h \
    graphics/unitpupup.h \
    graphics/battleborderitem.h

FORMS += \
        mainmenu.ui \
    battleform.ui

RESOURCES += \
    data00.qrc

DISTFILES +=
