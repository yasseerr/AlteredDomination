#include "country.h"

Country::Country(QObject *parent) : QObject(parent)
{

}

int Country::id() const
{
    return m_id;
}

QString Country::name() const
{
    return m_name;
}

QList<City *> Country::cities() const
{
    return m_cities;
}

QColor Country::color() const
{
    return m_color;
}

City *Country::capital() const
{
    return m_capital;
}

QImage Country::flag() const
{
    return m_flag;
}

QString Country::intID() const
{
    return m_intID;
}

void Country::setId(int id)
{
    if (m_id == id)
        return;

    m_id = id;
    emit idChanged(m_id);
}

void Country::setName(QString name)
{
    if (m_name == name)
        return;

    m_name = name;
    emit nameChanged(m_name);
}

void Country::setCities(QList<City *> cities)
{
    if (m_cities == cities)
        return;

    m_cities = cities;
    emit citiesChanged(m_cities);
}

void Country::setColor(QColor color)
{
    if (m_color == color)
        return;

    m_color = color;
    emit colorChanged(m_color);
}

void Country::setCapital(City *capital)
{
    if (m_capital == capital)
        return;

    m_capital = capital;
    emit capitalChanged(m_capital);
}

void Country::setFlag(QImage flag)
{
    if (m_flag == flag)
        return;

    m_flag = flag;
    emit flagChanged(m_flag);
}

void Country::setIntID(QString intID)
{
    if (m_intID == intID)
        return;

    m_intID = intID;
    emit intIDChanged(m_intID);
}
