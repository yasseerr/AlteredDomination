#include "animationhandlerbattle.h"
#include "bframe.h"
#include "bmapscene.h"

#include <QPropertyAnimation>

AnimationHandlerBattle::AnimationHandlerBattle(BMapScene *bmapS, QObject *parent): QObject(parent)
{
    bullet  =new QGraphicsRectItem(0,0,10,10);
    bullet->setBrush(Qt::darkRed);
    bullet->setZValue(60);
    bullet->setVisible(false);
    bScene = bmapS;
    bScene->addItem(bullet);

    bulletAnim = new QPropertyAnimation(this,"bulletPos");
    bulletAnim->setDuration(80);

    connect(bulletAnim,&QPropertyAnimation::finished,this,&AnimationHandlerBattle::onBulletStoped);

}

QPointF AnimationHandlerBattle::bulletPos() const
{
    return m_bulletPos;
}

void AnimationHandlerBattle::launchBullet(BFrame *dep, BFrame *des)
{
    bulletAnim->setStartValue(QPointF(dep->pos().x()+45,dep->pos().y()+45));
    bulletAnim->setEndValue(QPointF(des->pos().x()+45,des->pos().y()+45));
    bullet->setVisible(true);
    bulletAnim->start();
}

void AnimationHandlerBattle::onBulletStoped()
{
    bullet->setVisible(false);
}

void AnimationHandlerBattle::setBulletPos(QPointF bulletPos)
{
    if (m_bulletPos == bulletPos)
        return;
    m_bulletPos = bulletPos;
    bullet->setPos(bulletPos);
    bullet->update();
    emit bulletPosChanged(m_bulletPos);
}
