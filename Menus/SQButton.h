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

#ifndef SQBUTTON_H
#define SQBUTTON_H

#include <QWidget>

namespace Ui {
class SQButton;
}

class SQButton : public QWidget
{
    Q_OBJECT

public:
    explicit SQButton(int index, QWidget *parent = 0);
    ~SQButton();

signals:
    void clicked(int index);

private slots:
    void clicked();

private:
    Ui::SQButton *ui;
    int _index;
};

#endif // SQBUTTON_H
