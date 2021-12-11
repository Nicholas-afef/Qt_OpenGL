#ifndef MYGLWIDGET_H
#define MYGLWIDGET_H

#include <QtOpenGL>
#include <QtOpenGLWidgets/QtOpenGLWidgets>
#include <QOpenGLFunctions_4_0_Core>
#include <QTime>
#include <QCoreApplication>
#include <QMatrix4x4>
#include <QOpenGLShaderProgram>
#include <QOpenGLShader>
#include "meshloader.h"
#include "model.h"
#include "view.h"
#include "perspective.h"
#include <Qt3DRender/QMesh>

class MyGLWidget : public QOpenGLWidget{
public:
    MyGLWidget(QWidget *parent = nullptr);
    ~MyGLWidget();
    Model modelMatrix;
    View viewMatrix;
    bool textureSwap = false;
    float shine = 32.0f;
    void loadNewObject(std::string);
    void loadNewTexture(std::string);

private:
    void initializeGL() Q_DECL_OVERRIDE;
    void resizeGL(int w, int h) Q_DECL_OVERRIDE;
    void paintGL() Q_DECL_OVERRIDE;
    void reshape();
    void initializeShaders(std::string, std::string);
    void initializeModel(std::string);
    void initializeTextures(std::string);

private:
    QOpenGLExtraFunctions *m_funcs {nullptr};
    MeshLoader mesh;
    GLuint vao, vbo, ebo;
    std::unique_ptr<QOpenGLShaderProgram> shaderProgram;
    std::unique_ptr<QOpenGLTexture> m_texture1;
    GLuint texture {0};
    Perspective perspectiveMatrix;

public slots:
    void moveForward();
    void moveBackward();
    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();
    void setAxisOfRotation(int);
    void rotateObject(int);
};

#endif // MYGLWIDGET_H

