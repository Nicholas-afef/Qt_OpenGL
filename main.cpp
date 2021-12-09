#include <QApplication>
#include "mainwindow.h"
#include <iostream>
#include <QOpenGLContext>

int main(int argc, char **argv)
{
    QApplication a(argc, argv);

    if (QOpenGLContext::openGLModuleType() != QOpenGLContext::LibGL) {
        qWarning("This system does not support OpenGL. Exiting.");
        return -1;
    }

    QSurfaceFormat fmt;
        fmt.setVersion(4, 5);
        fmt.setProfile(QSurfaceFormat::CoreProfile);
        QSurfaceFormat::setDefaultFormat(fmt);

    MainWindow w;

    w.show();
    return a.exec();
}
