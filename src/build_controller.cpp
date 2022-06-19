#include "build_controller.h"

build_controller::build_controller()
{
    building = false;
    destroying = false;
    build_type = "none";
    zoom = sf::Vector2f(1, 1);
}

void build_controller::init(assets* resources)
{
    this->resources = resources;
    build_cost[0] = { 20, 20, 0 };
    build_cost[1] = { 40, 40, 0 };
    build_cost[2] = { 80, 80, 0 };
    build_cost[3] = { 160, 160, 160 };
    build_cost[4] = { 320, 320, 320 };
    build_cost[5] = { 640, 640, 0 };
    build_cost[6] = { 1280, 1280, 0 };
}

void build_controller::build_cmd_center(world &game_world, sf::Vector2i pos)
{
    sf::Vector2i coords = game_world.player_coordinates;
    int area_index = game_world.get_area_index(coords);
    if (!build_blocked(game_world, area_index, pos))
    {
        bool can_afford = true;
        bool already_built = false;
        std::string inv [2] = { "iron", "copper" };

        for (int i = 0; i < 2; i++)
        {
            if (game_world.inventory[inv[i]] < build_cost[6][i])
            {
                can_afford = false;
            }
        }

        for (unsigned int i = 0; i < game_world.areas.size(); i++)
        {
            if (game_world.areas[i].cmd_centers.size() > 0)
            {
                already_built = true;
                break;
            }
        }

        if (can_afford == true && already_built == false)
        {
            game_world.inventory["iron"] -= build_cost[6][0];
            game_world.inventory["copper"] -= build_cost[6][1];
            command_center new_cmd_center;
            new_cmd_center.position.x = pos.x - 32 * zoom.x;
            new_cmd_center.position.y = pos.y - 32 * zoom.x;
            new_cmd_center.sprite.setTexture(resources->cmd_center_texture);
            game_world.areas[area_index].cmd_centers.push_back(new_cmd_center);
        }
    }
}

void build_controller::build_logi_center(world &game_world, sf::Vector2i pos)
{
    sf::Vector2i coords = game_world.player_coordinates;
    int area_index = game_world.get_area_index(coords);
    if (!build_blocked(game_world, area_index, pos))
    {
        bool can_afford = true;
        std::string inv [2] = { "iron", "copper" };

        for (int i = 0; i < 2; i++)
        {
            if (game_world.inventory[inv[i]] < build_cost[5][i])
            {
                can_afford = false;
            }
        }

        if (can_afford == true)
        {
            game_world.inventory["iron"] -= build_cost[5][0];
            game_world.inventory["copper"] -= build_cost[5][1];
            logistics_center new_logi_center;
            new_logi_center.position.x = pos.x - 16 * zoom.x;
            new_logi_center.position.y = pos.y - 16 * zoom.x;
            new_logi_center.sprite.setTexture(resources->logi_center_texture);
            game_world.areas[area_index].logi_centers.push_back(new_logi_center);
        }
    }
}

void build_controller::build_generator(world &game_world, sf::Vector2i pos)
{
    sf::Vector2i coords = game_world.player_coordinates;
    int area_index = game_world.get_area_index(coords);
    if (!build_blocked(game_world, area_index, pos))
    {
        bool can_afford = true;
        std::string inv [2] = { "iron", "copper" };

        for (int i = 0; i < 2; i++)
        {
            if (game_world.inventory[inv[i]] < build_cost[0][i])
            {
                can_afford = false;
            }
        }

        if (can_afford == true)
        {
            game_world.inventory["iron"] -= build_cost[0][0];
            game_world.inventory["copper"] -= build_cost[0][1];
            generator new_generator;
            new_generator.position.x = pos.x - 8 * zoom.x;
            new_generator.position.y = pos.y - 8 * zoom.x;
            new_generator.sprite.setTexture(resources->generator_off_texture);
            game_world.areas[area_index].generators.push_back(new_generator);
        }
    }
}

