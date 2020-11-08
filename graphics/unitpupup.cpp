#include "unitpupup.h"
#include <QPainter>
#include "bframe.h"
#include "bmapscene.h"
#include"domain/battlemap.h"
#include"domain/unittype.h"
#include<qmap.h>
unitPupUp::unitPupUp(QObject *parent) : QObject(parent)
{
    setVisible(false);
    textPen.setWidth(50);
    textPen.setColor(Qt::white);

}

void unitPupUp::setUnitG(UnitGraphics *unitG)
{
    this->setPos(unitG->frame()->pos().x()+100,unitG->frame()->pos().y());
    m_unitG = unitG;
    rend.load(":/data/units/movements/"+unitG->unit()->type()+".svg");

    this->update();
    emit unitGChanged(m_unitG);
}

QRectF unitPupUp::boundingRect() const
{
    return QRectF(0,0,200,400);
}

void unitPupUp::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if(this->unitG()==nullptr)return;
    painter->setBrush(Qt::darkBlue);
    painter->setOpacity(0.5);
    painter->drawRoundRect(0,0,200,400,10,10);
    painter->setOpacity(1);
    painter->setPen(textPen);
    painter->drawText(20,50,"Unit Id : "+QString::number(unitG()->unit()->id()));
    painter->drawText(20,70,"Unit Type : "+unitG()->unit()->type());
    painter->drawText(20,90,"Cost : "+QString::number(unitG()->unit()->power()));
    painter->drawText(20,110,"IS A : ");
    int ii = 1;
    foreach (QString st, unitG()->bmapS()->bmap()->unitetypes().value(unitG()->unit()->type())->types()) {
        painter->drawText(40,110+(ii*15)," - "+st);
        ii++;
    }
    painter->drawText(20,170,"TARGETS : ");
    QStringList targets;
    foreach(UAttack *att, unitG()->bmapS()->bmap()->unitetypes().value(unitG()->unit()->type())->attacks()) {
        foreach(QString t,att->types()){
            if(targets.contains(t))continue;
            targets << t;
        }
    }
    ii = 1;
    foreach(QString t,targets){
        painter->drawText(40,170+(ii*15)," - "+t);
    }

    painter->translate(0,200);
    if(unitG()->bmapS()->bmap()->isMassiveBattle()){
        painter->translate(200,0);
        painter->rotate(90);
    }
    rend.render(painter,QRectF(0,0,200,200));

//    painter->drawText(20,90,"Id : "+QString::number(unitG()->unit()->id()));
//    painter->drawText(20,50,"Unit Id : "+QString::number(unitG()->unit()->id()));
}

UnitGraphics *unitPupUp::unitG() const
{
    return m_unitG;
}
