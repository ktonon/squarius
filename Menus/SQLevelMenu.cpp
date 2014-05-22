/**
 @file
 @author D2L Capture Team <dev@captual.com>
 @section LICENSE

 2008 - 2013 Desire2Learn Inc.
 All Rights Reserved.

 NOTICE:  All information contained herein is, and remains the property of
 Desire2Learn Incorporated and its suppliers, if any.  Dissemination of this
 information or reproduction of this material is strictly forbidden unless
 prior written permission is obtained from Desire2Learn Incorporated.
 */

#include "SQLevelMenu.h"
#include "ui_SQLevelMenu.h"

SQLevelMenu::SQLevelMenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SQLevelMenu)
{
    ui->setupUi(this);
    connect(ui->backButton, SIGNAL(clicked()), SIGNAL(back()));
    connect(ui->buttonGrid, SIGNAL(clicked(int)), SLOT(clicked(int)));
}

SQLevelMenu::~SQLevelMenu()
{
    delete ui;
}

void SQLevelMenu::setWorldMap(const SQPuzzle::WorldMap &map)
{
    _worldMap = map;
}

void SQLevelMenu::setWorld(SQPuzzle::World world)
{
    ui->buttonGrid->reset();
    SQPuzzle::LevelList list = _worldMap->value(world);
    foreach(SQPuzzle::Level level, *list.data())
        ui->buttonGrid->add(new SQButton(level));
}

void SQLevelMenu::clicked(int levelIndex)
{
    emit playLevel(SQPuzzle::Id(0, levelIndex));
}
