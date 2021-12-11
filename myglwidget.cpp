#include "myglwidget.h"


MyGLWidget::MyGLWidget(QWidget *parent): QOpenGLWidget(parent){}

MyGLWidget::~MyGLWidget(){
    //destructor called on window close, frees our dynamically allocated opengl resources
    makeCurrent();
    shaderProgram.reset();

    m_funcs->glDeleteVertexArrays(1, &this->vao);
    m_funcs->glDeleteBuffers(1,&this->vbo);

    doneCurrent();
}

void MyGLWidget::loadNewObject(std::string file){
    makeCurrent();
    m_funcs->glDeleteVertexArrays(1,&this->vao);
    m_funcs->glDeleteBuffers(1,&this->vbo);
    mesh.clear();

    initializeModel(file);

    doneCurrent();
}

void MyGLWidget::loadNewTexture(std::string file){
    makeCurrent();

    m_funcs->glDeleteTextures(1,&this->texture);
    initializeTextures(file);

    doneCurrent();
}

void MyGLWidget::initializeGL(){
    /* Function called once when the opengl context is created.
     * used to set the function behavior of the rendering context and
     * build our shader programs
    */
    if (!context()) {
        qCritical() << "Can't get OGL context";
        close();
        return;
    }

    m_funcs = context()->extraFunctions();
    if (!m_funcs) {
        qCritical() << "Can't get OGL 3.2";
        close();
        return;
    }

    m_funcs->initializeOpenGLFunctions();

    glEnable(GL_DEPTH_TEST); // Depth Testing
    glDepthFunc(GL_LEQUAL);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    //glDisable(GL_CULL_FACE);
    //glCullFace(GL_BACK);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    initializeModel("C:/QtWorkspace/Qt_OpenGL/Assets/low-poly-fox/low-poly-fox-by-pixelmannen.obj");
    initializeShaders("C:/QtWorkspace/Qt_OpenGL/VertexShader.glsl", "C:/QtWorkspace/Qt_OpenGL/FragmentShader.glsl");
    initializeTextures("C:/QtWorkspace/Qt_OpenGL/Assets/low-poly-fox/texture.png");
}

void MyGLWidget::resizeGL(int w, int h)
{
    if (!m_funcs)
        return;

    m_funcs->glViewport(0, 0, w, h);
}

void MyGLWidget::paintGL(){
    // This is our draw function for this object.
    if (!m_funcs) return;
    qDebug(std::to_string(viewMatrix.getPosition().x()).c_str());
    qDebug(std::to_string(viewMatrix.getPosition().y()).c_str());
    qDebug(std::to_string(viewMatrix.getPosition().z()).c_str());
    m_funcs->glClearColor(.5f, .5f, .5f, .5f);
    m_funcs->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shaderProgram->bind();
    /* Set shader uniforms here */
        // Set Light settings
    shaderProgram->setUniformValue("light.position", QVector3D(.5f,-26.0f,32.0f));
    shaderProgram->setUniformValue("light.ambient", QVector3D(0.2f, 0.2f, 0.2f));
    shaderProgram->setUniformValue("light.diffuse", QVector3D(0.6f, 0.6f, 0.6f));
    shaderProgram->setUniformValue("light.specular", QVector3D(1.0f, 1.0f, 1.0f));
    shaderProgram->setUniformValue("viewPos", viewMatrix.getPosition());
    shaderProgram->setUniformValue("normalMatrix", modelMatrix.getModel().inverted().transposed());

    // bind our texture
    m_funcs->glActiveTexture(GL_TEXTURE0);
    m_funcs->glBindTexture(GL_TEXTURE_2D, texture);
        //set material settings
    shaderProgram->setUniformValue("Material.u_Texture", 0);
    shaderProgram->setUniformValue("material.shininess", 32.0f);

    reshape();
    qDebug("test1");
    m_funcs->glDrawElements(GL_TRIANGLES,mesh.getVertexSize(), GL_UNSIGNED_INT, nullptr);
    qDebug("test2");
    //m_funcs->glDrawArrays(GL_TRIANGLES, mesh.getVertexSize(), (GLsizei)mesh.getVertexSize());

    shaderProgram->release();
    //m_funcs->glBindTexture(GL_TEXTURE_2D, 0);
}

