#include "multiplayergame.h"

#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <QQmlContext>
#include <QTime>

#include <domain/country.h>
#include <domain/player.h>

#include <graphics/bframe.h>

MultiplayerGame::MultiplayerGame(QTcpSocket *s, QString countryP,int turn, QObject *parent): QObject(parent),addUnitsView(new QQuickView())
{

    connect(s,&QTcpSocket::readyRead,this,&MultiplayerGame::messageReceived);
    receivedSize = 0;
    unitsSubmited = false;
    opppnantUnitsSubmited = false;
    battleForm = nullptr;
    playerTurn = turn;

    qmlRegisterType<City>();
    qmlRegisterType<Country>();
    qmlRegisterType<Unit>();
    qmlRegisterType<Player>();


    QFile *unitsFile;
    unitsFile = new QFile(":/scripts/units.json");
    unitsFile->open(QIODevice::ReadOnly|QIODevice::Text);
    QTextStream inUnits(unitsFile);
    QJsonDocument unitsdoc = QJsonDocument::fromJson(inUnits.readAll().toLocal8Bit());
    foreach (QJsonValue unitVal, unitsdoc.array()) {
        QJsonObject unitObj = unitVal.toObject();
        unitTypsMap.insert(unitObj.value("name").toString(),unitObj);
    }


    QFile *jsonFile;
    jsonFile = new QFile(":/data/map.json");
    jsonFile->open(QIODevice::ReadOnly|QIODevice::Text);
    QTextStream in(jsonFile);
    QJsonDocument doc = QJsonDocument::fromJson(in.readAll().toLocal8Bit());
    QJsonArray countriesArrayJ = doc.array();
    foreach (QJsonValue countryJ, countriesArrayJ) {
        if(!(countryJ.toObject().value("name")==countryP))continue;
        Country *thisCountry = new Country();
        thisCountry->setName(countryJ.toObject().value("name").toString());
        thisCountry->setIntID(countryJ.toObject().value("flag").toString());
        thisCountry->setColor(Qt::blue);
        thisCountry->setFunds(500);
        thisCountry->setIncome(0);
        QJsonArray citiesJ = countryJ.toObject().value("cities").toArray();
//        QTime t;
        qDebug()<< QTime::currentTime().msec();
        srand(QTime::currentTime().msec());
        QJsonObject thisCityJ = citiesJ.at(rand()%(citiesJ.size()-1)).toObject();
        m_myCity = new City();
        m_myCity->setCountry(thisCountry);
        m_myCity->setIncome(0);
        m_myCity->setName(thisCityJ.value("name").toString());

        Player *thisPlayer = new Player(m_myCity);
        thisPlayer->setid(1);
        thisPlayer->setCountry(thisCountry);
        thisPlayer->setName("ThisPlayer");
        thisPlayer->setType(PlayerType::HUMAIN);
        thisCountry->setPlayer(thisPlayer);
    }

    /// sending information to the server
    QVariantMap command3Info;
    command3Info.insert("code",3);
    command3Info.insert("country",countryP);
    command3Info.insert("city",myCity()->name());
    QJsonDocument command3J = QJsonDocument::fromVariant(command3Info);
    QByteArray command3Data;
    QDataStream out(&command3Data,QIODevice::WriteOnly);
//    quint16 sizeMsg = (quint16) command3J.toJson().size();
//    char *toWrite = (char*)&sizeMsg;
//    command3Data.append(toWrite,sizeof(quint16));
    out << (quint16)command3J.toJson().size();
    command3Data.append(command3J.toJson());
    m_serverSocket = s;
//    qDebug()<<command3Data;
    s->write(command3Data);

    addUnitsView->rootContext()->setContextProperty("addUnitsView",addUnitsView);
    addUnitsView->rootContext()->setContextProperty("multiplayerGame",this);
    addUnitsView->setSource(QUrl("qrc:/scripts/multiplayer/MultiplayerUnitSelection.qml"));
    addUnitsView->show();
}


ServerEngin *MultiplayerGame::gameServer() const
{
    return m_gameServer;
}

QTcpSocket *MultiplayerGame::serverSocket() const
{
    return m_serverSocket;
}

QString MultiplayerGame::unitsText()
{
    QFile file(":/scripts/units.json");
    file.open(QIODevice::ReadOnly|QIODevice::Text);
    QTextStream st(&file);
    return st.readAll();
}

//int MultiplayerGame::funds()
//{
//    return myCity()->country()->funds();
//}

//QString MultiplayerGame::cityName()
//{
//    return myCity()->name();
//}

//QString MultiplayerGame::countryName()
//{
//    return myCity()->country()->name();
//}

