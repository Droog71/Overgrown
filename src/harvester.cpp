#include "harvester.h"

harvester::harvester()
{
    fired = false;
    cycled = false;
    destroying = false;
    destroy_timer = 0;
    harvest_timer = 0;
}

void harvester::harvest(assets &resources, growth &area_growth, std::map<std::string, int> &inventory, int &power, float frame_time, bool in_range)
{
    float rand_mod = rand() % 5;
    int rand_negative = rand() % 100;
    rand_mod = rand_negative >= 50 ? rand_mod * -1 : rand_mod;

    harvest_timer += 10 * frame_time;
    if (harvest_timer >= 10 + rand_mod && harvest_timer < 15 && cycled == false)
    {
        bool found_spores = false;
        int spore_count = area_growth.spores.size();

        for (int i = 0; i < spore_count; i++)
        {
            if (area_growth.spores[i].alive == true)
            {
                sf::Vector2f spore_pos = area_growth.spores[i].position;
                float distance = get_distance(position, spore_pos);
                if (distance <= 50)
                {
                    found_spores = true;
                    target = area_growth.spores[i].position;
                }
            }
        }

        float power_consumption = 3 - (difficulty * 1);

        if (power >= power_consumption && found_spores == true)
        {
            inventory["spores"]++;
            power -= power_consumption;

            for (int i = 0; i < spore_count; i++)
            {
                float resistance = difficulty * area_growth.strength;
                float distance = get_distance(target, area_growth.spores[i].position);
                if (distance <= 5 * resistance)
                {
                    area_growth.spores[i].alive = false;
                    if (std::find(area_growth.injuries.begin(), area_growth.injuries.end(), area_growth.spores[i].position) == area_growth.injuries.end())
                    {
                        area_growth.injuries.push_back(area_growth.spores[i].position);
                    }
                }
            }

            if (in_range == true)
            {
                sprite.setTexture(resources.harvester_firing_texture);
                for (int i = 0; i < 10; i++)
                {
                    if (resources.harvester_sounds[i].getStatus() != sf::Sound::Playing)
                    {
                        resources.harvester_sounds[i].setVolume(20 * audio_volume);
                        resources.harvester_sounds[i].play();
                        break;
                    }
                }
            }

            fired = true;
        }

        cycled = true;
    }
    else if (harvest_timer >= 15 + rand_mod)
    {
        sprite.setTexture(resources.harvester_texture);
        harvest_timer = 0;
        fired = false;
        cycled = false;
    }
}

void harvester::check_spores(growth &area_growth, assets &resources, bool in_range)
{
    for (unsigned int i = 0; i < area_growth.spores.size(); i++)
    {
        float distance = get_distance(area_growth.spores[i].position, position);

        if (distance <= 20 && area_growth.spores[i].alive == true)
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

void harvester::play_explosion_sound(assets &resources)
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
