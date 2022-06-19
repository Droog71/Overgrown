#ifndef ANNIHILATOR_H
#define ANNIHILATOR_H

#include <growth.h>
#include <iostream>
#include <assets.h>
#include <settings.h>
#include <supplies.h>
#include <algorithm>
#include <calc_helper.h>
#include <SFML/Graphics.hpp>

class annihilator
{
    public:
        annihilator();
        bool fired;
        bool cycled;
        bool destroying;
        int power_buffer;
        float destroy_timer;
        float fire_timer;
        sf::Sprite sprite;
        sf::Vector2f position;
        sf::Vector2f target;
        void check_spores(growth &area_growth, assets &resources, bool in_range);
        void play_explosion_sound(assets &resources);
        void fire(assets &resources, growth &area_growth, std::map<std::string, int> &inventory, int &power, float frame_time, bool in_range);
};

#endif // ANNIHILATOR_H
