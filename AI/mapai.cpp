#include "mapai.h"

#include <graphics/citygraphics.h>
#include <graphics/mapview.h>

#include <domain/unit.h>

#include <QTime>

MapAI::MapAI(QObject *parent) : QObject(parent),m_mapView(nullptr),m_player(nullptr),m_totalthreat(0)
{
    /// initialize the widraw vector
    m_widrawVector.insert("soldier",3);
    m_widrawVector.insert("sniper",1);
    m_widrawVector.insert("rocketlauncher",1);
    m_widrawVector.insert("artillery",1);
    m_widrawVector.insert("afv",1);
    m_widrawVector.insert("tank",1);
    m_widrawVector.insert("antiaircraft",1);
    m_widrawVector.insert("attackhelicopter",1);
    m_widrawVector.insert("mlrs",1);
    m_widrawVector.insert("modernarmor",1);
    m_widrawVector.insert("fighter",1);

    p_widraw1000 << QPair<QString,int>("soldier",5);
    p_widraw1000 << QPair<QString,int>("sniper",1);
    p_widraw1000 << QPair<QString,int>("fighter",1);
    p_widraw1000 << QPair<QString,int>("modernarmor",1);
    p_widraw1000 << QPair<QString,int>("attackhelicopter",1);
    p_widraw1000 << QPair<QString,int>("tank",1);
    p_widraw1000 << QPair<QString,int>("afv",1);
    p_widraw1000 << QPair<QString,int>("antiaircraft",1);
    p_widraw1000 << QPair<QString,int>("mlrs",1);
    p_widraw1000 << QPair<QString,int>("rocketlauncher",1);
    p_widraw1000 << QPair<QString,int>("artillery",1);

    p_widraw500 << QPair<QString,int>("soldier",5);
    p_widraw500 << QPair<QString,int>("sniper",1);
    p_widraw500 << QPair<QString,int>("tank",2);
    p_widraw500 << QPair<QString,int>("afv",2);
    p_widraw500 << QPair<QString,int>("attackhelicopter",1);
    p_widraw500 << QPair<QString,int>("antiaircraft",1);
    p_widraw500 << QPair<QString,int>("fighter",1);
    p_widraw500 << QPair<QString,int>("modernarmor",1);
    p_widraw500 << QPair<QString,int>("mlrs",1);
    p_widraw500 << QPair<QString,int>("rocketlauncher",1);
    p_widraw500 << QPair<QString,int>("artillery",1);

    p_widraw100 << QPair<QString,int>("soldier",2);
    p_widraw100 << QPair<QString,int>("rocketlauncher",2);
    p_widraw100 << QPair<QString,int>("afv",1);
    p_widraw100 << QPair<QString,int>("antiaircraft",1);
    p_widraw100 << QPair<QString,int>("tank",1);
    p_widraw100 << QPair<QString,int>("attackhelicopter",1);
    p_widraw100 << QPair<QString,int>("sniper",1);
    p_widraw100 << QPair<QString,int>("fighter",1);
    p_widraw100 << QPair<QString,int>("modernarmor",1);
    p_widraw100 << QPair<QString,int>("mlrs",1);
    p_widraw100 << QPair<QString,int>("artillery",1);




    /// initialise prices
//    m_prices.
    m_prices.insert("soldier",5);
    m_prices.insert("sniper",10);
    m_prices.insert("rocketlauncher",15);
    m_prices.insert("artillery",20);
    m_prices.insert("afv",30);
    m_prices.insert("tank",50);
    m_prices.insert("antiaircraft",60);
    m_prices.insert("attackhelicopter",70);
    m_prices.insert("mlrs",90);
    m_prices.insert("modernarmor",100);
    m_prices.insert("fighter",120);


    /// initialize the total vector
    m_totalParType.insert("soldier",0);
    m_totalParType.insert("sniper",0);
    m_totalParType.insert("rocketlauncher",0);
    m_totalParType.insert("artillery",0);
    m_totalParType.insert("afv",0);
    m_totalParType.insert("tank",0);
    m_totalParType.insert("antiaircraft",0);
    m_totalParType.insert("attackhelicopter",0);
    m_totalParType.insert("mlrs",0);
    m_totalParType.insert("modernarmor",0);
    m_totalParType.insert("fighter",0);


    ///initialize chosing matrix
    foreach (QString key, m_widrawVector.keys()) {
        QMap<QString,int> tmp;
        /// initialize the total vector
        if(key == "soldier"){
                tmp.insert("soldier",1);
                tmp.insert("sniper",1);
                tmp.insert("rocketlauncher",0);
                tmp.insert("artillery",0);
                tmp.insert("afv",1);
                tmp.insert("tank",0);
                tmp.insert("antiaircraft",0);
                tmp.insert("attackhelicopter",1);
                tmp.insert("mlrs",0);
                tmp.insert("modernarmor",0);
                tmp.insert("fighter",0);
        }
        else if(key =="sniper"){
                tmp.insert("soldier",1);
                tmp.insert("sniper",1);
                tmp.insert("rocketlauncher",0);
                tmp.insert("artillery",0);
                tmp.insert("afv",1);
                tmp.insert("tank",0);
                tmp.insert("antiaircraft",0);
                tmp.insert("attackhelicopter",1);
                tmp.insert("mlrs",0);
                tmp.insert("modernarmor",0);
                tmp.insert("fighter",0);
        }
        else if(key =="rocketlauncher"){
                tmp.insert("soldier",1);
                tmp.insert("sniper",1);
                tmp.insert("rocketlauncher",0);
                tmp.insert("artillery",0);
                tmp.insert("afv",1);
                tmp.insert("tank",0);
                tmp.insert("antiaircraft",0);
                tmp.insert("attackhelicopter",0);
                tmp.insert("mlrs",0);
                tmp.insert("modernarmor",0);
                tmp.insert("fighter",0);
        }
        else if(key =="artillery"){
                tmp.insert("soldier",1);
                tmp.insert("sniper",1);
                tmp.insert("rocketlauncher",1);
                tmp.insert("artillery",0);
                tmp.insert("afv",1);
                tmp.insert("tank",1);
                tmp.insert("antiaircraft",0);
                tmp.insert("attackhelicopter",0);
                tmp.insert("mlrs",0);
                tmp.insert("modernarmor",0);
                tmp.insert("fighter",0);
        }
        else if(key == "afv"){
                tmp.insert("soldier",0);
                tmp.insert("sniper",0);
                tmp.insert("rocketlauncher",1);
                tmp.insert("artillery",1);
                tmp.insert("afv",0);
                tmp.insert("tank",1);
                tmp.insert("antiaircraft",0);
                tmp.insert("attackhelicopter",1);
                tmp.insert("mlrs",0);
                tmp.insert("modernarmor",0);
                tmp.insert("fighter",0);
        }
        else if(key == "tank"){
                tmp.insert("soldier",0);
                tmp.insert("sniper",0);
                tmp.insert("rocketlauncher",1);
                tmp.insert("artillery",1);
                tmp.insert("afv",0);
                tmp.insert("tank",1);
                tmp.insert("antiaircraft",0);
                tmp.insert("attackhelicopter",1);
                tmp.insert("mlrs",0);
                tmp.insert("modernarmor",0);
                tmp.insert("fighter",0);
         }
         else if(key== "antiaircraft"){
                tmp.insert("soldier",0);
                tmp.insert("sniper",0);
                tmp.insert("rocketlauncher",1);
                tmp.insert("artillery",1);
                tmp.insert("afv",0);
                tmp.insert("tank",1);
                tmp.insert("antiaircraft",0);
                tmp.insert("attackhelicopter",1);
                tmp.insert("mlrs",1);
                tmp.insert("modernarmor",0);
                tmp.insert("fighter",0);
         }
        else if(key == "attackhelicopter"){
                tmp.insert("soldier",0);
                tmp.insert("sniper",0);
                tmp.insert("rocketlauncher",0);
                tmp.insert("artillery",0);
                tmp.insert("afv",0);
                tmp.insert("tank",0);
                tmp.insert("antiaircraft",1);
                tmp.insert("attackhelicopter",1);
                tmp.insert("mlrs",0);
                tmp.insert("modernarmor",0);
                tmp.insert("fighter",1);
         }
         else if(key =="mlrs"){
                tmp.insert("soldier",0);
                tmp.insert("sniper",0);
                tmp.insert("rocketlauncher",1);
                tmp.insert("artillery",0);
                tmp.insert("afv",0);
                tmp.insert("tank",1);
                tmp.insert("antiaircraft",0);
                tmp.insert("attackhelicopter",1);
                tmp.insert("mlrs",1);
                tmp.insert("modernarmor",1);
                tmp.insert("fighter",1);
         }
         else if(key == "modernarmor"){
                tmp.insert("soldier",0);
                tmp.insert("sniper",0);
                tmp.insert("rocketlauncher",1);
                tmp.insert("artillery",1);
                tmp.insert("afv",0);
                tmp.insert("tank",1);
                tmp.insert("antiaircraft",0);
                tmp.insert("attackhelicopter",1);
                tmp.insert("mlrs",1);
                tmp.insert("modernarmor",1);
                tmp.insert("fighter",1);
         }
         else if(key == "fighter"){
                tmp.insert("soldier",0);
                tmp.insert("sniper",0);
                tmp.insert("rocketlauncher",0);
                tmp.insert("artillery",0);
                tmp.insert("afv",0);
                tmp.insert("tank",0);
                tmp.insert("antiaircraft",1);
                tmp.insert("attackhelicopter",1);
                tmp.insert("mlrs",0);
                tmp.insert("modernarmor",0);
                tmp.insert("fighter",1);
         }
         m_choosingMatrix.insert(key,tmp);
    }


    QTime t;
    qsrand(t.msecsSinceStartOfDay());

}

