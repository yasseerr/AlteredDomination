#include "battlemap.h"
#include "city.h"

#include <QDebug>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QTextStream>

BattleMap::BattleMap(City *a,City *d,QObject *parent) : QObject(parent),
    m_attacker(a),
    m_deffender(d)
{
//--------calculating the size--------------------------//
    m_size.setX(14);
    m_size.setY(1+qMax(a->units().size()/2,d->units().size()/2));
    m_attackerMoves = 1+(a->units().size()/16);
    m_deffenderMoves = 1+(d->units().size()/16);
    m_baseSize = 2;
//--------loading the units types---------------------//

    QFile typesFile(":/scripts/units.json");
    typesFile.open(QFile::ReadOnly|QFile::Text);
    QTextStream inJ(&typesFile);
    QJsonDocument jd = QJsonDocument::fromJson(inJ.readAll().toLocal8Bit());
    QJsonArray rootArray = jd.array();
    foreach (QJsonValue v, rootArray) {
        QJsonObject typeJ = v.toObject();
        UnitType *type = new UnitType();
        type->setId(typeJ.value("id").toInt());
        type->setName(typeJ.value("name").toString());
        type->setCost(typeJ.value("cost").toInt());
        m_unitetypes.insert(type->name(),type);

        /// maptype of this type
        foreach (QJsonValue maptype, typeJ.value("types").toArray()) {
            type->addType(maptype.toString());
        }

        ///-------------------- moves------------------
        foreach (QJsonValue umoveJ, typeJ.value("moves").toArray()) {
            QJsonObject umoveO = umoveJ.toObject();
            UMove *umove = new UMove(this);
            umove->setX(umoveO.value("x").toInt());
            umove->setY(umoveO.value("y").toInt());
            foreach (QJsonValue depV, umoveO.value("dependencies").toArray()) {
                QJsonObject depO = depV.toObject();
                umove->addDependecie(QPoint(depO.value("x").toInt(),depO.value("y").toInt()));
            }
            type->addMove(umove);
        }
        ///--------------------- attacks ------------------------
        foreach (QJsonValue uattJ, typeJ.value("attacks").toArray()) {
            QJsonObject uattO = uattJ.toObject();
            UAttack *uatt = new UAttack(this);
            uatt->setX(uattO.value("x").toInt());
            uatt->setY(uattO.value("y").toInt());
            foreach (QJsonValue depV, uattO.value("dependencies").toArray()) {
                QJsonObject depO = depV.toObject();
                uatt->addDependecie(QPoint(depO.value("x").toInt(),depO.value("y").toInt()));
            }
            foreach (QJsonValue tyV, uattO.value("affect").toArray()) {
                uatt->addType(tyV.toString());
            }
            type->addAttack(uatt);
        }
    }
}

City *BattleMap::attacker() const
{
    return m_attacker;
}

City *BattleMap::deffender() const
{
    return m_deffender;
}

QPoint BattleMap::size() const
{
    return m_size;
}

int BattleMap::attackerMoves() const
{
    return m_attackerMoves;
}

int BattleMap::deffenderMoves() const
{
    return m_deffenderMoves;
}

QMap<QString, UnitType *> BattleMap::unitetypes() const
{
    return m_unitetypes;
}

int BattleMap::baseSize() const
{
    return m_baseSize;
}

void BattleMap::setAttacker(City *attacker)
{
    if (m_attacker == attacker)
        return;

    m_attacker = attacker;
    emit attackerChanged(m_attacker);
}

void BattleMap::setDeffender(City *deffender)
{
    if (m_deffender == deffender)
        return;

    m_deffender = deffender;
    emit deffenderChanged(m_deffender);
}

void BattleMap::setSize(QPoint size)
{
    if (m_size == size)
        return;

    m_size = size;
    emit sizeChanged(m_size);
}

void BattleMap::setAttackerMoves(int attackerMoves)
{
    if (m_attackerMoves == attackerMoves)
        return;

    m_attackerMoves = attackerMoves;
    emit attackerMovesChanged(m_attackerMoves);
}

void BattleMap::setDeffenderMoves(int deffenderMoves)
{
    if (m_deffenderMoves == deffenderMoves)
        return;

    m_deffenderMoves = deffenderMoves;
    emit deffenderMovesChanged(m_deffenderMoves);
}

void BattleMap::setUnitetypes(QMap<QString, UnitType *> unitetypes)
{
    if (m_unitetypes == unitetypes)
        return;

    m_unitetypes = unitetypes;
    emit unitetypesChanged(m_unitetypes);
}

void BattleMap::setBaseSize(int baseSize)
{
    if (m_baseSize == baseSize)
        return;

    m_baseSize = baseSize;
    emit baseSizeChanged(m_baseSize);
}
