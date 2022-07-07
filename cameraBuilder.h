#pragma once

#include "camera.h"
#include "settings.h"

class CameraBuilder {
private:
    Camera camera;
public:
    CameraBuilder(Player& object_, sf::RenderWindow& window_, int (&scene_)[mapWidth][mapHeight])
        : camera({object_, window_, scene_})
    {}

    CameraBuilder& directionX(double dirX);
    CameraBuilder& directionY(double dirX);
    CameraBuilder& planeX(double planeX);
    CameraBuilder& planeY(double planeY);
    CameraBuilder& width(int width);
    CameraBuilder& height(int height);
    Camera build();
};
