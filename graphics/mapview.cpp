#include "citygraphics.h"
#include "mapview.h"

#include <QApplication>
#include <QBitmap>
#include <QCoreApplication>
#include <QDir>
#include <QGraphicsOpacityEffect>
#include <QGraphicsProxyWidget>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QLayout>
#include <QMouseEvent>
#include <QQmlContext>
#include <QRgb>
#include <QScrollBar>
#include <QSvgRenderer>
#include <qdatetime.h>
#include <qdebug.h>
#include <qgraphicssceneevent.h>
#include <domain/city.h>
#include <domain/unit.h>
#include <AI/mapai.h>


MapView::MapView(QObject *parent):QGraphicsView()
{


    ///initiating the view
    zoomLevel = 8;
    m_selectedCityGraphics = nullptr ;
//    verticalScrollBar()->setRange(1200,600);
//    horizontalScrollBar()->setRange(1200,600);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
//    horizontalScrollBar()->setVisible(false);

    m_mapScene = new QGraphicsScene();
    m_map = new Map(this);

    ///setting the view movement timer
    moveViewTimer.setInterval(120);
    connect(&moveViewTimer,&QTimer::timeout,this,&MapView::moveView);
    movementDirection = 1;


    /// ----------view COnfig---------------
    this->setTransformationAnchor(QGraphicsView::NoAnchor);
    this->setMouseTracking(true);


    /// setting the City UI
    CityUI  = new QQuickView();
    CityUI->setColor(Qt::transparent);
    CityUI->setFlags(Qt::ToolTip);
//    CityUI->setAttribute(Qt::WA_TranslucentBackground);
    CityUI->rootContext()->setContextProperty("viewUI",CityUI);
    CityUI->rootContext()->setContextProperty("mapUI",this);
    CityUI->rootContext()->setContextProperty("city",new City());

    /// setting the menuOpt UI
    menuOptUI  = new QQuickView();
    menuOptUI->setColor(Qt::transparent);
    menuOptUI->setFlags(Qt::ToolTip);
//    CityUI->setAttribute(Qt::WA_TranslucentBackground);
    menuOptUI->rootContext()->setContextProperty("menuOpt",menuOptUI);
    menuOptUI->rootContext()->setContextProperty("mapView",this);


    qmlRegisterType<City>("City",1,0,"City");
    qmlRegisterType<Country>();
    qmlRegisterType<Unit>();
    qmlRegisterType<Player>();

    CityUI->setSource(QUrl("qrc:/CityUI.qml"));
    menuOptUI->setSource(QUrl("qrc:/scripts/MapMenuOptions.qml"));



    /// setting the addUnit UI
    addUnitUI = new QQuickView();
    CityUI->rootContext()->setContextProperty("addUI",addUnitUI);
    addUnitUI->setColor(Qt::transparent);
    addUnitUI->setFlags(Qt::ToolTip);
//    addUnitUI->seta(Qt::WA_TranslucentBackground);
    addUnitUI->rootContext()->setContextProperty("cityViewUI",CityUI);
    addUnitUI->rootContext()->setContextProperty("mapUI",this);
    addUnitUI->setSource(QUrl("qrc:/scripts/AddUnitUI.qml"));
    addUnitUI->rootContext()->setContextProperty("addUI",addUnitUI);
//    addUnitUI->show();


    /// setting the moveUnit UI
    moveUnitUI = new QQuickView();
//    CityUI->rootContext()->setContextProperty("addUI",addUnitUI);
    moveUnitUI->setColor(Qt::transparent);
    moveUnitUI->setFlags(Qt::ToolTip);
//    moveUnitUI->setAttribute(Qt::WA_TranslucentBackground);
//    moveUnitUI->rootContext()->setContextProperty("cityViewUI",CityUI);
    moveUnitUI->rootContext()->setContextProperty("mapUI",this);
    moveUnitUI->setSource(QUrl("qrc:/scripts/MoveUnitsUI.qml"));
    moveUnitUI->rootContext()->setContextProperty("moveUI",moveUnitUI);
//    moveUnitUI->show();



    /// setting the attack UI
    attackUI = new QQuickView();
//    CityUI->rootContext()->setContextProperty("addUI",addUnitUI);
    attackUI->setColor(Qt::transparent);
    attackUI->setFlags(Qt::ToolTip);
//    attackUI->setAttribute(Qt::WA_TranslucentBackground);
//    moveUnitUI->rootContext()->setContextProperty("cityViewUI",CityUI);
    attackUI->rootContext()->setContextProperty("mapUI",this);
    CityUI->rootContext()->setContextProperty("attackUI",attackUI);
    attackUI->rootContext()->setContextProperty("attackUI",attackUI);
    attackUI->setSource(QUrl("qrc:/scripts/AttackUI.qml"));

     ///creating the mapgraphics and add it to the view
    glob  = new QGraphicsItemGroup();
    m_mapGraphics = new  QGraphicsSvgItem(":/data/map_mask.svg");
    m_mapGraphics->setOpacity(0.6);
    this->m_mapScene->addItem(m_mapGraphics);
    //glob->setAcceptHoverEvents(true);
    m_mapGraphics->setScale(zoomLevel);

    testRect = new QGraphicsTextItem("Altered Domination by --AFKAAR Games--");
    testRect->setPos(30,30);
//    testRect->ensureVisible();
    testRect->setFont(QFont("Arial",60));
    m_mapScene->addItem(testRect);

    /// teting the opacity mask



//    QImage *pItemp = new QImage(":/data/mapBG8.jpg");
//    QGraphicsRectItem *rec = new QGraphicsRectItem(0,0,3000,1000);
//    rec->setBrush(*pItemp);
//    QGraphicsOpacityEffect *eff = new QGraphicsOpacityEffect();
//    eff->setOpacity(0.5);
//    eff->setEnabled(true);
//    QBitmap *mask = new QBitmap(":/data/map_mask_2.png");
//    eff->setOpacityMask(*mask);

//    rec->setGraphicsEffect(eff);
//    m_mapScene->addItem(rec);
//    pmi->setScale(4);


    QPixmap *pItem = new QPixmap(":/data/sea3.jpg");
    m_mapScene->setBackgroundBrush(*pItem);
//    pItem->moveBy(-725,30);
    this->setScene(m_mapScene);

    /// adding the cities
    CityUI->hide();
    addUnitUI->hide();


    /// the map AI
    m_mapAI = new MapAI(this);
    m_turnNumber = 0;
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
    QFile *jsonFile;
    jsonFile = m_mode==MapView::GDP? new QFile(":/data/map.json"):new QFile(":/data/map_2.json");
    jsonFile->open(QIODevice::ReadOnly|QIODevice::Text);
    QTextStream in(jsonFile);
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

        /// creation of the Player object
        Player *p = new Player(this);
        p->setid(country->id());
        p->setCountry(country);
        country->setPlayer(p);
        if(country->name()== this->activePStr()){
            p->setName("Player 1");
            p->setType(PlayerType::HUMAIN);
            m_activePlayer = p;
            m_actuelPlayer = p;
        }else {
            p->setName("AI_"+country->name());
            p->setType(PlayerType::AI);
        }
        m_players.append(p);

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
            country->addCity(city);

            /// loading the neigbours
            QJsonValue neigboursV = cityJ.value("neighbours");
            QJsonArray neighbours = neigboursV.toArray();
            QList<int> nTmp;

            foreach (QJsonValue neighbourV, neighbours) {
                nTmp.append(neighbourV.toInt());
            }
            city->setNeigboursId(nTmp);



            /// cityGraphics
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
            cityG->setScale(0.09);
            cityG->setMapView(this);
//            cityG->setParentItem(glob);
            m_mapScene->addItem(cityG);
            m_citiesGraphics.insert(city->id(),cityG);
            connect(this,&MapView::zoomChange,cityG,&CityGraphics::zoomChanged);

//            QGraphicsRectItem *cityR = new QGraphicsRectItem(QRectF(city.x(),city.y(),60,60),glob);
//            cityR->setBrush(Qt::red);

        }
        country->setFunds(country->income());
    }
    this->centerOn(m_activePlayer->country()->cities().at(0)->x(),
                   m_activePlayer->country()->cities().at(0)->y());


    /// neighbours graphics
    foreach (CityGraphics *cG, m_citiesGraphics) {
        foreach (int neighbourID, cG->city()->neigboursId()) {
//            if(!citiesGraphics().contains(neighbourID)) return;
            bool exi = false;
            foreach (LinkGraphics *lgt, citiesGraphics().value(neighbourID)->links()) {
                if(lgt->link()->des() == cG->city()) {
                    exi=true;
                }
            }
            if(exi) continue;
            LinkN *l = new LinkN(this);
            l->setDep(cG->city());
            l->setDes(this->citiesGraphics().value(neighbourID)->city());

            cG->city()->addNeighbour(this->citiesGraphics().value(neighbourID)->city());
            this->citiesGraphics().value(neighbourID)->city()->addNeighbour(cG->city());

            LinkGraphics *lg = new LinkGraphics(l,this);
            m_links.append(lg);
            cG->m_links.append(lg);
            citiesGraphics().value(neighbourID)->m_links.append(lg);
            m_mapScene->addItem(lg);
            connect(this,&MapView::zoomChange,lg,&LinkGraphics::zoomChanged);

        }
    }

}

