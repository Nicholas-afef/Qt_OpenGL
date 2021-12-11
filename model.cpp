#include "model.h"

Model::Model(){
    translate = QVector3D(0.0f, 0.0f, 0.0f);
    rotAngle = 0.0f;
    axisOfRotation = QVector3D(0.0f, 1.0f, 0.0f);
    scalar = 1;
}

void Model::setPosition(QVector3D pos){
    translate = pos;
}

void Model::setAngle(float theta) {
    rotAngle = theta;
}

void Model::setAxisOfRotation(QVector3D aor){
    axisOfRotation = aor;
}

void Model::setScalar(float s){
    scalar = s;
}

QMatrix4x4 Model::getModel(){
    QMatrix4x4 matrix;
    matrix.setToIdentity();
    matrix.scale(scalar);
    matrix.rotate(rotAngle, axisOfRotation);
    matrix.translate(translate);
    return matrix;
}

void Model::rotateObject(float theta) {
    rotAngle = theta;
}
