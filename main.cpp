#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cstdlib>

#include "player.h"
#include "camera.h"
#include "cameraBuilder.h"
#include "profile.h"

int worldMap[24][24] =
        {
                {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
                {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
                {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
                {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
                {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
                {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
        };

int main() {

    int w = int(sf::VideoMode::getDesktopMode().width), h = int(sf::VideoMode::getDesktopMode().height);

    // Create the main window
    sf::RenderWindow window(
            // have to add 1 to make Style::None act like Borderless Windowed instead of Fullscreen
            sf::VideoMode(w + 1, h),
            "SFML window",
            sf::Style::None
            );

    window.setFramerateLimit(60);
    sf::Clock clock = sf::Clock();
    sf::Time fps;

    Controller controller;
    Player player{22, 12, controller};
    player.camera = std::make_unique<Camera>(Camera::builder(player, window, worldMap)
                                                     .width(w)
                                                     .height(h)
                                                     .planeX(0)
                                                     .planeY(0.66)
                                                     .directionX(-1)
                                                     .directionY(0)
                                                     .build());

    // Start the game loop
    while (window.isOpen()) {
//        LOG_DURATION("Cycle")
        // Process events
        sf::Event event{};
        while (window.pollEvent(event)) {
            // Close window: exit
            if (event.type == sf::Event::Closed)
                window.close();

            // Escape key: exit
            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))
                window.close();
        }

        window.clear();

        player.camera->drawFrame();

        fps = clock.getElapsedTime();
        clock.restart();

        player.move(
                fps.asSeconds() * 5.0, //the constant value is in squares/second
                fps.asSeconds() * 3.0  //the constant value is in radians/second
                );

        window.display();
        window.clear();
    }

    return EXIT_SUCCESS;
}