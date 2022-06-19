#include <generator.h>

generator::generator()
{
    gen_timer = 0;
    destroy_timer = 0;
    destroying = false;
    logi_connected = false;
}

void generator::generate_power(assets &resources, std::map<std::string, int> &inventory, int &power, float frame_time)
{
    float rand_mod = rand() % 5;
    int rand_negative = rand() % 100;
    rand_mod = rand_negative >= 50 ? rand_mod * -1 : rand_mod;

    gen_timer += 10 * frame_time;
    if (gen_timer >= 10 + rand_mod)
    {
        if (inventory["coal"] > 0 && logi_connected == true)
        {
            if (power < 100)
            {
                power++;
            }
            inventory["coal"] -= 1;
            sprite.setTexture(resources.generator_on_texture);
        }
        else
        {
            sprite.setTexture(resources.generator_off_texture);
        }
        gen_timer = 0;
    }
}

void generator::check_spores(growth &area_growth, assets &resources, bool in_range)
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

void generator::play_explosion_sound(assets &resources)
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
