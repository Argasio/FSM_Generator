#include "staterect.h"
#include <QPainter>
StateRect::StateRect(QPoint cornerA, QPoint cornerB)
{
    rect = QRect::span(cornerA, cornerB);
    QPointF topLeft = rect.topLeft();
    rect.moveTo(0,0);
    this->moveBy(topLeft.x(), topLeft.y());
}

void StateRect::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawRoundedRect(rect,10,10);
}

QRectF StateRect::boundingRect() const
{
    return rect;
}

