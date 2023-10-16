#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include"toolbar.h"
#include "editorview.h"
#include <QMouseEvent>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    QRect viewRect = QRect(0,0,600,400);
    editor_view = new EditorView(this, viewRect);
    connect(editor_view, &EditorView::mouseMoveCb, this, &MainWindow::mouseInfo);
    ui->group_middle->layout()->addWidget(editor_view);
    toolbar* draw_toolbar = new toolbar(this, editor_view);
    ui->group_middle->layout()->addWidget(draw_toolbar);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mouseInfo(int x, int y)
{
    QString str;
    str.append("x=");
    str.append(QString::number(x));
    str.append("y=");
    str.append(QString::number(y));
    ui->label->setText(str);
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{

    //editor_view->mouseMoveEvent(event);
}



void MainWindow::mousePressEvent(QMouseEvent *event)
{

    // get coordinates as integers
    int x = event->pos().x();
    int y = event->pos().y();
    // pass the event to the current mode handler
    if(event->buttons() & Qt::LeftButton)
    {

    }
    else if(event->buttons() & Qt::MiddleButton)
    {

    }
    else if(event->buttons() & Qt::RightButton)
    {

    }
    // propagate event
    QMainWindow::mousePressEvent(event);
}
