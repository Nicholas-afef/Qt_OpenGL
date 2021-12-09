#ifndef PERSPECTIVE_H
#define PERSPECTIVE_H

#include <QMatrix4x4>
#include <QtMath>

class Perspective{
private:
    float angle;
    float nearPlane;
    float farPlane;
public:
    QMatrix4x4 pMatrix;
    Perspective();
    void setAngle(float);
    void setNear(float);
    void setFar(float);
    QMatrix4x4 getPerspective(float);
    void changeAngle(float);
    void moveNearPlane(float);
    void moveFarPlane(float);
};


#endif // PERSPECTIVE_H
