#include "mainmenu.h"
#include "ui_mainmenu.h"

#include <QQmlComponent>
#include <QQmlContext>
#include <QQuickItem>
#include <QThread>

MainMenu::MainMenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainMenu)
{
    ui->setupUi(this);
    m_mapView = new MapView(this);
    connect(m_mapView,&MapView::attackerWon,this,&MainMenu::onAttackerWon);

    ///---- temporary setting the active player country-----------
    m_activePlayerStr = "dz";
    m_mapView->setActivePStr(m_activePlayerStr);


    m_mapView->loadFromJson();
    ui->CitiesDisplayUI->hide();
    ui->horizontalLayout_2->addWidget(m_mapView);

///--------------------- setting up the MapMenu--------------------------

    ui->MapMenuUI->rootContext()->setContextProperty("activePlayer",m_mapView->activePlayer());
    ui->MapMenuUI->rootContext()->setContextProperty("actuelPlayer",m_mapView->actuelPlayer());
    ui->MapMenuUI->rootContext()->setContextProperty("citiesDisplayUI",ui->CitiesDisplayUI);
    ui->MapMenuUI->rootContext()->setContextProperty("mainmenu",this);
    ui->MapMenuUI->rootContext()->setContextProperty("menuOpt",mapView()->menuOptUI);

    ui->CitiesDisplayUI->rootContext()->setContextProperty("mainmenu",this);
    reDisplayCities();


}

MainMenu::~MainMenu()
{
    delete ui;
}

MapView* MainMenu::mapView() const
{
    return m_mapView;
}

QString MainMenu::activePlayerStr() const
{
    return m_activePlayerStr;
}

void MainMenu::startGame()
{

}

void MainMenu::setMapView(MapView* mapView)
{
    if (m_mapView == mapView)
        return;

    m_mapView = mapView;
    emit mapViewChanged(m_mapView);
}

void MainMenu::setActivePlayerStr(QString activePlayerStr)
{
    if (m_activePlayerStr == activePlayerStr)
        return;

    m_activePlayerStr = activePlayerStr;
    emit activePlayerStrChanged(m_activePlayerStr);
}

void MainMenu::reDisplayCities()
{
    foreach (City *c, m_mapView->activePlayer()->country()->cities()) {
        emit sendCityToDisplay(c);
    }
}

void MainMenu::focusOnCity(City *c)
{
    m_mapView->centerOn(c->x(),c->y());
}

void MainMenu::runNextTurn()
{
    m_mapView->setEnabled(false);
    foreach (Player *p, m_mapView->players()) {
        p->country()->setFunds(p->country()->funds()+p->country()->income());
        if(p == m_mapView->activePlayer()) continue;
        m_mapView->setActuelPlayer(p);
//        QThread::msleep(200);
    }
    m_mapView->setEnabled(true);
    m_mapView->setActuelPlayer(m_mapView->activePlayer());
}

void MainMenu::onAttackerWon(City *C)
{
    sendCityToDisplay(C);
}
