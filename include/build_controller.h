#ifndef BUILD_CONTROLLER_H
#define BUILD_CONTROLLER_H

#include <world.h>
#include <assets.h>
#include <iostream>
#include <harvester.h>
#include <calc_helper.h>
#include <SFML/Graphics.hpp>

class build_controller
{
    public:
        sf::Vector2f zoom;
        bool building;
        bool destroying;
        std::string build_type;
        std::array<int, 3> build_cost [7];
        void init(assets* resources);
        void build_harvester(world &game_world, sf::Vector2i pos);
        void build_cannon(world &game_world, sf::Vector2i pos);
        void build_annihilator(world &game_world, sf::Vector2i pos);
        void build_generator(world &game_world, sf::Vector2i pos);
        void build_drill(world &game_world, sf::Vector2i pos);
        void build_logi_center(world &game_world, sf::Vector2i pos);
        void build_cmd_center(world &game_world, sf::Vector2i pos);
        void destroy(world &game_world, sf::Vector2i mouse_pos, assets* resources);
        void play_explosion_sound(assets* resources);
        build_controller();
    private:
        assets* resources;
        bool build_blocked(world &game_world, int area_index, sf::Vector2i pos);

};

#endif // BUILD_CONTROLLER_H
