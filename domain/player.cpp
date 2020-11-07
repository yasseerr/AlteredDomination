#include "player.h"
#include "country.h"
Player::Player(QObject *parent) : QObject(parent)
{

}

int Player::id() const
{
    return m_id;
}

QString Player::name() const
{
    return m_name;
}

Country *Player::country() const
{
    return m_country;
}

PlayerType Player::type() const
{
    return m_type;
}

void Player::setid(int id)
{
    if (m_id == id)
        return;

    m_id = id;
    emit idChanged(m_id);
}

void Player::setName(QString name)
{
    if (m_name == name)
        return;

    m_name = name;
    emit nameChanged(m_name);
}

void Player::setCountry(Country* country)
{
    if (m_country == country)
        return;

    m_country = country;
    emit countryChanged(m_country);
}

void Player::setType(PlayerType type)
{
    if (m_type == type)
        return;

    m_type = type;
    emit typeChanged(m_type);
}
