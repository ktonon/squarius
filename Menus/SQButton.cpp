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

#include "SQButton.h"
#include "ui_SQButton.h"

SQButton::SQButton(int index, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SQButton),
    _index(index)
{
    ui->setupUi(this);
    connect(ui->pushButton, SIGNAL(clicked()), SLOT(clicked()));
    ui->pushButton->setText(QString::number(index));
}

SQButton::~SQButton()
{
    delete ui;
}

void SQButton::clicked()
{
    emit clicked(_index);
}
