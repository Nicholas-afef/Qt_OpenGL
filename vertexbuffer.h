#ifndef VERTEXBUFFER_H
#define VERTEXBUFFER_H

#include <QtOpenGL>
#include <QOpenGLFunctions>
#include <iostream>

class VertexBuffer: protected QOpenGLFunctions {
private:
    unsigned int vertexBufferId;
    unsigned int size;
public:
    VertexBuffer(const void* data, unsigned int size);
    ~VertexBuffer();

    void bind();
    void unbind();
    unsigned int getSize() const;
    unsigned int getId() const;
};
#endif // VERTEXBUFFER_H
