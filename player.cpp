#include "player.h"

void Player::move(double moveSpeed, double rotSpeed) {
    controller.move(*this, moveSpeed, rotSpeed);
}

void Player::moveForward(double moveSpeed) {
    if(camera->scene[int(x + camera->dirX * moveSpeed)][int(y)] == false)
        x += camera->dirX * moveSpeed;
    if(camera->scene[int(x)][int(y + camera->dirY * moveSpeed)] == false)
        y += camera->dirY * moveSpeed;
}

void Player::moveBackward(double moveSpeed) {
    if(camera->scene[int(x - camera->dirX * moveSpeed)][int(y)] == false)
        x -= camera->dirX * moveSpeed;
    if(camera->scene[int(x)][int(y - camera->dirY * moveSpeed)] == false)
        y -= camera->dirY * moveSpeed;
}

void Player::turnLeft(double rotSpeed) {
    camera->turnLeft(rotSpeed);
}

void Player::turnRight(double rotSpeed) {
    camera->turnRight(rotSpeed);
}

Player::Player(int x_, int y_, Controller controller_)
    : x(x_)
    , y(y_)
    , controller(controller_)
{}