void build_controller::build_drill(world &game_world, sf::Vector2i pos)
{
    int area_index = game_world.get_area_index(game_world.player_coordinates);
    if (!build_blocked(game_world, area_index, pos))
    {
        bool can_afford = true;
        std::string inv [2] = { "iron", "copper" };

        for (int i = 0; i < 2; i++)
        {
            if (game_world.inventory[inv[i]] < build_cost[1][i])
            {
                can_afford = false;
            }
        }

        if (can_afford == true)
        {
            game_world.inventory["iron"] -= build_cost[1][0];
            game_world.inventory["copper"] -= build_cost[1][1];
            drill new_drill;
            new_drill.position.x = pos.x - 8 * zoom.x;
            new_drill.position.y = pos.y - 8 * zoom.x;
            new_drill.sprite.setTexture(resources->drill_texture);
            game_world.areas[area_index].drills.push_back(new_drill);
        }
    }
}

void build_controller::build_harvester(world &game_world, sf::Vector2i pos)
{
    int area_index = game_world.get_area_index(game_world.player_coordinates);
    if (!build_blocked(game_world, area_index, pos))
    {
        bool can_afford = true;
        std::string inv [3] = { "iron", "copper", "spores" };

        for (int i = 0; i < 3; i++)
        {
            if (game_world.inventory[inv[i]] < build_cost[2][i])
            {
                can_afford = false;
            }
        }

        if (can_afford == true)
        {
            game_world.inventory["iron"] -= build_cost[2][0];
            game_world.inventory["copper"] -= build_cost[2][1];
            game_world.inventory["spores"] -= build_cost[2][2];
            harvester new_harvester;
            new_harvester.position.x = pos.x - 8 * zoom.x;
            new_harvester.position.y = pos.y - 8 * zoom.x;
            new_harvester.sprite.setTexture(resources->harvester_texture);
            game_world.areas[area_index].harvesters.push_back(new_harvester);
        }
    }
}

void build_controller::build_cannon(world &game_world, sf::Vector2i pos)
{
    int area_index = game_world.get_area_index(game_world.player_coordinates);
    if (!build_blocked(game_world, area_index, pos))
    {
        bool can_afford = true;
        std::string inv [3] = { "iron", "copper", "spores" };

        for (int i = 0; i < 3; i++)
        {
            if (game_world.inventory[inv[i]] < build_cost[3][i])
            {
                can_afford = false;
            }
        }

        if (can_afford == true)
        {
            game_world.inventory["iron"] -= build_cost[3][0];
            game_world.inventory["copper"] -= build_cost[3][1];
            game_world.inventory["spores"] -= build_cost[3][2];
            cannon new_cannon;
            new_cannon.position.x = pos.x - 16 * zoom.x;
            new_cannon.position.y = pos.y - 16 * zoom.x;
            new_cannon.sprite.setTexture(resources->cannon_texture);
            game_world.areas[area_index].cannons.push_back(new_cannon);
        }
    }
}

void build_controller::build_annihilator(world &game_world, sf::Vector2i pos)
{
    int area_index = game_world.get_area_index(game_world.player_coordinates);
    if (!build_blocked(game_world, area_index, pos))
    {
        bool can_afford = true;
        std::string inv [3] = { "iron", "copper", "spores" };

        for (int i = 0; i < 3; i++)
        {
            if (game_world.inventory[inv[i]] < build_cost[4][i])
            {
                can_afford = false;
            }
        }

        if (can_afford == true)
        {
            game_world.inventory["iron"] -= build_cost[4][0];
            game_world.inventory["copper"] -= build_cost[4][1];
            game_world.inventory["spores"] -= build_cost[4][2];
            annihilator new_annihilator;
            new_annihilator.position.x = pos.x - 16 * zoom.x;
            new_annihilator.position.y = pos.y - 16 * zoom.x;
            new_annihilator.sprite.setTexture(resources->annihilator_texture);
            game_world.areas[area_index].annihilators.push_back(new_annihilator);
        }
    }
}

