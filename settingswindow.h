#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include <QDialog>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QRadioButton>
#include <QSpinBox>

#include "keyboard.h"

class SettingsWindow : public QDialog {
    Q_OBJECT

public:
    explicit SettingsWindow(KeyBoard *keyBoard, QWidget *parent);
    ~SettingsWindow();

private:
    void setUpr1();
    void setUpr2();
    void setUpr3();
    void setUpButtons();

    KeyBoard* keyBoard;

    QGroupBox* rotor1gb;
    QGroupBox* rotor2gb;
    QGroupBox* rotor3gb;

    QVector <QRadioButton*>* rotor1Radios;
    QVector <QRadioButton*>* rotor2Radios;
    QVector <QRadioButton*>* rotor3Radios;

    QSpinBox* rotor1Spin;
    QSpinBox* rotor2Spin;
    QSpinBox* rotor3Spin;

    QHBoxLayout* buttonsLayout;

    int rotor1Sel;
    int rotor2Sel;
    int rotor3Sel;

    int rotor1Pos;
    int rotor2Pos;
    int rotor3Pos;

signals:
   void rotor1Settings(int selection, int position);
   void rotor2Settings(int selection, int position);
   void rotor3Settings(int selection, int position);

public slots:
   void accept() override;
   void open() override;

};

#endif // SETTINGSWINDOW_H
