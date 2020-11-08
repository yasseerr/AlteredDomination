#ifndef BMAPSCENE_H
#define BMAPSCENE_H



#include "animationhandlerbattle.h"
#include "battleborderitem.h"

#include<QDeadlineTimer>
#include <QGraphicsScene>
#include <QObject>
#include <QQuickView>
#include <QQuickWidget>
#include <domain/battlemap.h>
#include <domain/player.h>
#include <domain/unit.h>

#include<graphics/animations.h>
#include <QGraphicsSvgItem>
#include <QSvgRenderer>
#include<QTcpSocket>

#include <graphics/unitpupup.h>

class BFrame;
class UnitGraphics;
class BattleAI;



//enum BattlePhase{

//    STARTING,PLACING,PROMOTING,PLAYING
//};

class BMapScene :  public QGraphicsScene
{
    Q_OBJECT

    Q_PROPERTY(BattleMap* bmap READ bmap WRITE setBmap NOTIFY bmapChanged)
    Q_PROPERTY(QMap<QPair<int,int>,BFrame*> frames READ frames WRITE setframes NOTIFY framesChanged)
    Q_PROPERTY(QMap<Unit*,UnitGraphics*> units READ units WRITE setUnits NOTIFY unitsChanged)
    Q_PROPERTY(Player* currentPlayer READ currentPlayer WRITE setCurrentPlayer NOTIFY currentPlayerChanged)
    Q_PROPERTY(City* currentCityPlaying READ currentCityPlaying WRITE setCurrentCityPlaying NOTIFY currentCityPlayingChanged)
    Q_PROPERTY(BMapScene::BattlePhase phase READ phase WRITE setPhase NOTIFY phaseChanged)
    Q_PROPERTY(BFrame* selectedFrame READ selectedFrame WRITE setSelectedFrame NOTIFY selectedFrameChanged)
    Q_PROPERTY(QDeadlineTimer* turnTimer READ turnTimer WRITE setTurnTimer NOTIFY turnTimerChanged)
    Q_PROPERTY(int turncount READ turncount WRITE setTurncount NOTIFY turncountChanged)
    Q_PROPERTY(int  generalsToChooseA READ generalsToChooseA WRITE setGeneralsToChooseA NOTIFY generalsToChooseAChanged)
    Q_PROPERTY(int generalsToChooseD READ generalsToChooseD WRITE setGeneralsToChooseD NOTIFY generalsToChooseDChanged)
    Q_PROPERTY(BattleAI* battleAI READ battleAI WRITE setBattleAI NOTIFY battleAIChanged)
    Q_PROPERTY(bool isMultiplayer READ isMultiplayer WRITE setIsMultiplayer NOTIFY isMultiplayerChanged)
    Q_PROPERTY(QTcpSocket* serverSocket READ serverSocket WRITE setServerSocket NOTIFY serverSocketChanged)
    Q_PROPERTY(bool isOpponateReady READ isOpponateReady WRITE setIsOpponateReady NOTIFY isOpponateReadyChanged)
    Q_PROPERTY(bool isMeReady READ isMeReady WRITE setIsMeReady NOTIFY isMeReadyChanged)


    BattleMap* m_bmap;



    QMap<QPair<int,int>,BFrame*> m_frames;

    QMap<Unit*,UnitGraphics*> m_units;

    Player* m_currentPlayer;

    BFrame* m_selectedFrame;

    QDeadlineTimer* m_turnTimer;

    int m_turncount;

    int m_generalsToChooseA;

    int m_generalsToChooseD;

    City* m_currentCityPlaying;

    BattleAI* m_battleAI;



    bool m_isMultiplayer;

    QTcpSocket* m_serverSocket;

    bool m_isOpponateReady;

    bool m_isMeReady;

public:

    enum BattlePhase{

        STARTING,PLACING,PROMOTING,PLAYING
    };

    Q_ENUM(BattlePhase)

    BMapScene::BattlePhase m_phase;

    Animations *animItem;

    QList<BFrame*> previousFramesThisTurn;
    QList<BFrame*> previousFramesLastTurn;

    AnimationHandlerBattle *animHandler;

    QGraphicsRectItem *bar1;
    QGraphicsRectItem *bar2;

    ///unit resrc
    unitPupUp *unitPP;
    QSvgRenderer *unitRend;
    BattleBorderItem *borderItem;
    QImage *unitClip;

    explicit BMapScene(QTcpSocket *serv = nullptr,QObject *parent = nullptr);


    void removeUnitG(Unit *u);

    bool thereIsAnimationRunning;

    BattleMap* bmap() const;

    QMap<QPair<int,int>,BFrame*> frames() const;

    QMap<Unit*,UnitGraphics*> units() const;

    Player* currentPlayer() const;

    BMapScene::BattlePhase phase() const;

    BFrame* selectedFrame() const;

    QDeadlineTimer* turnTimer() const;

    int turncount() const;

    int generalsToChooseA() const;

    int generalsToChooseD() const;


    void cheCkEndTurn();
    void zoomIN();
    void zoomOUT();


    void sendChangeInPos(BFrame *framDep,BFrame *framDes);
    void sendChangeStateMultiplayer(QString st);
    void sendPromote(BFrame *fr,int unset);


    City* currentCityPlaying() const;

    BattleAI* battleAI() const;

    bool isMultiplayer() const;

    QTcpSocket* serverSocket() const;

    bool isOpponateReady() const;

    bool isMeReady() const;

signals:

    void bmapChanged(BattleMap* bmap);

    void framesChanged(QMap<QPair<int,int>,BFrame*> frames);

    void unitsChanged(QMap<Unit*,UnitGraphics*> units);

    void currentPlayerChanged(Player* currentPlayer);

    void phaseChanged(BMapScene::BattlePhase phase);

    void selectedFrameChanged(BFrame* selectedFrame);

    void turnTimerChanged(QDeadlineTimer* turnTimer);

    void turncountChanged(int turncount);

    void generalsToChooseAChanged(int generalsToChooseA);

    void generalsToChooseDChanged(int generalsToChooseD);

    void currentCityPlayingChanged(City* currentCityPlaying);

    void battleEndedA();
    void battleEndedD();
    void setViewEnable(bool isE);
    void bmapLoaded(bool p);

    void battleAIChanged(BattleAI* battleAI);

    void isMultiplayerChanged(bool isMultiplayer);

    void serverSocketChanged(QTcpSocket* serverSocket);

    void isOpponateReadyChanged(bool isOpponateReady);

    void isMeReadyChanged(bool isMeReady);

public slots:
    void setBmap(BattleMap* bmap);
    void setframes(QMap<QPair<int,int>,BFrame*> frames);
    void setUnits(QMap<Unit*,UnitGraphics*> units);
    void setCurrentPlayer(Player* currentPlayer);
    void setPhase(BMapScene::BattlePhase phase);
    void setSelectedFrame(BFrame* selectedFrame);
    void setTurnTimer(QDeadlineTimer* turnTimer);
    void setTurncount(int turncount);
    void setGeneralsToChooseA(int generalsToChooseA);
    void setGeneralsToChooseD(int generalsToChooseD);
    void setCurrentCityPlaying(City* currentCityPlaying);
    void setBattleAI(BattleAI* battleAI);
    void setIsMultiplayer(bool isMultiplayer);
    void setServerSocket(QTcpSocket* serverSocket);
    void setIsOpponateReady(bool isOpponateReady);
    void setIsMeReady(bool isMeReady);
};

#endif // BMAPSCENE_H
