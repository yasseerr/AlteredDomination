#ifndef COUNTRY_H
#define COUNTRY_H

#include <QColor>
#include <QImage>
#include <QObject>

class City;

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
    int m_id;

    QString m_name;

    QList<City*> m_cities;

    QColor m_color;

    City* m_capital;

    QImage m_flag;

    QString m_intID;

public:
    explicit Country(QObject *parent = nullptr);

    int id() const;

    QString name() const;

    QList<City*> cities() const;

    QColor color() const;

    City* capital() const;

    QImage flag() const;

    QString intID() const;

signals:

    void idChanged(int id);

    void nameChanged(QString name);

    void citiesChanged(QList<City*> cities);

    void colorChanged(QColor color);

    void capitalChanged(City* capital);

    void flagChanged(QImage flag);

    void intIDChanged(QString intID);

public slots:
    void setId(int id);
    void setName(QString name);
    void setCities(QList<City*> cities);
    void setColor(QColor color);
    void setCapital(City* capital);
    void setFlag(QImage flag);
    void setIntID(QString intID);
};

#endif // COUNTRY_H
