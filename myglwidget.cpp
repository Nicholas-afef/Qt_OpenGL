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

    initializeModel();
    initializeShaders();
    initializeTextures();
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
    m_funcs->glDrawArrays(GL_TRIANGLES, vbo, (GLsizei)mesh.getSize());

    shaderProgram->release();
    //m_funcs->glBindTexture(GL_TEXTURE_2D, 0);
}

void MyGLWidget::reshape() {
    shaderProgram->bind();
    QMatrix4x4 m = modelMatrix.getModel();
    QMatrix4x4 v = viewMatrix.getView();
    QMatrix4x4 p = perspectiveMatrix.getPerspective(width()/height());
    shaderProgram->setUniformValue("perspectiveMatrix", p);
    shaderProgram->setUniformValue("viewMatrix", v);
    shaderProgram->setUniformValue("modelMatrix", m);
}

void MyGLWidget::initializeShaders(){
    shaderProgram = std::make_unique<QOpenGLShaderProgram>();
    shaderProgram->addShaderFromSourceFile(QOpenGLShader::Vertex, "C:/QtWorkspace/HelloOpenGL/VertexShader.glsl");
    shaderProgram->addShaderFromSourceFile(QOpenGLShader::Fragment, "C:/QtWorkspace/HelloOpenGL/FragmentShader.glsl");
    shaderProgram->link();
}

void MyGLWidget::initializeTextures(){
    QImage image("C:/QtWorkspace/HelloOpenGL/assets/CatObj/Cat_diffuse.jpg");
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

void MyGLWidget::initializeModel(){
    // Initializes our mesh object
    // setup vertex data
    qDebug("loading our mesh");
    mesh = MeshLoader("C:/QtWorkspace/HelloOpenGL/assets/CatObj/12221_Cat_v1_l3.obj");
    qDebug("-----Vertex Count----");
    qDebug(std::to_string(mesh.getSize()).c_str());
    //Create VAO
    m_funcs->glGenVertexArrays(1, &this->vao);
    m_funcs->glBindVertexArray(this->vao);

    //GEN VBO AND BIND AND SEND DATA
    m_funcs->glGenBuffers(1, &this->vbo);
    m_funcs->glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
    m_funcs->glBufferData(GL_ARRAY_BUFFER, mesh.getSize() * sizeof(Vertex), mesh.getVertices(), GL_STATIC_DRAW);

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
    m_funcs->glBindVertexArray(0);
}

//=================SLOTS=======================
void MyGLWidget::moveForward(){
    qDebug("forward .5f");
    viewMatrix.moveForward(10.0f);
    paintGL();
}

void MyGLWidget::moveBackward(){
    qDebug("backward .5f");
    viewMatrix.moveBackward(10.0f);
    paintGL();
}

void MyGLWidget::moveLeft(){
    qDebug("left .5f");
    viewMatrix.moveLeft(10.0f);
    paintGL();
}

void MyGLWidget::moveRight(){
    qDebug("right .5f");
    viewMatrix.moveRight(10.0f);
    paintGL();
}

void MyGLWidget::moveUp(){
    qDebug("up .5f");
    viewMatrix.moveUp(10.0f);
    paintGL();
}

void MyGLWidget::moveDown(){
    qDebug("down .5f");
    viewMatrix.moveDown(10.0f);
    paintGL();
}

void MyGLWidget::lookHorizontal(int theta){
    viewMatrix.lookHorizontal((float)theta);
}
void MyGLWidget::lookVertical(int theta){
    viewMatrix.lookVertical((float)theta);
}