void MyGLWidget::reshape() {
    shaderProgram->bind();
    static bool init;
    if(!init){
        viewMatrix.setPosition(mesh.getFirstPosition() - QVector3D(4000.0f, 0.0f, 0.0f));
        init = true;
    }
    QMatrix4x4 m = modelMatrix.getModel();
    QMatrix4x4 v = viewMatrix.getView();
    QMatrix4x4 p = perspectiveMatrix.getPerspective(width()/height());
    shaderProgram->setUniformValue("perspectiveMatrix", p);
    shaderProgram->setUniformValue("modelViewMatrix", v * m);
    qDebug("reshape");
}

void MyGLWidget::initializeShaders(std::string vertex, std::string fragment){
    shaderProgram = std::make_unique<QOpenGLShaderProgram>();
    shaderProgram->addShaderFromSourceFile(QOpenGLShader::Vertex, QString::fromStdString(vertex));
    shaderProgram->addShaderFromSourceFile(QOpenGLShader::Fragment, QString::fromStdString(fragment));
    shaderProgram->link();
}

void MyGLWidget::initializeTextures(std::string textureFile){
    QImage image(QString::fromStdString(textureFile));
    if (image.isNull()) {
        qCritical() << "Can't load image";
        close();
        return;
    }
    image = image.convertToFormat(QImage::Format_RGBA8888);

    m_funcs->glGenTextures(1, &texture);
    m_funcs->glBindTexture(GL_TEXTURE_2D, texture);
    m_funcs->glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.width(), image.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, image.bits());
    m_funcs->glGenerateMipmap(GL_TEXTURE_2D);
    m_funcs->glBindTexture(GL_TEXTURE_2D, 0);
}

void MyGLWidget::initializeModel(std::string file){
    // Initializes our mesh object
    // setup vertex data
    qDebug("loading our mesh");
    mesh = MeshLoader(file);
    qDebug("-----Vertex Count----");
    qDebug(std::to_string(mesh.getVertexSize()).c_str());
    //Create VAO
    m_funcs->glGenVertexArrays(1, &this->vao);
    m_funcs->glBindVertexArray(this->vao);

    //Create EBO
    m_funcs->glGenBuffers(1,&this->ebo);
    m_funcs->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    m_funcs->glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.getIndexSize() * sizeof(GLuint), mesh.getIndices(), GL_STATIC_DRAW);

    //GEN VBO AND BIND AND SEND DATA
    m_funcs->glGenBuffers(1, &this->vbo);
    m_funcs->glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
    m_funcs->glBufferData(GL_ARRAY_BUFFER, mesh.getVertexSize() * sizeof(Vertex), mesh.getVertices(), GL_STATIC_DRAW);

    //Position attribute
    m_funcs->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, position));
    m_funcs->glEnableVertexAttribArray(0);

    //Normal attribute
    m_funcs->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));
    m_funcs->glEnableVertexAttribArray(1);

    //Texcoord attribute
    m_funcs->glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texture));
    m_funcs->glEnableVertexAttribArray(2);

    //Color attribute
    m_funcs->glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, color));
    m_funcs->glEnableVertexAttribArray(3);

    //BIND VAO 0
    m_funcs->glBindVertexArray(vbo);
}

//=================SLOTS=======================
void MyGLWidget::moveForward(){
    qDebug("forward");
    viewMatrix.moveForward(100.0f);
    update();
}

void MyGLWidget::moveBackward(){
    qDebug("backward");
    viewMatrix.moveBackward(100.0f);
    update();
}

void MyGLWidget::moveLeft(){
    qDebug("left");
    viewMatrix.moveLeft(10.0f);
    update();
}

void MyGLWidget::moveRight(){
    qDebug("right .5f");
    viewMatrix.moveRight(10.0f);
    update();
}

void MyGLWidget::moveUp(){
    qDebug("up .5f");
    viewMatrix.moveUp(10.0f);
    update();
}

void MyGLWidget::moveDown(){
    qDebug("down .5f");
    viewMatrix.moveDown(10.0f);
    update();
}
void MyGLWidget::setAxisOfRotation(int i){
   if(i == 0){
       modelMatrix.setAxisOfRotation(QVector3D(1.0f, 0.0f, 0.0f));
   }
   else if(i == 1){
       modelMatrix.setAxisOfRotation(QVector3D(0.0f, 1.0f, 0.0f));
   }
   else{
       modelMatrix.setAxisOfRotation(QVector3D(0.0f, 0.0f, 1.0f));
   }
}

void MyGLWidget::rotateObject(int degrees){
    modelMatrix.rotateObject((float)degrees);
    update();
}
