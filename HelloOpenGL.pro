QT       += core gui opengl openglwidgets 3drender

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11 console

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

LIBS += -lOpenGL32

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    meshloader.cpp \
    model.cpp \
    myglwidget.cpp \
    perspective.cpp \
    view.cpp

HEADERS += \
    mainwindow.h \
    meshloader.h \
    model.h \
    myglwidget.h \
    perspective.h \
    view.h

FORMS += \
    mainwindow.ui

OTHER_FILES += fragmentShader.glsl\
               vertexShader.vsh

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    FragmentShader.glsl \
    LightingFragmentShader.glsl \
    LightingVertexShader.glsl \
    VertexShader.glsl

INCLUDEPATH += $$PWD/dependencies/lib/Debug
DEPENDPATH += $$PWD/dependencies/lib/Debug
