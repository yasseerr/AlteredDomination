#include "bframe.h"
#include "bmapscene.h"
#include "unitgraphics.h"

#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>

#include <domain/city.h>
#include <domain/country.h>

#include <AI/battleai.h>

BFrame::BFrame(QObject *parent) : QObject(parent),
    m_bmapS(nullptr),
    m_toAttack(false),
    m_toMoveTo(false),
    m_unitG(nullptr),
    m_x(0),
    m_y(0),
    m_isSeletedFrame(false),
    m_isPrevious(false),
    m_isActualMove(false),
    m_isDestroyer(false),
    m_idDestroyed(false),
    m_moveId(-1)

{
    this->setAcceptHoverEvents(true);
    this->setAcceptTouchEvents(true);

}

void BFrame::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    update();
    if(m_unitG == nullptr)return;
    m_unitG->setIsHovered(true);
    m_unitG->update();

}

void BFrame::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    update();
    if(m_unitG == nullptr)return;
    m_unitG->setIsHovered(false);
    m_unitG->update();
}

void BFrame::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button()==Qt::RightButton){
        if(this->unitG() != nullptr){
            bmapS()->unitPP->setVisible(true);
            bmapS()->unitPP->setUnitG(this->unitG());
            bmapS()->update(bmapS()->unitPP->boundingRect());

        }
        return;
    }
    if(bmapS()->unitPP->isVisible()){
        bmapS()->unitPP->setVisible(false);
        bmapS()->update(bmapS()->unitPP->boundingRect());

    }

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
                    if(this->unitG()->unit()->city() != bmapS()->currentCityPlaying()) return;
                    qDebug()<< "makan wallou";
                    m_bmapS->setSelectedFrame(this);
                    this->setIsSeletedFrame(true);
                }
            }else{
                if(this->unitG() == nullptr){
                    if(this->bmapS()->selectedFrame()->unitG()->unit()->city() != bmapS()->bmap()->attacker())return;
//                     this->setUnitG(bmapS()->selectedFrame()->unitG());
                    if(bmapS()->isMultiplayer()) bmapS()->sendChangeInPos(bmapS()->selectedFrame(),this);
                    this->bmapS()->selectedFrame()->unitG()->moveAnimation(this);
                    this->bmapS()->selectedFrame()->setIsSeletedFrame(false);
                    this->bmapS()->selectedFrame()->update();
                    this->bmapS()->setSelectedFrame(nullptr);
                }else{
                    if(this->bmapS()->selectedFrame()->unitG()->unit()->city() != bmapS()->bmap()->attacker())return;
//                    UnitGraphics *tmp = m_bmapS->selectedFrame()->unitG();
//                    bmapS()->selectedFrame()->setUnitG(this->unitG());
//                    this->setUnitG(tmp);
                    if(bmapS()->isMultiplayer()) bmapS()->sendChangeInPos(bmapS()->selectedFrame(),this);
                    this->bmapS()->selectedFrame()->unitG()->moveAnimation(this);
                    this->unitG()->moveAnimation(bmapS()->selectedFrame());
                    this->bmapS()->selectedFrame()->setIsSeletedFrame(false);
                    this->bmapS()->selectedFrame()->update();
                    this->bmapS()->setSelectedFrame(nullptr);
                }
            }
        }
        ///*******************deffender************************
        else if(this->x()> this->bmapS()->bmap()->size().x()-4){
            if(this->bmapS()->selectedFrame() == nullptr){
                if(this->unitG() == nullptr){
                     return;
                }else{
                    if(this->unitG()->unit()->city() != bmapS()->currentCityPlaying()
                            /*&&(bmapS()->bmap()->attacker()->country()->player()->type() == PlayerType::NET||
                               bmapS()->bmap()->deffender()->country()->player()->type() == PlayerType::NET
                               )*/) return;
                    m_bmapS->setSelectedFrame(this);
                    this->setIsSeletedFrame(true);
                }
            }else{
                if(this->unitG() == nullptr){
                    if(this->bmapS()->selectedFrame()->unitG()->unit()->city() != bmapS()->bmap()->deffender())return;
//                     this->setUnitG(bmapS()->selectedFrame()->unitG());
                    if(bmapS()->isMultiplayer()) bmapS()->sendChangeInPos(bmapS()->selectedFrame(),this);
                    this->bmapS()->selectedFrame()->unitG()->moveAnimation(this);
                    this->bmapS()->selectedFrame()->setIsSeletedFrame(false);
                    this->bmapS()->selectedFrame()->update();
                    this->bmapS()->setSelectedFrame(nullptr);
                }else{
                    if(this->bmapS()->selectedFrame()->unitG()->unit()->city() != bmapS()->bmap()->deffender())return;
//                     this->setUnitG(bmapS()->selectedFrame()->unitG());
                    if(bmapS()->isMultiplayer()) bmapS()->sendChangeInPos(bmapS()->selectedFrame(),this);
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
            if(bmapS()->currentCityPlaying() != bmapS()->bmap()->attacker())return;
            if(event->button() == Qt::LeftButton){
                if(this->unitG()->isGeneral() == true)return;
//                qDebug()<< "wellah gir fat manha sans pitier";
                if(bmapS()->generalsToChooseA() == 0) return;
                if(bmapS()->isMultiplayer())bmapS()->sendPromote(this,1);
                unitG()->setIsGeneral(true);
                unitG()->unit()->setType("soldier");
                bmapS()->setGeneralsToChooseA(bmapS()->generalsToChooseA()-1);
                unitG()->update();
                return;
            }else if (event->button() == Qt::RightButton) {
                if(!unitG()->isGeneral())return;
                if(bmapS()->isMultiplayer())bmapS()->sendPromote(this,-1);
                unitG()->setIsGeneral(false);
                bmapS()->setGeneralsToChooseA(bmapS()->generalsToChooseA()+1);
            }

        }else {
            /// deffender
            if(bmapS()->currentCityPlaying() != bmapS()->bmap()->deffender())return;
            if(event->button() == Qt::LeftButton){
                if(this->unitG()->isGeneral() == true)return;
//                qDebug()<< "fat manha sans pitier";
                if(bmapS()->generalsToChooseD() == 0) return;
                if(bmapS()->isMultiplayer())bmapS()->sendPromote(this,1);
                unitG()->setIsGeneral(true);
                unitG()->unit()->setType("soldier");
                bmapS()->setGeneralsToChooseD(bmapS()->generalsToChooseD()-1);
                unitG()->update();
                return;
            }else if (event->button() == Qt::RightButton) {
                if(!unitG()->isGeneral())return;
                if(bmapS()->isMultiplayer())bmapS()->sendPromote(this,-1);
                unitG()->setIsGeneral(false);
                bmapS()->setGeneralsToChooseD(bmapS()->generalsToChooseD()+1);
            }
        }

    }
///-------------------playing--------------------------------
    else if (this->bmapS()->phase() == BMapScene::PLAYING) {
        /// player turn verification

//        qDebug() << "well we are oviously playing";

        /// new selection        
        if(bmapS()->selectedFrame() == nullptr ){
//            qDebug() << "it wasnt the selected frame !";
            if(this->unitG() == nullptr) return;

//            qDebug() << "selecting new selected frame";

            if(this->unitG()->unit()->city() != bmapS()->currentCityPlaying())return;
            if(this->unitG()->unit()->used())return;
            this->setIsSeletedFrame(true);
            highlightMovesAttacks();
        }else{

            qDebug()<< bmapS()->selectedFrame()->x() << " : " << bmapS()->selectedFrame()->y();

            if(this->bmapS()->selectedFrame()->unitG()->unit()->city() != bmapS()->currentCityPlaying())return;
            ///-------move to------------
            if(toMoveTo()){

//                qDebug() << "well lets move here ! ";

                /* graphics ****************/
                this->setIsActualMove(true);
                bmapS()->selectedFrame()->setIsActualMove(true);
                bmapS()->selectedFrame()->setMoveId( bmapS()->currentCityPlaying()==bmapS()->bmap()->attacker()?
                                                         bmapS()->generalsToChooseA():bmapS()->generalsToChooseD());
                this->setMoveId( bmapS()->currentCityPlaying()==bmapS()->bmap()->attacker()?
                                                         bmapS()->generalsToChooseA():bmapS()->generalsToChooseD());
                bmapS()->previousFramesThisTurn.append(this);
                bmapS()->previousFramesThisTurn.append(bmapS()->selectedFrame());

                bmapS()->selectedFrame()->unHighlight();
                bmapS()->selectedFrame()->setIsSeletedFrame(false);

                bmapS()->selectedFrame()->unitG()->unit()->setUsed(true);
                if(bmapS()->isMultiplayer()) bmapS()->sendChangeInPos(bmapS()->selectedFrame(),this);
//                qDebug() << "it should move after that";
                bmapS()->selectedFrame()->unitG()->moveAnimation(this);
                bmapS()->cheCkEndTurn();
//                this->setUnitG(bmapS()->selectedFrame()->unitG());
//                bmapS()->selectedFrame()->setUnitG(nullptr);
            }
            ///attack
            else if (toAttack()) {
//                qDebug() << "Attacking ************";
                bmapS()->animHandler->launchBullet(bmapS()->selectedFrame(),this);

                this->setIsActualMove(true);
                bmapS()->selectedFrame()->setIsActualMove(true);
                bmapS()->selectedFrame()->setMoveId( bmapS()->currentCityPlaying()==bmapS()->bmap()->attacker()?
                                                         bmapS()->generalsToChooseA():bmapS()->generalsToChooseD());
                this->setMoveId( bmapS()->currentCityPlaying()==bmapS()->bmap()->attacker()?
                                                         bmapS()->generalsToChooseA():bmapS()->generalsToChooseD());
                bmapS()->selectedFrame()->setIsDestroyer(true);
                this->setIdDestroyed(true);
                bmapS()->previousFramesThisTurn.append(this);
                bmapS()->previousFramesThisTurn.append(bmapS()->selectedFrame());

                bmapS()->selectedFrame()->unitG()->explosionAudio->play();
                bmapS()->selectedFrame()->unHighlight();
                bmapS()->selectedFrame()->setIsSeletedFrame(false);
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
                bmapS()->animItem->runAnimation(this->pos().x(),this->pos().y());
                if(bmapS()->isMultiplayer()) bmapS()->sendChangeInPos(bmapS()->selectedFrame(),this);
//                bmapS()->selectedFrame()->unitG()->moveAnimation(this);
                checkWineLose();
                bmapS()->setSelectedFrame(nullptr);
                bmapS()->cheCkEndTurn();
            }else {
                bmapS()->selectedFrame()->unHighlight();
                bmapS()->selectedFrame()->setIsSeletedFrame(false);
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

void BFrame::mouseRightPressEventAI()
{
    QGraphicsSceneMouseEvent *event = new QGraphicsSceneMouseEvent();
    event->setPos(QPointF(10,10));
    event->setButton(Qt::RightButton);
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
        this->bmapS()->battleAI()->gameEnded = true;
        emit this->bmapS()->battleEndedD();
    }else if (bmapS()->bmap()->deffenderMoves() == 0) {
        this->bmapS()->battleAI()->gameEnded = true;
        emit this->bmapS()->battleEndedA();
    }
}

void BFrame::cancelSelected()
{
    this->setIsDestroyer(false);
    this->setIdDestroyed(false);
    this->setMoveId(-1);
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

void BFrame::setIsPrevious(bool isPrevious)
{
    if (m_isPrevious == isPrevious)
        return;

    m_isPrevious = isPrevious;
    this->update();
    emit isPreviousChanged(m_isPrevious);
}

void BFrame::setIsActualMove(bool isActualMove)
{
    if (m_isActualMove == isActualMove)
        return;

    m_isActualMove = isActualMove;
    this->update();
    emit isActualMoveChanged(m_isActualMove);
}

void BFrame::setMoveId(int moveId)
{
    if (m_moveId == moveId)
        return;

    m_moveId = moveId;
    emit moveIdChanged(m_moveId);
}

void BFrame::setIdDestroyed(bool idDestroyed)
{
    if (m_idDestroyed == idDestroyed)
        return;

    m_idDestroyed = idDestroyed;
    emit idDestroyedChanged(m_idDestroyed);
}

void BFrame::setIsDestroyer(bool isDestroyer)
{
    if (m_isDestroyer == isDestroyer)
        return;

    m_isDestroyer = isDestroyer;
    emit isDestroyerChanged(m_isDestroyer);
}

QRectF BFrame::boundingRect() const
{
    return QRectF(0,0,100,100);
}

void BFrame::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    /// ---------------- default rect------------------------
    painter->setOpacity(0.3);
    if((x()+y())%2 == 0)painter->setBrush(Qt::gray);
    else painter->setBrush(Qt::white);
    painter->drawRect(boundingRect());
    painter->setOpacity(1);

///------------------- hover rect --------------------------
    if(isUnderMouse()&&unitG()!=nullptr)
            painter->drawImage(5,5,bmapS()->unitClip->scaled(90,90));
///------------------ selected rect -----------------------------------
    painter->setOpacity(0.4);
    if(isSeletedFrame()){
        painter->setBrush(Qt::blue);
        painter->drawRect(boundingRect());
    }
///--------------------move to ---------------------------
    if(toMoveTo()){
        painter->setBrush(Qt::darkGreen);
        painter->drawRect(QRectF(30,30,40,40));
    }
///--------------------attack to ---------------------------
    if(toAttack()){
        painter->setBrush(Qt::red);
        painter->drawRect(boundingRect());
    }
///------------------- previous rect-------------------------
    if(isPrevious()){
         painter->setBrush(Qt::magenta);
         painter->drawRect(QRectF(30,30,40,40));
    }

///------------------- previous rect-------------------------
    if(isActualMove()){
        painter->setBrush(Qt::darkYellow);
        painter->drawRect(QRectF(30,30,40,40));
    }
    painter->setOpacity(1);
///------------------- destroyed image-------------------------
    if(idDestroyed()){
        painter->drawImage(0,30,QImage(":/data/cracking.png").scaled(100,100));
    }
///------------------- destroyer iùage-------------------------
    if(isDestroyer()){
        painter->drawImage(0,0,QImage(":/data/canon.png").scaled(30,20));
    }
///------------------- move test-------------------------
    if(moveId()!=-1){
        QPen p1;
        p1.setWidth(25);
        p1.setBrush(Qt::white);
        painter->setBrush(Qt::black);
        painter->drawRect(80,80,20,20);
        painter->setPen(p1);
        painter->drawText(84,90,"M"+QString::number(moveId()));
    }

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
