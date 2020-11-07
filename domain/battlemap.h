#ifndef BATTLEMAP_H
#define BATTLEMAP_H

#include "unittype.h"

#include <QMap>
#include <QObject>
#include <QPoint>

class City;

class BattleMap : public QObject
{
    Q_OBJECT
    Q_PROPERTY(City* attacker READ attacker WRITE setAttacker NOTIFY attackerChanged)
    Q_PROPERTY(City* deffender READ deffender WRITE setDeffender NOTIFY deffenderChanged)
    Q_PROPERTY(QPoint size READ size WRITE setSize NOTIFY sizeChanged)
    Q_PROPERTY(int attackerMoves READ attackerMoves WRITE setAttackerMoves NOTIFY attackerMovesChanged)
    Q_PROPERTY(int deffenderMoves READ deffenderMoves WRITE setDeffenderMoves NOTIFY deffenderMovesChanged)
    Q_PROPERTY(QMap<QString,UnitType*> unitetypes READ unitetypes WRITE setUnitetypes NOTIFY unitetypesChanged)
    Q_PROPERTY(int baseSize READ baseSize WRITE setBaseSize NOTIFY baseSizeChanged)

    City* m_attacker;

    City* m_deffender;

    QPoint m_size;

    int m_attackerMoves;

    int m_deffenderMoves;

    QMap<QString,UnitType*> m_unitetypes;

    int m_baseSize;

public:
    explicit BattleMap(City *a,City *d,QObject *parent = nullptr);

    City* attacker() const;

    City* deffender() const;

    QPoint size() const;

    int attackerMoves() const;

    int deffenderMoves() const;

    QMap<QString,UnitType*> unitetypes() const;

    int baseSize() const;

signals:

    void attackerChanged(City* attacker);

    void deffenderChanged(City* deffender);

    void sizeChanged(QPoint size);

    void attackerMovesChanged(int attackerMoves);

    void deffenderMovesChanged(int deffenderMoves);

    void unitetypesChanged(QMap<QString,UnitType*> unitetypes);

    void baseSizeChanged(int baseSize);

public slots:
    void setAttacker(City* attacker);
    void setDeffender(City* deffender);
    void setSize(QPoint size);
    void setAttackerMoves(int attackerMoves);
    void setDeffenderMoves(int deffenderMoves);
    void setUnitetypes(QMap<QString,UnitType*> unitetypes);
    void setBaseSize(int baseSize);
};

#endif // BATTLEMAP_H
