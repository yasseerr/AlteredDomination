#ifndef COUNTRY_H
#define COUNTRY_H

#include <QColor>
#include <QImage>
#include <QObject>
#include <QVariant>

class City;
class Player;
class Country : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int id READ id WRITE setId NOTIFY idChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QList<City*> cities READ cities WRITE setCities NOTIFY citiesChanged)
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
    Q_PROPERTY(City* capital READ capital WRITE setCapital NOTIFY capitalChanged)
    Q_PROPERTY(QImage flag READ flag WRITE setFlag NOTIFY flagChanged)
    Q_PROPERTY(QString intID READ intID WRITE setIntID NOTIFY intIDChanged)
    Q_PROPERTY(Player* player READ player WRITE setPlayer NOTIFY playerChanged)
    Q_PROPERTY(int income READ income WRITE setIncome NOTIFY incomeChanged)
    Q_PROPERTY(int funds READ funds WRITE setFunds NOTIFY fundsChanged)
    int m_id;

    QString m_name;

    QList<City*> m_cities;

    QColor m_color;

    City* m_capital;

    QImage m_flag;

    QString m_intID;

    Player* m_player;

    int m_income;

    int m_funds;

public:
    void addCity(City *c);
    void removeCity(City *c);
    QVariant toVariant();

    explicit Country(QObject *parent = nullptr);

    int id() const;

    QString name() const;

    QList<City*> cities() const;

    QColor color() const;

    City* capital() const;

    QImage flag() const;

    QString intID() const;

    Player* player() const;

    int income() const;

    int funds() const;

signals:

    void idChanged(int id);

    void nameChanged(QString name);

    void citiesChanged(QList<City*> cities);

    void colorChanged(QColor color);

    void capitalChanged(City* capital);

    void flagChanged(QImage flag);

    void intIDChanged(QString intID);

    void playerChanged(Player* player);

    void incomeChanged(int income);

    void fundsChanged(int funds);

public slots:
    void setId(int id);
    void setName(QString name);
    void setCities(QList<City*> cities);
    void setColor(QColor color);
    void setCapital(City* capital);
    void setFlag(QImage flag);
    void setIntID(QString intID);
    void setPlayer(Player* player);
    void setIncome(int income);
    void setFunds(int funds);
};

#endif // COUNTRY_H
