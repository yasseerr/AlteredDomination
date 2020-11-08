#include "battleai.h"

#include <graphics/bframe.h>
#include <graphics/unitgraphics.h>

#include <domain/city.h>
#include <domain/player.h>

#include <QCoreApplication>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QThread>
#include <battleform.h>

BattleAI::BattleAI(QObject *parent) : QObject(parent),m_player(nullptr),m_city(nullptr),animationCount(0),m_acceptOrProposeDraw(false)
{
    gameEnded =false;
}

void BattleAI::placeUnits()
{
    scene()->setCurrentCityPlaying(this->city());
    animationList.clear();
    int mapcenter = battleForm()->bScene()->bmap()->size().y()/2;
    int centerIndex =  (battleForm()->bScene()->bmap()->size().y()-(this->city()->units().size()/3))/2;
    int disttributionIndex =0;
    QList<Unit*> units_redistribute;



    /// see idf there is air units
    bool thereIsAirUnits = false;
    foreach (Unit *u, city()->units()) {
        if(scene()->bmap()->unitetypes().value(u->type())->types().contains("air")){
            thereIsAirUnits = true;
            break;
        }
    }

    if(m_city == battleForm()->bScene()->bmap()->deffender()){
        int airIndex=-1;
        int machineIndex =-1;
        int humanIndex =-1;
        foreach (Unit *u, city()->units()) {
            if(scene()->bmap()->unitetypes().value(u->type())->types().contains("human")){
//                    qDebug()<<(mapcenter+(pow(-1,(humanIndex+1))*(humanIndex/2+1)));
                if(!scene()->frames().contains(QPair<int,int>(
                                                          (scene()->bmap()->size().x()-1),
                                                          humanIndex==-1?mapcenter
                                                                       :((mapcenter+pow(-1,(humanIndex+1))*(humanIndex/2+1)))
                                                          ))){
                    humanIndex++;
                    continue;
                }


                BFrame* dep =scene()->units().value(u)->frame();
                BFrame* des = scene()->frames().value(QPair<int,int>(
                                                          thereIsAirUnits?(scene()->bmap()->size().x()-1)
                                                                        :(scene()->bmap()->size().x()-2),
                                                          humanIndex==-1?mapcenter:((mapcenter+pow(-1,(humanIndex+1))*
                                                                                          (humanIndex/2+1)))
                                                          ));

                animationList.append(QPair<BFrame*,BFrame*>(dep,des));
                humanIndex++;
            }
            else if(scene()->bmap()->unitetypes().value(u->type())->types().contains("air")){
                BFrame* dep =scene()->units().value(u)->frame();
                if(!scene()->frames().contains(QPair<int,int>(
                                                          (scene()->bmap()->size().x()-2),
                                                          airIndex==-1?mapcenter:((mapcenter+pow(-1,(airIndex+1))*
                                                                                        (airIndex/2+1)))
                                                          ))){
                    airIndex++;
                    continue;
                }

                BFrame *des =scene()->frames().value(QPair<int,int>(
                                                          (scene()->bmap()->size().x()-2),
                                                          airIndex==-1?mapcenter:((mapcenter+pow(-1,(airIndex+1))*
                                                                                        (airIndex/2+1)))
                                                          ));

                animationList.append(QPair<BFrame*,BFrame*>(dep,des));
                airIndex++;
            }
            else if(scene()->bmap()->unitetypes().value(u->type())->types().contains("machin")){
                if(!scene()->frames().contains(QPair<int,int>(
                                                          (scene()->bmap()->size().x()-3),
                                                          machineIndex==-1?mapcenter:((mapcenter+pow(-1,(machineIndex+1))*
                                                                                            (machineIndex/2+1)))
                                                          ))){
                    machineIndex++;
                    continue;
                }

                BFrame* dep =scene()->units().value(u)->frame();
                BFrame* des = scene()->frames().value(QPair<int,int>(
                                                          (scene()->bmap()->size().x()-3),
                                                          machineIndex==-1?mapcenter:((mapcenter+pow(-1,(machineIndex+1))*
                                                                                            (machineIndex/2+1)))
                                                          ));

                animationList.append(QPair<BFrame*,BFrame*>(dep,des));
                machineIndex++;
            }

        }

    }else {
        int airIndex=-1;
        int machineIndex =-1;
        int humanIndex =-1;
        foreach (Unit *u, city()->units()) {
            if(scene()->bmap()->unitetypes().value(u->type())->types().contains("human")){
//                    qDebug()<<(mapcenter+(pow(-1,(humanIndex+1))*(humanIndex/2+1)));
                if(!scene()->frames().contains(QPair<int,int>(
                                                          0,
                                                          humanIndex==-1?mapcenter
                                                                       :((mapcenter+pow(-1,(humanIndex+1))*(humanIndex/2+1)))
                                                          ))){
                    humanIndex++;
                    continue;
                }


                BFrame* dep =scene()->units().value(u)->frame();
                BFrame* des = scene()->frames().value(QPair<int,int>(
                                                          thereIsAirUnits?0
                                                                        :1,
                                                          humanIndex==-1?mapcenter:((mapcenter+pow(-1,(humanIndex+1))*
                                                                                          (humanIndex/2+1)))
                                                          ));

                if(dep != des)animationList.append(QPair<BFrame*,BFrame*>(dep,des));
                humanIndex++;
            }
            else if(scene()->bmap()->unitetypes().value(u->type())->types().contains("air")){
                BFrame* dep =scene()->units().value(u)->frame();
                if(!scene()->frames().contains(QPair<int,int>(
                                                          1,
                                                          airIndex==-1?mapcenter:((mapcenter+pow(-1,(airIndex+1))*
                                                                                        (airIndex/2+1)))
                                                          ))){
                    airIndex++;
                    continue;
                }

                BFrame *des =scene()->frames().value(QPair<int,int>(
                                                          1,
                                                          airIndex==-1?mapcenter:((mapcenter+pow(-1,(airIndex+1))*
                                                                                        (airIndex/2+1)))
                                                          ));

                if(dep != des)animationList.append(QPair<BFrame*,BFrame*>(dep,des));
                airIndex++;
            }
            else if(scene()->bmap()->unitetypes().value(u->type())->types().contains("machin")){
                if(!scene()->frames().contains(QPair<int,int>(
                                                          2,
                                                          machineIndex==-1?mapcenter:((mapcenter+pow(-1,(machineIndex+1))*
                                                                                            (machineIndex/2+1)))
                                                          ))){
                    machineIndex++;
                    continue;
                }

                BFrame* dep =scene()->units().value(u)->frame();
                BFrame* des = scene()->frames().value(QPair<int,int>(
                                                          2,
                                                          machineIndex==-1?mapcenter:((mapcenter+pow(-1,(machineIndex+1))*
                                                                                            (machineIndex/2+1)))
                                                          ));

                if(dep != des)animationList.append(QPair<BFrame*,BFrame*>(dep,des));
                machineIndex++;
            }

        }
    }
    runAnimation();
}

