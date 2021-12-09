#include "view.h"

View::View(){
    position = QVector3D(0.0f, 0.0f, 0.0f);
    pointVector = QVector3D(1.0, 0.0, 0.0);
    upVector = QVector3D(0.0, 1.0, 0.0);
    pitch = 0.0f;
    yaw = 0.0f;
    sensitivity = 0.1f;
}

QVector3D View::getPosition() {
    return position;
}

void View::setCamera(QVector3D const& pos, QVector3D const& point, QVector3D const& up){
    position = pos;
    pointVector = point;
    upVector = up;
}

void View::setPosition(QVector3D const& pos){
    position = pos;
}

void View::setPointVector(QVector3D const& point){
    pointVector = point;
}

void View::setUpVector(QVector3D const& up){
    upVector = up;
}

QMatrix4x4 View::getView(){
    //position = position in 3d-space
    //point vector is a normalized vector pointing in a direction at our position
    QMatrix4x4 m;
    m.lookAt(position, (position + pointVector), upVector);
    return m;
}

void View::calcDirections(float xOffset, float yOffset) {
    pitch += yOffset * sensitivity;
    yaw += xOffset * sensitivity;

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;
    if (yaw >= 360) {
        yaw -= 360;
    }
    if (yaw < 0) {
        yaw += 360;
    }

    pointVector.setX(qCos(qDegreesToRadians(yaw)) * qCos(qDegreesToRadians(pitch)));
    pointVector.setY(qSin(qDegreesToRadians(pitch)));
    pointVector.setZ(qSin(qDegreesToRadians(yaw)) * qCos(qDegreesToRadians(pitch)));
    pointVector.normalize();
}

void View::moveForward(float speed) {
    position.setX(position.x() + (pointVector.x() * speed));
    position.setZ(position.z() + (pointVector.z() * speed));
}

void View::moveBackward(float speed){
    position.setX(position.x() - (pointVector.x() * speed));
    position.setZ(position.z() - (pointVector.z() * speed));
}

void View::moveLeft(float speed){
    QVector3D orthPoint = QVector3D::crossProduct(pointVector, upVector);
    position.setX(position.x() - (orthPoint.x() * speed));
    position.setZ(position.z() - (orthPoint.z() * speed));
}

void View::moveRight(float speed){
    QVector3D orthPoint = QVector3D::crossProduct(pointVector, upVector);
    position.setX(position.x() + (orthPoint.x() * speed));
    position.setZ(position.z() + (orthPoint.z() * speed));
}

void View::moveUp(float speed) {
    position.setY(position.y() + speed);
}

void View::moveDown(float speed) {
    position.setY(position.y() - speed);
}

void View::lookHorizontal(float theta){
    //perform a rotation about the z-axis
    float rads = qDegreesToRadians(theta);
    pointVector.setX(qCos(rads)*pointVector.x() - qSin(rads) * pointVector.y());
    pointVector.setY(qSin(rads)*pointVector.x() + qCos(rads)*pointVector.y());
    pointVector.normalize();
}
void View::lookVertical(float theta){
    //perform a rotation about the y-axis
    float rads = qDegreesToRadians(theta);
    pointVector.setX(qCos(rads)*pointVector.x() + qSin(rads)*pointVector.z());
    pointVector.setZ(-qSin(rads)*pointVector.x() + qCos(rads)*pointVector.z());
    pointVector.normalize();
}
