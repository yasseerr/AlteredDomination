#include "unitgraphics.h"
#include "citygraphics.h"
#include "bmapscene.h"
#include "bframe.h"

#include <QPainter>
#include <QPropertyAnimation>

#include <domain/country.h>

#include <AI/battleai.h>
UnitGraphics::UnitGraphics(QObject *parent) : QObject(parent)
{
    setTransformOriginPoint(50,50);
}

void UnitGraphics::setUnit(Unit *unit)
{
    if (m_unit == unit)
        return;

    m_unit = unit;
    emit unitChanged(m_unit);
}

void UnitGraphics::setBmapS(BMapScene *bmapS)
{
    if (m_bmapS == bmapS)
        return;

    m_bmapS = bmapS;
    emit bmapSChanged(m_bmapS);
}

void UnitGraphics::setFrame(BFrame *frame)
{
    if (m_frame == frame)
        return;

    m_frame = frame;
    emit frameChanged(m_frame);
}

void UnitGraphics::setIsGeneral(bool isGeneral)
{
    if (m_isGeneral == isGeneral)
        return;

    m_isGeneral = isGeneral;
    emit isGeneralChanged(m_isGeneral);
}

void UnitGraphics::moveAnimationEnded(QPropertyAnimation::State stat)
{
    if(stat != QPropertyAnimation::Stopped) return;
    this->setPos(0,0);
    this->frame()->setUnitG(this);
    bmapS()->setSelectedFrame(nullptr);
    bmapS()->thereIsAnimationRunning = false;
    if(this->unit()->city()->country()->player()->type() == PlayerType::AI){
        this->bmapS()->battleAI()->runAnimation();
    }
}


QRectF UnitGraphics::boundingRect() const
{
    return QRectF(0,0,100,100);

}

void UnitGraphics::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setOpacity(0.4);
    painter->fillRect(10,10,80,80,unit()->city()->country()->color());
    painter->setOpacity(1);
    if(this->bmapS()->bmap()->attacker() != this->unit()->city()){
        painter->drawImage(70,10,QImage(":/data/flags/"+unit()->city()->country()->intID()+".png").scaled(20,15));
        painter->drawImage(10,10,QImage(":/data/units/"+this->unit()->type()+".png").scaled(80,80).mirrored(true,false));
    }
    else{
        painter->drawImage(10,10,QImage(":/data/units/"+this->unit()->type()+".png").scaled(80,80));
        painter->drawImage(10,10,QImage(":/data/flags/"+unit()->city()->country()->intID()+".png").scaled(20,15));
    }

    ///-------- general sign ----------------
    if(isGeneral()){
        painter->setOpacity(1);
        painter->drawImage(35,5,QImage(":/data/icons/general.jpg").scaled(30,30));
    }
}

Unit *UnitGraphics::unit() const
{
    return m_unit;
}

BMapScene *UnitGraphics::bmapS() const
{
    return m_bmapS;
}

BFrame *UnitGraphics::frame() const
{
    return m_frame;
}

bool UnitGraphics::isGeneral() const
{
    return m_isGeneral;
}

void UnitGraphics::moveAnimation(BFrame *f)
{
    bmapS()->thereIsAnimationRunning = true;
    this->frame()->setUnitG(nullptr);
    this->setFrame(f);
    QPropertyAnimation *moveAnim = new QPropertyAnimation(this,"pos",this);
    connect(moveAnim,&QPropertyAnimation::stateChanged,this,&UnitGraphics::moveAnimationEnded);
    moveAnim->setEndValue(mapFromScene(f->pos()));
    if(bmapS()->phase() == BMapScene::PLACING) moveAnim->setDuration(200);
    else moveAnim->setDuration(700);
    moveAnim->setEasingCurve(QEasingCurve::InOutCubic);
    moveAnim->start();
}
