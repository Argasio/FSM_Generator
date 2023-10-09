#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "editorview.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    EditorView* editor_view;
    Ui::MainWindow *ui;
public slots:
    void mouseInfo(int x, int y);
protected:
    void mouseMoveEvent(QMouseEvent *event);
};
#endif // MAINWINDOW_H
