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

#ifndef SQWORLDMENU_H
#define SQWORLDMENU_H

#include "Game/SQPuzzle.h"
#include <QWidget>

namespace Ui {
class SQWorldMenu;
}

class SQWorldMenu : public QWidget
{
    Q_OBJECT

public:
    explicit SQWorldMenu(QWidget *parent = 0);
    ~SQWorldMenu();

    void setWorldMap(const SQPuzzle::WorldMap &map);

signals:
    void back();
    void showWorld(int index);

private:
    Ui::SQWorldMenu *ui;
};

#endif // SQWORLDMENU_H
