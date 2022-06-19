#ifndef GENERATOR_H
#define GENERATOR_H

#include <assets.h>
#include <growth.h>
#include <iostream>
#include <settings.h>
#include <calc_helper.h>
#include <SFML/Graphics.hpp>

class generator
{
    public:
        generator();
        float gen_timer;
        float destroy_timer;
        bool destroying;
        bool logi_connected;
        sf::Sprite sprite;
        sf::Vector2f position;
        void check_spores(growth &area_growth, assets &resources, bool in_range);
        void play_explosion_sound(assets &resources);
        void generate_power(assets &resources, std::map<std::string, int> &inventory, int &power, float frame_time);
};

#endif // GENERATOR_H
