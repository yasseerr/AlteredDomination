#include "citygraphics.h"
#include "mapview.h"

#include <QApplication>
#include <QCoreApplication>
#include <QGraphicsProxyWidget>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMouseEvent>
#include <QQmlContext>
#include <QRgb>
#include <QScrollBar>
#include <qdebug.h>
#include <qgraphicssceneevent.h>
#include <domain/city.h>
#include <domain/unit.h>


MapView::MapView(QObject *parent):QGraphicsView()
{


    ///initiating the view
    zoomLevel = 8;
    verticalScrollBar()->setRange(1200,600);
    horizontalScrollBar()->setRange(1200,600);

    m_mapScene = new QGraphicsScene();
    m_map = new Map(this);

    ///setting the view movement timer
    moveViewTimer.setInterval(120);
    connect(&moveViewTimer,&QTimer::timeout,this,&MapView::moveView);
    movementDirection = 1;


    /// ----------view COnfig---------------
    this->resize(1200,600);
    this->setTransformationAnchor(QGraphicsView::NoAnchor);
    this->setMouseTracking(true);


    /// setting the City UI
    CityUI  = new QQuickWidget(this);
    CityUI->setParent(this);
    CityUI->setClearColor(Qt::transparent);
    CityUI->setWindowFlags(Qt::ToolTip);
    CityUI->setAttribute(Qt::WA_TranslucentBackground);
    CityUI->rootContext()->setContextProperty("viewUI",CityUI);
    CityUI->rootContext()->setContextProperty("mapUI",this);
    CityUI->rootContext()->setContextProperty("city",new City());

    qmlRegisterType<City>("City",1,0,"City");
    qmlRegisterType<Country>();
    qmlRegisterType<Unit>();

    CityUI->setSource(QUrl("qrc:/CityUI.qml"));



    /// setting the addUnit UI
    addUnitUI = new QQuickWidget(CityUI);
    CityUI->rootContext()->setContextProperty("addUI",addUnitUI);
    addUnitUI->setClearColor(Qt::transparent);
    addUnitUI->setWindowFlags(Qt::ToolTip);
    addUnitUI->setAttribute(Qt::WA_TranslucentBackground);
    addUnitUI->rootContext()->setContextProperty("cityViewUI",CityUI);
    addUnitUI->rootContext()->setContextProperty("mapUI",this);
    addUnitUI->setSource(QUrl("qrc:/scripts/AddUnitUI.qml"));
    addUnitUI->rootContext()->setContextProperty("addUI",addUnitUI);
    addUnitUI->show();



     ///creating the mapgraphics and add it to the view
    glob  = new QGraphicsItemGroup();
    m_mapGraphics = new  QGraphicsSvgItem(":/data/map.svg");
    this->m_mapScene->addItem(m_mapGraphics);
    //glob->setAcceptHoverEvents(true);
    m_mapGraphics->setScale(zoomLevel);
    testRect = new QGraphicsRectItem(0,0,100,100);
    testRect->setBrush(Qt::red);
    m_mapScene->addItem(testRect);
    this->setScene(m_mapScene);

    /// adding the cities
    loadFromJson();
//    m_mapScene->addWidget(CityUI,Qt::ToolTip);
//    m_mapScene->addWidget(addUnitUI),Qt::ToolTip;
    CityUI->hide();
    addUnitUI->hide();
    this->show();

}


Map *MapView::map() const
{
    return m_map;
}

QMap<int, CityGraphics *> MapView::citiesGraphics() const
{
    return m_citiesGraphics;
}

QGraphicsSvgItem *MapView::mapGraphics() const
{
    return m_mapGraphics;
}

