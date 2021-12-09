#include "mesh.h"

Mesh::Mesh(Vertex* vertexArray, const unsigned& nrOfVertices, GLuint* indexArray, const unsigned& nrOfIndices){

    this->nrOfVertices = nrOfVertices;

    this->vertexArray = new Vertex[this->nrOfVertices];
    for (size_t i = 0; i < nrOfVertices; i++){
        this->vertexArray[i] = vertexArray[i];
    }

    this->initVAO();
}

Mesh::~Mesh(){
    glDeleteVertexArrays(1, &this->VAO);
    glDeleteBuffers(1, &this->VBO);

    if (this->nrOfIndices > 0)
    {
        glDeleteBuffers(1, &this->EBO);
    }

    delete[] this->vertexArray;
    delete[] this->indexArray;
}

void Mesh::initVAO(){
    //Create VAO
    glCreateVertexArrays(1, &this->VAO);
    glBindVertexArray(this->VAO);

    //GEN VBO AND BIND AND SEND DATA
    glGenBuffers(1, &this->VBO);
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glBufferData(GL_ARRAY_BUFFER, this->nrOfVertices * sizeof(Vertex), this->vertexArray, GL_STATIC_DRAW);

    //GEN EBO AND BIND AND SEND DATA
    if (this->nrOfIndices > 0)
    {
        glGenBuffers(1, &this->EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->nrOfIndices * sizeof(GLuint), this->indexArray, GL_STATIC_DRAW);
    }

    //SET VERTEXATTRIBPOINTERS AND ENABLE (INPUT ASSEMBLY)
    //Position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, position));
    glEnableVertexAttribArray(0);
    //Color
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, color));
    glEnableVertexAttribArray(1);
    //Texcoord
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texcoord));
    glEnableVertexAttribArray(2);
    //Normal
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));
    glEnableVertexAttribArray(3);

    //BIND VAO 0
    glBindVertexArray(0);
}

void Mesh::updateUniforms(QOpenGLShader* shader){
    shader->setMat4fv(this->ModelMatrix, "ModelMatrix");
}

void Mesh::render(QOpenGLShaderProgram* shader){
    //Update uniforms
    shaderProgram->setUniformValue("normalMatrix", model.getModel());

    shader->use();

    //Bind VAO
    glBindVertexArray(this->VAO);

    //RENDER
    glDrawArrays(GL_TRIANGLES, 0, this->nrOfVertices);

    //Cleanup
    glBindVertexArray(0);
    glUseProgram(0);
    glActiveTexture(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}