void BattleAI::runAnimation()
{
    if(scene()->phase() == BMapScene::PLAYING)return;
    if(animationList.size()==0){
        scene()->setPhase(BMapScene::PROMOTING);
        this->selectGenerals();
        m_battleForm->bScene()->setCurrentCityPlaying(enemyCity);
        return;
    }
    animationCount++;
    if(animationCount%2 != 1)return;
//    if(scene()->thereIsAnimationRunning)return;
    QPair<BFrame*,BFrame*> animationFrames = animationList.first();
    animationList.removeFirst();
    /// replacing the frames of the replaced frame
    for (int i = 0; i < animationList.size(); ++i) {
        QPair<BFrame*,BFrame*> pair = animationList.at(i);
        if(pair.first != animationFrames.second)continue;
        pair.first = animationFrames.first;
        animationList.removeAt(i);
        if(pair.first == pair.second)continue;
        animationList << pair;
    }
    animationCount +=  animationFrames.second->unitG()==nullptr?1:0;
    if(animationFrames.first == animationFrames.second){
        if(animationFrames.second->unitG()!=nullptr)animationCount++;
        runAnimation();
        return;
    }
    animationFrames.first->mousePressEventAI();
    animationFrames.second->mousePressEventAI();
}

void BattleAI::selectGenerals()
{
    int generalsCount = city()==scene()->bmap()->attacker()?scene()->generalsToChooseA():scene()->generalsToChooseD();
    /// selecting the soldiers groupe
    QList<Unit*> soldiers;
    foreach (Unit *u, city()->units()) {
        if(u->type() == "soldier"){
            soldiers << u;
        }
    }
    if(soldiers.size()<generalsCount){
        for (int i = 0; i < soldiers.size(); ++i) {
            scene()->units().value(soldiers.at(i))->frame()->mousePressEventAI();
            generalsCount--;
        }
        QList<int> used;
        while (generalsCount>0) {
            int a = qrand()%(city()->units().size());
            if(used.contains(a))continue;
            used << a;
            if(city()->units().values().at(a)->type() == "soldier")continue;
            scene()->units().value(m_city->units().values().at(a))->frame()->mousePressEventAI();
            generalsCount --;
        }
    }else{
        for (int i = 0; i < generalsCount; ++i) {
            int a = qrand()%(soldiers.size());
            scene()->units().value(soldiers.at(a))->frame()->mousePressEventAI();
            soldiers.removeAt(a);
        }
    }
}



