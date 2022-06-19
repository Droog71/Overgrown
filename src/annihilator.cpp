#include "annihilator.h"

annihilator::annihilator()
{
    fired = false;
    cycled = false;
    destroying = false;
    destroy_timer = 0;
    fire_timer = 0;
    power_buffer = 0;
}

void annihilator::fire(assets &resources, growth &area_growth, std::map<std::string, int> &inventory, int &power, float frame_time, bool in_range)
{
    if (power >= 50  && power_buffer <= 1600)
    {
        power_buffer += (50 + (50 * difficulty));
        power -= (20 - (10 * difficulty));
        if (in_range == true && resources.power_buffer_sound.getStatus() != sf::Sound::Playing)
        {
            float pitch = 1 + (((float)power_buffer / 1600) * 2);
            resources.power_buffer_sound.setVolume(20 * audio_volume);
            resources.power_buffer_sound.setPitch(pitch);
            resources.power_buffer_sound.play();
        }
    }

    float rand_mod = rand() % 5;
    int rand_negative = rand() % 100;
    rand_mod = rand_negative >= 50 ? rand_mod * -1 : rand_mod;

    fire_timer += 10 * frame_time;
    if (fire_timer >= 10 + rand_mod && fire_timer < 30 && area_growth.alive == true && cycled == false)
    {
        bool found_growth = get_distance(position, area_growth.position) <= 100;

        if (power_buffer >= 1600 && found_growth == true && area_growth.alive == true)
        {
            power_buffer = 0;
            target = area_growth.position;
            sprite.setTexture(resources.annihilator_firing_texture);
            fired = true;

            if (in_range == true)
            {
                sprite.setTexture(resources.annihilator_firing_texture);
                resources.annihilator_sound.setVolume(75 * audio_volume);
                resources.annihilator_sound.play();
            }
        }

        cycled = true;
    }
    else if (fire_timer >= 30 + rand_mod)
    {
        sprite.setTexture(resources.annihilator_texture);
        fire_timer = 0;
        cycled = false;

        if (fired == true)
        {
            if (area_growth.health < 4 * area_growth.strength)
            {
                play_explosion_sound(resources);
                area_growth.destroying = true;
            }
            else
            {
                area_growth.health--;
            }
            fired = false;
        }
    }
}

void annihilator::check_spores(growth &area_growth, assets &resources, bool in_range)
{
    for (unsigned int i = 0; i < area_growth.spores.size(); i++)
    {
        float distance = get_distance(area_growth.spores[i].position, position);

        if (distance <= 30 && area_growth.spores[i].alive == true)
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

void annihilator::play_explosion_sound(assets &resources)
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
