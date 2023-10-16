#include "drawarrow.h"
#include "../GraphicsItems/arrow.h"
#include "../GraphicsItems/aiarrow.h"
#include<QGraphicsLineItem>
void Mode_DrawArrow::Event_MouseLeftClick(float x, float y, int mouseFlags, int keyboardFlags)
{
    if(pointBuffer.isNull())
    {
        pointBuffer.reset(new QPoint(x, y));
    }
    else
    {
        if(previewItem.isNull() == false)
        {
            view->scene()->removeItem(previewItem.get());
            previewItem.reset();
        }
        QLineF line =  QLineF(*pointBuffer.get(), QPoint(x,y));
        ArrowItem* arrow= new ArrowItem(*pointBuffer.get(), QPoint(x,y)); //Arrow(nullptr,  &line, 100);
        view->scene()->addItem(arrow);
        pointBuffer.reset();
    }
}
/**
 * @brief Mode_DrawArrow::Event_MouseMove
 * @param x
 * @param y
 * @param flags
 */
void Mode_DrawArrow::Event_MouseMove(float x, float y, int mouseFlags, int keyboardFlags)
{
    if(pointBuffer.isNull() == false)
    {
        if(previewItem.isNull() == false)
        {
            view->scene()->removeItem(previewItem.get());
        }
        QLineF line =  QLineF(*pointBuffer.get(), QPoint(x,y));
        previewItem.reset(new ArrowItem(*pointBuffer.get(), QPoint(x,y))); //Arrow(nullptr,  &line, 100);
        view->scene()->addItem(previewItem.get());

    }
}

void Mode_DrawArrow::Exit(EditorMode* newMode)
{
    pointBuffer.reset();
}
