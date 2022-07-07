#include <SFML/Window.hpp>

#include "controller.h"

void Controller::move(Controllable& controllable, double moveSpeed, double rotSpeed) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        controllable.turnLeft(rotSpeed);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        controllable.turnRight(rotSpeed);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        controllable.moveForward(moveSpeed);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        controllable.moveBackward(moveSpeed);
    }
}