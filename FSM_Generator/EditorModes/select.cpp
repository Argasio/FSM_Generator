#include "select.h"
#include <QDebug>
#include <QMenu>
#include <QAction>
Mode_Select::Mode_Select(EditorView *_view)
    :EditorMode::EditorMode(ModeId_Select)
{
    view = _view;
    this->view->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this->view, &QGraphicsView::customContextMenuRequested,this,&Mode_Select::GenerateContextMenu);

}

void Mode_Select::GenerateContextMenu(QPoint p)
{
    QMenu contextMenuLocal =  QMenu(("Context menu"), this->view);
    connect(this, SIGNAL(destroyed()),&contextMenuLocal,SLOT(deleteLater()));
    menuAction = new QAction("Remove Data Point", this);
    connect(menuAction,
            SIGNAL(triggered()),
            this,
            SLOT(addArrowPoint()));
    contextMenuLocal.addAction(menuAction);
    contextMenuLocal.exec(this->view->mapToGlobal(p));
    contextMenuLocal.show();
}
void Mode_Select::Event_MouseRightClick(float x, float y, int mouseFlags, int keyboardFlags)
{

    qDebug()<<"SelectRightClick";


}

void Mode_Select::Event_MouseMove(float x, float y, int mouseFlags, int keyboardFlags)
{

}

void Mode_Select::Event_MouseDoubleClick(float x, float y, int mouseFlags, int keyboardFlags)
{
    qDebug()<<"SelectDoubleClick";
}

void Mode_Select::Event_MouseLeftClick(float x, float y, int mouseFlags, int keyboardFlags)
{
    qDebug()<<"SelectLeftClick";
}

void Mode_Select::Exit(EditorMode *newMode)
{
    qDebug()<<"SelectExit";
}

void Mode_Select::addArrowPoint()
{

}
