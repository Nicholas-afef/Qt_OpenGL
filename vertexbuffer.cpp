#include "vertexbuffer.h"

VertexBuffer::VertexBuffer(const void* vertexData, unsigned int vertexDataSize){
    size = vertexDataSize;
    // std::cout << "vertexBuffer size: " << size << std::endl;
    glGenBuffers(1, &vertexBufferId);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
    glBufferData(GL_ARRAY_BUFFER, vertexDataSize, vertexData, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer(){
    glDeleteBuffers(1, &vertexBufferId);
}

void VertexBuffer::bind(){
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
}

void VertexBuffer::unbind(){
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

unsigned int VertexBuffer::getSize() const{
    return size;
}

unsigned int VertexBuffer::getId() const {
    return vertexBufferId;
}
