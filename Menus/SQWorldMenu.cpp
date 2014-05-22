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

#include "SQWorldMenu.h"
#include "ui_SQWorldMenu.h"
#include <Game/SQPuzzle.h>

SQWorldMenu::SQWorldMenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SQWorldMenu)
{
    ui->setupUi(this);
    connect(ui->backButton, SIGNAL(clicked()), SIGNAL(back()));
    connect(ui->buttonGrid, SIGNAL(clicked(int)), SIGNAL(showWorld(int)));
}

SQWorldMenu::~SQWorldMenu()
{
    delete ui;
}

void SQWorldMenu::setWorldMap(const SQPuzzle::WorldMap &map)
{
    foreach(SQPuzzle::World world, map->keys())
        ui->buttonGrid->add(new SQButton(world));
}
