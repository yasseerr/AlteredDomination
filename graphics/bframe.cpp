#include "bframe.h"
#include "bmapscene.h"
#include "unitgraphics.h"

#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>

#include <domain/city.h>

BFrame::BFrame(QObject *parent) : QObject(parent),
    m_bmapS(nullptr),
    m_toAttack(false),
    m_toMoveTo(false),
    m_unitG(nullptr),
    m_x(0),
    m_y(0),
    m_isSeletedFrame(false)
{
    this->setAcceptHoverEvents(true);
    this->setAcceptTouchEvents(true);

}

void BFrame::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    update();
    if(m_unitG == nullptr)return;
    m_unitG->setScale(0.9);

}

void BFrame::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    update();
    if(m_unitG == nullptr)return;
    m_unitG->setScale(1);
}

void BFrame::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(bmapS()->thereIsAnimationRunning)return;
///-------------------placing--------------------------------
    if(this->bmapS()->phase() == BMapScene::PLACING){
        if(this == this->bmapS()->selectedFrame())return;
        //*************** attacker**************
        if(this->x()<3){
            if(this->bmapS()->selectedFrame() == nullptr){
                if(this->unitG() == nullptr){
                     return;
                }else{
                    m_bmapS->setSelectedFrame(this);
                    this->setIsSeletedFrame(true);
                }
            }else{
                if(this->unitG() == nullptr){
                    if(this->bmapS()->selectedFrame()->unitG()->unit()->city() != bmapS()->bmap()->attacker())return;
//                     this->setUnitG(bmapS()->selectedFrame()->unitG());
                     this->bmapS()->selectedFrame()->unitG()->moveAnimation(this);
                    this->bmapS()->selectedFrame()->setIsSeletedFrame(false);
                    this->bmapS()->selectedFrame()->update();
                    this->bmapS()->setSelectedFrame(nullptr);
                }else{
                    if(this->bmapS()->selectedFrame()->unitG()->unit()->city() != bmapS()->bmap()->attacker())return;
//                    UnitGraphics *tmp = m_bmapS->selectedFrame()->unitG();
//                    bmapS()->selectedFrame()->setUnitG(this->unitG());
//                    this->setUnitG(tmp);
                    this->bmapS()->selectedFrame()->unitG()->moveAnimation(this);
                    this->unitG()->moveAnimation(bmapS()->selectedFrame());
                    this->bmapS()->selectedFrame()->setIsSeletedFrame(false);
                    this->bmapS()->selectedFrame()->update();
                    this->bmapS()->setSelectedFrame(nullptr);
                }
            }
        }
        ///*******************deffender************************
        else if (this->x()> this->bmapS()->bmap()->size().x()-4) {
            if(this->bmapS()->selectedFrame() == nullptr){
                if(this->unitG() == nullptr){
                     return;
                }else{
                    m_bmapS->setSelectedFrame(this);
                    this->setIsSeletedFrame(true);
                }
            }else{
                if(this->unitG() == nullptr){
                    if(this->bmapS()->selectedFrame()->unitG()->unit()->city() != bmapS()->bmap()->deffender())return;
//                     this->setUnitG(bmapS()->selectedFrame()->unitG());
                    this->bmapS()->selectedFrame()->unitG()->moveAnimation(this);
                    this->bmapS()->selectedFrame()->setIsSeletedFrame(false);
                    this->bmapS()->selectedFrame()->update();
                    this->bmapS()->setSelectedFrame(nullptr);
                }else{
                    if(this->bmapS()->selectedFrame()->unitG()->unit()->city() != bmapS()->bmap()->deffender())return;
//                     this->setUnitG(bmapS()->selectedFrame()->unitG());
                     this->bmapS()->selectedFrame()->unitG()->moveAnimation(this);
                    this->unitG()->moveAnimation(bmapS()->selectedFrame());
                    this->bmapS()->selectedFrame()->setIsSeletedFrame(false);
                    this->bmapS()->selectedFrame()->update();
                    this->bmapS()->setSelectedFrame(nullptr);
                }
            }
        }


    }
///-------------------promoting--------------------------------
    else if (this->bmapS()->phase() == BMapScene::PROMOTING) {
        if(unitG() == nullptr)return;
        if(unitG()->unit()->city() == bmapS()->bmap()->attacker()){
            /// attacker
            if(event->button() == Qt::LeftButton){
                if(bmapS()->generalsToChooseA() == 0) return;
                unitG()->setIsGeneral(true);
                unitG()->unit()->setType("soldier");
                bmapS()->setGeneralsToChooseA(bmapS()->generalsToChooseA()-1);
                unitG()->update();
                return;
            }else if (event->button() == Qt::RightButton) {
                if(!unitG()->isGeneral())return;
                unitG()->setIsGeneral(false);
                bmapS()->setGeneralsToChooseA(bmapS()->generalsToChooseA()+1);
            }

        }else {
            /// deffender
            if(event->button() == Qt::LeftButton){
                if(bmapS()->generalsToChooseD() == 0) return;
                unitG()->setIsGeneral(true);
                unitG()->unit()->setType("soldier");
                bmapS()->setGeneralsToChooseD(bmapS()->generalsToChooseD()-1);
                unitG()->update();
                return;
            }else if (event->button() == Qt::RightButton) {
                if(!unitG()->isGeneral())return;
                unitG()->setIsGeneral(false);
                bmapS()->setGeneralsToChooseD(bmapS()->generalsToChooseD()+1);
            }
        }

    }
