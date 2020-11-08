#include "battleform.h"
#include "ui_battleform.h"

#include <AI/battleai.h>
#include <QPropertyAnimation>
#include <QQmlContext>
#include <domain/city.h>
#include <domain/country.h>
#include <domain/unit.h>
#include <graphics/bframe.h>
BattleForm::BattleForm(QTcpSocket *serv, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BattleForm),
    m_battleAI(new BattleAI(this)),
    m_serverSocket(serv)
{
    previousScale = 1;
    m_closeYet = false;
    m_isMultiplayer = false;
//    this->setWindowFlags(Qt::ToolTip);
    ui->setupUi(this);
    qmlRegisterType<BMapScene>();
    qmlRegisterType<BattleMap>();
    qmlRegisterType<BattleAI>();
    m_bScene = new BMapScene(m_serverSocket,this);
    ui->graphicsView->setScene(m_bScene);
    ui->battleMenu->rootContext()->setContextProperty("battleForm",this);

    connect(m_bScene,&BMapScene::battleEndedA,this,&BattleForm::onBattleEndedA);
    connect(m_bScene,&BMapScene::battleEndedD,this,&BattleForm::onBattleEndedD);
    connect(m_bScene,&BMapScene::setViewEnable,this,&BattleForm::setViewEnalble);
    connect(m_bScene,&BMapScene::bmapLoaded,this,&BattleForm::bmapLoaded);

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

bool BattleForm::isMultiplayer() const
{
    return m_isMultiplayer;
}

QTcpSocket *BattleForm::serverSocket() const
{
    return m_serverSocket;
}

bool BattleForm::isMassiveBattle() const
{
    return m_isMassiveBattle;
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
    /// removing the selected frame
    if(bScene()->selectedFrame() != nullptr){
        bScene()->selectedFrame()->setIsSeletedFrame(false);
        bScene()->setSelectedFrame(nullptr);
    }

    if(isMultiplayer()){
        if(bScene()->isOpponateReady()){
            bScene()->sendChangeStateMultiplayer("play");
            bScene()->setPhase(BMapScene::PLAYING);
            bScene()->setGeneralsToChooseA(bScene()->bmap()->attackerMoves());
            bScene()->setGeneralsToChooseD(bScene()->bmap()->deffenderMoves());
            bScene()->setCurrentCityPlaying(bScene()->bmap()->attacker());
            this->setWindowTitle(m_bScene->bmap()->attacker()->country()->name()+
                                 " VS "+m_bScene->bmap()->deffender()->country()->name());
            bScene()->setIsMeReady(false);
            bScene()->setIsOpponateReady(false);
        }
        else{
            setViewEnalble(false);
            bScene()->setIsMeReady(true);
            bScene()->sendChangeStateMultiplayer("play");
        }

    }else{
        bScene()->setPhase(BMapScene::PLAYING);
        bScene()->setGeneralsToChooseA(bScene()->bmap()->attackerMoves());
        bScene()->setGeneralsToChooseD(bScene()->bmap()->deffenderMoves());
        bScene()->setCurrentCityPlaying(bScene()->bmap()->attacker());
        this->setWindowTitle(m_bScene->bmap()->attacker()->country()->name()+" VS "+m_bScene->bmap()->deffender()->country()->name());
        if(bScene()->bmap()->attacker()->country()->player()->type() == PlayerType::AI)this->bScene()->battleAI()->playTurn();
    }
}

void BattleForm::surrender()
{

    if(this->bScene()->bmap()->attacker() == bScene()->currentCityPlaying()){

        bScene()->bmap()->setAttackerMoves(0);
        bScene()->frames().first()->checkWineLose();
//        this->onBattleEndedD();
        return;
    }else{
        bScene()->bmap()->setDeffenderMoves(0);
        bScene()->frames().first()->checkWineLose();
//        this->onBattleEndedA();
    }
}

void BattleForm::draw()
{
    this->onBattleEndedD();
}

void BattleForm::zoom(qreal z)
{
    ui->graphicsView->scale((1/previousScale)*z,(1/previousScale)*z);
    previousScale = z;
}

void BattleForm::setViewEnalble(bool b)
{
    ui->graphicsView->setEnabled(b);
}

void BattleForm::bmapLoaded(bool p)
{
    this->setIsMassiveBattle(p);
    emit bmapLoadedSig();

}

void BattleForm::fixScale()
{

//    qDebug()<<ui->graphicsView->width();
//    qDebug()<<bScene()->bmap()->size().y()*100;
//    qDebug()<<ui->graphicsView->height();
//    qDebug()<<bScene()->bmap()->size().x()*100;


    float bmapy = bScene()->bmap()->size().y()*100;
    float bmapx = bScene()->bmap()->size().x()*100;

    if(this->bScene()->bmap()->isMassiveBattle()){
//        float a = 1-((float)()/(float)ui->graphicsView->width());
//        float b = 1-((float)(bScene()->bmap()->size().x()*100 - ui->graphicsView->height())/(float)ui->graphicsView->height());
        float a =1/( bmapy/ (ui->graphicsView->width()+300) );
        float b =1/( bmapx/(ui->graphicsView->height()+300));
        ui->graphicsView->scale(qMin(a,b),qMin(a,b));

    }else{
        float a =1/( bmapy/( ui->graphicsView->height()+300) );
        float b =1/( bmapx/(ui->graphicsView->width()+300));
        ui->graphicsView->scale(qMin(a,b),qMin(a,b));
    }
}

void BattleForm::onBattleEndedA()
{
//    this->hide();
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
//    this->hide();
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

void BattleForm::setIsMultiplayer(bool isMultiplayer)
{
    if (m_isMultiplayer == isMultiplayer)
        return;

    m_isMultiplayer = isMultiplayer;
    this->bScene()->setIsMultiplayer(isMultiplayer);
    emit isMultiplayerChanged(m_isMultiplayer);
}

void BattleForm::setServerSocket(QTcpSocket *serverSocket)
{
    if (m_serverSocket == serverSocket)
        return;

    m_serverSocket = serverSocket;
    emit serverSocketChanged(m_serverSocket);
}

void BattleForm::setIsMassiveBattle(bool isMassiveBattle)
{
    if (m_isMassiveBattle == isMassiveBattle)
        return;

    m_isMassiveBattle = isMassiveBattle;

    foreach (BFrame* f, bScene()->frames().values()){

        if(isMassiveBattle) f->setPos(f->y()*100,f->x()*100);
        else f->setPos(f->x()*100,f->y()*100);

    }
    bScene()->bar1->setRect(isMassiveBattle?QRect(0,300,bScene()->bmap()->size().y()*100,4):
                                            QRect(300,0,4,bScene()->bmap()->size().y()*100));

    bScene()->bar2->setRect(isMassiveBattle? QRect(0,bScene()->bmap()->size().x()*100-300,bScene()->bmap()->size().y()*100,4):
                                             QRect(bScene()->bmap()->size().x()*100-300,0, 4,bScene()->bmap()->size().y()*100));

    bScene()->bmap()->setIsMassiveBattle(isMassiveBattle);
    bScene()->update();
    emit isMassiveBattleChanged(m_isMassiveBattle);
}

void BattleForm::setPromote()
{
    if(isMultiplayer()){
        bScene()->setIsMeReady(true);
        bScene()->sendChangeStateMultiplayer("promote");
        if(!bScene()->isOpponateReady())ui->graphicsView->setEnabled(false);
        else{
            bScene()->setPhase(BMapScene::PROMOTING);
            ui->graphicsView->setEnabled(true);
            bScene()->setIsMeReady(false);
            bScene()->setIsOpponateReady(false);
        }

    }else{
        m_battleAI->animationList.clear();
        m_battleAI->runAnimation();
    }

}