void MapView::loadFromJsonString(QString gamesave)
{
    /// loading materials for cities
    QImage *M10 = new QImage(":/data/cities/10M.png");
    QImage *M1 = new QImage(":/data/cities/1m.png");
    QImage *K500 = new QImage(":/data/cities/500k.png");
    QImage *K100 = new QImage(":/data/cities/100k.png");
    QImage *bgImage = new QImage(":/data/cities/bg.png");

    /// loading units types
    QJsonDocument doc = QJsonDocument::fromJson(gamesave.toLocal8Bit());

    /// loading
//    if(doc.isEmpty() || !doc.isArray()){
//        qDebug() << "empty or not array";
//        return;
//    }
    QJsonArray countries = doc.object().value("countries").toArray();
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

        /// creation of the Player object
        Player *p = new Player(this);
        p->setid(country->id());
        p->setCountry(country);
        country->setPlayer(p);
        if(country->name()== this->activePStr()){
            p->setName("Player 1");
            p->setType(PlayerType::HUMAIN);
            m_activePlayer = p;
            m_actuelPlayer = p;
        }else {
            p->setName("AI_"+country->name());
            p->setType(PlayerType::AI);
        }
        m_players.append(p);

        foreach (QJsonValue cityV, cities) {
            QJsonObject cityJ = cityV.toObject();

            /// the creation of the city object
            City *city = new City();
            city->setId(cityJ.value("id").toInt());
            city->setName(cityJ.value("name").toString());
            city->setX(cityJ.value("x").toInt()/**2.8346*zoomLevel*/);
            city->setY(cityJ.value("y").toInt()/**2.8346*zoomLevel*/);
            city->setType(static_cast<CityType>(cityJ.value("cityType").toInt()));
            city->setIncome(cityJ.value("income").toInt());
            city->setMap(this->map());

            this->map()->cities().insert(city->id(),city);
            city->setCountry(country);
            country->addCity(city);

            /// loading the neigbours
            QJsonValue neigboursV = cityJ.value("neighbours");
            QJsonArray neighbours = neigboursV.toArray();
            QList<int> nTmp;

            foreach (QJsonValue neighbourV, neighbours) {
                nTmp.append(neighbourV.toInt());
            }
            city->setNeigboursId(nTmp);

            /// loading the units

            QJsonValue unitsVt = cityJ.value("units");
            QJsonArray unitst = unitsVt.toArray();
            foreach (QJsonValue unitVt, unitst) {
                QJsonObject unitO = unitVt.toObject();
                Unit *ut = new Unit();
                ut->setType(unitO.value("name").toString());
                ut->setPower(unitO.value("power").toInt());
                ut->setName(unitO.value("name").toString());
                city->addUnit(ut);

            }

            /// cityGraphics
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
            cityG->setScale(0.09);
            cityG->setMapView(this);
//            cityG->setParentItem(glob);
            m_mapScene->addItem(cityG);
            m_citiesGraphics.insert(city->id(),cityG);
            connect(this,&MapView::zoomChange,cityG,&CityGraphics::zoomChanged);

//            QGraphicsRectItem *cityR = new QGraphicsRectItem(QRectF(city.x(),city.y(),60,60),glob);
//            cityR->setBrush(Qt::red);

        }
        country->setFunds(countryJ.value("funds").toInt());
    }
    if(m_actuelPlayer->country()->cities().size()>0){
        this->centerOn(m_activePlayer->country()->cities().at(0)->x(),
                       m_activePlayer->country()->cities().at(0)->y());
    }


    /// neighbours graphics
    foreach (CityGraphics *cG, m_citiesGraphics) {
        foreach (int neighbourID, cG->city()->neigboursId()) {
//            if(!citiesGraphics().contains(neighbourID)) return;
            bool exi = false;
            foreach (LinkGraphics *lgt, citiesGraphics().value(neighbourID)->links()) {
                if(lgt->link()->des() == cG->city()) {
                    exi=true;
                }
            }
            if(exi) continue;
            LinkN *l = new LinkN(this);
            l->setDep(cG->city());
            l->setDes(this->citiesGraphics().value(neighbourID)->city());

            cG->city()->addNeighbour(this->citiesGraphics().value(neighbourID)->city());
            this->citiesGraphics().value(neighbourID)->city()->addNeighbour(cG->city());

            LinkGraphics *lg = new LinkGraphics(l,this);
            m_links.append(lg);
            cG->m_links.append(lg);
            citiesGraphics().value(neighbourID)->m_links.append(lg);
            m_mapScene->addItem(lg);
            connect(this,&MapView::zoomChange,lg,&LinkGraphics::zoomChanged);

        }
    }



}

