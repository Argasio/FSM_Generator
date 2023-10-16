#ifndef STATERECT_H
#define STATERECT_H

#include <QGraphicsItem>

class StateRect : public QGraphicsItem
{
    QRectF rect;
public:
    StateRect(QPoint cornerA, QPoint cornerB);
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget);
    QRectF boundingRect() const;
};

#endif // STATERECT_H
