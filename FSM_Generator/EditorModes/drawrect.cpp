#include "drawrect.h"
#include "../GraphicsItems/staterect.h"

/**
 * @brief Mode_DrawRect::Event_MouseRightClick registers right click events used to draw the shape
 * @param x
 * @param y
 */
void Mode_DrawRect::Event_MouseLeftClick(float x, float y, int mouseFlags, int keyboardFlags)
{
    // check whether this is the first click and no previous point was registered
    if(pointBuffer.isNull())
    {
        // bufferize coordinate
        pointBuffer.reset(new QPoint(x, y));
    }
    else
    {
        // this is the conclusive click, register the new point and generate the base state shape
        StateRect* state= new StateRect(QPoint(*pointBuffer.get()),QPoint(x,y));
        // add  state item to the graphics scene
        view->scene()->addItem(state);
        // reset the point buffer fo rth enext item to be drawn
        pointBuffer.reset();
    }

}

/**
 * @brief Mode_DrawRect::Exit used to exit the draw state mode
 * @param newMode
 */
void Mode_DrawRect::Exit(EditorMode* newMode)
{
    // rese the point buffer
    pointBuffer.reset();
}