MapView* MapAI::mapView() const
{
    return m_mapView;
}

Player *MapAI::player() const
{
    return m_player;
}

QMap<City *, QStringList> MapAI::unitsToBuy() const
{
    return m_unitsToBuy;
}

QMap<City *, int> MapAI::treats() const
{
    return m_treats;
}


void MapAI::distributeFunds()
{
    ///calculate threats
    foreach (City *c, this->player()->country()->cities()) {
        int totalTmp = 0;
        QStringList tmp;
        /// units to by by cities
        int i =0;
        foreach (City *neighbor, c->neighbours()) {
            if(neighbor->country() == this->player()->country())continue;
            i++;
            totalTmp = totalTmp<neighbor->power()?neighbor->power():totalTmp;
            foreach (Unit *u, neighbor->units().values()) {
                tmp << u->type();
            }
        }
        if(i == 0)continue;
        m_unitsToBuy.insert(c,tmp);
        m_treats.insert(c,totalTmp);
        m_totalthreat += totalTmp;
    }

    /// unit to by to attack
    if(mapView()->turnNumber() == 0){
        int additionalMoney = (this->player()->country()->funds())/m_treats.size();
        foreach (City *c, m_treats.keys()) {
            m_treats.insert(c,additionalMoney);
        }
    }else{
        int additionalMoney =0;
        if(this->player()->country()->funds()>m_totalthreat){
            additionalMoney = m_treats.size() == 0?0:(this->player()->country()->funds()-m_totalthreat)/m_treats.size();
        }
        foreach (City *c, m_treats.keys()) {
            float threatRatio = m_totalthreat==0?1/m_treats.size():(m_treats.value(c)/m_totalthreat);
            m_treats.insert(c,((threatRatio+(c->income()/player()->country()->income()))
                               *player()->country()->funds()/2)+additionalMoney);
        }
    }

    /// distribute and buy
    foreach (City *c, m_treats.keys()) {
        int cityTurnFunds = m_treats.value(c);
        QList<QPair<QString,int>> *widraw_type;
        if(cityTurnFunds <= 100)widraw_type = &p_widraw100;
        else if(cityTurnFunds > 100 && cityTurnFunds <500 )widraw_type = &p_widraw500;
        else if(cityTurnFunds >= 500)widraw_type = &p_widraw1000;
        while (cityTurnFunds >= 5 ) {
            for(int v=0;v< widraw_type->length();v++){
                QPair<QString,int> type = widraw_type->at(v);
                QString key = type.first;
                int rept = type.second;
                for (int i = 0; i < rept; ++i) {
                    if(cityTurnFunds < m_prices.value(key))continue;
                    cityTurnFunds -= m_prices.value(key);
                    Unit *u = new Unit(c);
                    u->setCity(c);
                    u->setType(key);
                    u->setPower(m_prices.value(key));
                    u->setName(key);
                    u->setUsed(false);
                    c->addUnit(u);
                    c->country()->setFunds(c->country()->funds()-u->power());
                }
            }
        }
    }
    /// cleaning for next country
    m_treats.clear();
    m_unitsToBuy.clear();
    m_totalthreat =0;

}