void MapView::loadFromJson()
{

    /// loading materials for cities
    QImage *M10 = new QImage(":/data/cities/10M.png");
    QImage *M1 = new QImage(":/data/cities/1m.png");
    QImage *K500 = new QImage(":/data/cities/500k.png");
    QImage *K100 = new QImage(":/data/cities/100k.png");
    QImage *bgImage = new QImage(":/data/cities/bg.png");

    /// loading units types


    /// configuring the file
    QFile jsonFile(":/data/map.json");
    jsonFile.open(QIODevice::ReadOnly|QIODevice::Text);
    QTextStream in(&jsonFile);
    QJsonDocument doc = QJsonDocument::fromJson(in.readAll().toLocal8Bit());

    /// loading
    if(doc.isEmpty() || !doc.isArray()){
        qDebug() << "empty or not array";
        return;
    }
    QJsonArray countries = doc.array();
    foreach (QJsonValue valueJ, countries) {
        QJsonObject countryJ = valueJ.toObject();
        QJsonValue citiesV = countryJ.value("cities");
        QJsonArray cities = citiesV.toArray();

        /// creation of the country object
        Country *country = new Country();
        country->setId(countryJ.value("id").toInt());
        country->setName(countryJ.value("name").toString());
        country->setIntID(countryJ.value("flag").toString());
        country->setFlag(QImage(":/data/flags/"+countryJ.value("flag").toString()+".png"));
        country->setColor(QColor(countryJ.value("color").toString()));
        this->map()->countries().insert(country->id(),country);

        foreach (QJsonValue cityV, cities) {
            QJsonObject cityJ = cityV.toObject();

            /// the creation of the city object
            City *city = new City();
            city->setId(cityJ.value("id").toInt());
            city->setName(cityJ.value("name").toString());
            city->setX(cityJ.value("x").toInt()*2.8346*zoomLevel);
            city->setY(cityJ.value("y").toInt()*2.8346*zoomLevel);
            city->setType(static_cast<CityType>(cityJ.value("cityType").toInt()));
            city->setIncome(cityJ.value("income").toInt());
            city->setMap(this->map());
            this->map()->cities().insert(city->id(),city);

            city->setCountry(country);
            country->cities().append(city);


            /// cityGraphics
//            QString fg = ":/flags"+country.value("flag").toString();

//            QGraphicsRectItem *cityR = new QGraphicsRectItem(QRectF(city.x(),city.y(),60,60),glob);
//            cityR->setBrush(QColor(country.value("color").toString()));
//            cityR->setOpacity(0.3);
//            QGraphicsPixmapItem *cityPng = new QGraphicsPixmapItem(":/data/flags/"+country.value("flag").toString()+".png",glob);
//            QGraphicsTextItem *cityText = new QGraphicsTextItem(city.name()+"(-"+QString::number(city.id())+"-)",glob);
//            cityText->setPos(city.x(),city.y()+55);
//            cityPng->setPos(city.x(),city.y());
//            cityPng->setScale(0.1);

            QImage *cityImg;
            if((int)city->type()<4){
                cityImg = K100;
            }else if ((int)city->type() <7) {
                cityImg = K500;
            }else if ((int)city->type() <10) {
                cityImg = M1;
            }else {
                cityImg = M10;
            }
            CityGraphics *cityG = new CityGraphics(city,cityImg);
            cityG->bgImage = bgImage;
//            this->citiesGraphics().insert(city->id(),cityG);
            cityG->setPos(city->x(),city->y());
            cityG->setScale(0.1);
            cityG->setMapView(this);
//            cityG->setParentItem(glob);
            m_mapScene->addItem(cityG);
            m_citiesGraphics.insert(city->id(),cityG);
            connect(this,&MapView::zoomChange,cityG,&CityGraphics::zoomChanged);

//            QGraphicsRectItem *cityR = new QGraphicsRectItem(QRectF(city.x(),city.y(),60,60),glob);
//            cityR->setBrush(Qt::red);

        }
//        country->setCapital(country->cities().at(0));
    }
    this->centerOn(citiesGraphics().value(9)->x(),citiesGraphics().value(9)->y());


}

QGraphicsView *MapView::view() const
{
    return m_view;
}

QGraphicsScene *MapView::mapScene() const
{
    return m_mapScene;
}



//void MapView::mousePressEvent(QMouseEvent *event)
//{

////    QGraphicsSceneMouseEvent *ev =  new QGraphicsSceneMouseEvent();
////    if(event->button() == Qt::LeftButton) zoomIn();
////    else if(event->button()== Qt::RightButton) zoomOut();

//}

