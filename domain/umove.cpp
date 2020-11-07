#include "umove.h"

UMove::UMove(QObject *parent) : QObject(parent)
{

}

int UMove::x() const
{
    return m_x;
}

int UMove::y() const
{
    return m_y;
}

QList<QPoint> UMove::dependecies() const
{
    return m_dependecies;
}

void UMove::addDependecie(QPoint p)
{
    m_dependecies.append(p);
}

void UMove::setX(int x)
{
    if (m_x == x)
        return;

    m_x = x;
    emit xChanged(m_x);
}

void UMove::setY(int y)
{
    if (m_y == y)
        return;

    m_y = y;
    emit yChanged(m_y);
}

void UMove::setDependecies(QList<QPoint> dependecies)
{
    if (m_dependecies == dependecies)
        return;

    m_dependecies = dependecies;
    emit dependeciesChanged(m_dependecies);
}
