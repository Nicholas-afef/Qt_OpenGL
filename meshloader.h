#ifndef MESHLOADER_H
#define MESHLOADER_H

#include <vector>
#include <QVector3D>
#include <iostream>
#include <fstream>
#include <QtOpenGL>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLShaderProgram>

struct Vertex{
    QVector3D position;
    QVector3D normal;
    QVector2D texture;
    QVector3D color;
};

class MeshLoader{
private:
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
public:
    MeshLoader();
    explicit MeshLoader(const std::string&);
    ~MeshLoader();
    void loadFile(const std::string&);
    void clear();
    void* getVertices();
    void* getIndices();
    QVector3D getFirstPosition();
    size_t getVertexSize() const;
    size_t getIndexSize() const;
};

#endif // MESHLOADER_H
