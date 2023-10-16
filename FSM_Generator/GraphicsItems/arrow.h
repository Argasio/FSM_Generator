#ifndef ARROW_H
#define ARROW_H

#include <QGraphicsItem>
#include <QObject>

class Arrow : public QGraphicsItem
{
    int triangleSize;
    QPolygonF tri;
    QPointF points[4];
public:
    Arrow(QGraphicsItem *parent = nullptr, QLineF* line = nullptr, int size = 0);
    void paint(QPainter *painter,
                  const QStyleOptionGraphicsItem *option,
                  QWidget *widget);
    QRectF boundingRect() const;

};

#endif // ARROW_H
