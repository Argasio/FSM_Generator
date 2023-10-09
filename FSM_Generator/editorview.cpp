#include "editorview.h"
#include "EditorModes/drawrect.h"
#include "editorview_modes.h"
#include "qgraphicsitem.h"

#include <QMouseEvent>>

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
    mode.get()->Action_Click(x,y);
}

void EditorView::mouseMoveEvent(QMouseEvent *event)
{
    // adapt coordinate system to scene
    QPointF p = this->mapToScene(event->pos());
    // get coordinates as integers
    int x = p.x();
    int y = p.y();
    // propagate mouse movement data
    emit mouseMoveCb(x,y);
    QGraphicsView::mouseMoveEvent(event);
}
