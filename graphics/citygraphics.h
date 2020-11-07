#ifndef CITYGRAPHICS_H
#define CITYGRAPHICS_H

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

public:

    CityGraphics(City *city_p,QImage *cityImg_p);

    // QGraphicsItem interface
    virtual QRectF boundingRect() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    City* city() const;

    QImage *bgImage;

    MapView* mapView() const;

    void hoverEnterEvent(QGraphicsSceneHoverEvent *ev);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *ev);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

    QList<UnitGraphics*> unitsG() const;

public slots:
    void setCity(City* city);
    void zoomChanged(double z);

    void setMapView(MapView *mapView);

    void setUnitsG(QList<UnitGraphics*> unitsG);

    Q_INVOKABLE void addUnitFromQml(QString type);

signals:
    void cityChanged(City* city);

    void mapViewChanged(MapView *mapView);

    void unitsGChanged(QList<UnitGraphics*> unitsG);


private :
    QImage *cityImg;
    QStringList unitsListstring;
    City* m_city;
    MapView *m_mapView;
    QList<UnitGraphics*> m_unitsG;
};

#endif // CITYGRAPHICS_H
