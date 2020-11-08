#include "citygraphics.h"
#include "mapview.h"

#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QPropertyAnimation>
#include <QQmlContext>
#include <QQuickItem>
#include <QVariantList>

#include <domain/city.h>
#include <domain/country.h>
#include <domain/unit.h>

#include <AI/battleai.h>
#include <AI/mapai.h>


CityGraphics::CityGraphics(City *city_p,QImage *cityImg_p):cityImg(cityImg_p),m_city(city_p),m_toAttack(false),m_moveToIt(false)
{
    setFlags(QGraphicsItem::ItemSendsGeometryChanges);
    setAcceptHoverEvents(true);
    setZValue(10);
    m_power = 0;

}

QRectF CityGraphics::boundingRect() const
{
    return QRectF(0,0,700,700);

}

void CityGraphics::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    painter->setOpacity(0.3);
    painter->fillRect(boundingRect(),city()->country()->color());
    painter->setOpacity(1);
    painter->drawImage(100,100,bgImage->scaled(600,600));
//    painter->drawImage(10,0,*cityImg);


    if(m_moveToIt)painter->drawImage(300,-256,QImage(":/data/icons/moveto.png"));
    if(m_toAttack)painter->drawImage(0,0,QImage(":/data/icons/target.png").scaled(700,700));


    /// city name rect+text
    painter->setOpacity(0.3);
    painter->setBrush(m_city->country()->color().darker());
    painter->drawRect(0,500,700,200);
    painter->setOpacity(1);
    QFont nameFont;
    nameFont.setPointSize(70);
    nameFont.setBold(true);
    painter->setFont(nameFont);
    painter->drawText(20,630,m_city->name()+"-"+QString::number(m_city->id())+"-");
    nameFont.setBold(false);
    nameFont.setPointSize(150);
    painter->setPen(Qt::white);
    painter->setFont(nameFont);
    painter->drawText(300,200,QString::number(m_city->income()));
    painter->drawImage(0,0,this->city()->country()->flag());
}

City* CityGraphics::city() const
{
    return m_city;
}

void CityGraphics::hoverEnterEvent(QGraphicsSceneHoverEvent *ev)
{

    setScale(0.1);
    foreach (LinkGraphics *ln, this->links()) {
        ln->setOpacity(1);
        if(ln->link()->des()->country() == ln->link()->dep()->country())ln->setPen(QPen(ln->link()->des()->country()->color(),
                                                                                        4,Qt::SolidLine));
        else ln->setPen(QPen(Qt::red,4,Qt::SolidLine));
    }
}

void CityGraphics::hoverLeaveEvent(QGraphicsSceneHoverEvent *ev)
{
    this->setScale(0.09);

    foreach (LinkGraphics *ln, this->links()) {
        ln->setOpacity(0.2);
        if(ln->link()->des()->country() == ln->link()->dep()->country())ln->setPen(QPen(ln->link()->des()->country()->color(),
                                                                                        3,Qt::DashDotLine));
        else ln->setPen(QPen(Qt::red,2,Qt::DotLine));
    }
}

void CityGraphics::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    ///--------------- cancel the movement if its not a neighbour-----------
    if((mapView()->selectedCityGraphics()!= nullptr) && (!m_moveToIt) && (!m_toAttack)){
        foreach (City *c, mapView()->selectedCityGraphics()->city()->neighbours()) {
            this->mapView()->citiesGraphics().value(c->id())->setMoveToIt(false);
            this->mapView()->citiesGraphics().value(c->id())->setToAttack(false);
        }
        this->mapView()->setSelectedCityGraphics(nullptr);
        this->mapView()->mapScene()->update();
        return;
    }