void build_controller::destroy(world &game_world, sf::Vector2i mouse_pos, assets* resources)
{
    int area_index = game_world.get_area_index(game_world.player_coordinates);

    for (unsigned int i = 0; i < game_world.areas[area_index].cmd_centers.size(); i++)
    {
        sf::Vector2f cmd_pos = game_world.areas[area_index].cmd_centers[i].position;
        sf::Vector2f mouse_f = sf::Vector2f(mouse_pos.x - 32, mouse_pos.y - 32);
        float distance = get_distance(cmd_pos, mouse_f);
        bool destroying = game_world.areas[area_index].cmd_centers[i].destroying;
        if (distance <= 32 * zoom.x && destroying == false)
        {
            game_world.areas[area_index].cmd_centers[i].destroying = true;
            game_world.inventory["iron"] += build_cost[6][0] / 2;
            game_world.inventory["copper"] += build_cost[6][1] / 2;
            play_explosion_sound(resources);
            break;
        }
    }

    for (unsigned int i = 0; i < game_world.areas[area_index].logi_centers.size(); i++)
    {
        sf::Vector2f logi_pos = game_world.areas[area_index].logi_centers[i].position;
        sf::Vector2f mouse_f = sf::Vector2f(mouse_pos.x - 16, mouse_pos.y - 16);
        float distance = get_distance(logi_pos, mouse_f);
        bool destroying = game_world.areas[area_index].logi_centers[i].destroying;
        if (distance <= 16 * zoom.x && destroying == false)
        {
            game_world.areas[area_index].logi_centers[i].destroying = true;
            game_world.inventory["iron"] += build_cost[5][0] / 2;
            game_world.inventory["copper"] += build_cost[5][1] / 2;
            play_explosion_sound(resources);
            break;
        }
    }

    for (unsigned int i = 0; i < game_world.areas[area_index].harvesters.size(); i++)
    {
        sf::Vector2f harvester_pos = game_world.areas[area_index].harvesters[i].position;
        sf::Vector2f mouse_f = sf::Vector2f(mouse_pos.x - 8, mouse_pos.y - 8);
        float distance = get_distance(harvester_pos, mouse_f);
        bool destroying = game_world.areas[area_index].harvesters[i].destroying;
        if (distance <= 8 * zoom.x && destroying == false)
        {
            game_world.areas[area_index].harvesters[i].destroying = true;
            game_world.inventory["iron"] += build_cost[2][0] / 2;
            game_world.inventory["copper"] += build_cost[2][1] / 2;
            game_world.inventory["spores"] += build_cost[2][2] / 2;
            play_explosion_sound(resources);
            break;
        }
    }

    for (unsigned int i = 0; i < game_world.areas[area_index].cannons.size(); i++)
    {
        sf::Vector2f cannon_pos = game_world.areas[area_index].cannons[i].position;
        sf::Vector2f mouse_f = sf::Vector2f(mouse_pos.x - 16, mouse_pos.y - 16);
        float distance = get_distance(cannon_pos, mouse_f);
        bool destroying = game_world.areas[area_index].cannons[i].destroying;
        if (distance <= 16 * zoom.x && destroying == false)
        {
            game_world.areas[area_index].cannons[i].destroying = true;
            game_world.inventory["iron"] += build_cost[3][0] / 2;
            game_world.inventory["copper"] += build_cost[3][1] / 2;
            game_world.inventory["spores"] += build_cost[3][2] / 2;
            play_explosion_sound(resources);
            break;
        }
    }

    for (unsigned int i = 0; i < game_world.areas[area_index].annihilators.size(); i++)
    {
        sf::Vector2f annihilator_pos = game_world.areas[area_index].annihilators[i].position;
        sf::Vector2f mouse_f = sf::Vector2f(mouse_pos.x - 16, mouse_pos.y - 16);
        float distance = get_distance(annihilator_pos, mouse_f);
        bool destroying = game_world.areas[area_index].annihilators[i].destroying;
        if (distance <= 16 * zoom.x && destroying == false)
        {
            game_world.areas[area_index].annihilators[i].destroying = true;
            game_world.inventory["iron"] += build_cost[4][0] / 2;
            game_world.inventory["copper"] += build_cost[4][1] / 2;
            game_world.inventory["spores"] += build_cost[4][2] / 2;
            play_explosion_sound(resources);
            break;
        }
    }

    for (unsigned int i = 0; i < game_world.areas[area_index].drills.size(); i++)
    {
        sf::Vector2f drill_pos = game_world.areas[area_index].drills[i].position;
        sf::Vector2f mouse_f = sf::Vector2f(mouse_pos.x - 8, mouse_pos.y - 8);
        float distance = get_distance(drill_pos, mouse_f);
        bool destroying = game_world.areas[area_index].drills[i].destroying;
        if (distance <= 8 * zoom.x && destroying == false)
        {
            game_world.areas[area_index].drills[i].destroying = true;
            game_world.inventory["iron"] += build_cost[1][0] / 2;
            game_world.inventory["copper"] += build_cost[1][1] / 2;
            play_explosion_sound(resources);
            break;
        }
    }

    for (unsigned int i = 0; i < game_world.areas[area_index].generators.size(); i++)
    {
        sf::Vector2f gen_pos = game_world.areas[area_index].generators[i].position;
        sf::Vector2f mouse_f = sf::Vector2f(mouse_pos.x - 8, mouse_pos.y - 8);
        float distance = get_distance(gen_pos, mouse_f);
        bool destroying = game_world.areas[area_index].generators[i].destroying;
        if (distance <= 8 * zoom.x && destroying == false)
        {
            game_world.areas[area_index].generators[i].destroying = true;
            game_world.inventory["iron"] += build_cost[0][0] / 2;
            game_world.inventory["copper"] += build_cost[0][1] / 2;
            play_explosion_sound(resources);
            break;
        }
    }
}

