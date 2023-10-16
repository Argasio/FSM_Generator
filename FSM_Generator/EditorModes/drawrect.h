#ifndef DRAWRECT_H
#define DRAWRECT_H


#include "../editormode.h"
#include"../editorview.h"
#include<QScopedPointer>
#include<QPoint>

/**
 * @brief The Mode_DrawRect class is used to draw state item which are represented in a rectangular shape
 */
class Mode_DrawRect:public EditorMode
{
    ///@brief view associated with the mode
    EditorView* view;
    ///@brief to construct the state item two points must be recorded, this holds the point of the first click
    QScopedPointer<QPoint> pointBuffer;

public:
    Mode_DrawRect( EditorView* _view)
        :EditorMode::EditorMode(ModeId_Draw_Rect)
    {
        view = _view;
    }
    ///@brief inherit Enter method form base class
    using EditorMode::Enter;
    ///@brief overload RightClick event for this mode
    void Event_MouseLeftClick(float x, float y,int mouseFlags, int keyboardFlags);
    ///@brief overload exit event for this mode
    void Exit(EditorMode* newMode);


};
#endif // DRAWRECT_H
