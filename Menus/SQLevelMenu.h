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

#ifndef SQLEVELMENU_H
#define SQLEVELMENU_H

#include <QWidget>
#include <Game/SQPuzzle.h>

namespace Ui {
class SQLevelMenu;
}

class SQLevelMenu : public QWidget
{
    Q_OBJECT

public:
    explicit SQLevelMenu(QWidget *parent = 0);
    ~SQLevelMenu();

    void setWorldMap(const SQPuzzle::WorldMap &map);
    void setWorld(SQPuzzle::World world);

signals:
    void back();
    void playLevel(const SQPuzzle::Id &puzzleId);

private slots:
    void clicked(int levelIndex);

private:
    Ui::SQLevelMenu *ui;
    SQPuzzle::WorldMap _worldMap;
};

#endif // SQLEVELMENU_H
