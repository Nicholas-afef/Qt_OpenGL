#ifndef VIEW_H
#define VIEW_H

#include <QMatrix4x4>
#include <QVector3D>
#include <QtMath>

class View{
private:
    QVector3D position;
    QVector3D pointVector;
    QVector3D upVector;
    float pitch, yaw;
    float sensitivity;
public:
    View();
    QMatrix4x4 vMatrix;
    void setCamera(QVector3D const&, QVector3D const&, QVector3D const&);
    void setPosition(QVector3D const&);
    void setPointVector(QVector3D const&);
    void setUpVector(QVector3D const&);
    QMatrix4x4 getView();
    QVector3D getPosition();
    void calcDirections(float, float);
    void lookHorizontal(float);
    void lookVertical(float);
    void moveForward(float speed);
    void moveBackward(float speed);
    void moveLeft(float speed);
    void moveRight(float speed);
    void moveUp(float speed);
    void moveDown(float speed);
};

#endif // VIEW_H
