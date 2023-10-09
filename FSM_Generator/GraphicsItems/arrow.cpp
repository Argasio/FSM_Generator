#include "arrow.h"
#include <QList>
#include <QPainter>

/**
 * @brief Arrow::Arrow creates an arrow graphic item
 * @details: we draw a line centered at local 0,0, with end at [line_length], 0
 *          then we add two points to form a triangle, whose apex is the line end
 *          then we use the graphicsitem properties to apply the transofmation offset and angle
 *          these two directly taken from the viewport drawn line
 *          the shape is so formed by 4 points (line start, arrow head, 2 arrow points)
 * @param parent
 * @param line line that generates the arrow from start to head in the viewport
 * @param size size of the arrow head
 */
Arrow::Arrow(QGraphicsItem *parent , QLineF* line, int size)
    : QGraphicsItem::QGraphicsItem(parent)
{
    this-> triangleSize = size;
    float angle = line->angle();
    float dx; float dy;
    dx = triangleSize*qSin(qDegreesToRadians(60));
    dy = triangleSize*qCos(qDegreesToRadians(60));
    points[0] = QPointF(0,0); // start at 0
    points[1] = QPointF(line->length(),0);// arrow head stems from 0 and has length equal to the drawn line
    points[2] = QPointF(points[1].x()-dx, points[1].y()+dy); // triangle vertex 1
    points[3] = QPointF(points[1].x()-dx, points[1].y()-dy); // triangle vertex 2
    this->tri = QPolygonF(QList<QPointF>{points[1], points[2], points[3]}); // form triangle
    // apply the desired rotation to the Item
    this->setRotation(-angle);
    // apply the desired position to the item
    this->moveBy(line->p1().x(), line->p1().y());



}

/**
 * @brief Arrow::paint used to draw the shapes compsing the arrow
 * @param painter
 * @param option
 * @param widget
 */
void Arrow::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    // draw the line with the first 2 points
    painter->drawLine(QLineF(points[0],points[1]));
    // draw the triangle as a polygon
    painter->drawPolygon(this->tri);
}

/**
 * @brief Arrow::boundingRect returns the rectangle enclosing the shape
 * @details the rectangle upper left corner will have the lowest x,y coordinates
            the rectangle lower right corner will have the highest x,y coordinates
 * @return rectangle
 */
QRectF Arrow::boundingRect() const
{
    QRectF rect;

    float minX = points[0].x(); // init minimum x
    float minY = points[0].y(); // init minimum y
    float maxX = points[0].x(); // init maximum x
    float maxY = points[0].y(); // init maximum y
    // search for absolute max and mins
    for (int i = 1; i< 4; i++) {
        if(points[i].x()>maxX)
        {
            maxX = points[i].x();
        }
        if(points[i].x()<= minX)
        {
            minX = points[i].x();
        }

        if(points[i].y()>maxY)
        {
            maxY = points[i].y();
        }
        if(points[i].y()<= minY)
        {
            minY = points[i].y();
        }
    }
    // build the rectangle
    rect = QRectF(QPointF(minX, minY), QPointF(maxX, maxY));
    return rect;
}
