#include "homemenu.h"
#include <QCoreApplication>
#include <QDir>
#include <QHostAddress>
#include <QJsonDocument>
#include <QJsonObject>
#include <QQmlContext>

HomeMenu::HomeMenu():QQuickView(),game(nullptr),multiplayerGame(nullptr)
{

    m_matchmackingSocket = new QTcpSocket();
    messageSize = 0;
    matchmakingServerSize = 0;
    QFile mapFile(":/data/map.json");
    mapFile.open(QIODevice::ReadOnly|QIODevice::Text);
    QTextStream st(&mapFile);
    setMapData(st.readAll());

    QFile savesFile(QDir::currentPath()+"/gameSaves.json");
    savesFile.open(QIODevice::ReadOnly|QIODevice::Text);
    QTextStream st2(&savesFile);
    setSavesData(st2.readAll());

    QFile tutoFile(":/data/tutorial.json");
    tutoFile.open(QIODevice::ReadOnly|QIODevice::Text);
    QTextStream st3(&tutoFile);
    setTutoData(st3.readAll());


    this->rootContext()->setContextProperty("homeClass",this);
    this->setSource(QUrl("qrc:/scripts/home/Intro.qml"));
    this->showMaximized();

}
void HomeMenu::startGame(QString cntr, int mode)
{
    game  = new MainMenu(cntr,mode,0,"");
    connect(game->mapView(),&MapView::returnHome,this,&HomeMenu::onReturnHome);
    this->hide();
    game->showMaximized();
}

void HomeMenu::loadGame(QString cntr, int turn, QString gameSaveString)
{
    game  = new MainMenu(cntr,1,1,gameSaveString);
    connect(game->mapView(),&MapView::returnHome,this,&HomeMenu::onReturnHome);
    game->mapView()->setTurnNumber(turn);
    this->hide();
    game->showMaximized();

}

void HomeMenu::deleteGameSave(QString newfilString)
{
    QFile savesFile(QDir::currentPath()+"/gameSaves.json");
    savesFile.open(QIODevice::WriteOnly|QIODevice::Text);
    QTextStream st2(&savesFile);
    st2 << newfilString.toLocal8Bit();
}

void HomeMenu::quitApp()
{
    QCoreApplication::quit();
}

void HomeMenu::entermatchmaking(QString ad, QString port, QString c)
{
    connect(m_matchmackingSocket,&QTcpSocket::connected,this,&HomeMenu::onMatchmakingConnect);
    connect(m_matchmackingSocket,&QTcpSocket::readyRead,this,&HomeMenu::onMatchmakingRespens);
    connect(m_matchmackingSocket,&QTcpSocket::disconnected,this,&HomeMenu::onMatchmakingDisconnect);

    countryString = c;

    m_matchmackingSocket->bind(port.toInt());
    m_matchmackingSocket->connectToHost(QHostAddress(ad),17777);
    qDebug() << m_matchmackingSocket->errorString();

}

void HomeMenu::startMultiplayerGameAsA()
{

}

void HomeMenu::startMultiplayerGameAsB(QString adress)
{

}

QString HomeMenu::mapData() const
{
    return m_mapData;
}

QString HomeMenu::savesData() const
{
    return m_savesData;
}

QString HomeMenu::tutoData() const
{
    return m_tutoData;
}

QTcpSocket *HomeMenu::matchmackingSocket() const
{
    return m_matchmackingSocket;
}

void HomeMenu::setMapData(QString mapData)
{
    if (m_mapData == mapData)
        return;

    m_mapData = mapData;
    emit mapDataChanged(m_mapData);
}

void HomeMenu::setSavesData(QString savesData)
{
    if (m_savesData == savesData)
        return;

    m_savesData = savesData;
    emit savesDataChanged(m_savesData);
}

void HomeMenu::onReturnHome()
{
    game->hide();
    QFile savesFile(QDir::currentPath()+"/gameSaves.json");
    savesFile.open(QIODevice::ReadOnly|QIODevice::Text);
    QTextStream st2(&savesFile);
    this->setSavesData(st2.readAll());

    this->showMaximized();
    game->deleteLater();
}

void HomeMenu::setTutoData(QString tutoData)
{
    if (m_tutoData == tutoData)
        return;

    m_tutoData = tutoData;
    emit tutoDataChanged(m_tutoData);
}

void HomeMenu::setMatchmackingSocket(QTcpSocket *matchmackingSocket)
{
    if (m_matchmackingSocket == matchmackingSocket)
        return;

    m_matchmackingSocket = matchmackingSocket;
    emit matchmackingSocketChanged(m_matchmackingSocket);
}

void HomeMenu::onMatchmakingConnect()
{
    m_matchmackingSocket->write("iwanttoplay");
}

void HomeMenu::onMatchmakingRespens()
{
    QDataStream in(m_matchmackingSocket);
    if(messageSize == 0){
        if(m_matchmackingSocket->bytesAvailable()<sizeof(quint8))return;
        in >> messageSize;
        qDebug()<< "matchmaking Number : "<<messageSize;

    }
    if(m_matchmackingSocket->bytesAvailable() < messageSize)return;
    QByteArray messageData;
    messageData.append(m_matchmackingSocket->read(messageSize));

    QJsonDocument doc = QJsonDocument::fromJson(messageData);
    QJsonObject mainObject = doc.object();
    int commandNumber = mainObject.value("code").toInt();
    qDebug()<<commandNumber;
    switch (commandNumber) {
    case 1:
        this->hide();
        disconnect(m_matchmackingSocket,&QTcpSocket::readyRead,this,&HomeMenu::onMatchmakingRespens);
        multiplayerGame = new MultiplayerGame(m_matchmackingSocket,countryString,mainObject.value("number").toInt());
        connect(multiplayerGame,&MultiplayerGame::mutiplayergameEnded,this,&HomeMenu::show);
        break;
    default:
        break;
    }
    messageSize = 0;


//    QString player1ServerAdress;
//    switch (matchmakingNumber) {
//        case 1:
//            multiplayerGame = new MultiplayerGame();
//            qDebug()<<1;
//            break;
//        case 2:
//            if(m_matchmackingSocket->bytesAvailable()<sizeof(quint8) && matchmakingServerSize == 0)return;
//            if(matchmakingServerSize == 0) in >> matchmakingServerSize;
//            if(m_matchmackingSocket->bytesAvailable()<matchmakingServerSize)return;
//            in >> player1ServerAdress;
//            multiplayerGame = new MultiplayerGame(player1ServerAdress);
//            qDebug()<<2<<" : "<<player1ServerAdress;
//            break;
//        case 50 :
//            qDebug()<<50;
//            break;
//        default:
//            qDebug()<<"not1 not 2!";
//            break;
//    }

}

void HomeMenu::onMatchmakingDisconnect()
{
    messageSize = 0;
    matchmakingServerSize = 0;

}