///-------------------playing--------------------------------
    else if (this->bmapS()->phase() == BMapScene::PLAYING) {
        /// player turn verification


        /// new selection        
        if(bmapS()->selectedFrame() == nullptr ){
            if(this->unitG() == nullptr) return;
            if(this->unitG()->unit()->city() != bmapS()->currentCityPlaying())return;
            if(this->unitG()->unit()->used())return;
            highlightMovesAttacks();
        }else{
            if(this->bmapS()->selectedFrame()->unitG()->unit()->city() != bmapS()->currentCityPlaying())return;
            ///-------move to------------
            if(toMoveTo()){
                bmapS()->selectedFrame()->unHighlight();
                bmapS()->selectedFrame()->unitG()->unit()->setUsed(true);
                bmapS()->selectedFrame()->unitG()->moveAnimation(this);
                bmapS()->cheCkEndTurn();
//                this->setUnitG(bmapS()->selectedFrame()->unitG());
//                bmapS()->selectedFrame()->setUnitG(nullptr);
            }
            ///attack
            else if (toAttack()) {
                bmapS()->selectedFrame()->unHighlight();
                bmapS()->selectedFrame()->unitG()->unit()->setUsed(true);
                Unit *u = this->unitG()->unit();
                UnitGraphics *ug = this->unitG();
                bmapS()->removeUnitG(u);
                if(ug->isGeneral()){
                    if(u->city() == bmapS()->bmap()->attacker())
                        bmapS()->bmap()->setAttackerMoves(bmapS()->bmap()->attackerMoves()-1);
                    else
                        bmapS()->bmap()->setDeffenderMoves(bmapS()->bmap()->deffenderMoves()-1);
                }
                this->setUnitG(nullptr);
                this->update();
                ug->setVisible(false);
                ug->update();
                u->city()->removeUnit(u->id());
                u->deleteLater();
                ug->deleteLater();
                bmapS()->selectedFrame()->unitG()->moveAnimation(this);
                checkWineLose();
                bmapS()->cheCkEndTurn();
            }else {
                bmapS()->selectedFrame()->unHighlight();
            }
            bmapS()->setSelectedFrame(nullptr);
        }
    }
    update();
}

void BFrame::mousePressEventAI()
{
    QGraphicsSceneMouseEvent *event = new QGraphicsSceneMouseEvent();
    event->setPos(QPointF(10,10));
    event->setButton(Qt::LeftButton);
    this->mousePressEvent(event);
}

void BFrame::highlightMovesAttacks()
{
    bmapS()->setSelectedFrame(this);
    UnitType *type = bmapS()->bmap()->unitetypes().value(this->unitG()->unit()->type());

   ///------------------moves------------------------
    foreach (UMove *um, type->moves()) {
        QPair<int,int> pairtmp;
        pairtmp.first = this->x()+um->x();
        pairtmp.second = this->y()+um->y();
        if(this->bmapS()->frames().contains(pairtmp)){
            BFrame *tm = this->bmapS()->frames().value(pairtmp);
            if(tm->unitG() != nullptr  )continue;

            ///-************ dependencies*************
            bool toContinu = false;
            foreach (QPoint p, um->dependecies()) {
                QPair<int,int> pairtmp2;
                pairtmp2.first = this->x()+p.x();
                pairtmp2.second = this->y()+p.y();
                if(this->bmapS()->frames().contains(pairtmp2)){
                    BFrame *tm2 = this->bmapS()->frames().value(pairtmp2);
                    if(tm2->unitG() != nullptr){
                        toContinu = true;
                    }
                }
            }
            if(toContinu) continue;
            tm->setToMoveTo(true);
            tm->update();
        }
    }
   ///--------------------- attacks------------------------
    foreach (UAttack *ua, type->attacks()) {
        QPair<int,int> pairtmp;
        pairtmp.first = this->x()+ua->x();
        pairtmp.second = this->y()+ua->y();
        if(this->bmapS()->frames().contains(pairtmp)){
            BFrame *tm = this->bmapS()->frames().value(pairtmp);
            if(tm->unitG() == nullptr )continue;
            if(tm->unitG()->unit()->city()->country() == this->unitG()->unit()->city()->country())continue;

            ///-************ dependencies*************
            bool toContinu = false;
            foreach (QPoint p, ua->dependencies()) {
                QPair<int,int> pairtmp2;
                pairtmp2.first = this->x()+p.x();
                pairtmp2.second = this->y()+p.y();
                if(this->bmapS()->frames().contains(pairtmp2)){
                    BFrame *tm2 = this->bmapS()->frames().value(pairtmp2);
                    if(tm2->unitG() != nullptr){
                        toContinu = true;
                    }
                }
            }
            if(toContinu) continue;
            /// affected types
            toContinu =true;
            UnitType *tmType = bmapS()->bmap()->unitetypes().value(tm->unitG()->unit()->type());
            foreach (QString t, ua->types()) {
                if(tmType->types().contains(t)){toContinu = false;break;}
            }
            if(toContinu) continue;
            tm->setToAttack(true);
            tm->update();
        }
    }
}

