#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <QGraphicsItemGroup>
#include <QObject>

#include "key.h"
#include "rotor.h"
#include "reflector.h"

class KeyBoard: public QObject, public QGraphicsItemGroup {
    Q_OBJECT

public:
    explicit KeyBoard(QObject *parent = Q_NULLPTR);
    ~KeyBoard();
    QChar passThrough(QChar input);

    //  Getters
    int getR1Setting();
    int getR2Setting();
    int getR3Setting();
    int getR1Pos();
    int getR2Pos();
    int getR3Pos();
    Rotor* getR1();
    Rotor* getR2();
    Rotor* getR3();

protected:
    void keyPressEvent(QKeyEvent *event) override;

private:
    QList <Key *> list;
    Key *lastLit = Q_NULLPTR;
    Rotor *first;
    Rotor *second;
    Rotor *third;
    Reflector *ref;

signals:
    void keyUsed(QChar output, bool forInputBox);

public slots:
    void reset();
};

#endif // KEYBOARD_H
