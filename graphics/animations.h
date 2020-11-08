#ifndef ANIMATIONS_H
#define ANIMATIONS_H

#include <QAudioOutput>
#include <QFile>
#include <QGraphicsItem>
#include <QObject>
#include <QSound>
#include <QTimer>

class Animations : public QObject,public QGraphicsItem
{
    Q_OBJECT
    Q_PROPERTY(QString selectedAnimation READ selectedAnimation WRITE setSelectedAnimation NOTIFY selectedAnimationChanged)
    Q_PROPERTY(QTimer* animtionTimer READ animtionTimer WRITE setAnimtionTimer NOTIFY animtionTimerChanged)

    QString m_selectedAnimation;

    QTimer* m_animtionTimer;

    QImage *explosionSprite;

    int frameNumber;

    QGraphicsRectItem bullet;


public:

    QMap<QString,QFile*> sounds;
    QAudioOutput *audioOut;
    QSound *s;

    explicit Animations(QObject *parent = nullptr);

    void runAnimation(int xp,int yp);

signals:

    void selectedAnimationChanged(QString selectedAnimation);

    void animtionTimerChanged(QTimer* animtionTimer);

public slots:
    void onTimerTick();
    void onAudioStatChanged(QAudio::State stat);

    void setSelectedAnimation(QString selectedAnimation);

    void setAnimtionTimer(QTimer* animtionTimer);

public:
    virtual QRectF boundingRect() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QString selectedAnimation() const;
    QTimer* animtionTimer() const
{
    return m_animtionTimer;
}
};

#endif // ANIMATIONS_H
