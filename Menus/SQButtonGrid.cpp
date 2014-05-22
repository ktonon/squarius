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

#include "SQButtonGrid.h"
#include "ui_SQButtonGrid.h"

SQButtonGrid::SQButtonGrid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SQButtonGrid),
    _columnCount(4)
{
    ui->setupUi(this);
}

SQButtonGrid::~SQButtonGrid()
{
    delete ui;
}

void SQButtonGrid::setColumnCount(int n)
{
    _columnCount = n;
}

void SQButtonGrid::add(SQButton *button)
{
    int index = _buttons.count();
    _buttons << button;
    connect(button, SIGNAL(clicked(int)), SIGNAL(clicked(int)));

    // TODO: does the grid take ownership of button?
    ui->gridLayout->addWidget(button, index / _columnCount, index % _columnCount, 1, 1);
}

void SQButtonGrid::reset()
{
    foreach(SQButton *button, _buttons)
        ui->gridLayout->removeWidget(button);
    _buttons.clear();
}
