#ifndef DRAWARROW_H
#define DRAWARROW_H

#include "../editormode.h"
#include"../editorview.h"
#include<QScopedPointer>
#include<QPoint>

class Mode_DrawArrow:public EditorMode
{
    EditorView* view;
    QScopedPointer<QPoint> pointBuffer;

public:
    Mode_DrawArrow( EditorView* _view)
        :EditorMode::EditorMode(ModeId_Draw_Arrow)
    {
        view = _view;
    }
    using EditorMode::Enter;
    void Action_Click(float x, float y);
    void Exit(EditorMode* newMode);


};
#endif // DRAWARROW_H
