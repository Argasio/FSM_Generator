#include "aiarrow.h"
#include <QPainter>
#include <QVector2D>
#include <QtMath>


ArrowItem::ArrowItem(QPointF start, QPointF end, QGraphicsItem *parent)
    : QGraphicsItem(parent)
{
    // Add the start and end points to the list of points
    points.append(start);
    points.append(end);

    // Set the default curvature value to 0.5
    curvature = 0.5;

    // Set the pen and brush properties
    pen.setWidth(2);
    pen.setColor(Qt::black);
    brush.setColor(Qt::red);

    // Update the path and shape of the arrow
    updatePath();
    // Debug infos
    qDebug()<<"ArrowCreated";
}

// The method that adds an intermediate point to the arrow
void ArrowItem::addPoint(QPointF point)
{
    // Append the point to the end of the list of points
    points.append(point);

    // Update the path and shape of the arrow
    updatePath();
}

// The method that sets the curvature of the arrow
void ArrowItem::setCurvature(qreal curvature)
{
    // Clamp the curvature value between 0 and 1
    this->curvature = qBound(0.0, curvature, 1.0);

    // Update the path and shape of the arrow
    updatePath();
}

// The method that returns the bounding rectangle of the arrow
QRectF ArrowItem::boundingRect() const
{
    // Return the bounding rectangle of the path
    return path.boundingRect();
}

// The method that paints the arrow on the painter
void ArrowItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    // Set the pen and brush for the painter
    painter->setPen(pen);
    painter->setBrush(brush);

    // Draw the path on the painter
    painter->drawPath(path);
}

// The helper method that updates the path and shape of the arrow
void ArrowItem::updatePath()
{
    // Clear the previous path
    path = QPainterPath();

    // Check if there are at least two points in the list
    if (points.size() < 2)
    {
        return;
    }

    // Move to the first point in the list
    path.moveTo(points.first());

    // Loop through the rest of the points in pairs
    for (int i = 1; i < points.size() - 1; i += 2) {
        // Get the current pair of points
        QPointF p1 = points[i];
        QPointF p2 = points[i + 1];

        // Calculate the midpoint between them
        QPointF mid = (p1 + p2) / 2;

        // Calculate the vector from p1 to p2
        QVector2D v(p2 - p1);

        // Calculate the normal vector to v
        QVector2D n(-v.y(), v.x());

        // Normalize n and scale it by curvature factor
        n.normalize();
        n *= v.length() * curvature;

        // Calculate the control point by adding n to mid
        QPointF c = mid + n.toPointF();

        // Add a quadratic curve to c and p2 to the path
        path.quadTo(c, p2);
    }

    // Get the last point in the list
    QPointF end = points.last();

    // Get the second last point in the list
    QPointF prev = points[points.size() - 2];

    // Calculate the vector from prev to end
    QVector2D v(end - prev);

    // Calculate the length and angle of v
    qreal length = v.length();
    qreal angle = qRadiansToDegrees(qAtan2(v.y(), v.x()));

    // Define some constants for drawing the arrow head
    const qreal headLength = 10;
    const qreal headAngle = 30;

    // Calculate the left and right points of the arrow head
    QPointF left = end - QTransform().rotate(angle - headAngle).map(QPointF(headLength, 0));
    QPointF right = end - QTransform().rotate(angle + headAngle).map(QPointF(headLength, 0));

    // Add a line to end to the path
    path.lineTo(end);

    // Move to left and add a line to end to the path
    path.moveTo(left);
    path.lineTo(end);

    // Move to right and add a line to end to the path
    path.moveTo(right);
    path.lineTo(end);
}

// The method that modifies a point in the list of points given a pointer and a coordinate
void ArrowItem::modifyPoint(QPointF* pointer, QPointF coordinate)
{
    // Check if the pointer is not null
    if (pointer != nullptr) {
        // Loop through the points in the list
        for (QPointF& p : points) {
            // Check if the pointer points to the current point
            if (pointer == &p) {
                // Change the x and y values of the point to the ones of the coordinate
                p.setX(coordinate.x());
                p.setY(coordinate.y());

                // Update the path and shape of the arrow
                updatePath();

                // Break the loop
                break;
            }
        }
    }
}

// The method that detects whether an input QPointF is within 20 pixels from any of the arrow points
QPointF* ArrowItem::detectPoint(QPointF input)
{
    // Initialize a pointer to store the closest point
    QPointF* closest = nullptr;

    // Initialize a variable to store the minimum distance
    qreal minDist = 20;

    // Loop through the points in the list
    for (QPointF& p : points) {
        // Calculate the distance between the input and the current point
        qreal dist = QLineF(input, p).length();

        // Check if the distance is less than the minimum distance
        if (dist < minDist) {
            // Update the minimum distance and the closest point
            minDist = dist;
            closest = &p;
        }
    }

    // Return the closest point or nullptr if none is found
    return closest;
}
