#include "unittype.h"

UnitType::UnitType()
{

}

int UnitType::id() const
{
    return m_id;
}

QString UnitType::name() const
{
    return m_name;
}

int UnitType::cost() const
{
    return m_cost;
}

QList<QString> UnitType::types() const
{
    return m_types;
}

QList<UMove*> UnitType::moves() const
{
    return m_moves;
}

QList<UAttack *> UnitType::attacks() const
{
    return m_attacks;
}

void UnitType::addType(QString s)
{
    m_types.append(s);
}

void UnitType::addMove(UMove *m)
{
    m_moves.append(m);
}

void UnitType::addAttack(UAttack *a)
{
    m_attacks.append(a);
}



void UnitType::setId(int id)
{
    if (m_id == id)
        return;

    m_id = id;
    emit idChanged(m_id);
}

void UnitType::setName(QString name)
{
    if (m_name == name)
        return;

    m_name = name;
    emit nameChanged(m_name);
}

void UnitType::setCost(int cost)
{
    if (m_cost == cost)
        return;

    m_cost = cost;
    emit costChanged(m_cost);
}

void UnitType::setTypes(QList<QString> types)
{
    if (m_types == types)
        return;

    m_types = types;
    emit typesChanged(m_types);
}

void UnitType::setMoves(QList<UMove*> moves)
{
    if (m_moves == moves)
        return;

    m_moves = moves;
    emit movesChanged(m_moves);
}

void UnitType::setAttacks(QList<UAttack *> attacks)
{
    if (m_attacks == attacks)
        return;

    m_attacks = attacks;
    emit attacksChanged(m_attacks);
}


