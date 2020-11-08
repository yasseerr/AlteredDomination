#ifndef HOMEMENU_H
#define HOMEMENU_H

#include <QObject>
#include <QQuickView>
#include <mainmenu.h>
#include <QTcpSocket>

#include <multiplayer/multiplayergame.h>
class HomeMenu : public QQuickView
{
    Q_OBJECT
    Q_PROPERTY(QString mapData READ mapData WRITE setMapData NOTIFY mapDataChanged)
    Q_PROPERTY(QString savesData READ savesData WRITE setSavesData NOTIFY savesDataChanged)
    Q_PROPERTY(QString tutoData READ tutoData WRITE setTutoData NOTIFY tutoDataChanged)
    Q_PROPERTY(QTcpSocket* matchmackingSocket READ matchmackingSocket WRITE setMatchmackingSocket NOTIFY matchmackingSocketChanged)
    QString m_mapData;    
    QString m_savesData;    
    QString m_tutoData;
    QString countryString;

    QTcpSocket* m_matchmackingSocket;

public:
    MainMenu *game;
    MultiplayerGame *multiplayerGame;
    quint8 messageSize;
    quint8 matchmakingServerSize;

    HomeMenu();
    Q_INVOKABLE void startGame(QString cntr,int mode);
    Q_INVOKABLE void loadGame(QString cntr,int turn,QString gameSaveString);
    Q_INVOKABLE void deleteGameSave(QString newfilString);
    Q_INVOKABLE void quitApp();
    Q_INVOKABLE void entermatchmaking(QString ad,QString port,QString c);
    void startMultiplayerGameAsA();
    void startMultiplayerGameAsB(QString adress);

    QString mapData() const;
    QString savesData() const;

    QString tutoData() const;

    QTcpSocket* matchmackingSocket() const;

public slots:
    void setMapData(QString mapData);
    void setSavesData(QString savesData);
    void onReturnHome();

    void setTutoData(QString tutoData);

    void setMatchmackingSocket(QTcpSocket* matchmackingSocket);

    void onMatchmakingConnect();
    void onMatchmakingRespens();
    void onMatchmakingDisconnect();

signals:
    void mapDataChanged(QString mapData);
    void savesDataChanged(QString savesData);
    void tutoDataChanged(QString tutoData);
    void matchmackingSocketChanged(QTcpSocket* matchmackingSocket);
};

#endif // HOMEMENU_H
