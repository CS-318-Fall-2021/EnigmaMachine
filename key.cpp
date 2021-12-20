#include "key.h"

#include <stdlib.h>
#include <QRadialGradient>
#include <QColor>

//  Constructor
Key::Key(qreal x, qreal y, QChar label, QObject *parent)
    : QObject(parent) {
    this->x = x;
    this->y = y;
    this->label = label;
    lit = false;
}

//  Destructor
Key::~Key() {}

//  Getter for the label
QChar Key::getLabel() { return label; }

//  Changes the bool pressed value from true to false or vice versa
void Key::setLit() {
    if (lit) {
        lit = false;
        update();
    } else {
        lit = true;
        update();
    }
}

//  @Overridden
QRectF Key::boundingRect() const { return QRect(x, y, 100, 100); }

// @Overridden
void Key::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    QRectF rect = boundingRect();

    QPen pen1(Qt::black, 1);
    QPen pen2(Qt::white, 2);
    QPen pen3(QColor(255, 247, 0, 255), 2);

    QLinearGradient back(x+50, y, x+50, y+100);
    back.setColorAt(0, QColor(156, 156, 156, 255));
    back.setColorAt(1, QColor(131, 131, 131, 255));
    QBrush backBrush(back);

    QRadialGradient gradient(rect.center(), 35, rect.center());
    gradient.setColorAt(0, QColor(255, 247, 74, 150));
    gradient.setColorAt(1, QColor(255, 247, 74, 0));
    QBrush glowBrush(gradient);

    QFont font("TypeWriter", 24, 2);

    painter->setPen(pen1);
    painter->drawRect(rect);

    painter->fillRect(rect, backBrush);
    if (lit) {
        painter->fillRect(rect, glowBrush);
        painter->setPen(pen3);
        painter->setFont(font);
        painter->drawText(rect, Qt::AlignCenter, label);
    } else {
        painter->fillRect(rect, backBrush);
        painter->setPen(pen2);
        painter->setFont(font);
        painter->drawText(rect, Qt::AlignCenter, label);
    }
}


