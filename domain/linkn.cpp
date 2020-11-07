#include "linkn.h"

LinkN::LinkN(QObject *parent) : QObject(parent)
{

}

City *LinkN::dep() const
{
    return m_dep;
}

City *LinkN::des() const
{
    return m_des;
}

void LinkN::setDep(City *dep)
{
    if (m_dep == dep)
        return;

    m_dep = dep;
    emit depChanged(m_dep);
}

void LinkN::setDes(City *des)
{
    if (m_des == des)
        return;

    m_des = des;
    emit desChanged(m_des);
}