//QString MultiplayerGame::countryFlag()
//{
//    return myCity()->country()->intID();
//}

void MultiplayerGame::addUnitFromQml(QString t, int c)
{
    Unit *u = new Unit();
    u->setType(t);
    u->setPower(c);
    u->setCity(m_myCity);
    m_myCity->addUnit(u);
}

void MultiplayerGame::submitUnits()
{
    QVariantMap unitsVariant;
    unitsVariant.insert("code",4);
    QVariantList unitsVariantList;
    foreach (Unit *u, m_myCity->units().values()) {
        unitsVariantList << u->type();
    }
    unitsVariant.insert("units",unitsVariantList);
    QJsonDocument doc  = QJsonDocument::fromVariant(unitsVariant);
    sendMssage(doc.toJson());
    unitsSubmited = true;
    if(opppnantUnitsSubmited){
        launchGame();
    }
}

void MultiplayerGame::sendMssage(QByteArray m)
{
    QByteArray packet;
    QDataStream in(&packet,QIODevice::WriteOnly);
    in << (quint16)m.size();
    packet.append(m);
    m_serverSocket->write(packet);
}

void MultiplayerGame::launchGame()
{
    battleForm = new BattleForm(this->m_serverSocket);
    battleForm->bScene()->setCurrentPlayer(m_myCity->country()->player());
    battleForm->bScene()->setCurrentCityPlaying(m_myCity);
//    battleForm->bScene()->setCurrentCityPlaying(playerTurn==1?m_myCity:m_opponantCity);
    BattleMap *bm = new BattleMap(playerTurn==1?m_myCity:m_opponantCity,playerTurn==2?m_myCity:m_opponantCity,battleForm);
    battleForm->bScene()->setBmap(bm);


    connect(battleForm,SIGNAL(battleEnded()),this,SLOT(battleEnded()));
    connect(battleForm,SIGNAL(battleEndedA()),this,SLOT(battleEndedA()));
    battleForm->setIsMultiplayer(true);
    battleForm->publishMaptoQMl();
    battleForm->show();
}

City *MultiplayerGame::myCity() const
{
    return m_myCity;
}

City *MultiplayerGame::opponantCity() const
{
    return m_opponantCity;
}

