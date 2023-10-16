#include "../editormode.h"
#include"../editorview.h"
#include<QScopedPointer>
#include<QPoint>

#ifndef SELECT_H
#define SELECT_H


class Mode_Select:public EditorMode
{
    Q_OBJECT
    EditorView* view = nullptr; ///< associated viewport
    QScopedPointer<QPoint> pointBuffer;///< holds coordinates of the first click used to draw the arrow
    QPoint rightClickCoordinateBuffer;
    QMenu* contextMenu = nullptr;
    QAction* menuAction = nullptr;
public:
    Mode_Select( EditorView* _view);
    // overloads the inherited enter method
    using EditorMode::Enter;
    ///@brief right click event to start and the transition draw
    void Event_MouseRightClick(float x, float y, int mouseFlags, int keyboardFlags);
    ///@brief propapgates the mouse move event it results in the draw preview
    void Event_MouseMove(float x, float y, int mouseFlags, int keyboardFlags);
    ///@brief event that relates a doule click
    void Event_MouseDoubleClick(float x, float y, int mouseFlags, int keyboardFlags);

    void Event_MouseLeftClick(float x, float y, int mouseFlags, int keyboardFlags);
    ///@brief Overloads the exi from this mode
    void Exit(EditorMode* newMode);
    public slots:
    void addArrowPoint();
private:
    void GenerateContextMenu(QPoint p);
};

#endif // SELECT_H
