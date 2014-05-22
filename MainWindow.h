/**
 * @file
 * @author Kevin Tonon <kevin@betweenconcepts.com>
 * @section LICENSE
 * 2013 Kevin Tonon
 * All Rights Reserved
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMatrix4x4>
#include <QMainWindow>
#include "Game/SQPuzzle.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    enum StackedWidgetIndex {
        MainMenu = 0,
        WorldMenu = 1,
        LevelMenu = 2,
        Engine = 3
    };

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void showMainMenu();
    void showWorldMenu();
    void showLevelMenu(int worldIndex);
    void playLevel(const SQPuzzle::Id &puzzleId);

    void engineChangedState();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
