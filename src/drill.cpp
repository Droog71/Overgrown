#include "drill.h"

drill::drill()
{
    cycled = false;
    destroying = false;
    found_node = false;
    drill_timer = 0;
    destroy_timer = 0;
    node_type = "";
}

void drill::mine(assets &resources, std::array<resource_node, 5> &resource_nodes, std::map<std::string, int> &inventory, int &power, float frame_time, bool in_range)
{
    float rand_mod = rand() % 5;
    int rand_negative = rand() % 100;
    rand_mod = rand_negative >= 50 ? rand_mod * -1 : rand_mod;

    drill_timer += 10 * frame_time;
    if (drill_timer >= 10 + rand_mod && drill_timer < 20 && cycled == false)
    {
        float power_consumption = 3 - (difficulty * 1);

        if (found_node == false)
        {
            for (int i = 0; i < 5; i++)
            {
                sf::Vector2f node_pos = resource_nodes[i].position;
                float distance = get_distance(position, node_pos);
                if (distance <= 20)
                {
                    found_node = true;
                    node_type = resource_nodes[i].type;
                }
            }
        }
        else if (power >= power_consumption)
        {
            inventory[node_type] += 5;
            power -= power_consumption;
            if (in_range == true)
            {
                sprite.setTexture(resources.drill_mining_texture);
                for (int i = 0; i < 10; i++)
                {
                    if (resources.drill_sounds[i].getStatus() != sf::Sound::Playing)
                    {
                        resources.drill_sounds[i].setVolume(25 * audio_volume);
                        resources.drill_sounds[i].play();
                        break;
                    }
                }
            }
        }
        cycled = true;
    }
    else if (drill_timer >= 20 + rand_mod)
    {
        sprite.setTexture(resources.drill_texture);
        drill_timer = 0;
        cycled = false;
    }
}

void drill::check_spores(growth &area_growth, assets &resources, bool in_range)
{
    for (unsigned int i = 0; i < area_growth.spores.size(); i++)
    {
        float distance = get_distance(area_growth.spores[i].position, position);
        if (distance <= 10 && area_growth.spores[i].alive == true)
        {
            destroying = true;
            if (in_range == true)
            {
                play_explosion_sound(resources);
            }
            break;
        }
    }
}

void drill::play_explosion_sound(assets &resources)
{
    for (int i = 0; i < 10; i++)
    {
        if (resources.explosion_sounds[i].getStatus() != sf::Sound::Playing)
        {
            resources.explosion_sounds[i].setVolume(100 * audio_volume);
            resources.explosion_sounds[i].play();
            break;
        }
    }
}
