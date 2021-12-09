#ifndef MESH_H
#define MESH_H

#include <QVector3D>
#include <QtOpenGL>
#include "meshloader.h"
#include "model.h"

class Mesh{
private:
    Vertex * vertexArray;
    unsigned nrOfVertices;
    GLuint* indexArray;
    unsigned nrOfIndices;

    GLuint VAO;
    GLuint VBO;

    void initVAO();

public:
    Mesh(
        Vertex* vertexArray,
        const unsigned& nrOfVertices,
        GLuint* indexArray,
        const unsigned& nrOfIndices,
        QVector3D position = QVector3D(0.f,0.f,0.f),
        QVector3D origin = QVector3D(0.f,0.f,0.f),
        QVector3D rotation = QVector3D(0.f,0.f,0.f),
        QVector3D scale = QVector3D(1.f,1.f,1.f));

    Mesh(Vertex*, const unsigned&, GLuint*, const unsigned&);
    Model model;
    ~Mesh();

    void render(QOpenGLShader* shader);
};
#endif // MESH_H
