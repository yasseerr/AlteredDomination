#ifndef MAP_H
#define MAP_H

#include "country.h"

#include <QObject>
#include <qmap.h>

class City;

class Map : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QMap<int,City*> cities READ cities WRITE setCities NOTIFY citiesChanged)
    Q_PROPERTY(QMap<int,Country*> countries READ countries WRITE setCountries NOTIFY countriesChanged)

    QMap<int,City*> m_cities;

    QMap<int,Country*> m_countries;

public:
    explicit Map(QObject *parent = nullptr);

QMap<int,City*> cities() const;

QMap<int,Country*> countries() const;

signals:

void citiesChanged(QMap<int,City*> cities);

void countriesChanged(QMap<int,Country*> countries);

public slots:
void setCities(QMap<int,City*> cities);
void setCountries(QMap<int,Country*> countries);
};

#endif // MAP_H
