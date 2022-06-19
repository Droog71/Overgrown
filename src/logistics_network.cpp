#include "logistics_network.h"

bool logistics_connected(int area_index, world &game_world)
{
    int cmd = game_world.areas[area_index].cmd_centers.size();
    int logi = game_world.areas[area_index].logi_centers.size();

    if (cmd > 0)
    {
        game_world.areas[area_index].connected = true;
        return true;
    }

    if (cmd < 1 && logi < 1)
    {
        game_world.areas[area_index].connected = false;
        return false;
    }

    sf::Vector2i coords = game_world.areas[area_index].coordinates;
    sf::Vector2i n = sf::Vector2i(coords.x, coords.y + 1);
    sf::Vector2i s = sf::Vector2i(coords.x, coords.y - 1);
    sf::Vector2i e = sf::Vector2i(coords.x + 1, coords.y);
    sf::Vector2i w = sf::Vector2i(coords.x - 1, coords.y);
    sf::Vector2i dirs [4] = { n, s, e, w };

    for (int i = 0; i < 4; i++)
    {
        int index = game_world.get_area_index(dirs[i]);
        if (index != -1)
        {
            int cmd_count = game_world.areas[index].cmd_centers.size();
            int logi_count = game_world.areas[index].logi_centers.size();

            if ( cmd_count > 0)
            {
                game_world.areas[area_index].connected = true;
                return true;
            }

            if (logi_count > 0 && game_world.areas[index].connected == true)
            {
                game_world.areas[area_index].connected = true;
                return true;
            }
        }
    }
    game_world.areas[area_index].connected = false;
    return false;
}
