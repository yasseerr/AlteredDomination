#include "mainmenu.h"
#include "ui_mainmenu.h"

MainMenu::MainMenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainMenu)
{
    ui->setupUi(this);
    connect(ui->pushButton,&QPushButton::clicked,this,&MainMenu::startGame);
}

MainMenu::~MainMenu()
{
    delete ui;
}

void MainMenu::startGame()
{
     mapView = new MapView(this);

}
