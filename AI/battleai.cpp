#include "battleai.h"

#include <graphics/bframe.h>
#include <graphics/unitgraphics.h>

#include <domain/city.h>
#include <domain/player.h>

#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QThread>
#include <battleform.h>

BattleAI::BattleAI(QObject *parent) : QObject(parent),m_player(nullptr),m_city(nullptr),animationCount(0)
{

}

void BattleAI::placeUnits()
{
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

                animationList.append(QPair<BFrame*,BFrame*>(dep,des));
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

                animationList.append(QPair<BFrame*,BFrame*>(dep,des));
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

                animationList.append(QPair<BFrame*,BFrame*>(dep,des));
                machineIndex++;
            }

        }
    }
    runAnimation();
}

void BattleAI::runAnimation()
{
    if(scene()->phase() != BattlePhase::PLACING)return;
    if(animationList.size()==0){
        scene()->setPhase(BattlePhase::PROMOTING);
        this->selectGenerals();
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
        animationList << pair;
    }
    animationCount +=  animationFrames.second->unitG()==nullptr?1:0;
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

BattleForm *BattleAI::battleForm() const
{
    return m_battleForm;
}

Player *BattleAI::player() const
{
    return m_player;
}

QMap<QString, QList<BFrame *> > BattleAI::dangerFrames() const
{
    return m_dangerFrames;
}

QMap<BFrame *, BFrame *> BattleAI::availableAttacks() const
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

void BattleAI::setDangerFrames(QMap<QString, QList<BFrame *> > dangerFrames)
{
    if (m_dangerFrames == dangerFrames)
        return;

    m_dangerFrames = dangerFrames;
    emit dangerFramesChanged(m_dangerFrames);
}

void BattleAI::setAvailableAttacks(QMap<BFrame *, BFrame *> availableAttacks)
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
    emit cityChanged(m_city);
}

void BattleAI::setScene(BMapScene *scene)
{
    if (m_scene == scene)
        return;

    m_scene = scene;
    emit sceneChanged(m_scene);
}