void BattleAI::playTurn()
{
    while (scene()->thereIsAnimationRunning) {
        QCoreApplication::processEvents();
    }
    detectSurroundingFrames();
    detectDangerFrames();
    detectThretenedUnits();
    detectAttackOpportunities();
    detectForkPossibilities();
    studyDraw();
    studySurrender();
    applyMoves();


    /// cleaning
    m_dangerFrames.clear();
    m_availableAttacks.clear();
    toBeSurroundedFrames.clear();
    toSurroundMoves.clear();
    forkMoves.clear();
    createThreatPossib.clear();
    threatenedUnits.clear();
    movesRating.clear();

}

void BattleAI::detectSurroundingFrames()
{
    foreach (Unit *u, enemyCity->units()) {
        UnitGraphics *ug = scene()->units().value(u);
        if(!ug->isGeneral())continue;
        toBeSurroundedFrames << ug->frame();
        foreach (UMove *p, scene()->bmap()->unitetypes().value(u->type())->moves()) {
            if(!scene()->frames().contains(QPair<int,int>(ug->frame()->x()+p->x(),ug->frame()->y()+p->y())))continue;
            BFrame *f = scene()->frames().value(QPair<int,int>(ug->frame()->x()+p->x(),ug->frame()->y()+p->y()));
            if(f->unitG() != nullptr) continue;
            toBeSurroundedFrames << f;
        }
    }
}

void BattleAI::detectDangerFrames()
{
    foreach (Unit *u, enemyCity->units()) {
        UnitGraphics *ug = scene()->units().value(u);
        foreach (UAttack *a, scene()->bmap()->unitetypes().value(u->type())->attacks()){
            if(!scene()->frames().contains(QPair<int,int>(ug->frame()->x()+a->x(),ug->frame()->y()+a->y())))continue;
            BFrame *f = scene()->frames().value(QPair<int,int>(ug->frame()->x()+a->x(),ug->frame()->y()+a->y()));
            QStringList tmp ;
            tmp << m_dangerFrames.value(f);
            tmp << a->types();
            m_dangerFrames.insert(f,tmp);
        }
    }
//    qDebug()<<m_dangerFrames.size();
}

void BattleAI::studyDraw()
{
    if(this->city()->power()>enemyCity->power())return;
    if(scene()->turncount()>15)setAcceptOrProposeDraw(true);
}

void BattleAI::studySurrender()
{
    bool willISurrender = true;
    if(hasTypeOfUnits(this->city(),"air") && !hasTypeOfUnits(enemyCity,"air"))willISurrender = false;
    else if(hasTypeOfUnits(this->city(),"machin") && !hasTypeOfUnits(enemyCity,"machin"))willISurrender = false;
    else if(city()->power() > enemyCity->power()/10) willISurrender=false;
    if(!willISurrender)return;
    battleForm()->surrender();
}

