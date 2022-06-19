#ifndef DRILL_H
#define DRILL_H

#include <assets.h>
#include <growth.h>
#include <iostream>
#include <settings.h>
#include <resource_node.h>
#include <calc_helper.h>

class drill
{
    public:
        drill();
        bool cycled;
        bool destroying;
        bool found_node;
        float drill_timer;
        float destroy_timer;
        std::string node_type;
        sf::Sprite sprite;
        sf::Vector2f position;
        void check_spores(growth &area_growth, assets &resources, bool in_range);
        void play_explosion_sound(assets &resources);
        void mine(assets &resources, std::array<resource_node, 5> &resource_nodes, std::map<std::string, int> &inventory, int &power, float frame_time, bool in_range);
};

#endif // DRILL_H