//------------------------------ movement system-------------------------------------------------
    if(moveToIt()){
        this->mapView()->selectedCityGraphics()->city()->setUsed(true);
        mapView()->moveUnitUI->rootContext()->setContextProperty("sourceCity",mapView()->selectedCityGraphics());
        mapView()->moveUnitUI->rootContext()->setContextProperty("destinationCity",this);

        foreach (Unit *u, this->city()->units().values()) {
            emit unitToQml(u->id(),u->type());
        }
        foreach (Unit *u, mapView()->selectedCityGraphics()->city()->units().values()) {
            emit mapView()->selectedCityGraphics()->unitToQml(u->id(),u->type());
        }
        mapView()->moveUnitUI->show();
        return;

    }else if (m_toAttack) {

///------------------------- attack system----------------------------------------------------
        mapView()->attackUI->rootContext()->setContextProperty("sourceCity",mapView()->selectedCityGraphics());
        mapView()->attackUI->rootContext()->setContextProperty("destinationCity",this);
        foreach (Unit *u, this->city()->units().values()) {
            emit unitToAttackQml(u->type());
        }
        foreach (Unit *u, mapView()->selectedCityGraphics()->city()->units().values()) {
            emit mapView()->selectedCityGraphics()->unitToAttackQml(u->type());
        }
        mapView()->attackUI->show();
        return;
    }
///------------------------- ownership for the current player -----------------------------------
//    if(mapView()->actuelPlayer() != this->city()->country()->player() ) return;

    mapView()->CityUI->rootContext()->setContextProperty("city",this->city());
    mapView()->CityUI->rootContext()->setContextProperty("cityGraphics",this);
    mapView()->addUnitUI->rootContext()->setContextProperty("cityGraphics",this);
    mapView()->addUnitUI->rootContext()->setContextProperty("cityUI",mapView()->CityUI);
    mapView()->CityUI->rootContext()->setContextProperty("cityUI",mapView()->CityUI);
    mapView()->CityUI->show();


    foreach (Unit *tmp, city()->units().values()) {
        city()->addedUnitSig(tmp->type());
    }
}

QList<UnitGraphics *> CityGraphics::unitsG() const
{
    return m_unitsG;
}

QList<LinkGraphics*> CityGraphics::links()
{
    return m_links;
}

bool CityGraphics::moveToIt() const
{
    return m_moveToIt;
}

bool CityGraphics::toAttack() const
{
    return m_toAttack;
}

void CityGraphics::moveUnits()
{
    if(this->city()->used())return;
    foreach (City *c,this->city()->neighbours()) {
        if(!(this->city()->country() == c->country()))continue;
        this->mapView()->citiesGraphics().value(c->id())->setMoveToIt(true);
    }
    this->mapView()->setSelectedCityGraphics(this);
//    this->mapView()->CityUI->hide();

}

void CityGraphics::attack()
{
    if(this->city()->used())return;
    if(this->city()->units().size()==0)return;
    foreach (City *c,this->city()->neighbours()) {
        if((this->city()->country() == c->country()))continue;
        this->mapView()->citiesGraphics().value(c->id())->setToAttack(true);
    }
    this->mapView()->setSelectedCityGraphics(this);

}

void CityGraphics::cancelAttack()
{
    foreach (City *c,this->city()->neighbours()) {
        if((this->city()->country() == c->country()))continue;
        this->mapView()->citiesGraphics().value(c->id())->setToAttack(false);
    }
    this->mapView()->setSelectedCityGraphics(nullptr);
}

void CityGraphics::startBattle()
{
    this->mapView()->selectedCityGraphics()->city()->setUsed(true);
    /// ---------- i cas the deffender haz no unit--------------
    if(this->city()->units().size() == 0){
            this->city()->country()->removeCity(this->city());
            this->city()->setCountry(this->mapView()->selectedCityGraphics()->city()->country());
            this->mapView()->selectedCityGraphics()->city()->country()->addCity(this->city());


            foreach (Unit *u, this->mapView()->selectedCityGraphics()->city()->units()) {
                this->city()->addUnit(u);
                u->setCity(this->city());
                this->mapView()->selectedCityGraphics()->city()->removeUnit(u->id());
            }

            Player *p = mapView()->selectedCityGraphics()->city()->country()->player();
            if(mapView()->selectedCityGraphics()->city()->country()->player()->type()== PlayerType::HUMAIN)
                mapView()->selectedCityGraphics()->deSelect();
            emit mapView()->attackerWon(this->city());
            this->city()->setUsed(true);
            if(p->type() == PlayerType::AI){
                mapView()->mapAI()->launchBattleAI_Player();
            }
            return;
    }

    mapView()->setEnabled(false);
    mapView()->battleForm = new BattleForm();
    mapView()->battleForm->bScene()->setCurrentPlayer(mapView()->activePlayer());
    mapView()->battleForm->bScene()->setCurrentCityPlaying(mapView()->selectedCityGraphics()->city());
    BattleMap *bm = new BattleMap(mapView()->selectedCityGraphics()->city(),this->city(),mapView()->battleForm);
    mapView()->battleForm->bScene()->setBmap(bm);



    connect(mapView()->battleForm,SIGNAL(battleEnded()),this,SLOT(onBattleEnded()));
    connect(mapView()->battleForm,SIGNAL(battleEndedA()),this,SLOT(onAttackerWon()));

    mapView()->battleForm->publishMaptoQMl();
    mapView()->battleForm->showFullScreen();
//    mapView()->battleForm->battleAI()->placeUnits();

}

