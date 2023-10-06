#ifndef DRAWRECT_H
#define DRAWRECT_H


#include "../editormode.h"
#include"../editorview.h"
#include<QScopedPointer>
#include<QPoint>


class Mode_DrawRect:public EditorMode
{
    EditorView* view;
    QPoint pointBuffer;

public:
    Mode_DrawRect( EditorView* _view)
        :EditorMode::EditorMode(ModeId_Draw_Rect)
    {
        view = _view;
    }
    using EditorMode::Enter;
    void Action_Click(float x, float y);
    void Exit(EditorMode* newMode);


};
#endif // DRAWRECT_H
