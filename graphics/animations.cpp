#include "animations.h"

#include <QDebug>
#include <QPainter>
#include <QSound>
#include <QTimer>

Animations::Animations(QObject *parent) : QObject(parent),
    m_selectedAnimation("explosion"),
    m_animtionTimer(new QTimer()),
    explosionSprite(new QImage(":/data/animations/explosion2.png")),
    frameNumber(0)
{

    bullet.setBrush(Qt::black);
    bullet.setRect(0,0,30,30);


    this->setVisible(false);
    m_animtionTimer->setInterval(60);
    connect(m_animtionTimer,&QTimer::timeout,this,&Animations::onTimerTick);


    //sounds

//    QFile *f  = new QFile(":/data/sounds/explosion.wav");
//    f->open(QIODevice::ReadOnly);
//    sounds.insert("explosion",f);
//    qDebug()<< f->size();
//    QAudioFormat format;
//    format.setSampleRate(8000);
//    format.setChannelCount(1);
//    format.setSampleSize(8);
//    format.setCodec("audio/pcm");
//    format.setByteOrder(QAudioFormat::LittleEndian);
//    format.setSampleType(QAudioFormat::UnSignedInt);

//    QAudioDeviceInfo info(QAudioDeviceInfo::defaultOutputDevice());
//   if (!info.isFormatSupported(format)) {
//      qWarning() << "Raw audio format not supported by backend, cannot play audio.";
//   }

//    audioOut = new QAudioOutput(format,this);

//    connect(audioOut,&QAudioOutput::stateChanged,this,&Animations::onAudioStatChanged);

}

void Animations::runAnimation(int xp,int yp)
{
    this->setPos(xp,yp);
    this->setVisible(true);
    m_animtionTimer->start();
//    s->play(":/data/sounds/explosion.wav");
}

void Animations::onTimerTick()
{
    this->update();
    frameNumber++;
    if(frameNumber!=16)return;
    m_animtionTimer->stop();
    this->setVisible(false);
    frameNumber = 0;
}

void Animations::onAudioStatChanged(QAudio::State stat)
{
//    qDebug()<<audioOut->error();
}

void Animations::setSelectedAnimation(QString selectedAnimation)
{
    if (m_selectedAnimation == selectedAnimation)
        return;

    m_selectedAnimation = selectedAnimation;
    emit selectedAnimationChanged(m_selectedAnimation);
}

void Animations::setAnimtionTimer(QTimer *animtionTimer)
{
    if (m_animtionTimer == animtionTimer)
        return;

    m_animtionTimer = animtionTimer;
    emit animtionTimerChanged(m_animtionTimer);
}

QRectF Animations::boundingRect() const
{
    return QRectF(0,0,100,100);
}

void Animations::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

//    qDebug()<< frameNumber << " " << (64*frameNumber)%256 <<" " << 64*(frameNumber);
    painter->drawImage(15,23,*explosionSprite,(64*frameNumber)%256,64*((frameNumber/4)%4),64,64);

}

QString Animations::selectedAnimation() const
{
    return m_selectedAnimation;
}
