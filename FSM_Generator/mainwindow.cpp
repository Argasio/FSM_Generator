#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include"toolbar.h"
#include "editorview.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    QRect viewRect = QRect(0,0,600,400);
    EditorView* editor_view = new EditorView(this, viewRect);
    ui->group_middle->layout()->addWidget(editor_view);
    toolbar* draw_toolbar = new toolbar(this, editor_view);
    ui->group_middle->layout()->addWidget(draw_toolbar);
}

MainWindow::~MainWindow()
{
    delete ui;
}

