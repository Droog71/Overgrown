#include <math.h>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <growth.h>

// Constructor
growth::growth()
{
    index = 0;
    health = 4;
    strength = 0;
    injury_index = 0;
    growth_timer = 0.0f;
    growth_rate = 1.0f;
    spawn_timer = 0.0f;
    drift_timer = 0.0f;
    destroy_timer = 0.0f;
    alive = false;
    healing = false;
    destroying = false;
}

void growth::grow(bool targeted, sf::Vector2f target, sf::RenderWindow &window, assets &resources, float frame_time)
{
	if (index < spores.size())
	{
        growth_timer += 1 * frame_time;
        if (growth_timer >= growth_rate)
        {
            if (injuries.size() == 0)
            {
                if (spores[index].alive == false)
                {
                    if (index == 0)
                    {
                        spores[index].position.x = position.x;
                        spores[index].position.y = position.y;
                    }
                    else
                    {
                        drift_timer += 1;
                        if (drift_timer >= 3 && targeted == true)
                        {
                            spores[index].position = last_pos;

                            if (spores[index].position.x > target.x)
                            {
                                spores[index].position.x = last_pos.x - 10;
                            }

                            if (spores[index].position.x < target.x)
                            {
                                spores[index].position.x = last_pos.x + 10;
                            }

                            if (spores[index].position.y > target.y)
                            {
                                spores[index].position.y = last_pos.y - 10;
                            }

                            if (spores[index].position.y < target.y)
                            {
                                spores[index].position.y = last_pos.y + 10;
                            }

                            drift_timer = 0;
                        }
                        else
                        {
                            int dir = rand() % 4;

                            if (dir == 0)
                            {
                                spores[index].position.x = last_pos.x + 10;
                                spores[index].position.y = last_pos.y;
                            }
                            else if (dir == 1)
                            {
                                spores[index].position.x = last_pos.x - 10;
                                spores[index].position.y = last_pos.y;
                            }
                            else if (dir == 2)
                            {
                                spores[index].position.x = last_pos.x;
                                spores[index].position.y = last_pos.y + 10;
                            }
                            else if (dir == 3)
                            {
                                spores[index].position.x = last_pos.x;
                                spores[index].position.y = last_pos.y - 10;
                            }
                        }
                    }

                    if (spores[index].position.x < 70)
                    {
                        spores[index].position.x = 70;
                    }

                    if (spores[index].position.x > window.getView().getSize().x - 270)
                    {
                        spores[index].position.x = window.getView().getSize().x - 270;
                    }

                    if (spores[index].position.y < 70)
                    {
                        spores[index].position.y = 70;
                    }

                    if (spores[index].position.y > window.getView().getSize().y - 70)
                    {
                        spores[index].position.y = window.getView().getSize().y - 70;
                    }

                    last_pos = spores[index].position;
                    spores[index].sprite.setTexture(resources.spore_texture);
                    spores[index].alive = true;
                }
            }
            else
            {
                heal(resources);
            }

            growth_timer = 0;
            index++;
        }
	}
	else
	{
        index = 0;
	}
}

void growth::heal(assets &resources)
{
    if (injury_index < injuries.size())
    {
        int heal_index = get_spore_index(injuries[injury_index]);
        if (heal_index != -1)
        {
            spores[heal_index].alive = true;
            injuries.erase(injuries.begin() + injury_index);
        }
        injury_index++;
    }
    else
    {
        injury_index = 0;
    }
}

unsigned int growth::get_spore_index(sf::Vector2f coords)
{
    for (unsigned int i = 0; i < spores.size(); i++)
    {
        if ((int)spores[i].position.x == (int)coords.x && (int)spores[i].position.y == (int)coords.y)
        {
            return i;
        }
    }
    return -1;
}
