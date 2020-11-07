#include "uattack.h"

UAttack::UAttack(QObject *parent) : QObject(parent)
{

}

int UAttack::x() const
{
    return m_x;
}

int UAttack::y() const
{
    return m_y;
}

QList<QString> UAttack::types() const
{
    return m_types;
}

QList<QPoint> UAttack::dependencies() const
{
    return m_dependencies;
}

void UAttack::addType(QString s)
{
    m_types.append(s);
}

void UAttack::addDependecie(QPoint p)
{
    m_dependencies.append(p);
}

void UAttack::setX(int x)
{
    if (m_x == x)
        return;

    m_x = x;
    emit xChanged(m_x);
}

void UAttack::setY(int y)
{
    if (m_y == y)
        return;

    m_y = y;
    emit yChanged(m_y);
}

void UAttack::setTypes(QList<QString> types)
{
    if (m_types == types)
        return;

    m_types = types;
    emit typesChanged(m_types);
}

void UAttack::setDependencies(QList<QPoint> dependencies)
{
    if (m_dependencies == dependencies)
        return;

    m_dependencies = dependencies;
    emit dependenciesChanged(m_dependencies);
}
