#ifndef MAPAI_H
#define MAPAI_H

#include <QMap>
#include <QObject>

#include <domain/country.h>


class MapView;
class Player;
class City;
class MapAI : public QObject
{
    Q_OBJECT
    Q_PROPERTY(MapView* mapView READ mapView WRITE setMapView NOTIFY mapViewChanged)
    Q_PROPERTY(Player* player READ player WRITE setPlayer NOTIFY playerChanged)
    Q_PROPERTY(QMap<City*,int> treats READ treats WRITE setTreats NOTIFY treatsChanged)
    Q_PROPERTY(QMap<City*,QStringList> unitsToBuy READ unitsToBuy WRITE setUnitsToBuy NOTIFY unitsToBuyChanged)
    Q_PROPERTY(int totalthreat READ totalthreat WRITE setTotalthreat NOTIFY totalthreatChanged)
    Q_PROPERTY(QMap<QString,int> widrawVector READ widrawVector WRITE setWidrawVector NOTIFY widrawVectorChanged)
    Q_PROPERTY(QMap<QString,int> totalParType READ totalParType WRITE setTotalParType NOTIFY totalParTypeChanged)
    Q_PROPERTY(QMap<QString,QMap<QString,int>> choosingMatrix READ choosingMatrix WRITE setChoosingMatrix NOTIFY choosingMatrixChanged)
    Q_PROPERTY(QMap<QString,int> prices READ prices WRITE setPrices NOTIFY pricesChanged)
    Q_PROPERTY(QList<QPair<QPair<City*,City*>,QPair<Country*,Country*>>> battlesForP1 READ battlesForP1
               WRITE setBattlesForP1 NOTIFY battlesForP1Changed)
    MapView* m_mapView;

    Player* m_player;

    QMap<City*,QStringList> m_unitsToBuy;

    QMap<City*,int> m_treats;

    int m_totalthreat;

    QMap<QString,int> m_widrawVector;

    QMap<QString,int> m_totalParType;

    QMap<QString,QMap<QString,int>> m_choosingMatrix;

    QMap<QString,int> m_prices;

    QList<QPair<QString,int>> p_widraw1000;
    QList<QPair<QString,int>> p_widraw500;
    QList<QPair<QString,int>> p_widraw100;

    QList<QPair<QPair<City*,City*>,QPair<Country*,Country*>>> m_battlesForP1;

public:
    explicit MapAI(QObject *parent = nullptr);

    MapView* mapView() const;

    Player* player() const;

    QMap<City*,QStringList> unitsToBuy() const;

    QMap<City*,int> treats() const;

    int totalthreat() const;

    QMap<QString,int> widrawVector() const;

    QMap<QString,int> totalParType() const;

    QMap<QString,QMap<QString,int>> choosingMatrix() const;

    QMap<QString,int> prices() const;

    void distributeFunds();
    void  resetTotalParType();

    void moveUnitsToFrontLine();

    void StudyAttackPossibilities();
    void startBattleAI_AI(City *c,City *n);
    void run();

    QList<QPair<QPair<City*,City*>,QPair<Country*,Country*>>> battlesForP1() const;

signals:

    void mapViewChanged(MapView* mapView);

    void playerChanged(Player* player);

    void unitsToBuyChanged(QMap<City*,QStringList> unitsToBuy);

    void treatsChanged(QMap<City*,int> treats);

    void totalthreatChanged(int totalthreat);

    void widrawVectorChanged(QMap<QString,int> widrawVector);

    void totalParTypeChanged(QMap<QString,int> totalParType);

    void choosingMatrixChanged(QMap<QString,QMap<QString,int>> choosingMatrix);

    void pricesChanged(QMap<QString,int> prices);

    void battlesForP1Changed(QList<QPair<QPair<City*,City*>,QPair<Country*,Country*>>> battlesForP1);

public slots:
    void setMapView(MapView* mapView);
    void setPlayer(Player* player);
    void setUnitsToBuy(QMap<City*,QStringList> unitsToBuy);
    void setTreats(QMap<City*,int> treats);
    void setTotalthreat(int totalthreat);
    void setWidrawVector(QMap<QString,int> widrawVector);
    void setTotalParType(QMap<QString,int> totalParType);
    void setChoosingMatrix(QMap<QString,QMap<QString,int>> choosingMatrix);
    void setPrices(QMap<QString,int> prices);
    void setBattlesForP1(QList<QPair<QPair<City*,City*>,QPair<Country*,Country*>>> battlesForP1);

    void launchBattleAI_Player();
};

#endif // MAPAI_H
