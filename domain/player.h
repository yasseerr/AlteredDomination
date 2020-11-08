#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>

enum PlayerType{
  HUMAIN,AI,NET
};
class Country;
class Player : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int id READ id WRITE setid NOTIFY idChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(Country* country READ country WRITE setCountry NOTIFY countryChanged)
    Q_PROPERTY(PlayerType type READ type WRITE setType NOTIFY typeChanged)
    int m_id;

    QString m_name;

    Country* m_country;

    PlayerType m_type;

public:
    explicit Player(QObject *parent = nullptr);

    int id() const;
    QString name() const;
    Country* country() const;
    PlayerType type() const;

signals:

    void idChanged(int id);
    void nameChanged(QString name);
    void countryChanged(Country* country);
    void typeChanged(PlayerType type);

public slots:
void setid(int id);
void setName(QString name);
void setCountry(Country* country);
void setType(PlayerType type);
};

#endif // PLAYER_H
