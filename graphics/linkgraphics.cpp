#include "linkgraphics.h"

#include <QPen>
#include<domain/country.h>
LinkGraphics::LinkGraphics(LinkN *l,QObject *parent) : QObject(parent),m_link(l)
{

    setPen(QPen(Qt::red,3,Qt::DotLine));
    this->setLine(
                l->dep()->x()+40,
                l->dep()->y()+40,
                l->des()->x()+40,
                l->des()->y()+40
                );
     setOpacity(0.2);
    if(l->des()->country() == l->dep()->country())setPen(QPen(l->des()->country()->color(),3,Qt::DashDotLine));

}

LinkN* LinkGraphics::link() const
{
    return m_link;
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
