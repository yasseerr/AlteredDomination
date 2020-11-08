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

public:

    QQuickView  *battleResultUI;

    explicit BattleForm(QWidget *parent = 0);
    ~BattleForm();

    BMapScene* bScene() const;

    BattleAI* battleAI() const;

    QString resultText() const;

    bool closeYet() const;

public slots:
    void setBScene(BMapScene* bScene);
    void publishMaptoQMl();
    Q_INVOKABLE void setPromote();
    Q_INVOKABLE void play();
    Q_INVOKABLE void surrender();
    Q_INVOKABLE void draw();

    void onBattleEndedA();
    void onBattleEndedD();
    void setBattleAI(BattleAI* battleAI);

    void setResultText(QString resultText);

    void setCloseYet(bool closeYet);

signals:
    void bSceneChanged(BMapScene* bScene);
    Q_INVOKABLE void battleEnded();
    Q_INVOKABLE void battleEndedA();

    void battleAIChanged(BattleAI* battleAI);

    void resultTextChanged(QString resultText);

    void closeYetChanged(bool closeYet);

private:
    Ui::BattleForm *ui;
    BMapScene* m_bScene;
    BattleAI* m_battleAI;
    QString m_resultText;
    bool m_closeYet;
};

#endif // BATTLEFORM_H
