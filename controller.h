#pragma once

class Controllable {
public:
    virtual void move(double moveSpeed, double rotSpeed) {}
    virtual void moveForward(double moveSpeed) = 0;
    virtual void moveBackward(double moveSpeed) = 0;
    virtual void turnLeft(double rotSpeed) = 0;
    virtual void turnRight(double rotSpeed) = 0;
};

class Controller {
public:
    void move(Controllable& controllable, double moveSpeed, double rotSpeed);
};