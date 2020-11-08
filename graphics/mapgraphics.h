#ifndef MAPGRAPHICS_H
#define MAPGRAPHICS_H

#include <QDomDocument>
#include <QFile>
#include <QGraphicsSvgItem>
#include <QJsonDocument>
#include <QObject>
#include <QSvgRenderer>


class MapView;

class MapGraphics : public QObject,public QGraphicsSvgItem
{
    Q_OBJECT

public:
    explicit MapGraphics(MapView *mV, QObject *parent = nullptr);

    void reavaluteCountrties();

    MapView *mapView;
    QJsonDocument originalCountriesJson;
    QFile *currentContries;
    QDomDocument *mapDocument;


    QSvgRenderer *rend;
    QSvgRenderer *rend2;



signals:

public slots:
};

#endif // MAPGRAPHICS_H