void MapAI::resetTotalParType()
{
    /// initialize the total vector
    m_totalParType.insert("soldier",0);
    m_totalParType.insert("sniper",0);
    m_totalParType.insert("rocketlauncher",0);
    m_totalParType.insert("artillery",0);
    m_totalParType.insert("afv",0);
    m_totalParType.insert("tank",0);
    m_totalParType.insert("antiaircraft",0);
    m_totalParType.insert("attackhelicopter",0);
    m_totalParType.insert("mlrs",0);
    m_totalParType.insert("modernarmor",0);
    m_totalParType.insert("fighter",0);
}

void MapAI::moveUnitsToFrontLine()
{
    foreach (City *c, this->player()->country()->cities()) {
        bool intern = true;
        foreach (City *n, c->neighbours()) {
            if(n->country() != this->player()->country()){
                intern = false;
                break;
            }
        }

        if(!intern)continue;
        if(c->units().size() == 0) continue;
        if(c->used()) continue;

        ///layer1 of neighbours
        bool layer1 =false;
        foreach (City *n, c->neighbours()) {
            foreach (City *n2, n->neighbours()) {
                if(n2->country() != this->player()->country()){
                    foreach (Unit *u, c->units()) {
                        u->setCity(n);
                        n->addUnit(u);
                        c->removeUnit(u->id());
                    }
                    c->setUsed(true);
                    layer1 = true;
                    break;
                }
            }
            if(layer1)break;
        }
        if(layer1)continue;
        /// layer 2
    }

}

