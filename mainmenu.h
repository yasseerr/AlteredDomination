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

public:
    explicit MainMenu(QWidget *parent = 0);
    ~MainMenu();
public slots  :
    void startGame();

private:
    Ui::MainMenu *ui;
    MapView *mapView;
};

#endif // MAINMENU_H
