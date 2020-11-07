#ifndef BATTLEFORM_H
#define BATTLEFORM_H

#include <QWidget>

#include <graphics/bmapscene.h>

namespace Ui {
class BattleForm;
}

class BattleForm : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(BMapScene* bScene READ bScene WRITE setBScene NOTIFY bSceneChanged)

public:
    explicit BattleForm(QWidget *parent = 0);
    ~BattleForm();

    BMapScene* bScene() const;

public slots:
    void setBScene(BMapScene* bScene);
    void publishMaptoQMl();
    Q_INVOKABLE void setPromote();
    Q_INVOKABLE void play();
    Q_INVOKABLE void surrender();
    void onBattleEndedA();
    void onBattleEndedD();
signals:
    void bSceneChanged(BMapScene* bScene);
    Q_INVOKABLE void battleEnded();
    Q_INVOKABLE void battleEndedA();

private:
    Ui::BattleForm *ui;
    BMapScene* m_bScene;
};

#endif // BATTLEFORM_H