int CityGraphics::power() const
{
    return m_power;
}

MapView* CityGraphics::mapView() const
{
    return m_mapView;
}

void CityGraphics::setCity(City* city)
{
    if (m_city == city)
        return;

    m_city = city;
    emit cityChanged(m_city);
}

void CityGraphics::zoomChanged(double z)
{
    this->city()->setX(city()->x()*z);
    this->city()->setY(city()->y()*z);
    this->setPos(city()->x(),city()->y());
}

void CityGraphics::setMapView(MapView *mapView)
{
    if (m_mapView == mapView)
        return;

    m_mapView = mapView;
    emit mapViewChanged(m_mapView);
}

void CityGraphics::setUnitsG(QList<UnitGraphics *> unitsG)
{
    if (m_unitsG == unitsG)
        return;
    m_unitsG = unitsG;
    emit unitsGChanged(m_unitsG);
}

void CityGraphics::addUnitFromQml(QString type,int cost)
{
    Unit *tmp = new Unit();
    tmp->setCity(this->city());
    tmp->setName(QString::number(tmp->id())+"_"+city()->name());
    tmp->setType(type);
    tmp->setPower(cost);
    city()->addedUnitSig(type);
    city()->addUnit(tmp);

    unitsListstring << type;

}

void CityGraphics::sendUnitToNeighbour(int idU)
{
    Unit *tmp =  city()->units().value(idU);
    mapView()->selectedCityGraphics()->city()->addUnit(tmp);
    city()->removeUnit(idU);

}

void CityGraphics::receiveUnitFromNeighbour(int idU)
{
    Unit *tmp =  mapView()->selectedCityGraphics()->city()->units().value(idU);
    mapView()->selectedCityGraphics()->city()->removeUnit(idU);
    city()->addUnit(tmp);
    tmp->setCity(this->city());

}

void CityGraphics::deSelect()
{
    foreach (City *c,this->city()->neighbours()) {
        this->mapView()->citiesGraphics().value(c->id())->setMoveToIt(false);
        this->mapView()->citiesGraphics().value(c->id())->setToAttack(false);
    }
    this->mapView()->setSelectedCityGraphics(nullptr);
    this->mapView()->mapScene()->update();

}

void CityGraphics::onBattleEnded()
{
    mapView()->battleForm->hide();
    Player *p = mapView()->battleForm->bScene()->bmap()->attacker()->country()->player();
    foreach (LinkGraphics *l,mapView()->citiesGraphics().value(mapView()->battleForm->bScene()->bmap()->deffender()->id())->links()) {
        l->updateAfterBattle();
    }
    mapView()->battleForm->deleteLater();
    if(mapView()->selectedCityGraphics() != nullptr)  mapView()->selectedCityGraphics()->deSelect();
    mapView()->setEnabled(true);

    /// the AI attack system
    if(p->type() == PlayerType::AI){
        mapView()->mapAI()->launchBattleAI_Player();
    }


}

void CityGraphics::setPower(int power)
{
    m_power = power;
}

void CityGraphics::onAttackerWon()
{
    this->city()->setUsed(true);
    emit mapView()->attackerWon(this->city());
}

void CityGraphics::setLinks(QList<LinkGraphics*> links)
{
    if (m_links == links)
        return;

    m_links = links;
    emit linksChanged(m_links);
}

void CityGraphics::setMoveToIt(bool moveToIt)
{
    if (m_moveToIt == moveToIt)
        return;

    m_moveToIt = moveToIt;
    emit moveToItChanged(m_moveToIt);
}

void CityGraphics::setToAttack(bool toAttack)
{
    if (m_toAttack == toAttack)
        return;

    m_toAttack = toAttack;
    emit toAttackChanged(m_toAttack);
}