void MapView::checkMouseInBoerder(QPoint mousePos)
{
    QRect rectTmpp = this->rect().adjusted(100,100,-100,-100);
    if(rectTmpp.contains(mousePos)){
        if(moveViewTimer.isActive()) moveViewTimer.stop();
        return;
    }
    //qDebug() << "boom 1";

    /// ------- finding the direction-------------------
    int minD = qMin(this->rect().x()+this->rect().width()-mousePos.x(),
                    qMin(this->rect().x()+mousePos.x(),
                    qMin(this->rect().y()+mousePos.y(),
                    this->rect().y()+this->rect().height()-mousePos.y()))
                    );
    //qDebug() << minD;
    if(this->rect().x()+this->rect().width()-mousePos.x() == minD) movementDirection = 3;
    else if(this->rect().x()+mousePos.x() == minD) movementDirection = 1;
    else if(this->rect().y()+mousePos.y() == minD) movementDirection = 2;
    else if(this->rect().y()+this->rect().height()-mousePos.y() == minD) movementDirection = 0;


//    switch (minD) {
//        //right
//    case (this->rect().x()+this->rect().width()-mousePos.x()):
//        movementDirection = 1;
//        break;
//        //left
//    case this->rect().x()+mousePos.x():
//        movementDirection = 3;
//        break;
//        //up
//    case this->rect().y()+mousePos.y():
//        movementDirection = 0 ;
//        break;
//        //down
//    case this->rect().y()+this->rect().height()-mousePos.y():
//        movementDirection = 2;
//        break;
//    }
    if(!moveViewTimer.isActive()) moveViewTimer.start();

}



void MapView::setMap(Map *map)
{
    if (m_map == map)
        return;

    m_map = map;
    emit mapChanged(m_map);
}

void MapView::setCitiesGraphics(QMap<int, CityGraphics *> citiesGraphics)
{
    if (m_citiesGraphics == citiesGraphics)
        return;

    m_citiesGraphics = citiesGraphics;
    emit citiesGraphicsChanged(m_citiesGraphics);
}

void MapView::setView(QGraphicsView *view)
{
    if (m_view == view)
        return;

    m_view = view;
    emit viewChanged(m_view);
}

void MapView::setMapScene(QGraphicsScene *mapScene)
{
    if (m_mapScene == mapScene)
        return;

    m_mapScene = mapScene;
    emit mapSceneChanged(m_mapScene);
}

void MapView::paintEvent(QPaintEvent *event)
{
    QGraphicsView::paintEvent(event);
}

void MapView::keyPressEvent(QKeyEvent *event)
{
    QGraphicsView::keyPressEvent(event);
    if(event->key() == Qt::Key_Plus) zoomIn();
    if(event->key() == Qt::Key_Minus) zoomOut();
}

void MapView::closeEvent(QCloseEvent *event)
{
    QGraphicsView::closeEvent(event);
    CityUI->close();
}

void MapView::moveView()
{
    switch (movementDirection) {
    case 0:
        this->translate(0,-100);
        break;
    case 1:
        this->translate(100,0);
        break;
    case 2:
        this->translate(0,100);
        break;
    case 3:
        this->translate(-100,0);
        break;

    }

}

void MapView::zoomIn()
{

    if(zoomLevel>=16) return;
    zoomLevel += 1;
    m_mapGraphics->setScale(zoomLevel);
    double z = (double)zoomLevel/(double)(zoomLevel-1);
    emit zoomChange(z);
    this->update();
    QPointF newP = this->mapToScene(this->rect().center());
    QPoint newPP(newP.x()*z,newP.y()*z);
    this->centerOn(newPP.x(),newPP.y());
    this->setSceneRect(QRectF(0,0,m_mapGraphics->boundingRect().width()*zoomLevel,
                              m_mapGraphics->boundingRect().height()*zoomLevel));
}

void MapView::zoomOut()
{
    if(zoomLevel<=4) return;
    zoomLevel -= 1;
    m_mapGraphics->setScale(zoomLevel);
    double z = (double)zoomLevel/(double)(zoomLevel+1);
    emit zoomChange(z);
    this->update();
    QPointF newP = this->mapToScene(this->rect().center());
    QPoint newPP(newP.x()*z,newP.y()*z);
    this->centerOn(newPP.x(),newPP.y());
    this->setSceneRect(QRectF(0,0,m_mapGraphics->boundingRect().width()*zoomLevel,
                              m_mapGraphics->boundingRect().height()*zoomLevel));

    //    this->m_mapScene->setSceneRect(m_mapGraphics);
}

QString MapView::unitsText()
{
    QFile file(":/scripts/units.json");
    file.open(QFile::ReadOnly|QFile::Truncate);
    QTextStream st(&file);
    return st.readAll();
}

