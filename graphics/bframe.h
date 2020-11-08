#ifndef BFRAME_H
#define BFRAME_H

#include <QGraphicsItem>
#include <QObject>

class UnitGraphics;
class BMapScene;

class BFrame : public QObject, public QGraphicsItem
{
    Q_OBJECT

    Q_PROPERTY(UnitGraphics* unitG READ unitG WRITE setUnitG NOTIFY unitGChanged)
    Q_PROPERTY(int x READ x WRITE setX NOTIFY xChanged)
    Q_PROPERTY(int y READ y WRITE setY NOTIFY yChanged)
    Q_PROPERTY(BMapScene* bmapS READ bmapS WRITE setBmapS NOTIFY bmapSChanged)
    Q_PROPERTY(bool toAttack READ toAttack WRITE setToAttack NOTIFY toAttackChanged)
    Q_PROPERTY(bool toMoveTo READ toMoveTo WRITE setToMoveTo NOTIFY toMoveToChanged)
    Q_PROPERTY(bool isSeletedFrame READ isSeletedFrame WRITE setIsSeletedFrame NOTIFY isSeletedFrameChanged)
    Q_PROPERTY(bool isPrevious READ isPrevious WRITE setIsPrevious NOTIFY isPreviousChanged)
    Q_PROPERTY(bool isActualMove READ isActualMove WRITE setIsActualMove NOTIFY isActualMoveChanged)
    Q_PROPERTY(int moveId READ moveId WRITE setMoveId NOTIFY moveIdChanged)
    Q_PROPERTY(bool idDestroyed READ idDestroyed WRITE setIdDestroyed NOTIFY idDestroyedChanged)
    Q_PROPERTY(bool isDestroyer READ isDestroyer WRITE setIsDestroyer NOTIFY isDestroyerChanged)
    

    int m_x;

    int m_y;

    BMapScene* m_bmapS;

    bool m_toAttack;

    bool m_toMoveTo;

    bool m_isSeletedFrame;

    bool m_isPrevious;

    bool m_isActualMove;
    
    int m_moveId;
    
    bool m_idDestroyed;
    
    bool m_isDestroyer;
    
public:
    UnitGraphics* m_unitG;

    explicit BFrame(QObject *parent = nullptr);
    virtual void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEventAI();
    void mouseRightPressEventAI();

    void highlightMovesAttacks();
    void unHighlight();
    void checkWineLose();

    void cancelSelected();

signals:

    void unitGChanged(UnitGraphics* unitG);

    void xChanged(int x);

    void yChanged(int y);

    void bmapSChanged(BMapScene* bmapS);

    void toAttackChanged(bool toAttack);

    void toMoveToChanged(bool toMoveTo);

    void isSeletedFrameChanged(bool isSeletedFrame);


    void isPreviousChanged(bool isPrevious);

    void isActualMoveChanged(bool isActualMove);
    
    void moveIdChanged(int moveId);
    
    void idDestroyedChanged(bool idDestroyed);
    
    void isDestroyerChanged(bool isDestroyer);
    
public slots:

// QGraphicsItem interface
    void setUnitG(UnitGraphics* unitG);

    void setX(int x);

    void setY(int y);

    void setBmapS(BMapScene* bmapS);

    void setToAttack(bool toAttack);

    void setToMoveTo(bool toMoveTo);

    void setIsSeletedFrame(bool isSeletedFrame);

    void setIsPrevious(bool isPrevious);

    void setIsActualMove(bool isActualMove);
    
    void setMoveId(int moveId);
    
    void setIdDestroyed(bool idDestroyed);
    
    void setIsDestroyer(bool isDestroyer);
    
public:
    virtual QRectF boundingRect() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    UnitGraphics* unitG() const;
    int x() const;
    int y() const;
    BMapScene* bmapS() const;
    bool toAttack() const;
    bool toMoveTo() const;
    bool isSeletedFrame() const;
    bool isPrevious() const
    {
        return m_isPrevious;
    }
    bool isActualMove() const
    {
        return m_isActualMove;
    }
    int moveId() const
    {
        return m_moveId;
    }
    bool idDestroyed() const
    {
        return m_idDestroyed;
    }
    bool isDestroyer() const
    {
        return m_isDestroyer;
    }
};

#endif // BFRAME_H
