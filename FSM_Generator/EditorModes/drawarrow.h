#ifndef DRAWARROW_H
#define DRAWARROW_H

#include "../editormode.h"
#include"../editorview.h"
#include<QScopedPointer>
#include<QPoint>
#include "../GraphicsItems/aiarrow.h"
/**
 * @brief The Mode_DrawArrow class is used to draw state transition arrows
 */
class Mode_DrawArrow:public EditorMode
{
    EditorView* view; ///< associated viewport
    QScopedPointer<QPoint> pointBuffer;///< holds coordinates of the first click used to draw the arrow
    QScopedPointer<ArrowItem> previewItem;///< used to preview an arrow item during draws
public:
    Mode_DrawArrow( EditorView* _view)
        :EditorMode::EditorMode(ModeId_Draw_Arrow)
    {
        view = _view;
    }
    // overloads the inherited enter method
    using EditorMode::Enter;
    ///@brief right click event to start and the transition draw
    void Event_MouseLeftClick(float x, float y, int mouseFlags, int keyboardFlags);
    ///@brief propapgates the mouse move event it results in the draw preview
    void Event_MouseMove(float x, float y, int mouseFlags, int keyboardFlags);
    ///@brief Overloads the exi from this mode
    void Exit(EditorMode* newMode);


};
#endif // DRAWARROW_H
