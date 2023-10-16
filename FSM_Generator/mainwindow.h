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
    QMenu* contextMenu = nullptr;
    QAction* menuAction = nullptr;
    void GenerateContextMenu(int x, int y);
public slots:
    void mouseInfo(int x, int y);
protected:
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent  *event);
};
#endif // MAINWINDOW_H