void BattleAI::detectThretenedUnits()
{
    foreach (Unit* u, city()->units()) {
        UnitGraphics *ug = scene()->units().value(u);
        if(!m_dangerFrames.contains(ug->frame()))continue;

        /// see if the unit is affected by that atack
        bool affected = false;
        foreach (QString t, scene()->bmap()->unitetypes().value(u->type())->types()) {
            if(m_dangerFrames.value(ug->frame()).contains(t))affected =true;
        }
        if(!affected)continue;

        /// choosing the escape to frame
        bool thereIsanEschap = false;
        BFrame *escapeFrame = nullptr;

        foreach (BFrame *esp, attackListForFrame(ug->frame(),u)+moveListForFrame(ug->frame(),u)) {
            if(dangerFrames().contains(esp))continue;
            thereIsanEschap = true;
            escapeFrame = esp;
        }

        if(!thereIsanEschap)continue;

        if(ug->isGeneral()){
            movesRating.insert(10000,QPair<BFrame*,BFrame*>(ug->frame(),escapeFrame));
            threatenedUnits << ug->frame();
        }
        else{
            movesRating.insert(u->power()+3,QPair<BFrame*,BFrame*>(ug->frame(),escapeFrame));
            threatenedUnits << ug->frame();
        }
//        ug->frame()->setSelected(true);
//        ug->frame()->update();
    }
    //    qDebug()<<threatenedUnits.size();
}




void BattleAI::detectAttackOpportunities()
{
    foreach (Unit *u, city()->units()) {
        foreach (UAttack *ua, scene()->bmap()->unitetypes().value(u->type())->attacks()) {
            UnitGraphics *ug = scene()->units().value(u);
            BFrame *actuelFrame = ug->frame();
            QPair<int,int> pairtmp;
            pairtmp.first = actuelFrame->x()+ua->x();
            pairtmp.second = actuelFrame->y()+ua->y();

            if(this->scene()->frames().contains(pairtmp)){
                BFrame *tm = this->scene()->frames().value(pairtmp);
                if(tm->unitG() == nullptr )continue;
                if(tm->unitG()->unit()->city()->country() == ug->unit()->city()->country())continue;

                ///-************ dependencies*************
                bool toContinu = false;
                foreach (QPoint p, ua->dependencies()) {
                    QPair<int,int> pairtmp2;
                    pairtmp2.first = actuelFrame->x()+p.x();
                    pairtmp2.second = actuelFrame->y()+p.y();
                    if(this->scene()->frames().contains(pairtmp2)){
                        BFrame *tm2 = this->scene()->frames().value(pairtmp2);
                        if(tm2->unitG() != nullptr){
                            toContinu = true;
                        }
                    }
                }
                if(toContinu) continue;
                /// affected types
                toContinu =true;
                UnitType *tmType = scene()->bmap()->unitetypes().value(tm->unitG()->unit()->type());
                foreach (QString t, ua->types()) {
                    if(tmType->types().contains(t)){toContinu = false;break;}
                }
                if(toContinu) continue;

                m_availableAttacks.insert(actuelFrame,tm);
                if(tm->unitG()->isGeneral()){
                    movesRating.insert(9000,QPair<BFrame*,BFrame*>(actuelFrame,tm));
                }else {
                    movesRating.insert(tm->unitG()->unit()->power()+2,QPair<BFrame*,BFrame*>(actuelFrame,tm));
                }
            }
        }
    }
//    qDebug() << m_availableAttacks.size();
}

