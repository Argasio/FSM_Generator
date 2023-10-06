#include "drawrect.h"



void Mode_DrawRect::Action_Click(float x, float y)
{
    pointBuffer = QPoint(x, y);
}

void Mode_DrawRect::Exit(EditorMode* newMode)
{

}
