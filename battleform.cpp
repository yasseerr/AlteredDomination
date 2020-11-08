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
    m_closeYet = false;
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

    /// the battle result
    battleResultUI = new QQuickView();
    battleResultUI->setTransientParent(this->windowHandle());
    battleResultUI->setModality(Qt::WindowModal);
    battleResultUI->setColor(Qt::transparent);
    battleResultUI->setFlag(Qt::ToolTip);
    battleResultUI->setSource(QUrl("qrc:/scripts/BattleResult.qml"));
//    battleResultUI->show();


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

QString BattleForm::resultText() const
{
    return m_resultText;
}

bool BattleForm::closeYet() const
{
    return m_closeYet;
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

    /// the result ui
    battleResultUI->rootContext()->setContextProperty("attacker",bScene()->bmap()->attacker());
    battleResultUI->rootContext()->setContextProperty("deffender",bScene()->bmap()->deffender());
    battleResultUI->rootContext()->setContextProperty("bform",this);
    battleResultUI->rootContext()->setContextProperty("battleResultUI",battleResultUI);

    m_bScene->setPhase(BMapScene::PLACING);
}

void BattleForm::play()
{
    bScene()->setPhase(BMapScene::PLAYING);
    bScene()->setGeneralsToChooseA(bScene()->bmap()->attackerMoves());
    bScene()->setGeneralsToChooseD(bScene()->bmap()->deffenderMoves());
    bScene()->setCurrentCityPlaying(bScene()->bmap()->attacker());
    this->setWindowTitle(m_bScene->bmap()->attacker()->country()->name()+" VS "+m_bScene->bmap()->deffender()->country()->name());
    if(bScene()->bmap()->attacker()->country()->player()->type() == PlayerType::AI)this->bScene()->battleAI()->playTurn();
}

void BattleForm::surrender()
{

    if(this->bScene()->bmap()->attacker() == bScene()->currentCityPlaying()){

        this->onBattleEndedD();
        return;
    }else{

        this->onBattleEndedA();
    }
}

void BattleForm::draw()
{
    this->onBattleEndedD();
}

void BattleForm::onBattleEndedA()
{
    this->hide();
    battleResultUI->show();
    if(bScene()->bmap()->attacker()->country()->player() == this->bScene()->currentPlayer())
        this->setResultText("Congratulation You toke over "+bScene()->bmap()->deffender()->name()+", Nice Fight");
    else this->setResultText(" oooooooh! You lost it Man, "+bScene()->bmap()->deffender()->name()+" is gone ");
    while(!m_closeYet)QCoreApplication::processEvents();

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
    this->hide();
    battleResultUI->show();
    if(bScene()->bmap()->attacker()->country()->player() == this->bScene()->currentPlayer())
        this->setResultText("You couldn't take "+bScene()->bmap()->deffender()->name()+",maby next time!");
    else this->setResultText(" hohoho! You cruched them  "+bScene()->bmap()->deffender()->name()+" is and always will be yours" );
    while(!m_closeYet)QCoreApplication::processEvents();
    emit this->battleEnded();
}

void BattleForm::setBattleAI(BattleAI *battleAI)
{
    if (m_battleAI == battleAI)
        return;

    m_battleAI = battleAI;
    emit battleAIChanged(m_battleAI);
}

void BattleForm::setResultText(QString resultText)
{
    if (m_resultText == resultText)
        return;

    m_resultText = resultText;
    emit resultTextChanged(m_resultText);
}

void BattleForm::setCloseYet(bool closeYet)
{
    if (m_closeYet == closeYet)
        return;

    m_closeYet = closeYet;
    emit closeYetChanged(m_closeYet);
}

void BattleForm::setPromote()
{
    m_battleAI->animationList.clear();
    m_battleAI->runAnimation();
}