void MapView::saveGame()
{
    QFile f (QDir::currentPath()+"/gamesaves.json");
    f.open(QFile::ReadWrite|QFile::Text);
//    qDebug()<< f.errorString();
    QTextStream ts(&f);
//    ts << "salem";
    /// the big object --the save----

    QVariantMap saveObj;
    QVariantList countriesList;
    foreach (Player *p, this->players()) {
        countriesList << p->country()->toVariant();
    }
    QDate d  = QDate::currentDate();

    saveObj.insert("country",this->activePlayer()->country()->name());
    saveObj.insert("turn",this->turnNumber());
    saveObj.insert("date",d.toString());
    saveObj.insert("flag",activePlayer()->country()->intID());
    saveObj.insert("countries",countriesList);

    QJsonDocument doc = QJsonDocument::fromJson(ts.readAll().toLocal8Bit());
    QJsonArray ar = doc.array();
    ar.append(QJsonValue::fromVariant(saveObj));
    doc.setArray(ar);
    f.resize(0);
    ts << doc.toJson();
    f.close();
}

void MapView::quitGame()
{
    QCoreApplication::quit();
}

void MapView::autoSave()
{
    QFile f (QDir::currentPath()+"/gamesaves.json");
    f.open(QFile::ReadWrite|QFile::Text);
//    qDebug()<< f.errorString();
    QTextStream ts(&f);
//    ts << "salem";
    /// the big object --the save----

    QVariantMap saveObj;
    QVariantList countriesList;
    foreach (Player *p, this->players()) {
        countriesList << p->country()->toVariant();
    }
    QDate d  = QDate::currentDate();

    saveObj.insert("country",this->activePlayer()->country()->name());
    saveObj.insert("turn",this->turnNumber());
    saveObj.insert("date",d.toString());
    saveObj.insert("flag",activePlayer()->country()->intID());
    saveObj.insert("countries",countriesList);

    QJsonDocument doc = QJsonDocument::fromJson(ts.readAll().toLocal8Bit());
    QJsonArray ar = doc.array();
    ar.removeAt(0);
    ar.insert(0,QJsonValue::fromVariant(saveObj));
    doc.setArray(ar);
    f.resize(0);
    ts << doc.toJson();
    f.close();
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

QList<LinkGraphics *> MapView::links() const
{
    return m_links;
}

CityGraphics *MapView::selectedCityGraphics() const
{
    return m_selectedCityGraphics;
}

Player *MapView::actuelPlayer() const
{
    return m_actuelPlayer;
}

Player *MapView::activePlayer() const
{
    return m_activePlayer;
}

QList<Player *> MapView::players() const
{
    return m_players;
}

QString MapView::activePStr() const
{
    return m_activePStr;
}

MapAI *MapView::mapAI() const
{
    return m_mapAI;
}

int MapView::turnNumber() const
{
    return m_turnNumber;
}

MapView::GameMode MapView::mode() const
{
    return m_mode;
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

void MapView::setLinks(QList<LinkGraphics *> links)
{
    if (m_links == links)
        return;

    m_links = links;
    emit linksChanged(m_links);
}

void MapView::setSelectedCityGraphics(CityGraphics *selectedCityGraphics)
{
    if (m_selectedCityGraphics == selectedCityGraphics)
        return;

    m_selectedCityGraphics = selectedCityGraphics;
    emit selectedCityGraphicsChanged(m_selectedCityGraphics);
}

void MapView::setActuelPlayer(Player *actuelPlayer)
{
    if (m_actuelPlayer == actuelPlayer)
        return;

    m_actuelPlayer = actuelPlayer;
    emit actuelPlayerChanged(m_actuelPlayer);
}

void MapView::setActivePlayer(Player *activePlayer)
{
    if (m_activePlayer == activePlayer)
        return;

    m_activePlayer = activePlayer;
    emit activePlayerChanged(m_activePlayer);
}

void MapView::setPlayers(QList<Player *> players)
{
    if (m_players == players)
        return;

    m_players = players;
    emit playersChanged(m_players);
}

void MapView::setActivePStr(QString activePStr)
{
    if (m_activePStr == activePStr)
        return;

    m_activePStr = activePStr;
    emit activePStrChanged(m_activePStr);
}

void MapView::setMapAI(MapAI *mapAI)
{
    if (m_mapAI == mapAI)
        return;

    m_mapAI = mapAI;
    emit mapAIChanged(m_mapAI);
}

void MapView::setTurnNumber(int turnNumber)
{
    if (m_turnNumber == turnNumber)
        return;

    m_turnNumber = turnNumber;
    emit turnNumberChanged(m_turnNumber);
}

void MapView::setMode(MapView::GameMode mode)
{
    if (m_mode == mode)
        return;

    m_mode = mode;
    emit modeChanged(m_mode);
}

