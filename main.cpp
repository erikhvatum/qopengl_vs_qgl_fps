#include "MainWindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    {
        QSurfaceFormat fmt = QSurfaceFormat::defaultFormat();
        fmt.setRenderableType(QSurfaceFormat::OpenGL);
        fmt.setProfile(QSurfaceFormat::CompatibilityProfile);
        fmt.setSwapBehavior(QSurfaceFormat::DoubleBuffer);
        fmt.setSwapInterval(0);
        fmt.setVersion(2, 1);
        fmt.setOptions(QSurfaceFormat::DeprecatedFunctions);
        fmt.setSamples(8);
        fmt.setRedBufferSize(8);
        fmt.setGreenBufferSize(8);
        fmt.setBlueBufferSize(8);
        fmt.setAlphaBufferSize(0);
        QSurfaceFormat::setDefaultFormat(fmt);
    }
    {
        QGLFormat fmt = QGLFormat::defaultFormat();
        fmt.setProfile(QGLFormat::CompatibilityProfile);
        fmt.setSwapInterval(0);
        fmt.setVersion(2, 1);
        fmt.setSamples(8);
        fmt.setRedBufferSize(8);
        fmt.setGreenBufferSize(8);
        fmt.setBlueBufferSize(8);
        fmt.setAlphaBufferSize(0);
        QGLFormat::setDefaultFormat(fmt);
    }

    MainWindow w;
    w.showMaximized();

    return a.exec();
}
