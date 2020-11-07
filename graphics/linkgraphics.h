#ifndef LINKGRAPHICS_H
#define LINKGRAPHICS_H

#include <QObject>
#include <QGraphicsPathItem>

#include <domain/linkn.h>


class LinkGraphics : public QObject,public QGraphicsLineItem
{
    Q_OBJECT
    Q_PROPERTY(LinkN* link READ link WRITE setLink NOTIFY linkChanged)
    LinkN *m_link;

public:
    explicit LinkGraphics(LinkN *l, QObject *parent = nullptr);

LinkN* link() const;

signals:

void linkChanged(LinkN* link);

public slots:
void setLink(LinkN* link);
void zoomChanged();
};

#endif // LINKGRAPHICS_H
