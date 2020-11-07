#ifndef CITY_H
#define CITY_H

#include <QObject>

class Country;
class Map;
class Unit;
enum CityType{
    K100G,K100D,K100T,K500G,K500D,K500T,M1G,M1D,M1T,M10G,M10D,M10T
};

class City : public QObject
{
    Q_PROPERTY(int id READ id WRITE setId NOTIFY idChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(Country* country READ country WRITE setCountry NOTIFY countryChanged)
    Q_PROPERTY(Map* map READ map WRITE setMap NOTIFY mapChanged)
    Q_PROPERTY(int x READ x WRITE setX NOTIFY xChanged)
    Q_PROPERTY(int y READ y WRITE setY NOTIFY yChanged)
    Q_PROPERTY(CityType type READ type WRITE setType NOTIFY typeChanged)
    Q_PROPERTY(QList<City*> neighbours READ neighbours WRITE setNeighbours NOTIFY neighboursChanged)
    Q_PROPERTY(int income READ income WRITE setIncome NOTIFY incomeChanged)
    Q_PROPERTY(QList<Unit*> units READ units WRITE setUnits NOTIFY unitsChanged)



    Q_OBJECT

    int m_id;

    QString m_name;

    Country* m_country;

    Map* m_map;

    int m_x;

    int m_y;

    CityType m_type;

    QList<City*> m_neighbours;

    int m_income;

    QList<Unit*> m_units;

public:
    explicit City(QObject *parent = nullptr);

    int id() const;

    QString name() const;

    Country* country() const;

    Map* map() const;

    int x() const;

    int y() const;

    CityType type() const;

    QList<City*> neighbours() const;

    int income() const;

    QList<Unit*> units() const;

signals:

    void idChanged(int id);

    void nameChanged(QString name);

    void countryChanged(Country* country);

    void mapChanged(Map* map);

    void xChanged(int x);

    void yChanged(int y);

    void typeChanged(CityType type);

    void neighboursChanged(QList<City*> neighbours);

    void incomeChanged(int income);

    void unitsChanged(QList<Unit*> units);

    void addedUnitSig(QString typeS);

public slots:
    void setId(int id);
    void setName(QString name);
    void setCountry(Country* country);
    void setMap(Map* map);
    void setX(int x);
    void setY(int y);
    void setType(CityType type);
    void setNeighbours(QList<City*> neighbours);
    void setIncome(int income);
    void setUnits(QList<Unit*> units);
};

#endif // CITY_H
