#ifndef UNIT_H
#define UNIT_H

#include <QObject>
class City;
class Unit : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int id READ id WRITE setId NOTIFY idChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(City* city READ city WRITE setCity NOTIFY cityChanged)
    Q_PROPERTY(int x READ x WRITE setX NOTIFY xChanged)
    Q_PROPERTY(int y READ y WRITE setY NOTIFY yChanged)
    Q_PROPERTY(QString type READ type WRITE setType NOTIFY typeChanged)
    Q_PROPERTY(bool used READ used WRITE setUsed NOTIFY usedChanged)

    static int idCount;

    int m_id;

    QString m_name;

    City* m_city;

    int m_x;

    int m_y;

    QString m_type;

    bool m_used;

public:
    explicit Unit(QObject *parent = nullptr);

    int id() const;

    QString name() const;

    City* city() const;

    int x() const;

    int y() const;

    QString type() const;

    bool used() const;

signals:

    void idChanged(int id);

    void nameChanged(QString name);

    void cityChanged(City* city);

    void xChanged(int x);

    void yChanged(int y);

    void typeChanged(QString type);

    void usedChanged(bool used);


public slots:

    void setId(int id);
    void setName(QString name);
    void setCity(City* city);
    void setX(int x);
    void setY(int y);
    void setType(QString type);
    void setUsed(bool used);
};

#endif // UNIT_H
