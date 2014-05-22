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

#ifndef SQMAINMENU_H
#define SQMAINMENU_H

#include <QWidget>

namespace Ui {
class SQMainMenu;
}

class SQMainMenu : public QWidget
{
    Q_OBJECT

public:
    explicit SQMainMenu(QWidget *parent = 0);
    ~SQMainMenu();

signals:
    void play();

private:
    Ui::SQMainMenu *ui;
};

#endif // SQMAINMENU_H
