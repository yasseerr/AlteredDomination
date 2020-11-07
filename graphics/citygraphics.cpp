#include "citygraphics.h"
#include "mapview.h"

#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QPropertyAnimation>
#include <QQmlContext>
#include <QQuickItem>

#include <domain/city.h>
#include <domain/country.h>
#include <domain/unit.h>


CityGraphics::CityGraphics(City *city_p,QImage *cityImg_p):cityImg(cityImg_p),m_city(city_p)
{
    setFlags(QGraphicsItem::ItemSendsGeometryChanges);
    setAcceptHoverEvents(true);


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
//    qDebug() << " entered ";
//    QPropertyAnimation *scaleAnim = new QPropertyAnimation(this,"scale",this);
//    scaleAnim->setDuration(50);
//    scaleAnim->setStartValue(0.1);
//    scaleAnim->setEndValue(0.12);
//    scaleAnim->setEasingCurve(QEasingCurve::OutQuad);
//    scaleAnim->start();
    setScale(0.12);
}

void CityGraphics::hoverLeaveEvent(QGraphicsSceneHoverEvent *ev)
{
    this->setScale(0.1);
}

void CityGraphics::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "clicked";
    mapView()->CityUI->rootObject();
    mapView()->CityUI->rootContext()->setContextProperty("city",this->city());
    mapView()->addUnitUI->rootContext()->setContextProperty("cityGraphics",this);
    mapView()->CityUI->show();

    foreach (QString tmp, unitsListstring) {
        city()->addedUnitSig(tmp);
    }
}

QList<UnitGraphics *> CityGraphics::unitsG() const
{
    return m_unitsG;
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

void CityGraphics::addUnitFromQml(QString type)
{
    Unit *tmp = new Unit();
    tmp->setCity(this->city());
    tmp->setName(QString::number(tmp->id())+"_"+city()->name());
    tmp->setType(type);
    city()->addedUnitSig(type);
    city()->units().append(tmp);

    unitsListstring << type;

}