void BFrame::unHighlight()
{
    UnitType *type = bmapS()->bmap()->unitetypes().value(this->unitG()->unit()->type());
    foreach (UMove *um, type->moves()) {
        QPair<int,int> pairtmp;
        pairtmp.first = this->x()+um->x();
        pairtmp.second = this->y()+um->y();
        if(this->bmapS()->frames().contains(pairtmp)){
            BFrame *tm = this->bmapS()->frames().value(pairtmp);
            tm->setToMoveTo(false);
            tm->update();
        }
    }
   ///--------------------- attacks------------------------
    foreach (UAttack *ua, type->attacks()) {
        QPair<int,int> pairtmp;
        pairtmp.first = this->x()+ua->x();
        pairtmp.second = this->y()+ua->y();
        if(this->bmapS()->frames().contains(pairtmp)){
            BFrame *tm = this->bmapS()->frames().value(pairtmp);
            tm->setToAttack(false);
            tm->update();
        }
    }

}

void BFrame::checkWineLose()
{
    if(bmapS()->bmap()->attackerMoves()==0){
        emit this->bmapS()->battleEndedD();
    }else if (bmapS()->bmap()->deffenderMoves() == 0) {
        emit this->bmapS()->battleEndedA();
    }
}

void BFrame::setUnitG(UnitGraphics *unitG)
{
    if (m_unitG == unitG)
        return;

    m_unitG = unitG;
    emit unitGChanged(m_unitG);
    if(unitG != nullptr) m_unitG->setParentItem(this);
}

void BFrame::setX(int x)
{
    if (m_x == x)
        return;

    m_x = x;
    emit xChanged(m_x);
}

void BFrame::setY(int y)
{
    if (m_y == y)
        return;

    m_y = y;
    emit yChanged(m_y);
}

void BFrame::setBmapS(BMapScene *bmapS)
{
    if (m_bmapS == bmapS)
        return;

    m_bmapS = bmapS;
    emit bmapSChanged(m_bmapS);
}

void BFrame::setToAttack(bool toAttack)
{
    if (m_toAttack == toAttack)
        return;

    m_toAttack = toAttack;
    emit toAttackChanged(m_toAttack);
}

void BFrame::setToMoveTo(bool toMoveTo)
{
    if (m_toMoveTo == toMoveTo)
        return;

    m_toMoveTo = toMoveTo;
    emit toMoveToChanged(m_toMoveTo);
}

void BFrame::setIsSeletedFrame(bool isSeletedFrame)
{
    if (m_isSeletedFrame == isSeletedFrame)
        return;

    m_isSeletedFrame = isSeletedFrame;
    emit isSeletedFrameChanged(m_isSeletedFrame);
}

QRectF BFrame::boundingRect() const
{
    return QRectF(0,0,100,100);
}

void BFrame::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    /// ---------------- default rect------------------------
    painter->setOpacity(0.3);
    if((x()+y())%2 == 0)painter->fillRect(boundingRect(),Qt::gray);
    else painter->fillRect(boundingRect(),Qt::white);
    painter->setOpacity(1);

///------------------- hover rect --------------------------
    if(isUnderMouse()&&unitG()!=nullptr)
            painter->drawImage(5,5,QImage(":/data/icons/frame.png").scaled(90,90));
///------------------ selected rect -----------------------------------
    painter->setOpacity(0.4);
    if(isSeletedFrame())
        painter->fillRect(boundingRect(),Qt::blue);
///--------------------move to ---------------------------
    if(toMoveTo())
        painter->fillRect(boundingRect(),Qt::green);
///--------------------attack to ---------------------------
    if(toAttack())
        painter->fillRect(boundingRect(),Qt::red);
}

UnitGraphics *BFrame::unitG() const
{
    return m_unitG;
}

int BFrame::x() const
{
    return m_x;
}

int BFrame::y() const
{
    return m_y;
}

BMapScene *BFrame::bmapS() const
{
    return m_bmapS;
}

bool BFrame::toAttack() const
{
    return m_toAttack;
}

bool BFrame::toMoveTo() const
{
    return m_toMoveTo;
}

bool BFrame::isSeletedFrame() const
{
    return m_isSeletedFrame;
}