void MapAI::StudyAttackPossibilities()
{
    foreach (City *c, this->player()->country()->cities()) {
        QList<City*> citiesToAttack;
        foreach (City *n, c->neighbours()) {
            if(c->country() == n->country())continue;
            if(c->used())continue;
            if(c->power() > (n->power()/2)){
                citiesToAttack << n;
            }
        }
        if(citiesToAttack.size()==0)continue;
        City *randomAttackCity = citiesToAttack.at(qrand()%citiesToAttack.size());
//                this->mapView()->setSelectedCityGraphics(mapView()->citiesGraphics().value(c->id()));
//                this->mapView()->citiesGraphics().value(n->id())->startBattle();

//        qDebug() << c->name() << "  " << randomAttackCity->name();
        if(this->player()->type() == PlayerType::AI && randomAttackCity->country()->player()->type() == PlayerType::AI){
            this->startBattleAI_AI(c,randomAttackCity);
            c->setUsed(true);
        }else if (this->player()->type() == PlayerType::AI && randomAttackCity->country()->player()->type() == PlayerType::HUMAIN) {
            QPair<City*,City*> battle(c,randomAttackCity);
            QPair<Country*,Country*> cntry(c->country(),randomAttackCity->country());
            m_battlesForP1 << QPair<QPair<City*,City*>,QPair<Country*,Country*>>(battle,cntry);
            c->setUsed(true);

        }
    }

}

void MapAI::startBattleAI_AI(City *c, City *n)
{
//    if(this->mapView()->turnNumber() == 0)return;
    int x = c->power();
    int y = n->power();
    int r = qrand()%(x+y);
    int e = (x-(x-y))/2;
    if(r<=(x-e)){

        /// attacker win
        n->country()->removeCity(n);
        c->country()->addCity(n);

        /// replacing the units
        foreach (Unit *u, n->units()) {
            n->removeUnit(u->id());
            u->deleteLater();
        }

        int unitToRomove = qrand()%c->units().size();
        for (int v2 = 0; v2 < unitToRomove; ++v2) {
            int randomUnit = qrand()%c->units().size();
            Unit *u = c->units().values().at(randomUnit);
            c->removeUnit(u->id());
            u->deleteLater();
        }

        for (int i = 0; i<c->units().size(); i+=2) {
            Unit *u = c->units().values().at(i);
            n->addUnit(u);
            c->removeUnit(u->id());
            u->setCity(n);
        }
        n->setUsed(true);


    }else if (r>(x-e) && r<(x+e)) {
        /// draw
        int unitToRomoveA = qrand()%c->units().size();
        int unitToRomoveD = qrand()%n->units().size();
        for (int v2 = 0; v2 < unitToRomoveA; ++v2) {
            int randomUnit = qrand()%c->units().size();
            Unit *u = c->units().values().at(randomUnit);
            c->removeUnit(u->id());
            u->deleteLater();
        }
        for (int v3 = 0; v3 < unitToRomoveD; ++v3) {
            int randomUnit = qrand()%n->units().size();
            Unit *u = n->units().values().at(randomUnit);
            n->removeUnit(u->id());
            u->deleteLater();
        }
    }else if(r>=(x+e)) {
        /// deffender win
        int unitToRomoveA = qrand()%c->units().size();
        int unitToRomoveD = qrand()%n->units().size();
        for (int v2 = 0; v2 < unitToRomoveA; ++v2) {
            int randomUnit = qrand()%c->units().size();
            Unit *u = c->units().values().at(randomUnit);
            c->removeUnit(u->id());
            u->deleteLater();
        }
        for (int v3 = 0; v3 < unitToRomoveD; ++v3) {
            int randomUnit = qrand()%n->units().size();
            Unit *u = n->units().values().at(randomUnit);
            n->removeUnit(u->id());
            u->deleteLater();
        }

    }

    /// updating the links
    foreach (LinkGraphics *l, mapView()->citiesGraphics().value(c->id())->links()) {
        l->updateAfterBattle();
    }
    foreach (LinkGraphics *l, mapView()->citiesGraphics().value(n->id())->links()) {
        l->updateAfterBattle();
    }

}

