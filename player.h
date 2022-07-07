#pragma once
#include <memory>

#include "camera.h"
#include "controller.h"

class Camera;

class Player : public Controllable {
public:
    Player(int i, int i1, Controller controller);

    double x, y;
    std::unique_ptr<Camera> camera;
    Controller controller;

    void move(double moveSpeed, double rotSpeed) override;
    void moveForward(double moveSpeed) override;
    void moveBackward(double moveSpeed) override;
    void turnLeft(double rotSpeed) override;
    void turnRight(double rotSpeed) override;
};