#pragma once
#include <SFML/Graphics.hpp>

#include "player.h"
#include "settings.h"
#include "controller.h"

class CameraBuilder;

class Player;

class Camera : public Controllable {
private:
    friend class CameraBuilder;
    int width = 0, height = 0;
    Player& object;
    sf::RenderWindow& window;

    Camera(Player& object_, sf::RenderWindow& window_, int (&scene_)[mapWidth][mapHeight])
        : object(object_)
        , window(window_)
        , scene(scene_)
    {}

    static void calculateStep(int& step, double& sideDist,
                              const double& rayDir, const double& rayPos,
                              const double& map, const double& deltaDist
                              );

public:
    int (&scene)[mapWidth][mapHeight];
    double dirX = 0, dirY = 0, planeX = 0, planeY = 0;
    static CameraBuilder builder(Player& object_, sf::RenderWindow& window_, int (&scene_)[mapWidth][mapHeight]);
    void performDDA(bool& notHit,
                    int& side,
                    int& mapX, int& mapY,
                    double& sideDistX, double& sideDistY,
                    const int& stepX, const int& stepY,
                    const double& deltaDistX, const double& deltaDistY);
    void drawFrame();

    void moveForward(double moveSpeed) override;
    void moveBackward(double moveSpeed) override;
    void turnLeft(double rotSpeed) override;
    void turnRight(double rotSpeed) override;
};