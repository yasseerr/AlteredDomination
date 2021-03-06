#include "bframe.h"
#include "bmapscene.h"
#include "unitgraphics.h"

#include <domain/city.h>
#include <domain/country.h>

#include <AI/battleai.h>

#include <QGraphicsProxyWidget>
#include <QJsonDocument>
#include <QPalette>
#include <battleform.h>

BMapScene::BMapScene(QTcpSocket *serv, QObject *parent) : QGraphicsScene(parent),
    m_serverSocket(serv),
    m_bmap(nullptr),
    m_currentPlayer(nullptr),
    m_phase(BMapScene::BattlePhase::STARTING),
    m_selectedFrame(nullptr),
    m_turnTimer(new QDeadlineTimer()),
    m_turncount(0),
    animItem(new Animations(this)),
    m_isMultiplayer(false),
    m_isOpponateReady(false),
    m_isMeReady(false)
{
    thereIsAnimationRunning =false;
    setBackgroundBrush(QPixmap(":/data/mapBG14.jpg"));
    animItem->setZValue(10);
    this->addItem(animItem);
    QSound *s= new QSound(":/data/sounds/introbattle.wav");
    s->play();

    animHandler = new AnimationHandlerBattle(this,this);
    unitRend = new QSvgRenderer(QString(":/data/units/unitdisplay.svg"));

    unitClip = new QImage(":/data/icons/frame.png");


    unitPP = new unitPupUp();
    unitPP->setZValue(100);
    this->addItem(unitPP);

    borderItem = new  BattleBorderItem();
    borderItem->scene = this;
    this->addItem(borderItem);

}

void BMapScene::removeUnitG(Unit *u)
{
    m_units.remove(u);
}

BattleMap *BMapScene::bmap() const
{
    return m_bmap;
}


QMap<QPair<int, int>, BFrame *> BMapScene::frames() const
{
    return m_frames;
}

QMap<Unit*,UnitGraphics *> BMapScene::units() const
{
    return m_units;
}

Player *BMapScene::currentPlayer() const
{
    return m_currentPlayer;
}

BMapScene::BattlePhase BMapScene::phase() const
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
            this->setTurncount(turncount()+1);
            this->setGeneralsToChooseD(bmap()->deffenderMoves());
            this->setCurrentCityPlaying(this->bmap()->deffender());
            foreach (Unit *u, bmap()->deffender()->units()) {
                u->setUsed(false);
            }
            foreach (BFrame* f, this->previousFramesLastTurn) {
                f->cancelSelected();
                f->setIsPrevious(false);
                previousFramesLastTurn.removeOne(f);
            }
            foreach (BFrame* f, this->previousFramesThisTurn) {
                f->setIsActualMove(false);
                f->setIsPrevious(true);
                previousFramesLastTurn.append(f);
                previousFramesThisTurn.removeOne(f);
            }
            if(m_currentCityPlaying->country()->player()->type() == PlayerType::AI){
                m_battleAI->playTurn();
            }

        }
    }else if (this->currentCityPlaying() == m_bmap->deffender()) {
        this->setGeneralsToChooseD(generalsToChooseD()-1);
        if(this->generalsToChooseD() == 0){
            this->setGeneralsToChooseA(bmap()->attackerMoves());
            this->setCurrentCityPlaying(this->bmap()->attacker());
            foreach (Unit *u, bmap()->attacker()->units()) {
                u->setUsed(false);
            }
            foreach (BFrame* f, this->previousFramesLastTurn) {
                f->cancelSelected();
                f->setIsPrevious(false);
                previousFramesLastTurn.removeOne(f);
            }
            foreach (BFrame* f, this->previousFramesThisTurn) {
                f->setIsActualMove(false);
                f->setIsPrevious(true);
                previousFramesLastTurn.append(f);
                previousFramesThisTurn.removeOne(f);
            }
            if(m_currentCityPlaying->country()->player()->type() == PlayerType::AI){
                m_battleAI->playTurn();
            }


        }
    }
    if(this->currentCityPlaying()->country()->player()->type() == PlayerType::HUMAIN)emit setViewEnable(true);
    else emit setViewEnable(false);
}

void BMapScene::sendChangeInPos(BFrame *framDep, BFrame *framDes)
{
    QVariantMap messageVariant;
    messageVariant.insert("code",6);
    messageVariant.insert("x1",framDep->x());
    messageVariant.insert("y1",framDep->y());
    messageVariant.insert("x2",framDes->x());
    messageVariant.insert("y2",framDes->y());
    QJsonDocument doc = QJsonDocument::fromVariant(messageVariant);

    QByteArray dataToSend;
    QDataStream outData(&dataToSend,QIODevice::WriteOnly);
    outData << (quint16) doc.toJson().size();
    dataToSend.append(doc.toJson());
    m_serverSocket->write(dataToSend);
}

void BMapScene::sendChangeStateMultiplayer(QString st)
{
    QVariantMap messageVariant;
    messageVariant.insert("code",7);
    messageVariant.insert("stat",st);
    QJsonDocument doc = QJsonDocument::fromVariant(messageVariant);

    QByteArray dataToSend;
    QDataStream outData(&dataToSend,QIODevice::WriteOnly);
    outData << (quint16) doc.toJson().size();
    dataToSend.append(doc.toJson());
    m_serverSocket->write(dataToSend);

}