void BattleAI::detectForkPossibilities()
{
    foreach (Unit *u, city()->units()) {
        UnitGraphics *ug = scene()->units().value(u);
        BFrame *f = ug->frame();
        UnitType *type = scene()->bmap()->unitetypes().value(u->type());
       ///------------------moves------------------------
        foreach (UMove *um, type->moves()) {
            QPair<int,int> pairtmp;
            pairtmp.first = f->x()+um->x();
            pairtmp.second = f->y()+um->y();
            if(scene()->frames().contains(pairtmp)){
                BFrame *tm = this->scene()->frames().value(pairtmp);
                if(tm->unitG() != nullptr  )continue;
                ///-************ dependencies*************
                bool toContinu = false;
                foreach (QPoint p, um->dependecies()) {
                    QPair<int,int> pairtmp2;
                    pairtmp2.first = f->x()+p.x();
                    pairtmp2.second = f->y()+p.y();
                    if(scene()->frames().contains(pairtmp2)){
                        BFrame *tm2 = scene()->frames().value(pairtmp2);
                        if(tm2->unitG() != nullptr){
                            toContinu = true;
                        }
                    }
                }
                if(toContinu) continue;

                /// here the tmporary battle frame is reachable see the attack possibilities from that
                if(isAffectedInFrame(tm,u)) continue;

                QList<BFrame*> tmAttacks = attackListForFrame(tm,u);
                if(tmAttacks.size()>1){
                    BFrame *maxPowerFrame = tmAttacks.first();
                    //// calculating the max

                    foreach (BFrame *bf, tmAttacks) {
                          if(maxPowerFrame->unitG()->unit()->power() >= bf->unitG()->unit()->power())continue;
                          maxPowerFrame = bf;
                    }

                    forkMoves<< QPair<BFrame*,BFrame*>(f,tm);
                    movesRating.insert(maxPowerFrame->unitG()->unit()->power()+1,QPair<BFrame*,BFrame*>(f,tm));

                }else if(tmAttacks.size() == 1){
                    createThreatPossib <<  QPair<BFrame*,BFrame*>(f,tm);
                    movesRating.insert(tmAttacks.first()->unitG()->unit()->power(),QPair<BFrame*,BFrame*>(f,tm));
                }
            }
        }
    }
//    qDebug()<< " fork list size : " << forkMoves.size();
//    qDebug()<< " create threat list size : " << createThreatPossib.size();
}

void BattleAI::buildStrategy()
{
    foreach (Unit *u, city()->units()) {
        UnitGraphics *ug = scene()->units().value(u);

        ///testing if it already there
        bool alreadyThere = false;
        foreach (BFrame *f, (moveListForFrame(ug->frame(),u)+attackListForFrame(ug->frame(),u))) {
           if(!toBeSurroundedFrames.contains(f))continue;
           toSurroundMoves.insert(3000,QPair<UnitGraphics*,BFrame*>(ug,f));
           alreadyThere = true;
           break;
        }
        if(alreadyThere)continue;

        ///finging path
        QList<BFrame*> movesPlusAttacksFrames = (moveListForFrame(ug->frame(),u)+attackListForFrame(ug->frame(),u));
        if(movesPlusAttacksFrames.size()==0)continue;
        int minimumFrameDistance = 1000;
        BFrame *minimumFrame = movesPlusAttacksFrames.first();
        foreach (BFrame *f, movesPlusAttacksFrames) {
            int distance = findPathTogenerals(1,f,u);
            if(! (distance < minimumFrameDistance))continue;
            minimumFrameDistance = distance;
            minimumFrame = f;
        }
        toSurroundMoves.insert(minimumFrameDistance,QPair<UnitGraphics*,BFrame*>(ug,minimumFrame));
    }
}

int BattleAI::findPathTogenerals(int layer, BFrame *f, Unit *u)
{
    int thisLayer = layer+1;
//    qDebug() << thisLayer;
    if(thisLayer == 5) return 50;

    QList<BFrame*> movesPlusAttacksFrames;
    movesPlusAttacksFrames << moveListForFrame(f,u) << attackListForFrame(f,u);
    if(movesPlusAttacksFrames.size() == 0) return 2000;
    /// see if we are there
    foreach (BFrame *f2, movesPlusAttacksFrames) {
        if(toBeSurroundedFrames.contains(f2)) return thisLayer;
    }

    int minimumFrameDistance = 1000;
    BFrame *minimumFrame = movesPlusAttacksFrames.first();
    foreach (BFrame *f2, movesPlusAttacksFrames) {
        int distance = findPathTogenerals(thisLayer,f2,u);
        if(! (distance < minimumFrameDistance))continue;
        minimumFrameDistance = distance;
        minimumFrame = f2;
    }
    return minimumFrameDistance;
}

bool BattleAI::hasTypeOfUnits(City *c, QString s)
{
    foreach (Unit *u, c->units()) {
        UnitType *ut = scene()->bmap()->unitetypes().value(u->type());
        if(ut->types().contains(s))return true;
    }
    return false;
}

