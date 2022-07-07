#include <SFML/Graphics.hpp>

#include "cameraBuilder.h"
#include "player.h"

CameraBuilder& CameraBuilder::directionX(const double dirX) {
    camera.dirX = dirX;
    return *this;
}

CameraBuilder& CameraBuilder::directionY(double dirY) {
    camera.dirY = dirY;
    return *this;
}

CameraBuilder& CameraBuilder::planeX(const double planeX) {
    camera.planeX = planeX;
    return *this;
}

CameraBuilder& CameraBuilder::planeY(const double planeY) {
    camera.planeY = planeY;
    return *this;
}

CameraBuilder& CameraBuilder::width(const int width) {
    camera.width = width;
    return *this;
}

CameraBuilder& CameraBuilder::height(const int height) {
    camera.height = height;
    return *this;
}

Camera CameraBuilder::build() {
    return camera;
}