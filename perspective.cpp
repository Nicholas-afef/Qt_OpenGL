#include "perspective.h"

Perspective::Perspective(){
    angle = 45.0f;
    nearPlane = 0.1f;
    farPlane = 10000.0f;
}

void Perspective::setAngle(float theta){
    angle = theta;
}

void Perspective::setNear(float near){
    nearPlane = near;
}

void Perspective::setFar(float far){
    farPlane = far;
}

QMatrix4x4 Perspective::getPerspective(float aspectRatio){
    QMatrix4x4 m;
    m.perspective(qDegreesToRadians(angle), aspectRatio, nearPlane, farPlane);
    return m;
}

void Perspective::changeAngle(float theta) {
    angle += theta;
    if (angle > 80) {
        angle = 80;
    }
    if (angle < 20) {
        angle = 20;
    }
}

void Perspective::moveNearPlane(float n) {
    nearPlane += n;
    if (nearPlane < .1f) {
        nearPlane = .1f;
    }
    if (nearPlane > (farPlane - 1.0f)) {
        nearPlane = farPlane - 1.0f;
    }
}

void Perspective::moveFarPlane(float n) {
    farPlane += n;
    if (farPlane < (nearPlane + 1.0f)) {
        farPlane = nearPlane + 1.0f;
    }
    if (farPlane > 100.0f) {
        farPlane = 100.0f;
    }
}
