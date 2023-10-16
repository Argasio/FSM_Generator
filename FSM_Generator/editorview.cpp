#include "editorview.h"
#include "EditorModes/drawrect.h"
#include "editorview_modes.h"
#include "qgraphicsitem.h"
#include <QScrollBar>
#include <QMouseEvent>

/**
 * @brief EditorView::EditorView
 * @param parent
 */
EditorView::EditorView(QWidget *parent, QRect rect)
    : QGraphicsView(parent),
    mode(new Mode_DrawRect(this))
{
    // create a diagram, treat is at a scene
    this->diagram = new DiagramScene(this);
    // give the drawing area a fixed size
    this->setFixedSize(500, 500);
    // create the scene space
    QRectF r = QRectF(0,0, 300, 300);
    // set diagram as view scene
    this->setScene(diagram);
    // view and diagram share the same space
    this->diagram->setSceneRect(r); //scene is going to be anchored inside the view, see transformationAnchor : ViewportAnchor
    // draw the scene enclosing boundaries
    QGraphicsRectItem* sceneRect = new QGraphicsRectItem(r);
    diagram->addItem(sceneRect);
    // enable mouse tracking in the view area
    this->setMouseTracking(true);
}

/**
 * @brief EditorView::getMode obtain current mode
 * @return current mode
 */
EditorMode* EditorView::getMode() const
{
    return mode.get();
}

/**
 * @brief EditorView::setMode assign current operation mode (tool)
 * @param newMode
 */
void EditorView::setMode(EditorMode *newMode)
{
    // execute exit action for current mode
    mode.get()->Exit(newMode);
    // assign this mode as the new one
    mode.reset(newMode);
    // execute entry action for current mode
    mode.get()->Enter();
}

/**
 * @brief EditorView::mousePressEvent propagates mouse vent
 * @param event
 */
void EditorView::mousePressEvent(QMouseEvent *event)
{
    // adapt coordinate system to scene
    QPointF p = this->mapToScene(event->pos());
    // get coordinates as integers
    int x = p.x();
    int y = p.y();
    // pass the event to the current mode handler
    if(event->buttons() & Qt::LeftButton)
    {
        mode.get()->Event_MouseLeftClick(x,y, event->buttons(), event->modifiers());
    }
    else if(event->buttons() & Qt::MiddleButton)
    {

    }
    else if(event->buttons() & Qt::RightButton)
    {
        mode.get()->Event_MouseRightClick(event->pos().x(),event->pos().y(), event->buttons(), event->modifiers());
    }
    // propagate event
    QGraphicsView::mousePressEvent(event);
}

/**
 * @brief EditorView::mouseMoveEvent tracks mouse movement
 * @param event
 */
void EditorView::mouseMoveEvent(QMouseEvent *event)
{
    // adapt coordinate system to scene
    QPointF p = this->mapToScene(event->pos());

    // get coordinates as integers
    int x = p.x();
    int y = p.y();

    // propagate mouse movement data
    emit mouseMoveCb(x,y);

    if(event->buttons() & Qt::MiddleButton)
    {
        // compute distance from last position recorded
        QPointF delta = event->globalPosition()-pLast ;
        // compute new scrollbar x position
        int newX = this->horizontalScrollBar()->value() + delta.x();
        // compute new vertical scrollbar position
        int newY = this->verticalScrollBar()->value() + delta.y();
        // apply horizontal scrollbar
        this->horizontalScrollBar()->setValue(newX);
        // apply vertical scrollbar
        this->verticalScrollBar()->setValue(newY);
        //this->translate(delta.x(),delta.y());
    }
    // notify the current working mode
    mode.get()->Event_MouseMove(x,y,event->buttons(), event->modifiers());
    // update last mouse position
    pLast = event->globalPosition();
    // propagate event
    QGraphicsView::mouseMoveEvent(event);
}

/**
 * @brief EditorView::mouseDoubleClickEvent records a double mouse press and propagates it according to the active mode
 * @param e event details
 */
void EditorView::mouseDoubleClickEvent(QMouseEvent *e)
{
    //trace
    qDebug()<<"DoubleClick";

    // adapt coordinate system to scene
    QPointF p = this->mapToScene(e->pos());

    // get coordinates as integers
    int x = p.x();
    int y = p.y();

    // notify the current working mode
    mode.get()->Event_MouseDoubleClick(x,y,e->buttons(), e->modifiers());
    // update last mouse position
    pLast = e->globalPosition();
    // propagate event
    QGraphicsView::mouseDoubleClickEvent(e);
}

/**
 * @brief EditorView::wheelEvent event that deals with mous ewheel scrolling
 *  this event will be used to zoom in or zoom out the viewport
 * @param event event information
 *
 */
void EditorView::wheelEvent(QWheelEvent *event)
{

    // get current transformation anchor and store it for later
    const ViewportAnchor anchor = transformationAnchor();
    // zoom considering the mouse position as starting point so anchor under mouse
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    // get scroll direction
    int angle = event->angleDelta().y();
    // zoom/scale amount (in or out9
    qreal factor;
    if (angle > 0) {
        factor = 1.1;
    } else {
        factor = 0.9;
    }
    // scale graphicsview
    scale(factor, factor);
    // restore previous transformation anchor
    setTransformationAnchor(anchor);
    // propagate event
    QGraphicsView::wheelEvent(event);

}
