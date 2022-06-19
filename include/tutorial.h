#ifndef TUTORIAL_H
#define TUTORIAL_H

#include <math.h>
#include <world.h>
#include <iostream>
#include <SFML/Graphics.hpp>

class tutorial
{
    public:
        int step;
        bool visible;
        bool completed;
        tutorial(std::string cwd);
        void draw_tutorial(sf::RenderWindow &window, world &game_world);

    private:
        sf::Texture gui_background_texture;
        sf::Sprite gui_background_sprite;
        sf::Text tutorial_text;
        sf::Font tutorial_font;
};

#endif // TUTORIAL_H
