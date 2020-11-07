#include "unitgraphics.h"
#include "citygraphics.h"
UnitGraphics::UnitGraphics(QObject *parent) : QObject(parent)
{

}

void UnitGraphics::setUnit(Unit *unit)
{
    if (m_unit == unit)
        return;

    m_unit = unit;
    emit unitChanged(m_unit);
}

void UnitGraphics::setCityG(CityGraphics *cityG)
{
    if (m_cityG == cityG)
        return;

    m_cityG = cityG;
    emit cityGChanged(m_cityG);
}

QRectF UnitGraphics::boundingRect() const
{

}

void UnitGraphics::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

}

Unit *UnitGraphics::unit() const
{
    return m_unit;
}

CityGraphics *UnitGraphics::cityG() const
{
    return m_cityG;
}
