#include "map.h"
#include "domain/city.h"
Map::Map(QObject *parent) : QObject(parent)
{

}

QMap<int, City *> Map::cities() const
{
    return m_cities;
}

QMap<int, Country *> Map::countries() const
{
    return m_countries;
}

void Map::setCities(QMap<int, City *> cities)
{
    if (m_cities == cities)
        return;

    m_cities = cities;
    emit citiesChanged(m_cities);
}

void Map::setCountries(QMap<int, Country *> countries)
{
    if (m_countries == countries)
        return;

    m_countries = countries;
    emit countriesChanged(m_countries);
}
