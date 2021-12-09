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
public:
    MeshLoader();
    explicit MeshLoader(const std::string&);
    ~MeshLoader();
    void loadFile(const std::string&);
    void clear();
    void* getVertices();
    size_t getSize() const;
};

#endif // MESHLOADER_H
