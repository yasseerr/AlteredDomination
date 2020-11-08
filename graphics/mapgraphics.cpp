#include "mapgraphics.h"
#include "mapview.h"

#include <QCoreApplication>
#include <QJsonArray>
#include <QJsonObject>
#include <QTextStream>

#include <domain/player.h>

MapGraphics::MapGraphics(MapView *mV, QObject *parent) : QObject(parent)
{
    QFile originCountriesFile(":/data/map.json");
    originCountriesFile.open(QIODevice::ReadOnly|QIODevice::Text);
    QTextStream originalCountriesStream(&originCountriesFile);
    originalCountriesJson = QJsonDocument::fromJson(originalCountriesStream.readAll().toLocal8Bit());

    mapView = mV;


    QFile originalMapFile(":/data/out.svg");
    originalMapFile.open(QIODevice::ReadOnly|QIODevice::Text);
    QTextStream originalMapStream(&originalMapFile);
    mapDocument = new QDomDocument("mapDocument");
    mapDocument->setContent(originalCountriesStream.readAll().toLocal8Bit());

    rend = new QSvgRenderer(QString(":/data/out.svg"),this);
    this->setSharedRenderer(rend);
    this->setOpacity(0.5);

}



void MapGraphics::reavaluteCountrties()
{

///*********************** svg load **************************************
    QFile f(":/data/out.svg");
    f.open(QIODevice::ReadOnly);
    qDebug()<<f.size();
    mapDocument->setContent(&f);
    qDebug()<<"-------------------------";
    QDomElement g = mapDocument->documentElement();

    //    QDomElement aa2 = g.elementsByTagName("svg").at(0).toElement();
    qDebug()<<"--" << g.attribute("id") ;
    QDomElement aa3 = g.elementsByTagName("g").at(0).toElement();
    qDebug()<<"--" << aa3.attribute("id") ;
//    QDomElement aa4 = aa3.elementsByTagName("g").at(0).toElement();
//    qDebug()<<"--" << aa4.attribute("id") ;
    QDomNodeList li = aa3.elementsByTagName("path");
    qDebug() << li.size() << " size ";




///********************* countries ********************************

    QJsonArray countriesArrayJ = originalCountriesJson.array();

    QMap<QString,Country*> mapCOuntryMaping;

    foreach (QJsonValue countryVal, countriesArrayJ) {
        /// the original country loop

        QJsonObject countryObj = countryVal.toObject();
        QJsonArray citiesJ = countryObj.value("cities").toArray();
        QMap<Country*,int> colonizersSpec;

        foreach (Player *p, mapView->players()) {
            /// classifing the countries loop
            foreach (City *c, p->country()->cities()) {
                /// player cities
                foreach (QJsonValue cityJ, citiesJ) {
                    /// see if the cities in the original country are in this player ownership
                    QJsonObject cityObj = cityJ.toObject();
                    if(c->id() == cityObj.value("id").toInt()){
                        colonizersSpec.insert(p->country(),
                                              colonizersSpec.contains(p->country())?
                                                  colonizersSpec.value(p->country())+cityObj.value("income").toInt():
                                                  cityObj.value("income").toInt());
                    }
                }
            }
        }

        Country *dominatingCountry = colonizersSpec.firstKey();
        foreach (Country *c, colonizersSpec.keys()) {
            if(colonizersSpec.value(c) > colonizersSpec.value(dominatingCountry))
                dominatingCountry = c;
        }
        mapCOuntryMaping.insert(countryObj.value("flag").toString(),dominatingCountry);

    }

///*********************************** joining ****************************

    for (int i = 0; i < li.size(); ++i) {
        QDomElement lelem = li.at(i).toElement();

        if(mapCOuntryMaping.contains(lelem.attribute("id"))){
            lelem.setAttribute("style","");
            lelem.setAttribute("fill",mapCOuntryMaping.value(lelem.attribute("id"))->color().name());
            lelem.setAttribute("stroke",mapCOuntryMaping.value(lelem.attribute("id"))->color().lighter(95).name());
        }
//        foreach (QJsonValue cValue, countArray) {
////                qDebug()<<  cValue.toObject().value("flag").toString() <<  " " << lelem.attribute("data-name");
//            if(cValue.toObject().value("flag").toString() == lelem.attribute("data-name")){
//                lelem.setAttribute("style","");
//                lelem.setAttribute("fill",cValue.toObject().value("color").toString());
//                lelem.setAttribute("stroke",QColor(cValue.toObject().value("color").toString()).lighter(95).name());

//                break;
//            }
//        }
    }
    QFile *ff = new QFile(QCoreApplication::applicationDirPath()+"/out.svg");
    qDebug()<<ff->size();
    ff->open(QIODevice::WriteOnly);
    ff->flush();
    QTextStream o(ff);
    o << mapDocument->toByteArray();
    ff->close();

    rend = new QSvgRenderer(QString(QCoreApplication::applicationDirPath()+"/out.svg"),this);
    this->setSharedRenderer(rend);
    this->update();
}