void BattleAI::applyMoves()
{
    /// calculation the number of moves
    int a = 0;
    if(this->city() == scene()->bmap()->attacker()){
        a = scene()->generalsToChooseA();
    }else if (this->city() == scene()->bmap()->deffender()) {
        a = scene()->generalsToChooseD();
    }

    qDebug() << " moves rating : " << movesRating.size();

    /// attacks and escaping
    QList<QPair<BFrame*,BFrame*>> ratingList = movesRating.values();
    while (a>0 && ratingList.size()>0 && !gameEnded) {
        while(scene()->thereIsAnimationRunning)QCoreApplication::processEvents();
        if(scene()->bmap()->deffenderMoves() == 0||scene()->bmap()->attackerMoves()==0)return;
        QPair<BFrame*,BFrame*> topMove = ratingList.last();
        ratingList.removeLast();
        for (int i = 0; i < ratingList.size(); ++i) {
            if(ratingList.at(i).first == topMove.first ||
               ratingList.at(i).second == topMove.second)
            ratingList.removeAt(i);
        }
        if(topMove.first->unitG() == nullptr)continue;
        if(topMove.first->unitG()->unit()->used())continue;
        qDebug()<< "(" << topMove.first->x() <<":" <<topMove.first->y() <<")"
                << "(" << topMove.second->x() <<":" <<topMove.second->y() <<")";

        /// fixing the bug of moving u it block the way for others
        QList<BFrame*> movesandattacks = moveListForFrame(topMove.first,topMove.first->unitG()->unit()) +
                                         attackListForFrame(topMove.first,topMove.first->unitG()->unit());
        if(!movesandattacks.contains(topMove.second))continue;

        topMove.first->mousePressEventAI();
        topMove.second->mousePressEventAI();
        a--;
    }
    if(a==0)return;

    /// strategy to suround
    buildStrategy();

    qDebug() << "strategy moves :" << toSurroundMoves.size();

    QList<QPair<UnitGraphics*,BFrame*>> strategyList = toSurroundMoves.values();
    while (a>0 && strategyList.size()>0) {
        while(scene()->thereIsAnimationRunning)QCoreApplication::processEvents();
        QPair<UnitGraphics*,BFrame*> topMove = strategyList.first();
         strategyList.removeFirst();

        if(topMove.first == nullptr)continue;
        if(topMove.first->unit()->used())continue;
        qDebug()<< "(" << topMove.first->frame()->x() <<":" <<topMove.first->frame()->y() <<")"
                << "(" << topMove.second->x() <<":" <<topMove.second->y() <<")";
        QList<BFrame*> movesandattacks = moveListForFrame(topMove.first->frame(),topMove.first->unit()) +
                                         attackListForFrame(topMove.first->frame(),topMove.first->unit());
        if(!movesandattacks.contains(topMove.second))continue;
        topMove.first->frame()->mousePressEventAI();
        topMove.second->mousePressEventAI();
        a--;
    }
    if(a==0)return;


}

QList<BFrame *> BattleAI::attackListForFrame(BFrame *f, Unit *u)
{
    QList<BFrame*> returnList;
    foreach (UAttack *ua, scene()->bmap()->unitetypes().value(u->type())->attacks()) {
        BFrame *actuelFrame = f;
        QPair<int,int> pairtmp;
        pairtmp.first = actuelFrame->x()+ua->x();
        pairtmp.second = actuelFrame->y()+ua->y();

        if(this->scene()->frames().contains(pairtmp)){
            BFrame *tm = this->scene()->frames().value(pairtmp);
            if(tm->unitG() == nullptr )continue;
            if(tm->unitG()->unit()->city()->country() == u->city()->country())continue;

            ///-************ dependencies*************
            bool toContinu = false;
            foreach (QPoint p, ua->dependencies()) {
                QPair<int,int> pairtmp2;
                pairtmp2.first = actuelFrame->x()+p.x();
                pairtmp2.second = actuelFrame->y()+p.y();
                if(this->scene()->frames().contains(pairtmp2)){
                    BFrame *tm2 = this->scene()->frames().value(pairtmp2);
                    if(tm2->unitG() != nullptr){
                        toContinu = true;
                    }
                }
            }
            if(toContinu) continue;
            /// affected types
            toContinu =true;
            UnitType *tmType = scene()->bmap()->unitetypes().value(tm->unitG()->unit()->type());
            foreach (QString t, ua->types()) {
                if(tmType->types().contains(t)){toContinu = false;break;}
            }
            if(toContinu) continue;

            returnList << tm;

        }
    }
    return returnList;
}

