#include "battleborderitem.h"

#include "bmapscene.h"

#include <QPainter>

BattleBorderItem::BattleBorderItem(QObject *parent) : QObject(parent),mapWidth(0),mapHeight(0)
{
    this->setZValue(500);
    this->setPos(-45,-45);
    rectPen.setWidth(6);
    rectPen.setStyle(Qt::SolidLine);
    rectPen.setColor(Qt::black);
}

QRectF BattleBorderItem::boundingRect() const
{
    return scene->bmap() ==nullptr?QRectF():
            QRectF(0,0,(scene->bmap()->isMassiveBattle()?mapHeight:mapWidth)+90,
                   (scene->bmap()->isMassiveBattle()?mapWidth:mapHeight)+90);
}

void BattleBorderItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    painter->setPen(rectPen);
    painter->setBrush(Qt::transparent);
    painter->setOpacity(0.5);
    painter->drawRect(boundingRect().adjusted(25,25,-25,-25));

    if(scene->bmap() == nullptr)return;
    painter->setOpacity(0.7);
    painter->setPen(QPen());
    painter->setBrush(Qt::black);
    painter->setPen(Qt::black);
    if(scene->bmap()->isMassiveBattle()){

        painter->save();
        painter->translate(45,0);
        for (int i = 0; i < scene->bmap()->size().y(); ++i) {
            painter->setBrush(i%2==0?Qt::gray:Qt::white);
            painter->drawRect(0,0,100,20);
            painter->drawText(45,13,QString::number(i));
            painter->translate(100,0);
        }
        painter->restore();
        painter->save();
        painter->translate(0,45);
        for (int i = 0; i < scene->bmap()->size().x(); ++i) {
            painter->setBrush(i%2==0?Qt::gray:Qt::white);
            painter->drawRect(0,0,20,100);
            painter->drawText(7,45,QString::number(i));
            painter->translate(0,100);
        }


        painter->restore();
        painter->save();
        painter->translate(45,scene->bmap()->size().x()*100+70);
        for (int i = 0; i < scene->bmap()->size().y(); ++i) {
            painter->setBrush(i%2==0?Qt::gray:Qt::white);
            painter->drawRect(0,0,100,20);
            painter->drawText(45,13,QString::number(i));
            painter->translate(100,0);
        }
        painter->restore();
        painter->save();
        painter->translate(scene->bmap()->size().y()*100+70,45);
        for (int i = 0; i < scene->bmap()->size().x(); ++i) {
            painter->setBrush(i%2==0?Qt::gray:Qt::white);
            painter->drawRect(0,0,20,100);
            painter->drawText(7,45,QString::number(i));
            painter->translate(0,100);
        }
        painter->restore();

    }else{
        painter->save();
        painter->translate(45,0);
        for (int i = 0; i < scene->bmap()->size().x(); ++i) {
            painter->setBrush(i%2==0?Qt::gray:Qt::white);
            painter->drawRect(0,0,100,20);
            painter->drawText(45,13,QString::number(i));
            painter->translate(100,0);
        }
        painter->restore();
        painter->save();
        painter->translate(0,45);
        for (int i = 0; i < scene->bmap()->size().y(); ++i) {
            painter->setBrush(i%2==0?Qt::gray:Qt::white);
            painter->drawRect(0,0,20,100);
            painter->drawText(7,45,QString::number(i));
            painter->translate(0,100);
        }


        painter->restore();
        painter->save();
        painter->translate(45,scene->bmap()->size().y()*100+70);
        for (int i = 0; i < scene->bmap()->size().x(); ++i) {
            painter->setBrush(i%2==0?Qt::gray:Qt::white);
            painter->drawRect(0,0,100,20);
            painter->drawText(45,13,QString::number(i));
            painter->translate(100,0);
        }
        painter->restore();
        painter->save();
        painter->translate(scene->bmap()->size().x()*100+70,45);
        for (int i = 0; i < scene->bmap()->size().y(); ++i) {
            painter->setBrush(i%2==0?Qt::gray:Qt::white);
            painter->drawRect(0,0,20,100);
            painter->drawText(7,45,QString::number(i));
            painter->translate(0,100);
        }
        painter->restore();
    }

}
