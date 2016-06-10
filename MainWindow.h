#include <QtWidgets>

class MainWindow
  : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent=nullptr);
    ~MainWindow();

protected:
    QToolBar* m_toolbar;
    QAction* m_
};
