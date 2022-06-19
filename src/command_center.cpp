#include "command_center.h"

command_center::command_center()
{
    destroying = false;
    destroy_timer = 0;
}

void command_center::check_spores(growth &area_growth, assets &resources, bool in_range)
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

void command_center::play_explosion_sound(assets &resources)
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

