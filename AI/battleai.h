#ifndef BATTLEAI_H
#define BATTLEAI_H

#include <QMap>
#include <QObject>
class BFrame;
class Player;
class BattleForm;
class City;
class BMapScene;
class BattleAI : public QObject
{
    Q_OBJECT
    Q_PROPERTY(BattleForm* battleForm READ battleForm WRITE setBattleForm NOTIFY battleFormChanged)
    Q_PROPERTY(BMapScene* scene READ scene WRITE setScene NOTIFY sceneChanged)
    Q_PROPERTY(Player* player READ player WRITE setPlayer NOTIFY playerChanged)
    Q_PROPERTY(City* city READ city WRITE setCity NOTIFY cityChanged)
    Q_PROPERTY(QMap<QString,QList<BFrame*>> dangerFrames READ dangerFrames WRITE setDangerFrames NOTIFY dangerFramesChanged)
    Q_PROPERTY(QMap<BFrame*,BFrame*> availableAttacks READ availableAttacks WRITE setAvailableAttacks NOTIFY availableAttacksChanged)

    BattleForm* m_battleForm;
    Player* m_player;
    QMap<QString,QList<BFrame*>> m_dangerFrames;
    QMap<BFrame*,BFrame*> m_availableAttacks;


    City* m_city;

    BMapScene* m_scene;

public:


    QList<QPair<BFrame*,BFrame*>> animationList;
    int animationCount;

    explicit BattleAI(QObject *parent = nullptr);


    Q_INVOKABLE void placeUnits();
    void runAnimation();

    Q_INVOKABLE void selectGenerals();


    BattleForm* battleForm() const;
    Player* player() const;
    QMap<QString,QList<BFrame*>> dangerFrames() const;
    QMap<BFrame*,BFrame*> availableAttacks() const;

    City* city() const;

    BMapScene* scene() const;

signals:

    void battleFormChanged(BattleForm* battleForm);
    void playerChanged(Player* player);
    void dangerFramesChanged(QMap<QString,QList<BFrame*>> dangerFrames);
    void availableAttacksChanged(QMap<BFrame*,BFrame*> availableAttacks);

    void cityChanged(City* city);

    void sceneChanged(BMapScene* scene);

public slots:

    void setBattleForm(BattleForm* battleForm);
    void setPlayer(Player* player);
    void setDangerFrames(QMap<QString,QList<BFrame*>> dangerFrames);
    void setAvailableAttacks(QMap<BFrame*,BFrame*> availableAttacks);
    void setCity(City* city);
    void setScene(BMapScene* scene);
};

#endif // BATTLEAI_H
