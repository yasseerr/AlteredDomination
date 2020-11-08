#ifndef BATTLEAI_H
#define BATTLEAI_H

#include <QMap>
#include <QObject>
class BFrame;
class Player;
class BattleForm;
class City;
class Unit;
class BMapScene;
class UnitGraphics;
class BattleAI : public QObject
{
    Q_OBJECT
    Q_PROPERTY(BattleForm* battleForm READ battleForm WRITE setBattleForm NOTIFY battleFormChanged)
    Q_PROPERTY(BMapScene* scene READ scene WRITE setScene NOTIFY sceneChanged)
    Q_PROPERTY(Player* player READ player WRITE setPlayer NOTIFY playerChanged)
    Q_PROPERTY(City* city READ city WRITE setCity NOTIFY cityChanged)
    Q_PROPERTY(QMap<BFrame*,QStringList> dangerFrames READ dangerFrames WRITE setDangerFrames NOTIFY dangerFramesChanged)
    Q_PROPERTY(QMultiMap<BFrame*,BFrame*> availableAttacks READ availableAttacks WRITE setAvailableAttacks NOTIFY availableAttacksChanged)
    Q_PROPERTY(bool acceptOrProposeDraw READ acceptOrProposeDraw WRITE setAcceptOrProposeDraw NOTIFY acceptOrProposeDrawChanged)
    BattleForm* m_battleForm;
    Player* m_player;
    QMap<BFrame*,QStringList> m_dangerFrames;
    QMultiMap<BFrame*,BFrame*> m_availableAttacks;


    City* m_city;
    City *enemyCity;

    BMapScene* m_scene;

    bool m_acceptOrProposeDraw;

public:

    QList<QPair<BFrame*,BFrame*>> animationList;
    int animationCount;

    QList<BFrame*> toBeSurroundedFrames;
    QMultiMap<int,QPair<UnitGraphics*,BFrame*>> toSurroundMoves;
    QList<QPair<BFrame*,BFrame*>> forkMoves;
    QList<BFrame*> threatenedUnits;
    QList<QPair<BFrame*,BFrame*>> createThreatPossib;
    QMultiMap<int,QPair<BFrame*,BFrame*>> movesRating;

    explicit BattleAI(QObject *parent = nullptr);


    Q_INVOKABLE void placeUnits();
    void runAnimation();

    Q_INVOKABLE void selectGenerals();

    void playTurn();
    void detectSurroundingFrames();
    void detectDangerFrames();
    void studyDraw();
    void studySurrender();
    void detectThretenedUnits();
    void detectAttackOpportunities();
    void detectForkPossibilities();

    void buildStrategy();
    int findPathTogenerals(int layer,BFrame *f,Unit *u);

    bool hasTypeOfUnits(City *c,QString s);

    void applyMoves();

    QList<BFrame*> attackListForFrame(BFrame *f,Unit *u);
    QList<BFrame*> moveListForFrame(BFrame *f,Unit *u);
    bool isAffectedInFrame(BFrame *des,Unit *u);

    BattleForm* battleForm() const;
    Player* player() const;
    QMap<BFrame*,QStringList> dangerFrames() const;
    QMultiMap<BFrame*,BFrame*> availableAttacks() const;

    City* city() const;

    BMapScene* scene() const;

    bool acceptOrProposeDraw() const;

signals:

    void battleFormChanged(BattleForm* battleForm);
    void playerChanged(Player* player);
    void dangerFramesChanged(QMap<BFrame*,QStringList>dangerFrames);
    void availableAttacksChanged(QMultiMap<BFrame*,BFrame*> availableAttacks);

    void cityChanged(City* city);

    void sceneChanged(BMapScene* scene);

    void acceptOrProposeDrawChanged(bool acceptOrProposeDraw);

public slots:

    void setBattleForm(BattleForm* battleForm);
    void setPlayer(Player* player);
    void setDangerFrames(QMap<BFrame*,QStringList> dangerFrames);
    void setAvailableAttacks(QMultiMap<BFrame*,BFrame*> availableAttacks);
    void setCity(City* city);
    void setScene(BMapScene* scene);
    void setAcceptOrProposeDraw(bool acceptOrProposeDraw);
};

#endif // BATTLEAI_H
