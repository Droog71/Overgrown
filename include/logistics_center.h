#ifndef LOGISTICS_CENTER_H
#define LOGISTICS_CENTER_H

#include <growth.h>
#include <assets.h>
#include <settings.h>
#include <calc_helper.h>
#include <SFML/Graphics.hpp>

class logistics_center
{
    public:
        logistics_center();
        sf::Vector2f position;
        sf::Sprite sprite;
        bool connected;
        bool destroying;
        float destroy_timer;
        void check_spores(growth &area_growth, assets &resources, bool in_range);
        void play_explosion_sound(assets &resources);
};

#endif // LOGISTICS_CENTER_H
