#ifndef HOMEMENU_H
#define HOMEMENU_H

#include <QObject>
#include <QQuickView>
#include <mainmenu.h>
class HomeMenu : public QQuickView
{
    Q_OBJECT
    Q_PROPERTY(QString mapData READ mapData WRITE setMapData NOTIFY mapDataChanged)
    Q_PROPERTY(QString savesData READ savesData WRITE setSavesData NOTIFY savesDataChanged)
    Q_PROPERTY(QString tutoData READ tutoData WRITE setTutoData NOTIFY tutoDataChanged)
    QString m_mapData;    
    QString m_savesData;    
    QString m_tutoData;

public:
    MainMenu *game;

    HomeMenu();
    Q_INVOKABLE void startGame(QString cntr,int mode);
    Q_INVOKABLE void loadGame(QString cntr,int turn,QString gameSaveString);
    Q_INVOKABLE void deleteGameSave(QString newfilString);
    Q_INVOKABLE void quitApp();

    QString mapData() const;
    QString savesData() const;

    QString tutoData() const;

public slots:
    void setMapData(QString mapData);
    void setSavesData(QString savesData);
    void onReturnHome();

    void setTutoData(QString tutoData);

signals:
    void mapDataChanged(QString mapData);
    void savesDataChanged(QString savesData);
    void tutoDataChanged(QString tutoData);
};

#endif // HOMEMENU_H
