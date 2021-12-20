#ifndef TEXTBOX_H
#define TEXTBOX_H

#include <QGraphicsItemGroup>

class TextBox : public QObject, public QGraphicsItemGroup{
    Q_OBJECT

public:
    explicit TextBox(qreal x, qreal y, bool isInputBox, QObject *parent = Q_NULLPTR);
    virtual ~TextBox();

    // overridden methods
    virtual QRectF boundingRect() const override;

private:
    bool isInputBox;
    QGraphicsRectItem *back;
    QString *labelContents;
    QGraphicsTextItem *label;

public slots:
    void updateText(QChar input, bool box);
    void reset();

};

#endif // TEXTBOXBACK_H