void MultiplayerGame::messageReceived()
{
//   qDebug()<< m_serverSocket->readAll();
    QDataStream in(m_serverSocket);
    //get the size of the message
    if(receivedSize == 0 && m_serverSocket->bytesAvailable()>=sizeof(quint16)){
        in >> receivedSize;
    }
    if(receivedSize != 0 && m_serverSocket->bytesAvailable()>= receivedSize){
        /// message resceived completly
        QString message1 = m_serverSocket->read(receivedSize);
        qDebug() << message1;
        QJsonDocument jDoc = QJsonDocument::fromJson(message1.toLocal8Bit());
        QJsonObject messageObj = jDoc.object();
        QByteArray respense;
        QDataStream out(&respense,QIODevice::WriteOnly);
        switch (messageObj.value("code").toInt()) {


            case 3:{
                QFile *jsonFile;
                jsonFile = new QFile(":/data/map.json");
                jsonFile->open(QIODevice::ReadOnly|QIODevice::Text);
                QTextStream inText(jsonFile);
                QJsonDocument doc = QJsonDocument::fromJson(inText.readAll().toLocal8Bit());
                QJsonArray countriesArrayJ = doc.array();
                foreach (QJsonValue countryJ, countriesArrayJ) {
                    if(!(countryJ.toObject().value("name").toString()== messageObj.value("country").toString()))continue;
                    Country *opponantCountry = new Country();
                    opponantCountry->setName(countryJ.toObject().value("name").toString());
                    opponantCountry->setIntID(countryJ.toObject().value("flag").toString());
                    opponantCountry->setColor(Qt::red);
                    opponantCountry->setFunds(500);
                    opponantCountry->setIncome(0);
                    m_opponantCity = new City();
                    m_opponantCity->setCountry(opponantCountry);
                    m_opponantCity->setIncome(0);
                    m_opponantCity->setName(messageObj.value("city").toString());
                    Player *opponantPlayer = new Player(m_opponantCity);
                    opponantPlayer->setid(2);
                    opponantPlayer->setCountry(opponantCountry);
                    opponantPlayer->setName("OpponantPlayer");
                    opponantPlayer->setType(PlayerType::NET);
                    opponantCountry->setPlayer(opponantPlayer);
                }
                }
                break;



            case 4:{
                   QJsonArray unitsArrayJ = messageObj.value("units").toArray();
                   foreach (QJsonValue unitValue, unitsArrayJ) {
                       Unit *u = new Unit();
                       u->setType(unitValue.toString());
                       u->setPower(this->unitTypsMap.value(unitValue.toString()).value("cost").toInt());
                       u->setCity(m_opponantCity);
                       m_opponantCity->addUnit(u);
                   }
                   opppnantUnitsSubmited = true;
                   if(unitsSubmited){
                       launchGame();
                   }
            }
                break;
            case 6:{
                   QPair<int,int> frameIndex1;
                   QPair<int,int> frameIndex2;
                   frameIndex1.first = messageObj.value("x1").toInt();
                   frameIndex1.second = messageObj.value("y1").toInt();
                   frameIndex2.first = messageObj.value("x2").toInt();
                   frameIndex2.second = messageObj.value("y2").toInt();
                   BFrame *depFrame = battleForm->bScene()->frames().value(frameIndex1);
                   BFrame *desFrame = battleForm->bScene()->frames().value(frameIndex2);
                   if(battleForm->bScene()->phase() == BMapScene::PLACING)
                       battleForm->bScene()->setCurrentCityPlaying(m_opponantCity);
                   depFrame->mousePressEventAI();
                   desFrame->mousePressEventAI();
                   if(battleForm->bScene()->phase() == BMapScene::PLACING)
                       battleForm->bScene()->setCurrentCityPlaying(m_myCity);
            }
                break;
            case 7:{
                   QString st = messageObj.value("stat").toString();

                   if(st == "promote"){
                       if(battleForm->bScene()->isMeReady()){
                           battleForm->bScene()->setPhase(BMapScene::PROMOTING);
                           battleForm->setViewEnalble(true);
                           battleForm->bScene()->setIsMeReady(false);
                           battleForm->bScene()->setIsOpponateReady(false);
                       }else{
                           battleForm->bScene()->setIsOpponateReady(true);
                       }
                   }

                   else if(st == "play"){
                       if(battleForm->bScene()->isMeReady()){
                           battleForm->bScene()->setPhase(BMapScene::PLAYING);
                           battleForm->bScene()->setGeneralsToChooseA(battleForm->bScene()->bmap()->attackerMoves());
                           battleForm->bScene()->setGeneralsToChooseD(battleForm->bScene()->bmap()->deffenderMoves());
                           battleForm->bScene()->setCurrentCityPlaying(battleForm->bScene()->bmap()->attacker());
                           battleForm->setWindowTitle(battleForm->bScene()->bmap()->attacker()->country()->name()+
                                                " VS "+battleForm->bScene()->bmap()->deffender()->country()->name());
                           battleForm->bScene()->setIsMeReady(false);
                           battleForm->bScene()->setIsOpponateReady(false);
                           battleForm->setViewEnalble(true);
                       }else{
                           battleForm->bScene()->setIsOpponateReady(true);
                       }
                   }
            }
                break;
            case 8:{
                QPair<int,int> frameIndex;
                frameIndex.first = messageObj.value("x").toInt();
                frameIndex.second = messageObj.value("y").toInt();
                int unset = messageObj.value("unset").toInt();
                BFrame *depFrame = battleForm->bScene()->frames().value(frameIndex);
                if(battleForm->bScene()->phase() == BMapScene::PROMOTING)
                    battleForm->bScene()->setCurrentCityPlaying(m_opponantCity);
                unset==1?depFrame->mousePressEventAI():depFrame->mouseRightPressEventAI();
                if(battleForm->bScene()->phase() == BMapScene::PROMOTING)
                    battleForm->bScene()->setCurrentCityPlaying(m_myCity);
             }
                break;
//            default:
//                qDebug() << "nada";
//                break;
        }
        receivedSize = 0;
    }

}

void MultiplayerGame::battleEnded()
{

}

void MultiplayerGame::battleEndedA()
{

}

void MultiplayerGame::setGameServer(ServerEngin *gameServer)
{
    if (m_gameServer == gameServer)
        return;

    m_gameServer = gameServer;
    emit gameServerChanged(m_gameServer);
}

void MultiplayerGame::setServerSocket(QTcpSocket *serverSocket)
{
    if (m_serverSocket == serverSocket)
        return;

    m_serverSocket = serverSocket;
    emit serverSocketChanged(m_serverSocket);
}

void MultiplayerGame::setMyCity(City *myCity)
{
    if (m_myCity == myCity)
        return;

    m_myCity = myCity;
    emit myCityChanged(m_myCity);
}

void MultiplayerGame::setOpponantCity(City *opponantCity)
{
    if (m_opponantCity == opponantCity)
        return;

    m_opponantCity = opponantCity;
    emit opponantCityChanged(m_opponantCity);
}



