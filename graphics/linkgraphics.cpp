#include "linkgraphics.h"

#include <QPen>
#include<domain/country.h>
LinkGraphics::LinkGraphics(LinkN *l,QObject *parent) : QObject(parent),m_link(l)
{

    setPen(QPen(Qt::red,2,Qt::DotLine));
    this->setLine(
                l->dep()->x()+40,
                l->dep()->y()+40,
                l->des()->x()+40,
                l->des()->y()+40
                );
     setOpacity(0.3);
    if(l->des()->country() == l->dep()->country())setPen(QPen(l->des()->country()->color().darker(150),3,Qt::DashDotLine));


}

LinkN* LinkGraphics::link() const
{
    return m_link;
}

void LinkGraphics::updateAfterBattle()
{
    setPen(QPen(Qt::red,2,Qt::DotLine));
    this->setLine(
                m_link->dep()->x()+40,
                m_link->dep()->y()+40,
                m_link->des()->x()+40,
                m_link->des()->y()+40
                );
     setOpacity(0.3);
    if(m_link->des()->country() == m_link->dep()->country())setPen(QPen(m_link->des()->country()->color().darker(150),3,Qt::DashDotLine));
    this->update();
}

void LinkGraphics::setLink(LinkN* link)
{
    if (m_link == link)
        return;

    m_link = link;
    emit linkChanged(m_link);
}

void LinkGraphics::zoomChanged()
{
    this->setLine(
                link()->dep()->x()+40,
                link()->dep()->y()+40,
                link()->des()->x()+40,
                link()->des()->y()+40
                );
}
