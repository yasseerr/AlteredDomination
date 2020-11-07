#ifndef UATTACK_H
#define UATTACK_H

#include <QObject>
#include <QPoint>

class UAttack : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int x READ x WRITE setX NOTIFY xChanged)
    Q_PROPERTY(int y READ y WRITE setY NOTIFY yChanged)
    Q_PROPERTY(QList<QString> types READ types WRITE setTypes NOTIFY typesChanged)
    Q_PROPERTY(QList<QPoint> dependencies READ dependencies WRITE setDependencies NOTIFY dependenciesChanged)
    int m_x;

    int m_y;

    QList<QString> m_types;

    QList<QPoint> m_dependencies;

public:
    explicit UAttack(QObject *parent = nullptr);

    int x() const;

    int y() const;

    QList<QString> types() const;

    QList<QPoint> dependencies() const;


    void addType(QString s);
    void addDependecie(QPoint p);

signals:

    void xChanged(int x);

    void yChanged(int y);

    void typesChanged(QList<QString> types);

    void dependenciesChanged(QList<QPoint> dependencies);

public slots:
    void setX(int x);
    void setY(int y);
    void setTypes(QList<QString> types);
    void setDependencies(QList<QPoint> dependencies);
};

#endif // UATTACK_H