QList<BFrame *> BattleAI::moveListForFrame(BFrame *f, Unit *u)
{
    QList<BFrame*> tmp;
    UnitType *type = scene()->bmap()->unitetypes().value(u->type());
    foreach (UMove *um, type->moves()) {
        QPair<int,int> pairtmp;
        pairtmp.first = f->x()+um->x();
        pairtmp.second = f->y()+um->y();
        if(scene()->frames().contains(pairtmp)){
            BFrame *tm = scene()->frames().value(pairtmp);
            if(tm->unitG() != nullptr)continue;

            ///-************ dependencies*************
            bool toContinu = false;
            foreach (QPoint p, um->dependecies()) {
                QPair<int,int> pairtmp2;
                pairtmp2.first = f->x()+p.x();
                pairtmp2.second = f->y()+p.y();
                if(this->scene()->frames().contains(pairtmp2)){
                    BFrame *tm2 = this->scene()->frames().value(pairtmp2);
                    if(tm2->unitG() != nullptr){
                        toContinu = true;
                    }
                }
            }
            if(toContinu) continue;
            tmp << tm;
        }
    }
    return tmp;
}

bool BattleAI::isAffectedInFrame(BFrame *des, Unit *u)
{
    if(!dangerFrames().contains(des))return false;
    if(!dangerFrames().value(des).toSet().intersects(scene()->bmap()->unitetypes().value(u->type())->types().toSet()))return false;
    return true;
}



BattleForm *BattleAI::battleForm() const
{
    return m_battleForm;
}

Player *BattleAI::player() const
{
    return m_player;
}

QMap<BFrame*,QStringList> BattleAI::dangerFrames() const
{
    return m_dangerFrames;
}

QMultiMap<BFrame *, BFrame *> BattleAI::availableAttacks() const
{
    return m_availableAttacks;
}

City *BattleAI::city() const
{
    return m_city;
}

BMapScene *BattleAI::scene() const
{
    return m_scene;
}

bool BattleAI::acceptOrProposeDraw() const
{
    return m_acceptOrProposeDraw;
}

void BattleAI::setBattleForm(BattleForm *battleForm)
{
    if (m_battleForm == battleForm)
        return;

    m_battleForm = battleForm;
    emit battleFormChanged(m_battleForm);
}

void BattleAI::setPlayer(Player *player)
{
    if (m_player == player)
        return;

    m_player = player;
    emit playerChanged(m_player);
}

void BattleAI::setDangerFrames(QMap<BFrame*,QStringList> dangerFrames)
{
    if (m_dangerFrames == dangerFrames)
        return;

    m_dangerFrames = dangerFrames;
    emit dangerFramesChanged(m_dangerFrames);
}

void BattleAI::setAvailableAttacks(QMultiMap<BFrame *, BFrame *> availableAttacks)
{
    if (m_availableAttacks == availableAttacks)
        return;

    m_availableAttacks = availableAttacks;
    emit availableAttacksChanged(m_availableAttacks);
}

void BattleAI::setCity(City *city)
{
    if (m_city == city)
        return;
    m_city = city;
    enemyCity = this->city()==scene()->bmap()->attacker()?scene()->bmap()->deffender():scene()->bmap()->attacker();
    emit cityChanged(m_city);
}

void BattleAI::setScene(BMapScene *scene)
{
    if (m_scene == scene)
        return;

    m_scene = scene;
    emit sceneChanged(m_scene);
}

void BattleAI::setAcceptOrProposeDraw(bool acceptOrProposeDraw)
{
    if (m_acceptOrProposeDraw == acceptOrProposeDraw)
        return;

    m_acceptOrProposeDraw = acceptOrProposeDraw;
    emit acceptOrProposeDrawChanged(m_acceptOrProposeDraw);
}
