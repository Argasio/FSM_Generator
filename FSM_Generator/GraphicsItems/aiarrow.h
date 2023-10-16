#include <QGraphicsItem>
#include <QPainterPath>
#include <QPainter>
#ifndef ARROWITEM_H
#define ARROWITEM_H
/**
@details A Qt C++ Class for a curved arrow with multiple points and a variable curvature, inheriting from QGraphicsItem.
            The class has a list of QPointF for the points, a qreal for the curvature, a QPen for the pen, and a QBrush for the brush.
        The class has methods for:
            Constructing the arrow with two points and an optional parent item.
            Adding an intermediate point to the end of the list.
            Setting the curvature between 0 and 1.
            Returning the bounding rectangle of the path.
            Painting the arrow with the pen, brush, and red circles for intermediate points.
            Updating the path and shape of the arrow with quadratic curves and lines for the arrow head.
            Detecting if an input QPointF is within 20 pixels from any point and returning the closest point or nullptr.
            Modifying a point in the list given a pointer and a coordinate.
 */
class ArrowItem : public QGraphicsItem
{
public:
    /**
     * @brief ArrowItem constructs an arrow item with a start and end point.
     * @param start The start point of the arrow.
     * @param end The end point of the arrow.
     * @param parent The optional parent item of the arrow.
     */
    ArrowItem(QPointF start, QPointF end, QGraphicsItem *parent = nullptr);

    /**
     * @brief addPoint adds an intermediate point that the arrow must pass through.
     * @param point The point to be added.
     */
    void addPoint(QPointF point);

    /**
     * @brief setCurvature sets the curvature of the path of the arrow.
     * @param curvature The curvature value between 0 and 1.
     */
    void setCurvature(qreal curvature);

    /**
     * @brief boundingRect returns the bounding rectangle of the arrow item.
     * @return The bounding rectangle of the arrow item.
     */
    QRectF boundingRect() const override;

    /**
     * @brief paint paints the arrow item on the given painter.
     * @param painter The painter to be used.
     * @param option The style option for the item.
     * @param widget The optional widget that this item is painted on.
     */
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

    /**
     * @brief ~ArrowItem destructor
     */
    virtual ~ArrowItem(){
        qDebug()<<"ArrowDeleted";
    }

    /**
     * @brief Detects whether an input QPointF is within 20 pixels from any of the arrow points.
     * @param input The input QPointF to be checked.
     * @return A pointer to the closest point in the list of points or nullptr if none is found.
     */
    QPointF* detectPoint(QPointF input);

    /**
    * @brief Modifies a point in the list of points given a pointer and a coordinate.
    * @param pointer A pointer to a point in the list of points.
    * @param coordinate A QPointF with the new x and y values for the point.
    */
    void modifyPoint(QPointF* pointer, QPointF coordinate);
private:
    // The list of points that define the path of the arrow
    QList<QPointF> points;

    // The curvature value of the path
    qreal curvature;

    // The painter path that represents the shape of the arrow
    QPainterPath path;

    // The pen that is used to draw the outline of the arrow
    QPen pen;

    // The brush that is used to fill the body of the arrow
    QBrush brush;

    // A helper method that updates the path and shape of the arrow
    void updatePath();


};
#endif
