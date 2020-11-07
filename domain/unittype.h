#ifndef UNITTYPE_H
#define UNITTYPE_H


#include <QObject>
#include "uattack.h"
#include "umove.h"

class UnitType : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int id READ id WRITE setId NOTIFY idChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(int cost READ cost WRITE setCost NOTIFY costChanged)
    Q_PROPERTY(QList<QString> types READ types WRITE setTypes NOTIFY typesChanged)
    Q_PROPERTY(QList<UMove*> moves READ moves WRITE setMoves NOTIFY movesChanged)
    Q_PROPERTY(QList<UAttack*> attacks READ attacks WRITE setAttacks NOTIFY attacksChanged)

    int m_id;

    QString m_name;

    int m_cost;

    QList<QString> m_types;

    QList<UMove*> m_moves;

    QList<UAttack*> m_attacks;

public:
    explicit UnitType();
    int id() const;
    QString name() const;

    int cost() const;

    QList<QString> types() const;


    QList<UMove*> moves() const;
    QList<UAttack*> attacks() const;

    void addType(QString s);
    void addMove(UMove *m);
    void addAttack(UAttack *a);

public slots:
    void setId(int id);
    void setName(QString name);

    void setCost(int cost);

    void setTypes(QList<QString> types);

    void setMoves(QList<UMove*> moves);
    void setAttacks(QList<UAttack*> attacks);

signals:
    void idChanged(int id);
    void nameChanged(QString name);
    void costChanged(int cost);
    void typesChanged(QList<QString> types);

    void movesChanged(QList<UMove*> moves);
    void attacksChanged(QList<UAttack*> attacks);
};

#endif // UNITTYPE_H
