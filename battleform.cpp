#include "battleform.h"
#include "ui_battleform.h"

#include <QQmlContext>
#include <domain/city.h>
#include <domain/country.h>
#include <domain/unit.h>
BattleForm::BattleForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BattleForm)
{
//    this->setWindowFlags(Qt::ToolTip);
    ui->setupUi(this);
    qmlRegisterType<BMapScene>();
    qmlRegisterType<BattleMap>();
    m_bScene = new BMapScene(this);
    ui->graphicsView->setScene(m_bScene);
    ui->battleMenu->rootContext()->setContextProperty("battleForm",this);

    connect(m_bScene,&BMapScene::battleEndedA,this,&BattleForm::onBattleEndedA);
    connect(m_bScene,&BMapScene::battleEndedD,this,&BattleForm::onBattleEndedD);
}

BattleForm::~BattleForm()
{
    delete ui;
}

BMapScene *BattleForm::bScene() const
{
    return m_bScene;
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
}

void BattleForm::surrender()
{
    if(this->bScene()->bmap()->attacker()->country()->player() == bScene()->currentPlayer()){
        return;
    }else{
        this->bScene()->bmap()->deffender()->units().clear();
        this->bScene()->bmap()->deffender()->setCountry(this->bScene()->bmap()->attacker()->country());
    }
}

void BattleForm::onBattleEndedA()
{
    foreach (Unit *u, this->bScene()->bmap()->deffender()->units()) {
        this->bScene()->bmap()->deffender()->removeUnit(u->id());
    }
    this->bScene()->bmap()->deffender()->country()->cities().removeOne(bScene()->bmap()->deffender());
    this->bScene()->bmap()->deffender()->setCountry(this->bScene()->bmap()->attacker()->country());
    this->bScene()->bmap()->attacker()->country()->addCity(this->bScene()->bmap()->deffender());
    foreach (Unit *u, bScene()->bmap()->attacker()->units()) {
        bScene()->bmap()->deffender()->addUnit(u);
        bScene()->bmap()->attacker()->removeUnit(u->id());
    }
    this->bScene()->bmap()->attacker()->country()->setIncome(this->bScene()->bmap()->attacker()->country()->income()+
                                                             this->bScene()->bmap()->deffender()->income());
    emit this->battleEndedA();
    emit this->battleEnded();

}

void BattleForm::onBattleEndedD()
{
    emit this->battleEnded();
}

void BattleForm::setPromote()
{
    bScene()->setPhase(BattlePhase::PROMOTING);
}
