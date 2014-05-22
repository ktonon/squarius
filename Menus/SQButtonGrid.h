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

#ifndef SQBUTTONGRID_H
#define SQBUTTONGRID_H

#include <QtCore>
#include <QWidget>
#include "SQButton.h"

namespace Ui {
class SQButtonGrid;
}

class SQButtonGrid : public QWidget
{
    Q_OBJECT

public:
    explicit SQButtonGrid(QWidget *parent = 0);
    ~SQButtonGrid();

    void setColumnCount(int n);

    void add(SQButton *button);
    void reset();

signals:
    void clicked(int index);

private:
    Ui::SQButtonGrid *ui;

    QList<SQButton*> _buttons;
    int _columnCount;
};

#endif // SQBUTTONGRID_H
