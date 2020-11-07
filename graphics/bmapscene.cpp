#include "bframe.h"
#include "bmapscene.h"
#include "unitgraphics.h"

#include <domain/city.h>

BMapScene::BMapScene(QObject *parent) : QGraphicsScene(parent),
    m_bmap(nullptr),
    m_currentPlayer(nullptr),
    m_phase(BattlePhase::STARTING),
    m_selectedFrame(nullptr),
    m_turnTimer(new QDeadlineTimer()),
    m_turncount(0)
{

    setBackgroundBrush(QPixmap(":/data/mapBG3.jpg"));


}

BattleMap *BMapScene::bmap() const
{
    return m_bmap;
}


QMap<QPair<int, int>, BFrame *> BMapScene::frames() const
{
    return m_frames;
}

QList<UnitGraphics *> BMapScene::units() const
{
    return m_units;
}

Player *BMapScene::currentPlayer() const
{
    return m_currentPlayer;
}

BattlePhase BMapScene::phase() const
{
    return m_phase;
}

BFrame *BMapScene::selectedFrame() const
{
    return m_selectedFrame;
}

QDeadlineTimer *BMapScene::turnTimer() const
{
    return m_turnTimer;
}

int BMapScene::turncount() const
{
    return m_turncount;
}

int BMapScene::generalsToChooseA() const
{
    return m_generalsToChooseA;
}

int BMapScene::generalsToChooseD() const
{
    return m_generalsToChooseD;
}

void BMapScene::cheCkEndTurn()
{
    if(this->currentCityPlaying() == m_bmap->attacker()){
        this->setGeneralsToChooseA(generalsToChooseA()-1);
        if(this->generalsToChooseA() == 0){
            this->setGeneralsToChooseD(bmap()->deffenderMoves());
            this->setCurrentCityPlaying(this->bmap()->deffender());
        }
    }else if (this->currentCityPlaying() == m_bmap->deffender()) {
        this->setGeneralsToChooseD(generalsToChooseD()-1);
        if(this->generalsToChooseD() == 0){
            this->setGeneralsToChooseA(bmap()->attackerMoves());
            this->setCurrentCityPlaying(this->bmap()->attacker());
        }
    }
}

City *BMapScene::currentCityPlaying() const
{
    return m_currentCityPlaying;
}

void BMapScene::setBmap(BattleMap *bmap)
{
    if (m_bmap == bmap)
        return;

    m_bmap = bmap;
    emit bmapChanged(m_bmap);
/// filling the scene
    m_generalsToChooseA = m_bmap->attackerMoves();
    m_generalsToChooseD = m_bmap->deffenderMoves();
    ///the frames
    for(int i =0 ; i< m_bmap->size().x();i++){
        for (int j = 0; j < m_bmap->size().y(); ++j) {
            BFrame *bf = new BFrame(this);
            bf->setBmapS(this);
            bf->setToAttack(false);
            bf->setToMoveTo(false);
            bf->setX(i);
            bf->setY(j);
            bf->setPos(i*100,j*100);
            QPair<int,int> tmppair;
            tmppair.first = i;
            tmppair.second = j;
            this->m_frames.insert(tmppair,bf);
            this->addItem(bf);
        }
    }
    /// the units
    for (int i = 0; i < m_bmap->attacker()->units().size(); ++i) {
        UnitGraphics *ug = new UnitGraphics(this);
        ug->setUnit(m_bmap->attacker()->units().values().at(i));
        ug->setIsGeneral(false);
        QPair<int,int> tmpp;
        tmpp.first = i/m_bmap->size().y();
        tmpp.second = i%m_bmap->size().y();
        ug->setFrame(this->frames().value(tmpp));
        ug->frame()->setUnitG(ug);
        ug->setParentItem(ug->frame());
        ug->setBmapS(this);
    }
    for (int i = 0; i < m_bmap->deffender()->units().size(); ++i) {
        UnitGraphics *ug = new UnitGraphics(this);
        ug->setUnit(m_bmap->deffender()->units().values().at(i));
        ug->setIsGeneral(false);
        QPair<int,int> tmpp;
        tmpp.first = m_bmap->size().x()-(i/m_bmap->size().y())-1;
        tmpp.second = i%m_bmap->size().y();
        ug->setFrame(this->frames().value(tmpp));
        ug->frame()->setUnitG(ug);
        ug->setBmapS(this);
        ug->setParentItem(ug->frame());
    }

}

void BMapScene::setframes(QMap<QPair<int, int>, BFrame *> frames)
{
    if (m_frames == frames)
        return;

    m_frames = frames;
    emit framesChanged(m_frames);
}

void BMapScene::setUnits(QList<UnitGraphics *> units)
{
    if (m_units == units)
        return;

    m_units = units;
    emit unitsChanged(m_units);
}

void BMapScene::setCurrentPlayer(Player *currentPlayer)
{
    if (m_currentPlayer == currentPlayer)
        return;

    m_currentPlayer = currentPlayer;
    emit currentPlayerChanged(m_currentPlayer);
}

void BMapScene::setPhase(BattlePhase phase)
{
    if (m_phase == phase)
        return;

    m_phase = phase;
    emit phaseChanged(m_phase);
}

void BMapScene::setSelectedFrame(BFrame *selectedFrame)
{
    if (m_selectedFrame == selectedFrame)
        return;

    m_selectedFrame = selectedFrame;
    emit selectedFrameChanged(m_selectedFrame);
}

void BMapScene::setTurnTimer(QDeadlineTimer *turnTimer)
{
    if (m_turnTimer == turnTimer)
        return;

    m_turnTimer = turnTimer;
    emit turnTimerChanged(m_turnTimer);
}

void BMapScene::setTurncount(int turncount)
{
    if (m_turncount == turncount)
        return;

    m_turncount = turncount;
    emit turncountChanged(m_turncount);
}

void BMapScene::setGeneralsToChooseA(int generalsToChooseA)
{
    if (m_generalsToChooseA == generalsToChooseA)
        return;

    m_generalsToChooseA = generalsToChooseA;
    emit generalsToChooseAChanged(m_generalsToChooseA);
}

void BMapScene::setGeneralsToChooseD(int generalsToChooseD)
{
    if (m_generalsToChooseD == generalsToChooseD)
        return;

    m_generalsToChooseD = generalsToChooseD;
    emit generalsToChooseDChanged(m_generalsToChooseD);
}

void BMapScene::setCurrentCityPlaying(City *currentCityPlaying)
{
    if (m_currentCityPlaying == currentCityPlaying)
        return;

    m_currentCityPlaying = currentCityPlaying;
    emit currentCityPlayingChanged(m_currentCityPlaying);
}


