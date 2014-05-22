/**
 * @file
 * @author Kevin Tonon <kevin@betweenconcepts.com>
 * @section LICENSE
 * 2013 Kevin Tonon
 * All Rights Reserved
 */

#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->mainMenu, SIGNAL(play()), SLOT(showWorldMenu()));
    connect(ui->worldMenu, SIGNAL(back()), SLOT(showMainMenu()));
    connect(ui->worldMenu, SIGNAL(showWorld(int)), SLOT(showLevelMenu(int)));
    connect(ui->levelMenu, SIGNAL(back()), SLOT(showWorldMenu()));
    connect(ui->levelMenu, SIGNAL(playLevel(SQPuzzle::Id)), SLOT(playLevel(SQPuzzle::Id)));
    SQPuzzle::WorldMap map = SQPuzzle::worldMap();
    ui->worldMenu->setWorldMap(map);
    ui->levelMenu->setWorldMap(map);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showMainMenu()
{
    ui->stackedWidget->setCurrentIndex(MainMenu);
}

void MainWindow::showWorldMenu()
{
    ui->stackedWidget->setCurrentIndex(WorldMenu);
}

void MainWindow::showLevelMenu(int worldIndex)
{
    ui->levelMenu->setWorld(worldIndex);
    ui->stackedWidget->setCurrentIndex(LevelMenu);
}

void MainWindow::playLevel(const SQPuzzle::Id &puzzleId)
{
    ui->engine->setPuzzleId(puzzleId);
    ui->stackedWidget->setCurrentIndex(Engine);
}

void MainWindow::engineChangedState()
{
//    ui->textBrowser->setText(ui->widget->toString());
}
