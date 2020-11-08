#ifndef BATTLEFORM_H
#define BATTLEFORM_H

#include <QQuickView>
#include <QQuickWidget>
#include <QWidget>

#include <graphics/bmapscene.h>


class BattleAI;
namespace Ui {
class BattleForm;
}

class BattleForm : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(BMapScene* bScene READ bScene WRITE setBScene NOTIFY bSceneChanged)
    Q_PROPERTY(BattleAI* battleAI READ battleAI WRITE setBattleAI NOTIFY battleAIChanged)
    Q_PROPERTY(QString resultText READ resultText WRITE setResultText NOTIFY resultTextChanged)
    Q_PROPERTY(bool closeYet READ closeYet WRITE setCloseYet NOTIFY closeYetChanged)
    Q_PROPERTY(bool isMultiplayer READ isMultiplayer WRITE setIsMultiplayer NOTIFY isMultiplayerChanged)
    Q_PROPERTY(bool isMassiveBattle READ isMassiveBattle WRITE setIsMassiveBattle NOTIFY isMassiveBattleChanged)
    Q_PROPERTY(QTcpSocket* serverSocket READ serverSocket WRITE setServerSocket NOTIFY serverSocketChanged)


public:

    QQuickView  *battleResultUI;
    qreal previousScale;

    explicit BattleForm(QTcpSocket *serv = nullptr,QWidget *parent = 0);
    ~BattleForm();

    BMapScene* bScene() const;

    BattleAI* battleAI() const;

    QString resultText() const;

    bool closeYet() const;

    bool isMultiplayer() const;

    QTcpSocket* serverSocket() const;

    bool isMassiveBattle() const;

public slots:
    void setBScene(BMapScene* bScene);
    void publishMaptoQMl();
    Q_INVOKABLE void setPromote();
    Q_INVOKABLE void play();
    Q_INVOKABLE void surrender();
    Q_INVOKABLE void draw();
    Q_INVOKABLE void zoom(qreal z);
    void setViewEnalble(bool b);
    void bmapLoaded(bool p);
    void fixScale();

    void onBattleEndedA();
    void onBattleEndedD();
    void setBattleAI(BattleAI* battleAI);

    void setResultText(QString resultText);

    void setCloseYet(bool closeYet);

    void setIsMultiplayer(bool isMultiplayer);

    void setServerSocket(QTcpSocket* serverSocket);

    void setIsMassiveBattle(bool isMassiveBattle);

signals:
    void bSceneChanged(BMapScene* bScene);
    Q_INVOKABLE void battleEnded();
    Q_INVOKABLE void battleEndedA();
    Q_INVOKABLE void bmapLoadedSig();

    void battleAIChanged(BattleAI* battleAI);

    void resultTextChanged(QString resultText);

    void closeYetChanged(bool closeYet);

    void isMultiplayerChanged(bool isMultiplayer);

    void serverSocketChanged(QTcpSocket* serverSocket);

    void isMassiveBattleChanged(bool isMassiveBattle);

private:
    Ui::BattleForm *ui;
    BMapScene* m_bScene;
    BattleAI* m_battleAI;
    QString m_resultText;
    bool m_closeYet;
    bool m_isMultiplayer;
    QTcpSocket* m_serverSocket;
    bool m_isMassiveBattle;
};

#endif // BATTLEFORM_H
