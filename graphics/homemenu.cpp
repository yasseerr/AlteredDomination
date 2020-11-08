#include "homemenu.h"

#include <QCoreApplication>
#include <QDir>
#include <QQmlContext>

HomeMenu::HomeMenu():QQuickView(),game(nullptr)
{
    QFile mapFile(":/data/map.json");
    mapFile.open(QIODevice::ReadOnly|QIODevice::Text);
    QTextStream st(&mapFile);
    setMapData(st.readAll());

    QFile savesFile(QDir::currentPath()+"/gameSaves.json");
    savesFile.open(QIODevice::ReadOnly|QIODevice::Text);
    QTextStream st2(&savesFile);
    setSavesData(st2.readAll());


    this->rootContext()->setContextProperty("homeClass",this);
    this->setSource(QUrl("qrc:/scripts/home/HomeMenu.qml"));
    this->showMaximized();

}
void HomeMenu::startGame(QString cntr, int mode)
{
    game  = new MainMenu(cntr,mode,0,"");
    connect(game->mapView(),&MapView::returnHome,this,&HomeMenu::onReturnHome);
    this->hide();
    game->showMaximized();
}

void HomeMenu::loadGame(QString cntr, int turn, QString gameSaveString)
{
    game  = new MainMenu(cntr,1,1,gameSaveString);
    connect(game->mapView(),&MapView::returnHome,this,&HomeMenu::onReturnHome);
    game->mapView()->setTurnNumber(turn);
    this->hide();
    game->showMaximized();

}

void HomeMenu::deleteGameSave(QString newfilString)
{
    QFile savesFile(QDir::currentPath()+"/gameSaves.json");
    savesFile.open(QIODevice::WriteOnly|QIODevice::Text);
    QTextStream st2(&savesFile);
    st2 << newfilString.toLocal8Bit();
}

void HomeMenu::quitApp()
{
    QCoreApplication::quit();
}

QString HomeMenu::mapData() const
{
    return m_mapData;
}

QString HomeMenu::savesData() const
{
    return m_savesData;
}

void HomeMenu::setMapData(QString mapData)
{
    if (m_mapData == mapData)
        return;

    m_mapData = mapData;
    emit mapDataChanged(m_mapData);
}

void HomeMenu::setSavesData(QString savesData)
{
    if (m_savesData == savesData)
        return;

    m_savesData = savesData;
    emit savesDataChanged(m_savesData);
}

void HomeMenu::onReturnHome()
{
    game->hide();

    QFile savesFile(QDir::currentPath()+"/gameSaves.json");
    savesFile.open(QIODevice::ReadOnly|QIODevice::Text);
    QTextStream st2(&savesFile);
    this->setSavesData(st2.readAll());

    this->showMaximized();
    game->deleteLater();
}
