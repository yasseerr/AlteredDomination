#ifndef UMOVE_H
#define UMOVE_H

#include <QObject>
#include <QPoint>

class UMove : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int x READ x WRITE setX NOTIFY xChanged)
    Q_PROPERTY(int y READ y WRITE setY NOTIFY yChanged)
    Q_PROPERTY(QList<QPoint> dependecies READ dependecies WRITE setDependecies NOTIFY dependeciesChanged)

    int m_x;

    int m_y;

    QList<QPoint> m_dependecies;

public:
    explicit UMove(QObject *parent = nullptr);

    int x() const;

    int y() const;

    QList<QPoint> dependecies() const;

    void addDependecie(QPoint p);

signals:

    void xChanged(int x);

    void yChanged(int y);

    void dependeciesChanged(QList<QPoint> dependecies);

public slots:
    void setX(int x);
    void setY(int y);
    void setDependecies(QList<QPoint> dependecies);
};

#endif // UMOVE_H
