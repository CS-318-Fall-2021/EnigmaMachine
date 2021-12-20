#include "rotor.h"

#include <QBrush>
#include <QPen>
#include <QVBoxLayout>
#include <QFont>
#include <charconv>

using namespace std;

//  Constructor with spec
Rotor::Rotor(qreal x, qreal y, int rotorSpec, QObject *parent)
    : QObject(parent) {
    back = new QGraphicsRectItem(x, y, 50, 200);
    QLinearGradient gradient(x+250, y, x+250, y+100);
    gradient.setColorAt(0, QColor(235, 235, 235, 255));
    gradient.setColorAt(1, QColor(196, 196, 196, 255));
    QBrush brush(gradient);
    QPen pen(Qt::black);

    back->setBrush(brush);
    back->setPen(pen);

    createNotches(x, y, pen);
    setUpSettingSign(x, y, pen, brush);

    setSetting(rotorSpec);
    setPos(0);    

    this->addToGroup(back);
}

//  Destructor
Rotor::~Rotor() {}

//  Shifts the spec'd Rotor one place forwards, changes the position by one
void Rotor::shift() {
    QChar temp = spec[0];
    spec.remove(0, 1);
    spec.append(temp);

    int front = pos[0];
    if (front == 25) hasRev = true;
    for (int i = 0; i < (int)pos.size()-1; ++i) {
        pos[i] = pos[i+1];
    }
    pos[pos.size()-1] = front;
}

//  Calls shift() the desired amount of times
void Rotor::shift(int times) {
    for (int i = 0; i < times; ++i) {
        this->shift();
    }
    num0->setText(QString::number(pos[0]));
    num0->setPos(seg4->boundingRect().x()+25-(0.5)*num0->boundingRect().width(),
                 seg4->boundingRect().y()+5);
    num1->setText(QString::number(pos[1]));
    num1->setPos(seg5->boundingRect().x()+25-(0.5)*num1->boundingRect().width(),
                 seg5->boundingRect().y()+5);
    num2->setText(QString::number(pos[2]));
    num2->setPos(seg6->boundingRect().x()+25-(0.5)*num2->boundingRect().width(),
                 seg6->boundingRect().y()+5);
    num3->setText(QString::number(pos[3]));
    num3->setPos(seg7->boundingRect().x()+25-(0.5)*num3->boundingRect().width(),
                 seg7->boundingRect().y()+5);
    num23->setText(QString::number(pos[23]));
    num23->setPos(seg1->boundingRect().x()+25-(0.5)*num23->boundingRect().width(),
                 seg1->boundingRect().y()+5);
    num24->setText(QString::number(pos[24]));
    num24->setPos(seg2->boundingRect().x()+25-(0.5)*num24->boundingRect().width(),
                 seg2->boundingRect().y()+5);
    num25->setText(QString::number(pos[25]));
    num25->setPos(seg3->boundingRect().x()+25-(0.5)*num25->boundingRect().width(),
                 seg3->boundingRect().y()+5);
}

//  Given the char value of the past character, will find its numerical
//      value per the alphabet, which will be the index for the next character
//      in the next Rotor
QChar Rotor::pass(QChar prev) {
    int index = alpha.indexOf(prev);
    return spec[index];
}

//  Given the char value of the past character, will pass through the
//      Rotor in the opposite direction
QChar Rotor::passBack(QChar prev) {
    int index = spec.indexOf(prev);
    return alpha[index];
}

//  Resets the settings
void Rotor::reset() {
    this->setSetting(setting);
    pos = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25};
    this->shift(0);
}

//  Getter method for the pos member
int Rotor::getPos() { return pos[0]; }

//  Getter method for the setting member
int Rotor::getSetting() {return setting; }

//  Returns whether the Rotor has fully revolved recently
bool Rotor::getHasRev() { return hasRev; }

//  Sets the position of the Rotor by the specification of the user
void Rotor::setPos(int newPos) { this->shift(newPos); }

//  Sets the setting of the Rotor by the specification of the user
void Rotor::setSetting(int rotorSpec) {
    setting = rotorSpec;
    switch (setting) {
        case 1: spec = first;
                settingSign = "I";
                break;
        case 2: spec = second;
                settingSign = "II";
                break;
        case 3: spec = third;
                settingSign = "III";
                break;
        case 4: spec = fourth;
                settingSign = "IV";
                break;
        case 5: spec = fifth;
                settingSign = "V";
                break;
    }
    settingSignText->setText(settingSign);
    settingSignText->setPos(settingSignBox->boundingRect().x()+20-(0.5)*settingSignText->boundingRect().width(),
                            settingSignBox->boundingRect().y()+20-(0.5)*settingSignText->boundingRect().height());
}

//  Sets up the box below each rotor that shows the # of the current rotor
void Rotor::setUpSettingSign(qreal x, qreal y, QPen pen, QBrush brush) {
    settingSignBox = new QGraphicsRectItem(x+5, y-55, 40, 40, back);
    settingSignBox->setBrush(brush);
    settingSignBox->setPen(pen);

    QFont font("TypeWriter", 15, 2);
    settingSignText = new QGraphicsSimpleTextItem(settingSignBox);
    settingSignText->setFont(font);
}

//  Sets the hasRev property back to false
void Rotor::setHasRev() { hasRev = false; }

//  Returns a formatted representation of the current setting of the Rotor
QString Rotor::curSetting() {
    QString result = "{";
    for (int i = 0; i < (int)spec.size()-1; ++i) {
        result += spec.at(i);
        result += ", ";
    }
    result += spec.at(spec.size()-1);
    result += "}";
    return result;
}

// Returns the character currently at the [0] position
char Rotor::curTop() { return spec.at(0).toLatin1(); }

//  Does annoying graphics calls
void Rotor::createNotches(qreal x, qreal y, QPen pen) {
    seg1 = new QGraphicsRectItem(x, y, 50, 28.6, back);
    seg1->setPen(pen);
    seg2 = new QGraphicsRectItem(x, y+28.6, 50, 28.6, back);
    seg2->setPen(pen);
    seg3 = new QGraphicsRectItem(x, y+57.2, 50, 28.6, back);
    seg3->setPen(pen);
    seg4 = new QGraphicsRectItem(x, y+85.8, 50, 28.6, back);
    seg4->setPen(pen);
    seg5 = new QGraphicsRectItem(x, y+114.4, 50, 28.6, back);
    seg5->setPen(pen);
    seg6 = new QGraphicsRectItem(x, y+143, 50, 28.6, back);
    seg6->setPen(pen);
    seg7 = new QGraphicsRectItem(x, y+171.6, 50, 28.4, back);
    seg7->setPen(pen);

    QFont font("TypeWriter", 10, 2);

    num0 = new QGraphicsSimpleTextItem(seg4);
    num0->setFont(font);
    num1 = new QGraphicsSimpleTextItem(seg5);
    num1->setFont(font);
    num2 = new QGraphicsSimpleTextItem(seg6);
    num2->setFont(font);
    num3 = new QGraphicsSimpleTextItem(seg7);
    num3->setFont(font);
    num23 = new QGraphicsSimpleTextItem(seg1);
    num23->setFont(font);
    num24 = new QGraphicsSimpleTextItem(seg2);
    num24->setFont(font);
    num25 = new QGraphicsSimpleTextItem(seg3);
    num25->setFont(font);
}

//  SLOTS
void Rotor::setRotor(int newSetting, int newPos) {
    this->reset();
    this->setSetting(newSetting);
    this->setPos(newPos);
}
