#include "drawarrow.h"
#include "../GraphicsItems/arrow.h"
#include<QGraphicsLineItem>
void Mode_DrawArrow::Action_Click(float x, float y)
{
    if(pointBuffer.isNull())
    {
        pointBuffer.reset(new QPoint(x, y));
    }
    else
    {
        QLineF line =  QLineF(*pointBuffer.get(), QPoint(x,y));
        Arrow* arrow= new Arrow(nullptr,  &line, 100);
        view->scene()->addItem(arrow);
        pointBuffer.reset();
    }
}

void Mode_DrawArrow::Exit(EditorMode* newMode)
{
    pointBuffer.reset();
}
