#ifndef KEY_H
#define KEY_H

#include <QGraphicsItem>
#include <QPainter>
#include <QLabel>
#include <QObject>

class Key: public QObject, public QGraphicsItem {
    Q_OBJECT

public:
    explicit Key(qreal x, qreal y, QChar label, QObject *parent = Q_NULLPTR);
    ~Key();
    QChar getLabel();
    void setLit();

    // overridden methods
    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter,
                       const QStyleOptionGraphicsItem *option,
                       QWidget *widget) override;

private:
    qreal x;
    qreal y;
    QChar label;
    bool lit;

};

#endif // KEY_H
