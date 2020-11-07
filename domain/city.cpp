#include "city.h"
#include "unit.h"
City::City(QObject *parent) : QObject(parent),m_id(0),m_name(""),m_x(0),m_y(0),m_type(K100G),m_income(0)
{

}

int City::id() const
{
    return m_id;
}

QString City::name() const
{
    return m_name;
}

Country *City::country() const
{
    return m_country;
}

Map *City::map() const
{
    return m_map;
}

int City::x() const
{
    return m_x;
}

int City::y() const
{
    return m_y;
}

CityType City::type() const
{
    return m_type;
}

QList<City *> City::neighbours() const
{
    return m_neighbours;
}

int City::income() const
{
    return m_income;
}

QList<Unit *> City::units() const
{
    return m_units;
}

void City::setId(int id)
{
    if (m_id == id)
        return;

    m_id = id;
    emit idChanged(m_id);
}

void City::setName(QString name)
{
    if (m_name == name)
        return;

    m_name = name;
    emit nameChanged(m_name);
}

void City::setCountry(Country *country)
{
    if (m_country == country)
        return;

    m_country = country;
    emit countryChanged(m_country);
}

void City::setMap(Map *map)
{
    if (m_map == map)
        return;

    m_map = map;
    emit mapChanged(m_map);
}

void City::setX(int x)
{
    if (m_x == x)
        return;

    m_x = x;
    emit xChanged(m_x);
}

void City::setY(int y)
{
    if (m_y == y)
        return;

    m_y = y;
    emit yChanged(m_y);
}

void City::setType(CityType type)
{
    if (m_type == type)
        return;

    m_type = type;
    emit typeChanged(m_type);
}

void City::setNeighbours(QList<City *> neighbours)
{
    if (m_neighbours == neighbours)
        return;

    m_neighbours = neighbours;
    emit neighboursChanged(m_neighbours);
}

void City::setIncome(int income)
{
    if (m_income == income)
        return;

    m_income = income;
    emit incomeChanged(m_income);
}

void City::setUnits(QList<Unit *> units)
{
    if (m_units == units)
        return;

    m_units = units;
    emit unitsChanged(m_units);
}
