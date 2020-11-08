#ifndef UNITPUPUP_H
#define UNITPUPUP_H

#include "unitgraphics.h"

#include <QGraphicsItem>
#include <QObject>
#include <QPen>

class unitPupUp : public QObject , public QGraphicsItem
{
    Q_OBJECT
    Q_PROPERTY(UnitGraphics* unitG READ unitG WRITE setUnitG NOTIFY unitGChanged)

    UnitGraphics* m_unitG;
    QPen textPen;
    QSvgRenderer rend;

public:
    explicit unitPupUp(QObject *parent = nullptr);

signals:

    void unitGChanged(UnitGraphics* unitG);

public slots:

// QGraphicsItem interface
    void setUnitG(UnitGraphics* unitG);

public:
    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    UnitGraphics* unitG() const;
};

#endif // UNITPUPUP_H
