#ifndef MAPVIEW_H
#define MAPVIEW_Hr

#include <QObject>
#include <QTimer>
#include <qgraphicsitem.h>
#include "domain/map.h"
#include "linkgraphics.h"
#include <QGraphicsView>
#include<QGraphicsPixmapItem>
#include <domain/map.h>
#include <QtSvg/QGraphicsSvgItem>
#include<QQuickView>
#include <QtQuickWidgets/QQuickWidget>
class CityGraphics;
class LinkGraphics;
class MapView :public QGraphicsView
{
    Q_OBJECT
    Q_PROPERTY(QGraphicsScene* mapScene READ mapScene WRITE setMapScene NOTIFY mapSceneChanged)
    Q_PROPERTY(Map* map READ map WRITE setMap NOTIFY mapChanged)
    Q_PROPERTY(QMap<int,CityGraphics*> citiesGraphics READ citiesGraphics WRITE setCitiesGraphics NOTIFY citiesGraphicsChanged)
    Q_PROPERTY(QGraphicsSvgItem* mapGraphics READ mapGraphics  NOTIFY mapGraphicsChanged)
    Q_PROPERTY(QGraphicsView* view READ view WRITE setView NOTIFY viewChanged)
    Q_PROPERTY(QList<LinkGraphics*> links READ links WRITE setLinks NOTIFY linksChanged)
    Q_PROPERTY(CityGraphics* selectedCityGraphics READ selectedCityGraphics WRITE setSelectedCityGraphics NOTIFY selectedCityGraphicsChanged)
    Map* m_map;

    QMap<int,CityGraphics*> m_citiesGraphics;

    QGraphicsSvgItem* m_mapGraphics;

    QGraphicsView* m_view;

    QGraphicsScene* m_mapScene;

    QGraphicsRectItem *testRect;

    QGraphicsItemGroup *glob ;

    QTimer moveViewTimer;

    int movementDirection;

    int zoomLevel;

    QList<LinkGraphics*> m_links;

    CityGraphics* m_selectedCityGraphics;

public:
    QQuickWidget *CityUI;
    QQuickWidget *addUnitUI;
    QQuickWidget *moveUnitUI;
    QQuickWidget *attackUI;
    QWidget *par1;


    MapView(QObject *parent);

    Map* map() const;

    QMap<int,CityGraphics*> citiesGraphics() const;

    QGraphicsSvgItem* mapGraphics() const;

    void loadFromJson();

    QGraphicsView* view() const;

    QGraphicsScene* mapScene() const;

//    void mousePressEvent(QMouseEvent *event);
    void checkMouseInBoerder(QPoint mousePos);


    QList<LinkGraphics*> links() const;

    CityGraphics* selectedCityGraphics() const;

public slots:

    void setMap(Map* map);

    void setCitiesGraphics(QMap<int,CityGraphics*> citiesGraphics);

    void setView(QGraphicsView* view);

    void setMapScene(QGraphicsScene* mapScene);
    virtual void paintEvent(QPaintEvent *event);
    virtual void keyPressEvent(QKeyEvent *event);
    virtual void closeEvent(QCloseEvent *event);

    void moveView();

    void zoomIn();

    void zoomOut();

    Q_INVOKABLE QString unitsText();

    void setLinks(QList<LinkGraphics*> links);

    void setSelectedCityGraphics(CityGraphics* selectedCityGraphics);

signals:

    void zoomChange(double z);
    void mapChanged(Map* map);
    void citiesGraphicsChanged(QMap<int,CityGraphics*> citiesGraphics);
    void mapGraphicsChanged(QGraphicsSvgItem* mapGraphics);
    void viewChanged(QGraphicsView* view);
    void mapSceneChanged(QGraphicsScene* mapScene);

    void linksChanged(QList<LinkGraphics*> links);
    void selectedCityGraphicsChanged(CityGraphics* selectedCityGraphics);
};

#endif // MAPVIEW_H
