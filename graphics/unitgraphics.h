#ifndef UNITGRAPHICS_H
#define UNITGRAPHICS_H

#include <QGraphicsItem>
#include <QObject>
#include <QPropertyAnimation>
#include <QSound>
#include <QSvgRenderer>
//#include <QAudioOutput>
#include <QFile>
#include "domain/unit.h"
class BMapScene;
class BFrame;
class UnitGraphics : public QObject,public QGraphicsItem
{
    Q_OBJECT
    Q_PROPERTY(Unit* unit READ unit WRITE setUnit NOTIFY unitChanged)
    Q_PROPERTY(BMapScene* bmapS READ bmapS WRITE setBmapS NOTIFY bmapSChanged)
    Q_PROPERTY(BFrame* frame READ frame WRITE setFrame NOTIFY frameChanged)
    Q_PROPERTY(bool isGeneral READ isGeneral WRITE setIsGeneral NOTIFY isGeneralChanged)
    Q_PROPERTY(QPointF pos READ pos WRITE setPos)
    Q_PROPERTY(bool isHovered READ isHovered WRITE setIsHovered NOTIFY isHoveredChanged)
    Unit* m_unit;

    BMapScene* m_bmapS;

    BFrame* m_frame;

    bool m_isGeneral;

    bool m_isHovered;

public:
//    QFile *sourseAudioM;
//    QFile *sourseAudioE;

    QSound *movementAudio;
    QSound *explosionAudio;
    QSvgRenderer *unitRend;
    explicit UnitGraphics(QObject *parent = nullptr);

signals:

    void unitChanged(Unit* unit);


    void bmapSChanged(BMapScene* bmapS);

    void frameChanged(BFrame* frame);

    void isGeneralChanged(bool isGeneral);

    void isHoveredChanged(bool isHovered);

public slots:

// QGraphicsItem interface
    void setUnit(Unit* unit);

    void setBmapS(BMapScene* bmapS);

    void setFrame(BFrame* frame);

    void setIsGeneral(bool isGeneral);

    void moveAnimationEnded(QPropertyAnimation::State stat);

    void setIsHovered(bool isHovered);

public:
    virtual QRectF boundingRect() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    Unit* unit() const;
    BMapScene* bmapS() const;
    BFrame* frame() const;
    bool isGeneral() const;

    void moveAnimation(BFrame *f);
    bool isHovered() const;
};

#endif // UNITGRAPHICS_H
