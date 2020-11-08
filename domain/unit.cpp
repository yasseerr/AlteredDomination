#include "unit.h"
#include "city.h"

int Unit::idCount = 0;

Unit::Unit(QObject *parent) : QObject(parent),
    m_id(idCount),
    m_name(""),
    m_type(""),
    m_x(0),
    m_y(0),
    m_used(false)
{
    idCount++;

}

int Unit::id() const
{
    return m_id;
}

QString Unit::name() const
{
    return m_name;
}

City *Unit::city() const
{
    return m_city;
}

int Unit::x() const
{
    return m_x;
}

int Unit::y() const
{
    return m_y;
}

QString Unit::type() const
{
    return m_type;
}

bool Unit::used() const
{
    return m_used;
}

int Unit::power() const
{
    return m_power;
}

QVariant Unit::toVariant()
{
    QVariantMap ret;
    ret.insert("name",m_name);
    ret.insert("power",m_power);
    return ret;
}

void Unit::setId(int id)
{
    if (m_id == id)
        return;

    m_id = id;
    emit idChanged(m_id);
}

void Unit::setName(QString name)
{
    if (m_name == name)
        return;

    m_name = name;
    emit nameChanged(m_name);
}

void Unit::setCity(City *city)
{
    if (m_city == city)
        return;

    m_city = city;
    emit cityChanged(m_city);
}

void Unit::setX(int x)
{
    if (m_x == x)
        return;

    m_x = x;
    emit xChanged(m_x);
}

void Unit::setY(int y)
{
    if (m_y == y)
        return;

    m_y = y;
    emit yChanged(m_y);
}

void Unit::setType(QString type)
{
    if (m_type == type)
        return;

    m_type = type;
    emit typeChanged(m_type);
}

void Unit::setUsed(bool used)
{
    if (m_used == used)
        return;

    m_used = used;
    emit usedChanged(m_used);
}

void Unit::setPower(int power)
{
    if (m_power == power)
        return;

    m_power = power;
    emit powerChanged(m_power);
}
