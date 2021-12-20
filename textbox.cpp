#include "textbox.h"

#include <QBrush>
#include <QPen>
#include <QFont>

//  Constructor
TextBox::TextBox(qreal x, qreal y, bool isInputBox, QObject *parent)
    : QObject(parent) {
    this->isInputBox = isInputBox;

    back = new QGraphicsRectItem(x, y, 500, 100);
    QLinearGradient gradient(x+250, y, x+250, y+100);
    gradient.setColorAt(0, QColor(235, 235, 235, 255));
    gradient.setColorAt(1, QColor(196, 196, 196, 255));
    QBrush brush(gradient);

    back->setBrush(brush);
    back->setPen(QPen(Qt::black));

    labelContents = new QString();
    label = new QGraphicsTextItem(*labelContents, back);
    label->setTextWidth(480);
    label->setFont(QFont("System", 17, 2));
    label->setDefaultTextColor(Qt::black);
    label->setPos(x+10, y);

    this->addToGroup(back);
}

//  Destructor
TextBox::~TextBox() {}

//  Overridden method
QRectF TextBox::boundingRect() const { return back->rect(); }

//  SLOT
void TextBox::updateText(QChar input, bool forInputBox) {
    if (forInputBox == isInputBox) {
        labelContents->push_back(input);
        label->setPlainText(*labelContents);
    }
}

//  SLOT
void TextBox::reset() {
    labelContents->clear();
    label->setPlainText(*labelContents);
}