void BMapScene::sendPromote(BFrame *fr,int unset)
{
    QVariantMap messageVariant;
    messageVariant.insert("code",8);
    messageVariant.insert("x",fr->x());
    messageVariant.insert("y",fr->y());
    messageVariant.insert("unset",unset);
    QJsonDocument doc = QJsonDocument::fromVariant(messageVariant);

    QByteArray dataToSend;
    QDataStream outData(&dataToSend,QIODevice::WriteOnly);
    outData << (quint16) doc.toJson().size();
    dataToSend.append(doc.toJson());
    m_serverSocket->write(dataToSend);

}


City *BMapScene::currentCityPlaying() const
{
    return m_currentCityPlaying;
}

BattleAI *BMapScene::battleAI() const
{
    return m_battleAI;
}

bool BMapScene::isMultiplayer() const
{
    return m_isMultiplayer;
}

QTcpSocket *BMapScene::serverSocket() const
{
    return m_serverSocket;
}

bool BMapScene::isOpponateReady() const
{
    return m_isOpponateReady;
}

bool BMapScene::isMeReady() const
{
    return m_isMeReady;
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
            bf->setPos(j*100,i*100);
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
        m_units.insert(ug->unit(),ug);
        ug->setIsGeneral(false);
        QPair<int,int> tmpp;
        tmpp.first = i/m_bmap->size().y();
        tmpp.second = i%m_bmap->size().y();
        ug->setFrame(this->frames().value(tmpp));
        ug->frame()->setUnitG(ug);
        ug->setParentItem(ug->frame());
        ug->setBmapS(this);
        ug->unitRend = this->unitRend;
    }
    for (int i = 0; i < m_bmap->deffender()->units().size(); ++i) {
        UnitGraphics *ug = new UnitGraphics(this);
        ug->setUnit(m_bmap->deffender()->units().values().at(i));
        m_units.insert(ug->unit(),ug);
        ug->setIsGeneral(false);
        QPair<int,int> tmpp;
        tmpp.first = m_bmap->size().x()-(i/m_bmap->size().y())-1;
        tmpp.second = i%m_bmap->size().y();
        ug->setFrame(this->frames().value(tmpp));
        ug->frame()->setUnitG(ug);
        ug->setBmapS(this);
        ug->setParentItem(ug->frame());
        ug->unitRend = this->unitRend;
    }

    bar1 = bmap->isMassiveBattle()?new QGraphicsRectItem(0,300,bmap->size().y()*100,4):
                                   new QGraphicsRectItem(300,0,4,bmap->size().y()*100);
    bar1->setBrush(bmap->attacker()->country()->color());
    bar1->setZValue(10);
    bar2 = bmap->isMassiveBattle()?new QGraphicsRectItem(0,bmap->size().x()*100-300, bmap->size().y()*100,4):
                                   new QGraphicsRectItem(bmap->size().x()*100-300,0, 4,bmap->size().y()*100);
    bar2->setBrush(bmap->deffender()->country()->color());
    bar2->setZValue(10);
    this->addItem(bar1);
    this->addItem(bar2);

    /// the user start first if its against an AI


    if(bmap->attacker()->country()->player()->type() == PlayerType::AI||
       bmap->deffender()->country()->player()->type() == PlayerType::AI)
        this->setCurrentCityPlaying(bmap->attacker()->country()->player()->type() == PlayerType::AI?bmap->deffender():bmap->attacker()) ;


    /// the AI
    if(m_bmap->attacker()->country()->player()->type() == PlayerType::AI){
        this->battleAI()->setPlayer(m_bmap->attacker()->country()->player());
        this->battleAI()->setCity(m_bmap->attacker());
    }else if(m_bmap->deffender()->country()->player()->type() == PlayerType::AI){
        this->battleAI()->setPlayer(m_bmap->deffender()->country()->player());
        this->battleAI()->setCity(m_bmap->deffender());
    }

    borderItem->mapWidth = bmap->size().x() *100;
    borderItem->mapHeight = bmap->size().y() *100;

    emit bmapLoaded(bmap->isMassiveBattle());
    /// the result ui


}

void BMapScene::setframes(QMap<QPair<int, int>, BFrame *> frames)
{
    if (m_frames == frames)
        return;

    m_frames = frames;
    emit framesChanged(m_frames);
}

void BMapScene::setUnits(QMap<Unit*,UnitGraphics *> units)
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

void BMapScene::setPhase(BMapScene::BattlePhase phase)
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

    qDebug()<<currentCityPlaying->name() << "isPlaying";
    m_currentCityPlaying = currentCityPlaying;
    emit currentCityPlayingChanged(m_currentCityPlaying);
}

void BMapScene::setBattleAI(BattleAI *battleAI)
{
    if (m_battleAI == battleAI)
        return;

    m_battleAI = battleAI;
    emit battleAIChanged(m_battleAI);
}

void BMapScene::setIsMultiplayer(bool isMultiplayer)
{
    if (m_isMultiplayer == isMultiplayer)
        return;

    m_isMultiplayer = isMultiplayer;
    emit isMultiplayerChanged(m_isMultiplayer);
}

void BMapScene::setServerSocket(QTcpSocket *serverSocket)
{
    if (m_serverSocket == serverSocket)
        return;

    m_serverSocket = serverSocket;
    emit serverSocketChanged(m_serverSocket);
}

void BMapScene::setIsOpponateReady(bool isOpponateReady)
{
    if (m_isOpponateReady == isOpponateReady)
        return;

    m_isOpponateReady = isOpponateReady;
    emit isOpponateReadyChanged(m_isOpponateReady);
}

void BMapScene::setIsMeReady(bool isMeReady)
{
    if (m_isMeReady == isMeReady)
        return;
    m_isMeReady = isMeReady;
    emit isMeReadyChanged(m_isMeReady);
}


