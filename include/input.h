#ifndef INPUT_H
#define INPUT_H

#include <math.h>
#include <world.h>
#include <assets.h>
#include <pause_menu.h>
#include <build_controller.h>
#include <SFML/Graphics.hpp>

struct input_event_params
{
    sf::Event event;
    pause_menu &p_menu;
    build_controller &builder;
    world &game_world;
    sf::Vector2i mouse_position;
};

class input
{
    public:
        void init(assets* resources);
        void handle_events(struct input_event_params &params);

    private:
        assets* resources;
};

#endif // INPUT_H
