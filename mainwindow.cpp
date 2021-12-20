#include "mainwindow.h"

#include <QMenu>
#include <QObject>
#include <QChar>
#include <QWidgetAction>
#include <QWidget>
#include <QRadioButton>
#include <QVBoxLayout>

#include "rotor.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {

    scene = new QGraphicsScene(QRect(0, 0, 1650, 900));
    view = new QGraphicsView(scene);
    setCentralWidget(view);
    view->setFixedSize(1650, 900);
    view->setRenderHint(QPainter::Antialiasing);
    view->show();

    menuBar = new QMenuBar(view);

    QLinearGradient gradient(QPointF(825, 0), QPointF(825, 900));
    QGradientStop one(0.01, QColor(64, 64, 64, 255));
    QGradientStop two(0.99, QColor(128, 128, 128, 255));
    gradient.setStops( QGradientStops{ one, two });
    scene->setBackgroundBrush(gradient);

    keyBoard = new KeyBoard();
    inputTextBox = new TextBox(100, 200, true);
    outputTextBox = new TextBox(1050, 200, false);
    createMarkers();

    settings = new SettingsWindow(keyBoard, this);

    createActions();
    createMenus();

    connect(keyBoard, &KeyBoard::keyUsed, inputTextBox, &TextBox::updateText);
    connect(keyBoard, &KeyBoard::keyUsed, outputTextBox, &TextBox::updateText);

    connect(settings, &QDialog::accepted, inputTextBox, &TextBox::reset);
    connect(settings, &QDialog::accepted, outputTextBox, &TextBox::reset);
    connect(settings, &SettingsWindow::rotor1Settings, keyBoard->getR1(), &Rotor::setRotor);
    connect(settings, &SettingsWindow::rotor2Settings, keyBoard->getR2(), &Rotor::setRotor);
    connect(settings, &SettingsWindow::rotor3Settings, keyBoard->getR3(), &Rotor::setRotor);

    scene->addItem(marker1);
    scene->addItem(marker2);
    scene->addItem(line1);
    scene->addItem(line2);
    scene->addItem(keyBoard);
    scene->addItem(inputTextBox);
    scene->addItem(outputTextBox);
    keyBoard->grabKeyboard();
}

MainWindow::~MainWindow() {}

void MainWindow::createActions() {
    resetAct = new QAction("Reset", this);
    connect(resetAct, &QAction::triggered, keyBoard, &KeyBoard::reset);
    connect(resetAct, &QAction::triggered, inputTextBox, &TextBox::reset);
    connect(resetAct, &QAction::triggered, outputTextBox, &TextBox::reset);

    settingsAct = new QAction("Settings", this);
    connect(settingsAct, &QAction::triggered, settings, &SettingsWindow::open);
}

void MainWindow::createMenus() {
    onlyMenu = menuBar->addMenu("Menu");
    onlyMenu->addAction(resetAct);
    onlyMenu->addAction(settingsAct);
}

void MainWindow::createMarkers() {
    QPointF one(670, 240);
    QPointF two(690, 250);
    QPointF three(670, 260);

    QPointF four(980, 240);
    QPointF five(960, 250);
    QPointF six(980, 260);

    QPolygonF triangleOne({one, two, three});
    QPolygonF triangleTwo({four, five, six});

    QPen pen(Qt::black);
    pen.setWidth(1);

    marker1 = new QGraphicsPolygonItem(triangleOne);
    marker2 = new QGraphicsPolygonItem(triangleTwo);
    line1 = new QGraphicsLineItem(760, 250, 790, 250);
    line2 = new QGraphicsLineItem(860, 250, 890, 250);

    marker1->setBrush(QBrush(Qt::darkGray));
    marker2->setBrush(QBrush(Qt::darkGray));
    line1->setPen(pen);
    line2->setPen(pen);
}

