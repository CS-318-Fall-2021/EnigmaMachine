#include "settingswindow.h"

#include <QVBoxLayout>
#include <QSpinBox>
#include <QPushButton>

//  Constructor
SettingsWindow::SettingsWindow(KeyBoard *keyBoard, QWidget *parent) :
    QDialog(parent) {

    this->keyBoard = keyBoard;
    QVBoxLayout* base = new QVBoxLayout;

    setUpr1();
    setUpr2();
    setUpr3();
    setUpButtons();

    base->addWidget(rotor1gb);
    base->addWidget(rotor2gb);
    base->addWidget(rotor3gb);
    base->addLayout(buttonsLayout);

    setLayout(base);
    setWindowTitle("Settings");
}

//  Destructor
SettingsWindow::~SettingsWindow() {}

//  Set up the first Rotor selection graphics
void SettingsWindow::setUpr1() {
    rotor1gb = new QGroupBox(QString("Rotor #1"));

    QRadioButton* r1Sel1 = new QRadioButton("I");
    QRadioButton* r1Sel2 = new QRadioButton("II");
    QRadioButton* r1Sel3 = new QRadioButton("III");
    QRadioButton* r1Sel4 = new QRadioButton("IV");
    QRadioButton* r1Sel5 = new QRadioButton("V");

    rotor1Radios = new QVector <QRadioButton*> ({r1Sel1, r1Sel2, r1Sel3, r1Sel4, r1Sel5});

    rotor1Spin = new QSpinBox();
    rotor1Spin->setRange(0, 25);

    QHBoxLayout* rotor1Layout = new QHBoxLayout;
    rotor1Layout->addWidget(r1Sel1);
    rotor1Layout->addWidget(r1Sel2);
    rotor1Layout->addWidget(r1Sel3);
    rotor1Layout->addWidget(r1Sel4);
    rotor1Layout->addWidget(r1Sel5);
    rotor1Layout->addSpacing(50);
    rotor1Layout->addWidget(rotor1Spin);

    rotor1gb->setLayout(rotor1Layout);
}

//  Set up the second Rotor selection graphics
void SettingsWindow::setUpr2() {
    rotor2gb = new QGroupBox(QString("Rotor #2"));

    QRadioButton* r2Sel1 = new QRadioButton("I");
    QRadioButton* r2Sel2 = new QRadioButton("II");
    QRadioButton* r2Sel3 = new QRadioButton("III");
    QRadioButton* r2Sel4 = new QRadioButton("IV");
    QRadioButton* r2Sel5 = new QRadioButton("V");

    rotor2Radios = new QVector <QRadioButton*> ({r2Sel1, r2Sel2, r2Sel3, r2Sel4, r2Sel5});

    rotor2Spin = new QSpinBox();
    rotor2Spin->setRange(0, 25);

    QHBoxLayout* rotor2Layout = new QHBoxLayout;
    rotor2Layout->addWidget(r2Sel1);
    rotor2Layout->addWidget(r2Sel2);
    rotor2Layout->addWidget(r2Sel3);
    rotor2Layout->addWidget(r2Sel4);
    rotor2Layout->addWidget(r2Sel5);
    rotor2Layout->addSpacing(50);
    rotor2Layout->addWidget(rotor2Spin);

    rotor2gb->setLayout(rotor2Layout);
}

//  Set up the third Rotor selection graphics
void SettingsWindow::setUpr3() {
    rotor3gb = new QGroupBox(QString("Rotor #3"));

    QRadioButton* r3Sel1 = new QRadioButton("I");
    QRadioButton* r3Sel2 = new QRadioButton("II");
    QRadioButton* r3Sel3 = new QRadioButton("III");
    QRadioButton* r3Sel4 = new QRadioButton("IV");
    QRadioButton* r3Sel5 = new QRadioButton("V");

    rotor3Radios = new QVector <QRadioButton*> ({r3Sel1, r3Sel2, r3Sel3, r3Sel4, r3Sel5});

    rotor3Spin = new QSpinBox();
    rotor3Spin->setRange(0, 25);

    QHBoxLayout* rotor3Layout = new QHBoxLayout;
    rotor3Layout->addWidget(r3Sel1);
    rotor3Layout->addWidget(r3Sel2);
    rotor3Layout->addWidget(r3Sel3);
    rotor3Layout->addWidget(r3Sel4);
    rotor3Layout->addWidget(r3Sel5);
    rotor3Layout->addSpacing(50);
    rotor3Layout->addWidget(rotor3Spin);

    rotor3gb->setLayout(rotor3Layout);
}

void SettingsWindow::setUpButtons() {
    buttonsLayout = new QHBoxLayout;
    QPushButton* applyButton = new QPushButton("Apply");
    QPushButton* cancelButton = new QPushButton("Cancel");

    buttonsLayout->addWidget(applyButton);
    buttonsLayout->addWidget(cancelButton);

    connect(applyButton, &QPushButton::pressed, this, &QDialog::accept);
    connect(cancelButton, &QPushButton::pressed, this, &QDialog::reject);
}

//  Overridden QDialog function
void SettingsWindow::accept() {
    for (int i = 0; i < 5; ++i) {
        if (rotor1Radios->at(i)->isChecked()) rotor1Sel = i+1;
        if (rotor2Radios->at(i)->isChecked()) rotor2Sel = i+1;
        if (rotor3Radios->at(i)->isChecked()) rotor3Sel = i+1;
    }
    rotor1Pos = rotor1Spin->value();
    rotor2Pos = rotor2Spin->value();
    rotor3Pos = rotor3Spin->value();

    emit rotor1Settings(rotor1Sel, rotor1Pos);
    emit rotor2Settings(rotor2Sel, rotor2Pos);
    emit rotor3Settings(rotor3Sel, rotor3Pos);
    this->QDialog::accept();
}

//  SLOT
void SettingsWindow::open() {
    rotor1Radios->at(keyBoard->getR1Setting()-1)->setChecked(true);
    rotor1Spin->setValue(keyBoard->getR1Pos());
    rotor2Radios->at(keyBoard->getR2Setting()-1)->setChecked(true);
    rotor2Spin->setValue(keyBoard->getR2Pos());
    rotor3Radios->at(keyBoard->getR3Setting()-1)->setChecked(true);
    rotor3Spin->setValue(keyBoard->getR3Pos());
    this->QDialog::open();
}


