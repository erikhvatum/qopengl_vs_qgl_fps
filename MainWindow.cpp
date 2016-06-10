#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent),
    m_qgl_widget_type_action(new QAction("QGLWidget", this)),
    m_qopengl_widget_type_action(new QAction("QOpenGLWidget", this)),
    m_qglwidget(nullptr),
    m_qopenglwidget(nullptr)
{
    m_toolbar = addToolBar("");
    m_toolbar->addAction(m_qgl_widget_type_action);
    m_toolbar->addAction(m_qopengl_widget_type_action);
}

MainWindow::~MainWindow()
{
}
