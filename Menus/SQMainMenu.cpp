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

#include "SQMainMenu.h"
#include "ui_SQMainMenu.h"

SQMainMenu::SQMainMenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SQMainMenu)
{
    ui->setupUi(this);
    connect(ui->playButton, SIGNAL(clicked()), SIGNAL(play()));
}

SQMainMenu::~SQMainMenu()
{
    delete ui;
}
