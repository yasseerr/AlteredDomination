#ifndef MULTIPLAYERGAME_H
#define MULTIPLAYERGAME_H

#include "serverengin.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QObject>
#include <QQuickView>
#include<QTcpSocket>
#include <battleform.h>

#include <domain/city.h>
#include <domain/unit.h>
class MultiplayerGame : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QTcpSocket* serverSocket READ serverSocket WRITE setServerSocket NOTIFY serverSocketChanged)
    Q_PROPERTY(ServerEngin* gameServer READ gameServer WRITE setGameServer NOTIFY gameServerChanged)
    Q_PROPERTY(City* myCity READ myCity WRITE setMyCity NOTIFY myCityChanged)
    Q_PROPERTY(City* opponantCity READ opponantCity WRITE setOpponantCity NOTIFY opponantCityChanged)


    ServerEngin* m_gameServer;    
    QTcpSocket* m_serverSocket;
    quint16 receivedSize;

    BattleForm *battleForm;
    int playerTurn;

    City* m_myCity;
    City* m_opponantCity;
    bool unitsSubmited;
    bool opppnantUnitsSubmited;

public:

    QQuickView *addUnitsView;
    QJsonDocument countriesDoc;
    QMap<QString,QJsonObject> unitTypsMap;
    explicit MultiplayerGame(QTcpSocket *s,QString country,int turn,QObject *parent = nullptr);

    ServerEngin* gameServer() const;

    QTcpSocket* serverSocket() const;

    Q_INVOKABLE QString unitsText();
//    Q_INVOKABLE int funds();
//    Q_INVOKABLE QString cityName();
//    Q_INVOKABLE QString countryName();
//    Q_INVOKABLE QString countryFlag();
    Q_INVOKABLE void addUnitFromQml(QString t,int c);
    Q_INVOKABLE void submitUnits();
    void sendMssage(QByteArray m);
    void launchGame();

    City* myCity() const;

    City* opponantCity() const;


signals:

    void gameServerChanged(ServerEngin* gameServer);    
    void serverSocketChanged(QTcpSocket* serverSocket);
    void mutiplayergameEnded();



    void myCityChanged(City* myCity);
    void opponantCityChanged(City* opponantCity);


public slots:


    void messageReceived();

    void battleEnded();
    void battleEndedA();

    void setGameServer(ServerEngin* gameServer);
    void setServerSocket(QTcpSocket* serverSocket);

    void setMyCity(City* myCity);
    void setOpponantCity(City* opponantCity);

};

#endif // MULTIPLAYERGAME_H
