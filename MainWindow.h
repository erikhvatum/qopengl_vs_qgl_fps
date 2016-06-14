#pragma once
#include <cstdint>
#include <QtOpenGL>
#include <QtWidgets>
#include "FPSCounter.h"

class MainWindow
  : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent=nullptr);

protected:
    enum class CentralWidgetType : std::uint8_t
    {
        QGLWidget,
        QOpenGLWidget
    };

    QToolBar* m_toolbar;
    QAction* m_qgl_widget_type_action;
    QAction* m_qopengl_widget_type_action;
    QGLWidget* m_qglwidget;
    QOpenGLWidget* m_qopenglwidget;
    QGraphicsScene* m_central_scene;
    QGraphicsView* m_central_view;
    QGraphicsTextItem* m_central_fps_item;
    QLabel* m_left_text;
    QLabel* m_right_text;
    FPSCounter m_fps_counter;

    void set_central_widget_type(CentralWidgetType central_widget_type);

protected slots:
    void on_qgl_widget_type_toggled(bool checked);
    void on_qopengl_widget_type_toggled(bool checked);
    void on_new_frame();

signals:
    void new_frame();
};
