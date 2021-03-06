#ifndef MAINMENU_H
#define MAINMENU_H

#include <QWidget>
#include <graphics/mapview.h>

namespace Ui {
class MainMenu;
}

class MainMenu : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(MapView* mapView READ mapView WRITE setMapView NOTIFY mapViewChanged)
    Q_PROPERTY(QString activePlayerStr READ activePlayerStr WRITE setActivePlayerStr NOTIFY activePlayerStrChanged)

public:

    explicit MainMenu(QString c,int m,int t,QString gameSave,QWidget *parent = 0);
    MainMenu(QString gamesave,QWidget *parent = 0);
    ~MainMenu();
    MapView* mapView() const;

    QString activePlayerStr() const;


public slots  :
    void startGame();

    void setMapView(MapView* mapView);

    void setActivePlayerStr(QString activePlayerStr);


    Q_INVOKABLE void reDisplayCities();
    Q_INVOKABLE void reDisplayCountries();
    Q_INVOKABLE void focusOnCity(City *c);
    Q_INVOKABLE void runNextTurn();
    void onAttackerWon(City *C);

    virtual void closeEvent(QCloseEvent *ev);
    virtual void hideEvent(QHideEvent *event);

signals:
    void mapViewChanged(MapView* mapView);
    void activePlayerStrChanged(QString activePlayerStr);

    void sendCityToDisplay(City *c);
    void clearCitiesInDisplay();

    void sendCountryToRanking(Country *c,int r);
    void clearCountriesInRanking();


private:

    Ui::MainMenu *ui;

    MapView *m_mapView;

    QString m_activePlayerStr;

};

#endif // MAINMENU_H
