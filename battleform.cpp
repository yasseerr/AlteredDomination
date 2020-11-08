#include "battleform.h"
#include "ui_battleform.h"

#include <AI/battleai.h>
#include <QPropertyAnimation>
#include <QQmlContext>
#include <domain/city.h>
#include <domain/country.h>
#include <domain/unit.h>
BattleForm::BattleForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BattleForm),
    m_battleAI(new BattleAI(this))
{
//    this->setWindowFlags(Qt::ToolTip);
    ui->setupUi(this);
    qmlRegisterType<BMapScene>();
    qmlRegisterType<BattleMap>();
    qmlRegisterType<BattleAI>();
    m_bScene = new BMapScene(this);
    ui->graphicsView->setScene(m_bScene);
    ui->battleMenu->rootContext()->setContextProperty("battleForm",this);

    connect(m_bScene,&BMapScene::battleEndedA,this,&BattleForm::onBattleEndedA);
    connect(m_bScene,&BMapScene::battleEndedD,this,&BattleForm::onBattleEndedD);


    this->setWindowTitle("Let the battle begin ...");
    /// the battle Ai stuff
    this->m_battleAI->setBattleForm(this);
    m_bScene->setBattleAI(this->battleAI());
    m_battleAI->setScene(m_bScene);


}

BattleForm::~BattleForm()
{
    delete ui;
}

BMapScene *BattleForm::bScene() const
{
    return m_bScene;
}

BattleAI *BattleForm::battleAI() const
{
    return m_battleAI;
}

void BattleForm::setBScene(BMapScene *bScene)
{
    if (m_bScene == bScene)
        return;

    m_bScene = bScene;
    emit bSceneChanged(m_bScene);
}

void BattleForm::publishMaptoQMl()
{
    ui->battleMenu->rootContext()->setContextProperty("attacker",bScene()->bmap()->attacker());
    ui->battleMenu->rootContext()->setContextProperty("deffender",bScene()->bmap()->deffender());
    ui->battleMenu->rootContext()->setContextProperty("bscene",m_bScene);
    m_bScene->setPhase(BattlePhase::PLACING);
}

void BattleForm::play()
{
    bScene()->setPhase(BattlePhase::PLAYING);
    bScene()->setGeneralsToChooseA(bScene()->bmap()->attackerMoves());
    bScene()->setGeneralsToChooseD(bScene()->bmap()->deffenderMoves());
    bScene()->setCurrentCityPlaying(bScene()->bmap()->attacker());
    this->setWindowTitle(m_bScene->bmap()->attacker()->country()->name()+" VS "+m_bScene->bmap()->deffender()->country()->name());
}

void BattleForm::surrender()
{
    if(this->bScene()->bmap()->attacker()->country()->player() == bScene()->currentPlayer()){
        return;
    }else{
        this->onBattleEndedA();
    }
}

void BattleForm::onBattleEndedA()
{
    foreach (Unit *u, this->bScene()->bmap()->deffender()->units()) {
        this->bScene()->bmap()->deffender()->removeUnit(u->id());
    }
    this->bScene()->bmap()->deffender()->country()->removeCity(bScene()->bmap()->deffender());
    this->bScene()->bmap()->deffender()->setCountry(this->bScene()->bmap()->attacker()->country());
    this->bScene()->bmap()->attacker()->country()->addCity(this->bScene()->bmap()->deffender());
    foreach (Unit *u, bScene()->bmap()->attacker()->units()) {
        bScene()->bmap()->deffender()->addUnit(u);
        bScene()->bmap()->attacker()->removeUnit(u->id());
    }

    emit this->battleEndedA();
    emit this->battleEnded();

}

void BattleForm::onBattleEndedD()
{
    emit this->battleEnded();
}

void BattleForm::setBattleAI(BattleAI *battleAI)
{
    if (m_battleAI == battleAI)
        return;

    m_battleAI = battleAI;
    emit battleAIChanged(m_battleAI);
}

void BattleForm::setPromote()
{
    m_battleAI->animationList.clear();
}
