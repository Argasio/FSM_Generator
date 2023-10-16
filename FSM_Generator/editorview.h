#ifndef EDITORVIEW_H
#define EDITORVIEW_H

#include <QObject>
#include <QGraphicsView>
#include<QRect>
#include<QScopedPointer>
#include "editormode.h"
#include"diagramscene.h"


class EditorView : public QGraphicsView
{
    Q_OBJECT
    DiagramScene* diagram;
    ///@brief current mode in the editor
    QScopedPointer<EditorMode> mode;
    ///@brief used to track mouse position cahnges during drag events
    QPointF pLast;
public:
    explicit EditorView(QWidget *parent = nullptr, QRect rect = QRect(0,0, 200, 200));


    EditorMode* getMode() const;
    void setMode(EditorMode *newMode);
    void mousePressEvent(QMouseEvent  *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseDoubleClickEvent( QMouseEvent * e );
    void wheelEvent(QWheelEvent *event);


signals:
    void mouseMoveCb(int x, int y);
protected:

};

#endif // EDITORVIEW_H
