#ifndef CITYGRAPHICS_H
#define CITYGRAPHICS_H

#include "linkgraphics.h"

#include <QObject>
#include <QGraphicsItem>
class City;
class MapView;
class UnitGraphics;
class CityGraphics :public QObject,public QGraphicsItem
{
    Q_OBJECT
    Q_PROPERTY(City* city READ city WRITE setCity NOTIFY cityChanged)
    Q_PROPERTY(qreal scale READ scale WRITE setScale)
    Q_PROPERTY(MapView* mapView READ mapView WRITE setMapView NOTIFY mapViewChanged)
    Q_PROPERTY(QList<UnitGraphics*> unitsG READ unitsG WRITE setUnitsG NOTIFY unitsGChanged)
    Q_PROPERTY(QList<LinkGraphics*> links READ links WRITE setLinks NOTIFY linksChanged)
    Q_PROPERTY(bool moveToIt READ moveToIt WRITE setMoveToIt NOTIFY moveToItChanged)
    Q_PROPERTY(bool toAttack READ toAttack WRITE setToAttack NOTIFY toAttackChanged)
    Q_PROPERTY(int power READ power WRITE setPower NOTIFY powerChanged)
public:


    QList<LinkGraphics*> m_links;

    CityGraphics(City *city_p,QImage *cityImg_p);

    // QGraphicsItem interface
    virtual QRectF boundingRect() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    City* city() const;

    QImage *bgImage;

    MapView* mapView() const;

    QList<UnitGraphics*> unitsG() const;

    QList<LinkGraphics*> links() ;

    bool moveToIt() const;

    bool toAttack() const;


    void hoverEnterEvent(QGraphicsSceneHoverEvent *ev);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *ev);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    Q_INVOKABLE void moveUnits();
    Q_INVOKABLE void attack();
    Q_INVOKABLE void cancelAttack();
    Q_INVOKABLE void startBattle();


    int power() const;

public slots:
    void setCity(City* city);
    void setMapView(MapView *mapView);
    void setUnitsG(QList<UnitGraphics*> unitsG); 
    void setLinks(QList<LinkGraphics*> links);
    void setMoveToIt(bool moveToIt);
    void setToAttack(bool toAttack);

    void zoomChanged(double z);
    Q_INVOKABLE void addUnitFromQml(QString type,int cost);
    Q_INVOKABLE void sendUnitToNeighbour(int idU);
    Q_INVOKABLE void receiveUnitFromNeighbour(int idU);
    Q_INVOKABLE void deSelect();
    Q_INVOKABLE void onBattleEnded();


    void setPower(int power);
    void onAttackerWon();

signals:
    void cityChanged(City* city);
    void mapViewChanged(MapView *mapView);
    void unitsGChanged(QList<UnitGraphics*> unitsG);
    void linksChanged(QList<LinkGraphics*> links);
    void moveToItChanged(bool moveToIt);
    void toAttackChanged(bool toAttack);

    void unitToQml(int idU,QString typeU);
    void unitToAttackQml(QString typeU);

    void powerChanged(int power);

private :
    QImage *cityImg;
    QStringList unitsListstring;
    City* m_city;
    MapView *m_mapView;
    QList<UnitGraphics*> m_unitsG;
    bool m_moveToIt;
    bool m_toAttack;
    int m_power;
};

#endif // CITYGRAPHICS_H
