#ifndef UNITGRAPHICS_H
#define UNITGRAPHICS_H

#include <QGraphicsItem>
#include <QObject>
#include "domain/unit.h"
class CityGraphics;
class UnitGraphics : public QObject,public QGraphicsItem
{
    Q_OBJECT
    Q_PROPERTY(Unit* unit READ unit WRITE setUnit NOTIFY unitChanged)
    Q_PROPERTY(CityGraphics* cityG READ cityG WRITE setCityG NOTIFY cityGChanged)

    Unit* m_unit;

    CityGraphics* m_cityG;

public:
    explicit UnitGraphics(QObject *parent = nullptr);

signals:

    void unitChanged(Unit* unit);

    void cityGChanged(CityGraphics* cityG);

public slots:

// QGraphicsItem interface
    void setUnit(Unit* unit);

    void setCityG(CityGraphics* cityG);

public:
    virtual QRectF boundingRect() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    Unit* unit() const;
    CityGraphics* cityG() const;
};

#endif // UNITGRAPHICS_H
