#ifndef MODEL_H
#define MODEL_H

#include <QMatrix4x4>
#include <QVector3D>

class Model{
private:
    QVector3D translate;
    float rotAngle;
    QVector3D axisOfRotation;
    float scalar;
public:
    Model();
    QMatrix4x4 mMatrix;
    void setPosition(QVector3D);
    void setAngle(float);
    void setAxisOfRotation(QVector3D);
    void setScalar(float);
    QMatrix4x4 getModel();
    void rotateObject(float);
};

#endif // MODEL_H
