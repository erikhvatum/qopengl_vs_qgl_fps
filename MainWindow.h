#pragma once

#include <QtWidgets>
#include <QtOpenGL>

class MainWindow
  : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent=nullptr);
    ~MainWindow();

protected:
    QToolBar* m_toolbar;
    QAction* m_qgl_widget_type_action;
    QAction* m_qopengl_widget_type_action;
    QGLWidget* m_qglwidget;
    QOpenGLWidget* m_qopenglwidget;

protected slots:
//    void on_
};
