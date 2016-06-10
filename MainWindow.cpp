#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
{
    m_toolbar = addToolBar("");
}

MainWindow::~MainWindow()
{
}