void MapAI::run()
{
    distributeFunds();
    moveUnitsToFrontLine();
    StudyAttackPossibilities();
}

QList<QPair<QPair<City*,City*>,QPair<Country*,Country*>>> MapAI::battlesForP1() const
{
    return m_battlesForP1;
}

int MapAI::totalthreat() const
{
    return m_totalthreat;
}

QMap<QString, int> MapAI::widrawVector() const
{
    return m_widrawVector;
}

QMap<QString, int> MapAI::totalParType() const
{
    return m_totalParType;
}

QMap<QString, QMap<QString, int> > MapAI::choosingMatrix() const
{
    return m_choosingMatrix;
}

QMap<QString, int> MapAI::prices() const
{
    return m_prices;
}



void MapAI::setMapView(MapView* mapView)
{
    if (m_mapView == mapView)
        return;

    m_mapView = mapView;
    emit mapViewChanged(m_mapView);
}

void MapAI::setPlayer(Player *player)
{
    if (m_player == player)
        return;

    m_player = player;
    emit playerChanged(m_player);
}

void MapAI::setUnitsToBuy(QMap<City *, QStringList> unitsToBuy)
{
    if (m_unitsToBuy == unitsToBuy)
        return;

    m_unitsToBuy = unitsToBuy;
    emit unitsToBuyChanged(m_unitsToBuy);
}

void MapAI::setTreats(QMap<City *, int> treats)
{
    if (m_treats == treats)
        return;

    m_treats = treats;
    emit treatsChanged(m_treats);
}

void MapAI::setTotalthreat(int totalthreat)
{
    if (m_totalthreat == totalthreat)
        return;

    m_totalthreat = totalthreat;
    emit totalthreatChanged(m_totalthreat);
}

void MapAI::setWidrawVector(QMap<QString, int> widrawVector)
{
    if (m_widrawVector == widrawVector)
        return;

    m_widrawVector = widrawVector;
    emit widrawVectorChanged(m_widrawVector);
}

void MapAI::setTotalParType(QMap<QString, int> totalParType)
{
    if (m_totalParType == totalParType)
        return;

    m_totalParType = totalParType;
    emit totalParTypeChanged(m_totalParType);
}

void MapAI::setChoosingMatrix(QMap<QString, QMap<QString, int> > choosingMatrix)
{
    if (m_choosingMatrix == choosingMatrix)
        return;

    m_choosingMatrix = choosingMatrix;
    emit choosingMatrixChanged(m_choosingMatrix);
}

void MapAI::setPrices(QMap<QString, int> prices)
{
    if (m_prices == prices)
        return;

    m_prices = prices;
    emit pricesChanged(m_prices);
}

void MapAI::setBattlesForP1(QList<QPair<QPair<City*,City*>,QPair<Country*,Country*>>> battlesForP1)
{
    if (m_battlesForP1 == battlesForP1)
        return;

    m_battlesForP1 = battlesForP1;
    emit battlesForP1Changed(m_battlesForP1);
}

void MapAI::launchBattleAI_Player()
{
    if(m_battlesForP1.size()==0) return;

    QPair<QPair<City*,City*>,QPair<Country*,Country*>> pair = m_battlesForP1.first();
    m_battlesForP1.removeFirst();

    QPair<City*,City*> battle = pair.first;
    QPair<Country*,Country*> cntry = pair.second;

    City *attacker = battle.first;
    City *deffender = battle.second;

    if(attacker->country() != cntry.first || deffender->country() != cntry.second){
        qDebug() << attacker->name() << "  " << deffender->name();
        this->launchBattleAI_Player();
        return;
    }

    mapView()->setSelectedCityGraphics(mapView()->citiesGraphics().value(attacker->id()));
    mapView()->citiesGraphics().value(deffender->id())->startBattle();


}
