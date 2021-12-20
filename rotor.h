#ifndef ROTOR_H
#define ROTOR_H

#include <vector>
#include <string>
#include <QString>
#include <QObject>
#include <QGraphicsItemGroup>
#include <QGraphicsRectItem>

class Rotor : public QObject, public QGraphicsItemGroup {
    Q_OBJECT

public:
    explicit Rotor(QObject *parent = Q_NULLPTR);
    explicit Rotor(qreal x, qreal y, int rotorSpec, QObject *parent = Q_NULLPTR);
    ~Rotor();
    void shift(int times);
    void reset();
    QChar pass(QChar prev);
    QChar passBack(QChar prev);
    int getPos();
    int getSetting();
    bool getHasRev();
    void setHasRev();

private:
    void shift();
    void setPos(int input);
    void setSetting(int rotorSpec);
    void setUpSettingSign(qreal x, qreal y, QPen pen, QBrush brush);
    QString curSetting();
    char curTop();
    void createNotches(qreal x, qreal y, QPen pen);

    QString spec;
    QString alpha    = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    //                  0         1         2
    //                  01234567890123456789012345
    QString first    = "EKMFLGDQVZNTOWYHXUSPAIBRCJ";
    QString second   = "AJDKSIRUXBLHWTMCQGZNPYFVOE";
    QString third    = "BDFHJLCPRTXVZNYEIWGAKMUSQO";
    QString fourth   = "ESOVPZJAYQUIRHXLNFTGKDCMWB";
    QString fifth    = "VZBRGITYUPSDNHLXAWMJQOFECK";

    std::vector <int> pos = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25}; //way too lazy to think of something clever
    int setting;
    QString settingSign;
    bool hasRev = false;
    QGraphicsRectItem *back;

    QGraphicsRectItem *seg1;
    QGraphicsRectItem *seg2;
    QGraphicsRectItem *seg3;
    QGraphicsRectItem *seg4;
    QGraphicsRectItem *seg5;
    QGraphicsRectItem *seg6;
    QGraphicsRectItem *seg7;


    QGraphicsSimpleTextItem *num0;
    QGraphicsSimpleTextItem *num1;
    QGraphicsSimpleTextItem *num2;
    QGraphicsSimpleTextItem *num3;
    QGraphicsSimpleTextItem *num23;
    QGraphicsSimpleTextItem *num24;
    QGraphicsSimpleTextItem *num25;

    QGraphicsRectItem *settingSignBox;
    QGraphicsSimpleTextItem *settingSignText;

public slots:
    void setRotor(int newSetting, int newPos);
};

#endif // ROTOR_H
