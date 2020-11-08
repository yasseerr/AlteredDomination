#ifndef BATTLEBORDERITEM_H
#define BATTLEBORDERITEM_H



#include <QGraphicsItem>
#include <QObject>
#include <QPen>
#include <QSvgRenderer>


class BMapScene;
class BattleBorderItem : public QObject,public QGraphicsItem
{
    Q_OBJECT
public:

    BMapScene *scene;
    int mapWidth;
    int mapHeight;
    QPen rectPen;

    explicit BattleBorderItem(QObject *parent = nullptr);

signals:

public slots:

    // QGraphicsItem interface
public:
    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

#endif // BATTLEBORDERITEM_H
