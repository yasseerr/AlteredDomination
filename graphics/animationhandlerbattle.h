#ifndef ANIMATIONHANDLERBATTLE_H
#define ANIMATIONHANDLERBATTLE_H



#include <QGraphicsItem>
#include <QObject>
#include <QPropertyAnimation>


class BMapScene;
class BFrame;

class AnimationHandlerBattle : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QPointF bulletPos READ bulletPos WRITE setBulletPos NOTIFY bulletPosChanged)

    QPointF m_bulletPos;

public:
    explicit AnimationHandlerBattle(BMapScene *bmapS ,QObject *parent = nullptr);
    BMapScene *bScene;
    QGraphicsRectItem *bullet;
    QPropertyAnimation *bulletAnim;

    QPointF bulletPos() const;

signals:

    void bulletPosChanged(QPointF bulletPos);

public slots:

    void launchBullet(BFrame *dep,BFrame *des);
    void onBulletStoped();

    void setBulletPos(QPointF bulletPos);
};

#endif // ANIMATIONHANDLERBATTLE_H
