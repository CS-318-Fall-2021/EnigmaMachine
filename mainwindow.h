#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMenuBar>
#include <QGroupBox>
#include <QWidgetAction>

#include "keyboard.h"
#include "textbox.h"
#include "settingswindow.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    void createActions();
    void createMenus();
    void createMarkers();

    QGraphicsScene *scene;
    QGraphicsView *view;

    // Screen Elements
    KeyBoard *keyBoard;
    TextBox *inputTextBox;
    TextBox *outputTextBox;
    QGraphicsPolygonItem *marker1;
    QGraphicsPolygonItem *marker2;
    QGraphicsLineItem *line1;
    QGraphicsLineItem *line2;

    // Menus
    QMenuBar *menuBar;
    QMenu *onlyMenu;

    // Actions
    QAction *resetAct;
    QAction *settingsAct;

    // Window
    SettingsWindow *settings;
};
#endif // MAINWINDOW_H