bool build_controller::build_blocked(world &game_world, int area_index, sf::Vector2i pos)
{
    sf::Vector2f pos_f = sf::Vector2f(pos.x, pos.y);

    for (unsigned int i = 0; i < game_world.areas[area_index].generators.size(); i++)
    {
        if (get_distance(pos_f, game_world.areas[area_index].generators[i].position) < 32 * zoom.x)
        {
            return true;
        }
    }

    for (unsigned int i = 0; i < game_world.areas[area_index].drills.size(); i++)
    {
        if (get_distance(pos_f, game_world.areas[area_index].drills[i].position) < 32 * zoom.x)
        {
            return true;
        }
    }

    for (unsigned int i = 0; i < game_world.areas[area_index].harvesters.size(); i++)
    {
        if (get_distance(pos_f, game_world.areas[area_index].harvesters[i].position) < 32 * zoom.x)
        {
            return true;
        }
    }

    for (unsigned int i = 0; i < game_world.areas[area_index].cannons.size(); i++)
    {
        if (get_distance(pos_f, game_world.areas[area_index].cannons[i].position) < 64 * zoom.x)
        {
            return true;
        }
    }

    for (unsigned int i = 0; i < game_world.areas[area_index].annihilators.size(); i++)
    {
        if (get_distance(pos_f, game_world.areas[area_index].annihilators[i].position) < 64 * zoom.x)
        {
            return true;
        }
    }

    if (build_type == "drill")
    {
        bool on_node = false;
        for (unsigned int i = 0; i < game_world.areas[area_index].resource_nodes.size(); i++)
        {
            float node_x = game_world.areas[area_index].resource_nodes[i].position.x + 8;
            float node_y = game_world.areas[area_index].resource_nodes[i].position.y + 8;
            sf::Vector2f node_pos = sf::Vector2f(node_x, node_y);
            if (get_distance(pos_f, node_pos) < 10 * zoom.x)
            {
                on_node = true;
            }
        }
        if (on_node == false)
        {
            return true;
        }
    }

    return false;
}

void build_controller::play_explosion_sound(assets* resources)
{
    for (int i = 0; i < 10; i++)
    {
        if (resources->explosion_sounds[i].getStatus() != sf::Sound::Playing)
        {
            resources->explosion_sounds[i].setVolume(100 * audio_volume);
            resources->explosion_sounds[i].play();
            break;
        }
    }
}
