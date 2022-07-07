#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <iostream>

#include "camera.h"
#include "cameraBuilder.h"

void Camera::calculateStep(int& step, double& sideDist,
                                      const double& rayDir, const double& rayPos,
                                      const double& map, const double& deltaDist
) {
    if (rayDir < 0) {
        step = -1;
        sideDist = (rayPos - map) * deltaDist;
    } else {
        step = 1;
        sideDist = (map + 1.0 - rayPos) * deltaDist;
    }
}

CameraBuilder Camera::builder(Player& object_, sf::RenderWindow& window_, int (&scene_)[mapWidth][mapHeight]) {
    return CameraBuilder{object_, window_, scene_};
}

void Camera::performDDA(bool& notHit,
                                   int& side,
                                   int& mapX, int& mapY,
                                   double& sideDistX, double& sideDistY,
                                   const int& stepX, const int& stepY,
                                   const double& deltaDistX, const double& deltaDistY
) {
    while (notHit) {
        //jump to next map square, OR in x-direction, OR in y-direction
        if (sideDistX < sideDistY) {
            sideDistX += deltaDistX;
            mapX += stepX;
            side = 0;
        } else {
            sideDistY += deltaDistY;
            mapY += stepY;
            side = 1;
        }
        //Check if ray has notHit a wall
        if (scene[mapX][mapY] > 0) notHit = false;
    }
}

void Camera::drawFrame() {
    for(int x = 0; x != width; x++) {
        // calculate ray position and direction
        double cameraX = 2 * x / double(width) - 1; //x-coordinate in camera space
        double rayPosX = object.x;
        double rayPosY = object.y;
        double rayDirX = dirX + planeX * cameraX;
        double rayDirY = dirY + planeY * cameraX;

        //which box of the map we're in
        int mapX = int(rayPosX);
        int mapY = int(rayPosY);

        //length of ray from current position to next x or y-side
        double sideDistX;
        double sideDistY;

        //length of ray from one x or y-side to next x or y-side
        double deltaDistX = std::sqrt(1 + (rayDirY * rayDirY) / (rayDirX * rayDirX));
        double deltaDistY = std::sqrt(1 + (rayDirX * rayDirX) / (rayDirY * rayDirY));
        double perpWallDist;

        //what direction to step in x or y-direction (either +1 or -1)
        int stepX;
        int stepY;

        bool notHit = true; //was there a wall notHit?
        int side; //was a NS or a EW wall notHit?

        //calculate step and initial sideDist
        calculateStep(stepX, sideDistX, rayDirX, rayPosX, mapX, deltaDistX);
        calculateStep(stepY, sideDistY, rayDirY, rayPosY, mapY, deltaDistY);

        performDDA(
                notHit, side, mapX, mapY, sideDistX, sideDistY,
                stepX, stepY, deltaDistX, deltaDistY
        );

        //Calculate distance projected on camera direction (oblique distance will give fisheye effect!)
        if (side == 0)
        perpWallDist = fabs((mapX - rayPosX + (1.0 - stepX) / 2) / rayDirX);
        else
        perpWallDist = fabs((mapY - rayPosY + (1.0 - stepY) / 2) / rayDirY);

        //Calculate height of line to draw on screen
        int lineHeight = abs(int(height / perpWallDist));

        //calculate lowest and highest pixel to fill in current stripe
        int drawStart = -lineHeight / 2 + height / 2;
        if(drawStart < 0)drawStart = 0;
        int drawEnd = lineHeight / 2 + height / 2;
        if(drawEnd >= height) drawEnd = height - 1;

        //choose wall color
        sf::Color color;
        switch(scene[mapX][mapY]) {
            case 1:  color = sf::Color::Red;     break; //red
            case 2:  color = sf::Color::Green;   break; //green
            case 3:  color = sf::Color::Blue;    break; //blue
            case 4:  color = sf::Color::White;   break; //white
            default: color = sf::Color::Yellow;  break; //yellow
        }

        //give x and y sides different brightness
        if (side == 1) {
        color = sf::Color(color.r / 2, color.g / 2, color.b / 2);
        }

        //draw the pixels of the stripe as a vertical line
        //verLine(x, drawStart, drawEnd, color);

        sf::Vertex line[2] =
                {
                        sf::Vertex(sf::Vector2f(float(x), float(drawStart)), color),
                        sf::Vertex(sf::Vector2f(float(x), float(drawEnd)), color)
                };
        window.draw(line , 2, sf::Lines);
    }
}

void Camera::moveForward(double moveSpeed) {}

void Camera::moveBackward(double moveSpeed) {}

void Camera::turnLeft(double rotSpeed) {
    double oldDirX = dirX;
    dirX = dirX * cos(rotSpeed) - dirY * sin(rotSpeed);
    dirY = oldDirX * sin(rotSpeed) + dirY * cos(rotSpeed);
    double oldPlaneX = planeX;
    planeX = planeX * cos(rotSpeed) - planeY * sin(rotSpeed);
    planeY = oldPlaneX * sin(rotSpeed) + planeY * cos(rotSpeed);
}

void Camera::turnRight(double rotSpeed) {
    double oldDirX = dirX;
    dirX = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed);
    dirY = oldDirX * sin(-rotSpeed) + dirY * cos(-rotSpeed);
    double oldPlaneX = planeX;
    planeX = planeX * cos(-rotSpeed) - planeY * sin(-rotSpeed);
    planeY = oldPlaneX * sin(-rotSpeed) + planeY * cos(-rotSpeed);
}