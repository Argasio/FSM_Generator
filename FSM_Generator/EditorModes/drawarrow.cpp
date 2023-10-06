#include "drawarrow.h"
#include<QGraphicsLineItem>
void Mode_DrawArrow::Action_Click(float x, float y)
{
    if(pointBuffer.isNull())
    {
        pointBuffer.reset(new QPoint(x, y));
    }
    else
    {
        QLine line =  QLine(*pointBuffer.get(), QPoint(x,y));
        QGraphicsLineItem* lineItem = new QGraphicsLineItem(line);
        view->scene()->addItem(lineItem);
        pointBuffer.reset();
    }
}

void Mode_DrawArrow::Exit(EditorMode* newMode)
{
    pointBuffer.reset();
}
