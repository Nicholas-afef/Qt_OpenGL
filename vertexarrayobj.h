#ifndef VERTEXARRAYOBJ_H
#define VERTEXARRAYOBJ_H

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "MeshLoader.h"
#include <vector>

class VertexArrayObj{
private:
    VertexBuffer vbo;
    IndexBuffer ibo;
    unsigned int vao;
public:
    VertexArrayObj(MeshLoader&);
    ~VertexArrayObj();

    void bind();
    void unbind();
    unsigned int getIboId();
    unsigned int getVboId();
};
#endif // VERTEXARRAYOBJ_H
