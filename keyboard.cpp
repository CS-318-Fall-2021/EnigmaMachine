#include "keyboard.h"

#include "key.h"

#include <QDebug>
#include <QKeyEvent>

//  Constructor
KeyBoard::KeyBoard(QObject *parent)
    : QObject(parent) {

    first = new Rotor(700, 150, 1);
    second = new Rotor(800, 150, 2);
    third = new Rotor(900, 150, 3);
    ref = new Reflector(1);

    Key *qKey = new Key(100, 450, 'Q', Q_NULLPTR);
    Key *wKey = new Key(250, 450, 'W', Q_NULLPTR);
    Key *eKey = new Key(400, 450, 'E', Q_NULLPTR);
    Key *rKey = new Key(550, 450, 'R', Q_NULLPTR);
    Key *tKey = new Key(700, 450, 'T', Q_NULLPTR);
    Key *yKey = new Key(850, 450, 'Y', Q_NULLPTR);
    Key *uKey = new Key(1000, 450, 'U', Q_NULLPTR);
    Key *iKey = new Key(1150, 450, 'I', Q_NULLPTR);
    Key *oKey = new Key(1300, 450, 'O', Q_NULLPTR);
    Key *pKey = new Key(1450, 450, 'P', Q_NULLPTR);

    Key *aKey = new Key(150, 600, 'A', Q_NULLPTR);
    Key *sKey = new Key(300, 600, 'S', Q_NULLPTR);
    Key *dKey = new Key(450, 600, 'D', Q_NULLPTR);
    Key *fKey = new Key(600, 600, 'F', Q_NULLPTR);
    Key *gKey = new Key(750, 600, 'G', Q_NULLPTR);
    Key *hKey = new Key(900, 600, 'H', Q_NULLPTR);
    Key *jKey = new Key(1050, 600, 'J', Q_NULLPTR);
    Key *kKey = new Key(1200, 600, 'K', Q_NULLPTR);
    Key *lKey = new Key(1350, 600, 'L', Q_NULLPTR);

    Key *zKey = new Key(200, 750, 'Z', Q_NULLPTR);
    Key *xKey = new Key(350, 750, 'X', Q_NULLPTR);
    Key *cKey = new Key(500, 750, 'C', Q_NULLPTR);
    Key *vKey = new Key(650, 750, 'V', Q_NULLPTR);
    Key *bKey = new Key(800, 750, 'B', Q_NULLPTR);
    Key *nKey = new Key(950, 750, 'N', Q_NULLPTR);
    Key *mKey = new Key(1100, 750, 'M', Q_NULLPTR);

    // alphabetical order
    list = {
        aKey, bKey, cKey, dKey, eKey, fKey, gKey, hKey, iKey, jKey,
        kKey, lKey, mKey, nKey, oKey, pKey, qKey, rKey, sKey,
        tKey, uKey, vKey, wKey, xKey, yKey, zKey
    };

    this->addToGroup(first);
    this->addToGroup(second);
    this->addToGroup(third);

    for (QGraphicsItem *x: list) { this->addToGroup(x); };
}

//  Destructor
KeyBoard::~KeyBoard() {}

//  Passes given key input through EnigmaMachine
QChar KeyBoard::passThrough(QChar input) {
    QChar output;
    output = first->pass(input);
    output = second->pass(output);
    output = third->pass(output);
    output = ref->pass(output);
    output = third->passBack(output);
    output = second->passBack(output);
    output = first->passBack(output);

    first->shift(1);
    if(first->getHasRev()) {
        second->shift(1);
        first->setHasRev();
    }
    if (second->getHasRev()) {
        third->shift(1);
        second->setHasRev();
    }

    return output;
}

int KeyBoard::getR1Setting() { return first->getSetting(); };
int KeyBoard::getR2Setting() { return second->getSetting(); };
int KeyBoard::getR3Setting() { return third->getSetting(); };
int KeyBoard::getR1Pos() { return first->getPos(); };
int KeyBoard::getR2Pos() { return second->getPos(); };
int KeyBoard::getR3Pos() { return third->getPos(); };
Rotor* KeyBoard::getR1() { return first; };
Rotor* KeyBoard::getR2() { return second; };
Rotor* KeyBoard::getR3() { return third; };


void KeyBoard::keyPressEvent(QKeyEvent *event) {
    if (event->key() >= Qt::Key_A && event->key() <= Qt::Key_Z) {
        Key *selected = list[(int)(event->key()-Qt::Key_A)];
        emit keyUsed(selected->getLabel(), true);

        Key *newKey = list[(this->passThrough(selected->getLabel()).unicode()-65)];
        emit keyUsed(newKey->getLabel(), false);

        if (lastLit != nullptr) lastLit->setLit();
        lastLit = newKey;

        newKey->setLit();
    }
}

void KeyBoard::reset() {
    first->reset();
    second->reset();
    third->reset();
    lastLit->setLit();
    lastLit = nullptr;
}
