#ifndef LINKN_H
#define LINKN_H

#include <QObject>
#include "city.h"

class LinkN : public QObject
{
    Q_OBJECT
    Q_PROPERTY(City* dep READ dep WRITE setDep NOTIFY depChanged)
    Q_PROPERTY(City* des READ des WRITE setDes NOTIFY desChanged)

    City* m_dep;

    City* m_des;

public:
    explicit LinkN(QObject *parent = nullptr);

City* dep() const;

City* des() const;

signals:

void depChanged(City* dep);

void desChanged(City* des);

public slots:
void setDep(City* dep);
void setDes(City* des);
};

#endif // LINKN_H
