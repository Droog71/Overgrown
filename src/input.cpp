#include <input.h>
#include <iostream>

void input::init(assets* resources)
{
    this->resources = resources;
}

void input::handle_events(struct input_event_params &params)
{
    if(params.event.type == sf::Event::KeyPressed)
    {
        if (params.event.key.code == sf::Keyboard::Up)
        {
            if (params.game_world.player_coordinates.y < sqrt(params.game_world.areas.size()) - 1)
            {
                params.game_world.player_coordinates.y++;
            }
        }

        if (params.event.key.code == sf::Keyboard::Down)
        {
            if (params.game_world.player_coordinates.y > 0)
            {
                params.game_world.player_coordinates.y--;
            }
        }

        if (params.event.key.code == sf::Keyboard::Right)
        {
            if (params.game_world.player_coordinates.x < sqrt(params.game_world.areas.size()) - 1)
            {
                params.game_world.player_coordinates.x++;
            }
        }

        if (params.event.key.code == sf::Keyboard::Left)
        {
            if (params.game_world.player_coordinates.x > 0)
            {
                params.game_world.player_coordinates.x--;
            }
        }

        if (params.event.key.code == sf::Keyboard::Escape)
        {
            params.p_menu.visible = !params.p_menu.visible;
        }
    }

    if (params.event.type == sf::Event::MouseButtonPressed)
    {
        if(params.event.mouseButton.button == sf::Mouse::Left)
        {
            if (params.builder.building == false && params.builder.destroying == false)
            {
                sf::Vector2f mouse_f = sf::Vector2f(params.mouse_position.x, params.mouse_position.y);
                int area_index = params.game_world.get_area_index(params.game_world.player_coordinates);
                for (int i = 0; i < 5; i++)
                {
                    std::string node_type = params.game_world.areas[area_index].resource_nodes[i].type;
                    sf::Vector2f node_pos = params.game_world.areas[area_index].resource_nodes[i].position;
                    node_pos.x = node_pos.x + 8;
                    node_pos.y = node_pos.y + 8;
                    if (get_distance(mouse_f, node_pos) < 8)
                    {
                        resources->dig_sound.setVolume(100 * audio_volume);
                        resources->dig_sound.play();
                        params.game_world.inventory[node_type]++;
                    }
                }
            }
        }
    }
}
