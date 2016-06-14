#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent),
    m_qgl_widget_type_action(new QAction("QGLWidget", this)),
    m_qopengl_widget_type_action(new QAction("QOpenGLWidget", this)),
    m_qopengl_window_type_action(new QAction("QOpenGLWindow", this)),
    m_qglwidget(nullptr),
    m_qopenglwidget(nullptr),
    m_openglwindow(nullptr),
    m_openglwindow_container(nullptr),
    m_central_scene(new QGraphicsScene(this)),
    m_central_view(nullptr),
    m_central_fps_item(m_central_scene->addText("")),
    m_left_text(new QLabel()),
    m_right_text(new QLabel())
{
    QWidget* left_widget{new QWidget()};
    left_widget->setLayout(new QVBoxLayout());
    left_widget->layout()->addWidget(m_left_text);
    left_widget->setMinimumWidth(200);
    left_widget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    QDockWidget* left_dock_widget{new QDockWidget("left QWidget")};
    left_dock_widget->setWidget(left_widget);
    left_dock_widget->setAllowedAreas(Qt::AllDockWidgetAreas);
    addDockWidget(Qt::LeftDockWidgetArea, left_dock_widget);
    QWidget* right_widget{new QWidget()};
    right_widget->setLayout(new QVBoxLayout());
    right_widget->layout()->addWidget(m_right_text);
    right_widget->setMinimumWidth(200);
    right_widget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    QDockWidget* right_dock_widget{new QDockWidget("right QWidget")};
    right_dock_widget->setWidget(right_widget);
    right_dock_widget->setAllowedAreas(Qt::AllDockWidgetAreas);
    addDockWidget(Qt::RightDockWidgetArea, right_dock_widget);
    QFont font("Monospace");
    font.setPixelSize(20);
    m_central_fps_item->setFont(font);
    m_central_fps_item->setDefaultTextColor(Qt::red);
    m_qgl_widget_type_action->setCheckable(true);
    m_qgl_widget_type_action->setChecked(false);
    m_qopengl_widget_type_action->setCheckable(true);
    m_qopengl_widget_type_action->setChecked(true);
    m_qopengl_window_type_action->setCheckable(true);
    m_qopengl_window_type_action->setChecked(false);
    m_toolbar = addToolBar("");
    m_toolbar->addAction(left_dock_widget->toggleViewAction());
    m_toolbar->addAction(right_dock_widget->toggleViewAction());
    m_toolbar->addAction(m_qgl_widget_type_action);
    m_toolbar->addAction(m_qopengl_widget_type_action);
    m_toolbar->addAction(m_qopengl_window_type_action);
    connect(m_qgl_widget_type_action, &QAction::triggered, this, &MainWindow::on_qgl_widget_type_toggled);
    connect(m_qopengl_widget_type_action, &QAction::triggered, this, &MainWindow::on_qopengl_widget_type_toggled);
    connect(m_qopengl_window_type_action, &QAction::triggered, this, &MainWindow::on_qopengl_window_type_toggled);
    on_qopengl_widget_type_toggled(true);
    connect(this, &MainWindow::new_frame, this, &MainWindow::on_new_frame, Qt::QueuedConnection);
    new_frame();
}

void MainWindow::on_qgl_widget_type_toggled(bool checked)
{
    if(!checked) return;
    m_qopengl_widget_type_action->setChecked(!checked);
    m_qopengl_window_type_action->setChecked(!checked);
    if(!m_qglwidget)
    {
        if(m_central_view)
        {
            setCentralWidget(nullptr);
            m_central_view->deleteLater();
        }
        m_central_view = new QGraphicsView(m_central_scene);
        m_central_view->setCacheMode(QGraphicsView::CacheNone);
        m_central_view->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
        m_central_view->setAutoFillBackground(false);
        setCentralWidget(m_central_view);
        if(m_qopenglwidget)
        {
            m_qopenglwidget->deleteLater();
            m_qopenglwidget = nullptr;
        }
        if(m_openglwindow)
        {
            m_openglwindow->deleteLater();
            m_openglwindow = nullptr;
            m_openglwindow_container->deleteLater();
            m_openglwindow_container = nullptr;
        }
        m_qglwidget = new QGLWidget();
        m_central_view->setViewport(m_qglwidget);
        m_fps_counter.clear();
    }
}

void MainWindow::on_qopengl_widget_type_toggled(bool checked)
{
    if(!checked) return;
    m_qgl_widget_type_action->setChecked(!checked);
    m_qopengl_window_type_action->setChecked(!checked);
    if(!m_qopenglwidget)
    {
        if(m_central_view)
        {
            setCentralWidget(nullptr);
            m_central_view->deleteLater();
        }
        m_central_view = new QGraphicsView(m_central_scene);
        m_central_view->setCacheMode(QGraphicsView::CacheNone);
        m_central_view->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
        m_central_view->setAutoFillBackground(false);
        setCentralWidget(m_central_view);
        if(m_qglwidget)
        {
            m_qglwidget->deleteLater();
            m_qglwidget = nullptr;
        }
        if(m_openglwindow)
        {
            m_openglwindow->deleteLater();
            m_openglwindow = nullptr;
            m_openglwindow_container->deleteLater();
            m_openglwindow_container = nullptr;
        }
        m_qopenglwidget = new QOpenGLWidget();
        m_central_view->setViewport(m_qopenglwidget);
        m_fps_counter.clear();
    }
}

void MainWindow::on_qopengl_window_type_toggled(bool checked)
{
    if(!checked) return;
    m_qgl_widget_type_action->setChecked(!checked);
    m_qopengl_widget_type_action->setChecked(!checked);
    if(!m_openglwindow)
    {
        if(m_central_view)
        {
            setCentralWidget(nullptr);
            m_central_view->deleteLater();
        }
        m_central_view = new QGraphicsView(m_central_scene);
        m_central_view->setCacheMode(QGraphicsView::CacheNone);
        m_central_view->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
        m_central_view->setAutoFillBackground(false);
        setCentralWidget(m_central_view);
        if(m_qglwidget)
        {
            m_qglwidget->deleteLater();
            m_qglwidget = nullptr;
        }
        if(m_qopenglwidget)
        {
            m_qopenglwidget->deleteLater();
            m_qopenglwidget = nullptr;
        }
        m_openglwindow = new OpenGLWindow();
        m_openglwindow_container = QWidget::createWindowContainer(m_openglwindow);
        m_central_view->setViewport(m_openglwindow_container);
        m_fps_counter.clear();
    }
}

void MainWindow::on_new_frame()
{
    QString s{m_fps_counter.qstring_query_update()};
    m_central_fps_item->setPlainText(s);
    m_left_text->setText(s);
    m_right_text->setText(s);
    new_frame();
}
