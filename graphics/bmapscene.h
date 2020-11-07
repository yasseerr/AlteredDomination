#ifndef BMAPSCENE_H
#define BMAPSCENE_H



#include<QDeadlineTimer>
#include <QGraphicsScene>
#include <QObject>
#include <domain/battlemap.h>
#include <domain/player.h>

class BFrame;
class UnitGraphics;

enum BattlePhase{

    STARTING,PLACING,PROMOTING,PLAYING
};



class BMapScene :  public QGraphicsScene
{
    Q_OBJECT
    Q_PROPERTY(BattleMap* bmap READ bmap WRITE setBmap NOTIFY bmapChanged)
    Q_PROPERTY(QMap<QPair<int,int>,BFrame*> frames READ frames WRITE setframes NOTIFY framesChanged)
    Q_PROPERTY(QList<UnitGraphics*> units READ units WRITE setUnits NOTIFY unitsChanged)
    Q_PROPERTY(Player* currentPlayer READ currentPlayer WRITE setCurrentPlayer NOTIFY currentPlayerChanged)
    Q_PROPERTY(City* currentCityPlaying READ currentCityPlaying WRITE setCurrentCityPlaying NOTIFY currentCityPlayingChanged)
    Q_PROPERTY(BattlePhase phase READ phase WRITE setPhase NOTIFY phaseChanged)
    Q_PROPERTY(BFrame* selectedFrame READ selectedFrame WRITE setSelectedFrame NOTIFY selectedFrameChanged)
    Q_PROPERTY(QDeadlineTimer* turnTimer READ turnTimer WRITE setTurnTimer NOTIFY turnTimerChanged)
    Q_PROPERTY(int turncount READ turncount WRITE setTurncount NOTIFY turncountChanged)
    Q_PROPERTY(int  generalsToChooseA READ generalsToChooseA WRITE setGeneralsToChooseA NOTIFY generalsToChooseAChanged)
    Q_PROPERTY(int generalsToChooseD READ generalsToChooseD WRITE setGeneralsToChooseD NOTIFY generalsToChooseDChanged)

    BattleMap* m_bmap;

    QMap<QPair<int,int>,BFrame*> m_frames;

    QList<UnitGraphics*> m_units;

    Player* m_currentPlayer;

    BattlePhase m_phase;

    BFrame* m_selectedFrame;

    QDeadlineTimer* m_turnTimer;

    int m_turncount;

    int m_generalsToChooseA;

    int m_generalsToChooseD;

    City* m_currentCityPlaying;

public:
    explicit BMapScene(QObject *parent = nullptr);

    BattleMap* bmap() const;

    QMap<QPair<int,int>,BFrame*> frames() const;

    QList<UnitGraphics*> units() const;

    Player* currentPlayer() const;

    BattlePhase phase() const;

    BFrame* selectedFrame() const;

    QDeadlineTimer* turnTimer() const;

    int turncount() const;

    int generalsToChooseA() const;

    int generalsToChooseD() const;


    void cheCkEndTurn();

    City* currentCityPlaying() const;

signals:

    void bmapChanged(BattleMap* bmap);

    void framesChanged(QMap<QPair<int,int>,BFrame*> frames);

    void unitsChanged(QList<UnitGraphics*> units);

    void currentPlayerChanged(Player* currentPlayer);

    void phaseChanged(BattlePhase phase);

    void selectedFrameChanged(BFrame* selectedFrame);

    void turnTimerChanged(QDeadlineTimer* turnTimer);

    void turncountChanged(int turncount);

    void generalsToChooseAChanged(int generalsToChooseA);

    void generalsToChooseDChanged(int generalsToChooseD);

    void currentCityPlayingChanged(City* currentCityPlaying);

    void battleEndedA();
    void battleEndedD();

public slots:
    void setBmap(BattleMap* bmap);
    void setframes(QMap<QPair<int,int>,BFrame*> frames);
    void setUnits(QList<UnitGraphics*> units);
    void setCurrentPlayer(Player* currentPlayer);
    void setPhase(BattlePhase phase);
    void setSelectedFrame(BFrame* selectedFrame);
    void setTurnTimer(QDeadlineTimer* turnTimer);
    void setTurncount(int turncount);
    void setGeneralsToChooseA(int generalsToChooseA);
    void setGeneralsToChooseD(int generalsToChooseD);
    void setCurrentCityPlaying(City* currentCityPlaying);
};

#endif // BMAPSCENE_H
