#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent),
    m_qgl_widget_type_action(new QAction("QGLWidget", this)),
    m_qopengl_widget_type_action(new QAction("QOpenGLWidget", this)),
    m_qglwidget(nullptr),
    m_qopenglwidget(nullptr),
    m_central_scene(new QGraphicsScene(this)),
    m_central_view(new QGraphicsView(m_central_scene)),
    m_central_fps_item(m_central_scene->addText("")),
    m_left_text(new QLabel()),
    m_rots{0,30,60},
    m_refresh_timer(new QTimer(this))
{
    QWidget* left_widget{new QWidget()};
    left_widget->setLayout(new QVBoxLayout());
    left_widget->layout()->addWidget(m_left_text);
    left_widget->setMinimumWidth(400);
    QDockWidget* left_dock_widget{new QDockWidget("left QWidget")};
    left_dock_widget->setWidget(left_widget);
    left_dock_widget->setAllowedAreas(Qt::AllDockWidgetAreas);
    addDockWidget(Qt::LeftDockWidgetArea, left_dock_widget);
    QFont font("Monospace");
    font.setPixelSize(20);
    m_central_fps_item->setFont(font);
    m_qgl_widget_type_action->setCheckable(true);
    m_qgl_widget_type_action->setChecked(false);
    m_qopengl_widget_type_action->setCheckable(true);
    m_qopengl_widget_type_action->setChecked(true);
    m_toolbar = addToolBar("");
    m_toolbar->addAction(left_dock_widget->toggleViewAction());
    m_toolbar->addAction(m_qgl_widget_type_action);
    m_toolbar->addAction(m_qopengl_widget_type_action);
    connect(m_qgl_widget_type_action, &QAction::triggered, this, &MainWindow::on_qgl_widget_type_toggled);
    connect(m_qopengl_widget_type_action, &QAction::triggered, this, &MainWindow::on_qopengl_widget_type_toggled);
    setCentralWidget(m_central_view);
    set_central_widget_type(CentralWidgetType::QOpenGLWidget);
    m_refresh_timer->setSingleShot(false);
    connect(m_refresh_timer, &QTimer::timeout, this, &MainWindow::on_refresh_timer_timeout);
    m_refresh_timer->start(0);
}

void MainWindow::set_central_widget_type(CentralWidgetType central_widget_type)
{
    if(central_widget_type == CentralWidgetType::QOpenGLWidget)
    {
        if(!m_qopenglwidget)
        {
            m_qopenglwidget = new QOpenGLWidget();
            m_central_view->setViewport(m_qopenglwidget);
            if(m_qglwidget)
            {
//                m_qglwidget->deleteLater();
                m_qglwidget = nullptr;
            }
            m_fps_counter.clear();
        }
    }
    else
    {
        if(!m_qglwidget)
        {
            m_qglwidget = new QGLWidget();
            m_central_view->setViewport(m_qglwidget);
            if(m_qopenglwidget)
            {
//                m_qopenglwidget->deleteLater();
                m_qopenglwidget = nullptr;
            }
            m_fps_counter.clear();
        }
    }
}

void MainWindow::on_qgl_widget_type_toggled(bool checked)
{
    set_central_widget_type(checked ? CentralWidgetType::QGLWidget : CentralWidgetType::QOpenGLWidget);
    m_qopengl_widget_type_action->setChecked(!checked);
}

void MainWindow::on_qopengl_widget_type_toggled(bool checked)
{
    set_central_widget_type(checked ? CentralWidgetType::QOpenGLWidget : CentralWidgetType::QGLWidget);
    m_qgl_widget_type_action->setChecked(!checked);
}

void MainWindow::on_refresh_timer_timeout()
{
    QString s{m_fps_counter.qstring_query_update()};
    m_central_fps_item->setPlainText(s);
    m_left_text->setText(s);
}
