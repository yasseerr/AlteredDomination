#ifndef SERVERENGIN_H
#define SERVERENGIN_H


#include <QTcpServer>
class ServerEngin : public QTcpServer
{
    Q_OBJECT
public:
    explicit ServerEngin(QObject *parent = nullptr);    
signals:

public slots:
};

#endif // SERVERENGIN_H
