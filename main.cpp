#ifdef __cplusplus
    #include <cstdlib>
#else
    #include <stdlib.h>
#endif

#include <gui.h>
#include <math.h>
#include <world.h>
#include <chrono>
#include <input.h>
#include <sstream>
#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <assets.h>
#include <growth.h>
#include <settings.h>
#include <tutorial.h>
#include <main_menu.h>
#include <pause_menu.h>
#include <key_bindings.h>
#include <logistics_network.h>
#include <build_controller.h>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

gui game_gui;
world game_world;
input game_input;
main_menu m_menu;
pause_menu p_menu;
assets resources;
key_bindings kb;
build_controller builder;
bool main_menu = true;
bool game_started = false;
bool show_fps = true;
bool show_keys;
bool tutorial_game = false;
float fps;
float frame_time;
float frame_timer;
float victory_timer;
sf::Vector2f zoom;
std::string cwd;
std::chrono::high_resolution_clock::time_point fps_start;
std::chrono::high_resolution_clock::time_point fps_finish;

// Spawns the initial enemy force.
void init_growth(sf::RenderWindow &window)
{
    int area_index = game_world.get_area_index(sf::Vector2i(31,31));
    int x = rand() % (int)window.getView().getSize().x - 250;
    int y = rand() % (int)window.getView().getSize().y - 70;
    game_world.areas[area_index].area_growth.position.x = x;
    game_world.areas[area_index].area_growth.position.y = y;
    if (game_world.areas[area_index].area_growth.position.x < 70)
    {
        game_world.areas[area_index].area_growth.position.x = 70;
    }
    if (game_world.areas[area_index].area_growth.position.y < 70)
    {
        game_world.areas[area_index].area_growth.position.y = 70;
    }
    game_world.areas[area_index].area_growth.alive = true;
}

void new_game(sf::RenderWindow &window)
{
    game_world.player_coordinates.x = 0;
    game_world.player_coordinates.y = 0;

    game_world.inventory["coal"] = 1000;
    game_world.inventory["iron"] = 5000;
    game_world.inventory["copper"] = 5000;

    int spores = tutorial_game == true ? 1000 : 0;
    game_world.inventory["spores"] = spores;

    std::vector<world::area> new_areas;
    game_world.areas = new_areas;
    game_world.areas.resize(1024);

    int area_index = 0;
    for (unsigned int y = 0; y < sqrt(game_world.areas.size()); y++)
    {
        for (int x = 0; x < sqrt(game_world.areas.size()); x ++)
        {
            game_world.areas[area_index].coordinates.x = x;
            game_world.areas[area_index].coordinates.y = y;
            area_index++;
        }
    }

    for (unsigned int i = 0; i < game_world.areas.size(); i++)
    {
        game_world.areas[i].area_growth.sprite.setTexture(resources.growth_texture);
        game_world.generate_resource_nodes(resources, window, i);
        game_world.areas[i].power = 0;
    }

    if (m_menu.new_game == true)
    {
        init_growth(window);
        m_menu.new_game = false;
    }
}

void quit_game()
{
    game_started = false;
    tutorial_game = false;
    p_menu.visible = false;
    p_menu.quit_game = false;
    m_menu.start_game = false;
    main_menu = true;
}

int main(int argc, char * argv[])
{
    srand(time(NULL));

    char cwd_char[PATH_MAX];
    if (getcwd(cwd_char, sizeof(cwd_char)) != NULL)
    {
       cwd = cwd_char;
    }

    sf::RenderWindow window;

    bool windowed = false;

    if (argc > 3)
    {
        if (strcmp(argv[1], "-window") == 0)
        {
            windowed = true;
            unsigned int x = std::stoi(argv[2]) < 1280 ? 1280 : std::stoi(argv[2]);
            unsigned int y = std::stoi(argv[3]) < 720 ? 720 : std::stoi(argv[3]);
            window.create(sf::VideoMode(x, y), "Overgrown", sf::Style::Close);
        }
    }

    if (windowed == false)
    {
        unsigned int width = sf::VideoMode::getDesktopMode().width;
        unsigned int height = sf::VideoMode::getDesktopMode().height;
        window.create(sf::VideoMode(width, height), "Overgrown", sf::Style::Fullscreen);
    }

    window.setFramerateLimit(60);
    zoom = sf::Vector2f(1, 1);
    resources.init(cwd);
    tutorial tut(cwd);
    load_settings(cwd);
    builder.init(&resources);
    game_gui.init(cwd, &resources);
    m_menu.init(cwd, &resources);
    p_menu.init(cwd, &resources);
    game_input.init(&resources);
    kb.load(cwd);
    new_game(window);

    while (window.isOpen())
    {
        fps_start = std::chrono::high_resolution_clock::now();
        sf::Vector2i mouse_pos = sf::Mouse().getPosition(window);

        if (main_menu == true)
        {
            window.setMouseCursorVisible(true);
            main_menu = m_menu.draw_menu(window, game_world, frame_time);
        }
        else
        {
            if (m_menu.new_game == true)
            {
                tutorial_game = m_menu.tutorial;
                m_menu.tutorial = false;
                new_game(window);
            }

            sf::Event event;
            while (window.pollEvent(event))
            {
                if (p_menu.visible == true)
                {
                    builder.building = false;
                    builder.destroying = false;
                    p_menu.handle_events(window, event, game_world, mouse_pos);
                }
                else
                {
                    struct input_event_params input_e_params = { event, p_menu, builder, game_world, mouse_pos };
                    game_input.handle_events(input_e_params);

                    struct gui_event_params gui_e_params = { window, p_menu, game_world, builder, event, mouse_pos };
                    game_gui.handle_events(gui_e_params);
                }

                if (event.type == sf::Event::Resized)
                {
                    sf::FloatRect visible_area(0, 0, event.size.width, event.size.height);
                    window.setView(sf::View(visible_area));
                }

                if (event.type == sf::Event::KeyPressed)
                {
                    if (event.key.code == kb.bindings["zoom"])
                    {
                        zoom = zoom == sf::Vector2f(1, 1) ? sf::Vector2f(2, 2) : sf::Vector2f(1, 1);
                        builder.zoom = zoom;
                    }

                    if (event.key.code == kb.bindings["show_tutorial"])
                    {
                        tut.visible = !tut.visible;
                    }

                    if (event.key.code == kb.bindings["show_keys"])
                    {
                        show_keys = !show_keys;
                    }

                    if (event.key.code == kb.bindings["show_fps"])
                    {
                        show_fps = !show_fps;
                    }
                }

                if (event.type == sf::Event::Closed)
                {
                    window.close();
                }
            }

            window.clear();

            resources.game_background_sprite.setPosition(0,0);
            sf::IntRect bgr = sf::IntRect(0, 0, window.getView().getSize().x, window.getView().getSize().y);
            resources.game_background_sprite.setTextureRect(bgr);
            window.draw(resources.game_background_sprite);

            resources.terrain_sprite.setScale(zoom);
            resources.terrain_sprite.setPosition(50, 50);
            float offset = zoom == sf::Vector2f(2, 2) ? 0.5 : 1;
            sf::IntRect tr = sf::IntRect(0, 0, (window.getView().getSize().x  -300) * offset, (window.getView().getSize().y - 100) * offset);
            resources.terrain_sprite.setTextureRect(tr);
            resources.terrain_sprite.setTexture(resources.terrain_texture);
            window.draw(resources.terrain_sprite);

            int area_power = 0;
            int living_growths = 0;

            for (unsigned int i = 0; i < game_world.areas.size(); i++)
            {
                bool in_range = false;
                int area_x = game_world.areas[i].coordinates.x;
                int area_y = game_world.areas[i].coordinates.y;
                if (area_x == game_world.player_coordinates.x && area_y == game_world.player_coordinates.y)
                {
                    for (int j = 0; j < 5; j++)
                    {
                        int node_x = game_world.areas[i].resource_nodes[j].position.x;
                        int node_y = game_world.areas[i].resource_nodes[j].position.y;
                        sf::Sprite node_sprite = game_world.areas[i].resource_nodes[j].sprite;
                        node_sprite.setScale(zoom);
                        node_sprite.setPosition(node_x, node_y);
                        window.draw(node_sprite);
                    }

                    for (unsigned int k = 0; k < game_world.areas[i].area_growth.spores.size(); k++)
                    {
                        if (game_world.areas[i].area_growth.spores[k].alive == true)
                        {
                            int spore_x = game_world.areas[i].area_growth.spores[k].position.x;
                            int spore_y = game_world.areas[i].area_growth.spores[k].position.y;
                            sf::Sprite spore_sprite = game_world.areas[i].area_growth.spores[k].sprite;
                            spore_sprite.setScale(zoom);
                            spore_sprite.setPosition(spore_x, spore_y);

                            float x_val = game_world.areas[i].coordinates.x;
                            float y_val = game_world.areas[i].coordinates.y;

                            if (x_val >= 24 && y_val >= 24)
                            {
                                game_world.areas[i].area_growth.strength = 0.25f;
                                spore_sprite.setTexture(resources.t3_spore_texture);
                            }
                            else if (x_val >= 16 && y_val >= 16)
                            {
                                game_world.areas[i].area_growth.strength = 0.5f;
                                spore_sprite.setTexture(resources.t2_spore_texture);
                            }
                            else
                            {
                                game_world.areas[i].area_growth.strength = 1.0f;
                                spore_sprite.setTexture(resources.spore_texture);
                            }

                            window.draw(spore_sprite);
                        }
                    }

                    if (game_world.areas[i].area_growth.alive == true)
                    {
                        int growth_x = game_world.areas[i].area_growth.position.x;
                        int growth_y = game_world.areas[i].area_growth.position.y;
                        sf::Sprite growth_sprite = game_world.areas[i].area_growth.sprite;
                        growth_sprite.setScale(zoom);
                        growth_sprite.setPosition(growth_x, growth_y);
                        window.draw(growth_sprite);
                    }

                    for (unsigned int l = 0; l < game_world.areas[i].cmd_centers.size(); l++)
                    {
                        int gen_x = game_world.areas[i].cmd_centers[l].position.x;
                        int gen_y = game_world.areas[i].cmd_centers[l].position.y;
                        sf::Sprite cmd_center_sprite = game_world.areas[i].cmd_centers[l].sprite;
                        cmd_center_sprite.setScale(zoom);
                        cmd_center_sprite.setPosition(gen_x, gen_y);
                        window.draw(cmd_center_sprite);
                    }

                    for (unsigned int l = 0; l < game_world.areas[i].logi_centers.size(); l++)
                    {
                        int gen_x = game_world.areas[i].logi_centers[l].position.x;
                        int gen_y = game_world.areas[i].logi_centers[l].position.y;
                        sf::Sprite logi_center_sprite = game_world.areas[i].logi_centers[l].sprite;
                        logi_center_sprite.setScale(zoom);
                        logi_center_sprite.setPosition(gen_x, gen_y);
                        window.draw(logi_center_sprite);
                    }

                    for (unsigned int l = 0; l < game_world.areas[i].generators.size(); l++)
                    {
                        int gen_x = game_world.areas[i].generators[l].position.x;
                        int gen_y = game_world.areas[i].generators[l].position.y;
                        sf::Sprite gen_sprite = game_world.areas[i].generators[l].sprite;
                        gen_sprite.setScale(zoom);
                        gen_sprite.setPosition(gen_x, gen_y);
                        window.draw(gen_sprite);
                    }

                    for (unsigned int l = 0; l < game_world.areas[i].drills.size(); l++)
                    {
                        int drill_x = game_world.areas[i].drills[l].position.x;
                        int drill_y = game_world.areas[i].drills[l].position.y;
                        sf::Sprite drill_sprite = game_world.areas[i].drills[l].sprite;
                        drill_sprite.setScale(zoom);
                        drill_sprite.setPosition(drill_x, drill_y);
                        window.draw(drill_sprite);
                    }

                    for (unsigned int l = 0; l < game_world.areas[i].harvesters.size(); l++)
                    {
                        int harvester_x = game_world.areas[i].harvesters[l].position.x;
                        int harvester_y = game_world.areas[i].harvesters[l].position.y;
                        sf::Sprite harvester_sprite = game_world.areas[i].harvesters[l].sprite;
                        harvester_sprite.setScale(zoom);
                        harvester_sprite.setPosition(harvester_x, harvester_y);
                        window.draw(harvester_sprite);

                        if (game_world.areas[i].harvesters[l].fired == true)
                        {
                            sf::VertexArray ray(sf::LinesStrip, 2);
                            float ray_x = game_world.areas[i].harvesters[l].position.x + 8;
                            float ray_y = game_world.areas[i].harvesters[l].position.y + 8;
                            ray[0].position.x = ray_x;
                            ray[0].position.y = ray_y;
                            ray[1].position = game_world.areas[i].harvesters[l].target;
                            ray[0].color = sf::Color::Green;
                            ray[1].color = sf::Color::Green;
                            if (ray[1].position != sf::Vector2f(0, 0))
                            {
                                window.draw(ray);
                            }
                        }
                    }

                    for (unsigned int l = 0; l < game_world.areas[i].cannons.size(); l++)
                    {
                        int cannon_x = game_world.areas[i].cannons[l].position.x;
                        int cannon_y = game_world.areas[i].cannons[l].position.y;
                        sf::Sprite cannon_sprite = game_world.areas[i].cannons[l].sprite;
                        cannon_sprite.setScale(zoom);
                        cannon_sprite.setPosition(cannon_x, cannon_y);
                        window.draw(cannon_sprite);

                        if (game_world.areas[i].cannons[l].fired == true)
                        {
                            if (game_world.areas[i].cannons[l].target != sf::Vector2f(0, 0))
                            {
                                sf::VertexArray ray = sf::VertexArray(sf::Triangles, 3);
                                float ray_x_0 = game_world.areas[i].cannons[l].position.x + 18;
                                float ray_y_0 = game_world.areas[i].cannons[l].position.y + 18;
                                float ray_x_1 = game_world.areas[i].cannons[l].position.x + 16;
                                float ray_y_1 = game_world.areas[i].cannons[l].position.y + 16;
                                float ray_x_2 = game_world.areas[i].cannons[l].target.x + 8;
                                float ray_y_2 = game_world.areas[i].cannons[l].target.y + 8;
                                ray[0].position = sf::Vector2f(ray_x_0, ray_y_0);
                                ray[1].position = sf::Vector2f(ray_x_1, ray_y_1);
                                ray[2].position = sf::Vector2f(ray_x_2, ray_y_2);
                                ray[0].color = sf::Color::Red;
                                ray[1].color = sf::Color::Red;
                                ray[2].color = sf::Color::Red;
                                window.draw(ray);
                            }
                        }
                    }

                    for (unsigned int l = 0; l < game_world.areas[i].annihilators.size(); l++)
                    {
                        int annihilator_x = game_world.areas[i].annihilators[l].position.x;
                        int annihilator_y = game_world.areas[i].annihilators[l].position.y;
                        sf::Sprite annihilator_sprite = game_world.areas[i].annihilators[l].sprite;
                        annihilator_sprite.setScale(zoom);
                        annihilator_sprite.setPosition(annihilator_x, annihilator_y);
                        window.draw(annihilator_sprite);

                        sf::VertexArray meter(sf::LinesStrip, 2);
                        float power_buffer = game_world.areas[i].annihilators[l].power_buffer;
                        float meter_x = game_world.areas[i].annihilators[l].position.x;
                        float meter_y = game_world.areas[i].annihilators[l].position.y + 30;
                        meter[0].position.x = meter_x;
                        meter[0].position.y = meter_y;
                        meter[1].position.x = meter_x + (power_buffer * 0.02f);
                        meter[1].position.y = meter_y;
                        meter[0].color = sf::Color::Yellow;
                        meter[1].color = sf::Color::Yellow;

                        if (meter[1].position != sf::Vector2f(0, 0))
                        {
                            window.draw(meter);
                        }

                        if (game_world.areas[i].annihilators[l].fired == true)
                        {
                            if (game_world.areas[i].annihilators[l].target != sf::Vector2f(0, 0))
                            {
                                sf::VertexArray ray = sf::VertexArray(sf::Triangles, 3);
                                float ray_x_0 = game_world.areas[i].annihilators[l].position.x + 24;
                                float ray_y_0 = game_world.areas[i].annihilators[l].position.y + 24;
                                float ray_x_1 = game_world.areas[i].annihilators[l].position.x + 10;
                                float ray_y_1 = game_world.areas[i].annihilators[l].position.y + 10;
                                float ray_x_2 = game_world.areas[i].annihilators[l].target.x + 16;
                                float ray_y_2 = game_world.areas[i].annihilators[l].target.y + 16;
                                ray[0].position = sf::Vector2f(ray_x_0, ray_y_0);
                                ray[1].position = sf::Vector2f(ray_x_1, ray_y_1);
                                ray[2].position = sf::Vector2f(ray_x_2, ray_y_2);
                                ray[0].color = sf::Color::Red;
                                ray[1].color = sf::Color::Red;
                                ray[2].color = sf::Color::Red;
                                window.draw(ray);
                            }
                        }
                    }

                    area_power = game_world.areas[i].power;
                    in_range = true;
                }

                if (p_menu.visible == false)
                {
                    if (game_world.areas[i].area_growth.alive == true)
                    {
                        if (game_world.areas[i].area_growth.destroying == false)
                        {
                            float x_val = game_world.areas[i].coordinates.x;
                            float y_val = game_world.areas[i].coordinates.y;

                            if (x_val >= 24 && y_val >= 24)
                            {
                                game_world.areas[i].area_growth.strength = 0.25f;
                                game_world.areas[i].area_growth.sprite.setTexture(resources.t3_growth_texture);
                            }
                            else if (x_val >= 16 && y_val >= 16)
                            {
                                game_world.areas[i].area_growth.strength = 0.5f;
                                game_world.areas[i].area_growth.sprite.setTexture(resources.t2_growth_texture);
                            }
                            else
                            {
                                game_world.areas[i].area_growth.strength = 1.0f;
                                game_world.areas[i].area_growth.sprite.setTexture(resources.growth_texture);
                            }

                            sf::Vector2f target = sf::Vector2f(0.0f, 0.0f);
                            bool targeted = false;
                            unsigned int gen_size = game_world.areas[i].generators.size();
                            if (gen_size > 0)
                            {
                                int rand_gen = rand() % gen_size;
                                target = game_world.areas[i].generators[rand_gen].position;
                                targeted = true;
                            }

                            float mod =  0.2f * difficulty;
                            float rate = 1.0f - gen_size * 0.2f + mod;
                            rate = rate < 0.1f ? 0.1f : rate;
                            game_world.areas[i].area_growth.growth_rate = rate;
                            game_world.areas[i].area_growth.grow(targeted, target, window, resources, frame_time);
                            living_growths++;
                        }
                        else
                        {
                            game_world.areas[i].area_growth.sprite.setTexture(resources.medium_explosion_texture);
                            game_world.areas[i].area_growth.destroy_timer += 10 * frame_time;
                            if (game_world.areas[i].area_growth.destroy_timer >= 10)
                            {
                                game_world.areas[i].area_growth.alive = false;
                            }
                        }
                    }
                    else
                    {
                        game_world.areas[i].area_growth.spawn_timer += 10 * frame_time;
                        float delay = game_world.areas[i].annihilators.size() > 0 ? 500 : 100;
                        if (game_world.areas[i].area_growth.spawn_timer >= delay)
                        {
                            if (game_world.spawn_growth(window, i, frame_time))
                            {
                                for (unsigned int g = 0; g < game_world.areas.size(); g++)
                                {
                                    game_world.areas[g].area_growth.spawn_timer = 0;
                                }
                            }
                        }
                    }

                    bool logi_connected = logistics_connected(i, game_world);

                    for (unsigned int l = 0; l < game_world.areas[i].generators.size(); l++)
                    {
                        if (game_world.areas[i].generators[l].destroying == false)
                        {
                            game_world.areas[i].generators[l].check_spores(game_world.areas[i].area_growth, resources, in_range);
                            game_world.areas[i].generators[l].logi_connected = logi_connected;
                            game_world.areas[i].generators[l].generate_power(resources, game_world.inventory, game_world.areas[i].power, frame_time);
                        }
                        else
                        {
                            game_world.areas[i].generators[l].sprite.setTexture(resources.explosion_texture);
                            game_world.areas[i].generators[l].destroy_timer += 10 * frame_time;
                            if (game_world.areas[i].generators[l].destroy_timer >= 10)
                            {
                                game_world.areas[i].generators.erase(game_world.areas[i].generators.begin() + l);
                            }
                        }
                    }

                    for (unsigned int l = 0; l < game_world.areas[i].cmd_centers.size(); l++)
                    {
                        if (game_world.areas[i].cmd_centers[l].destroying == false)
                        {
                            game_world.areas[i].cmd_centers[l].check_spores(game_world.areas[i].area_growth, resources, in_range);
                        }
                        else
                        {
                            game_world.areas[i].cmd_centers[l].sprite.setTexture(resources.large_explosion_texture);
                            game_world.areas[i].cmd_centers[l].destroy_timer += 10 * frame_time;
                            if (game_world.areas[i].cmd_centers[l].destroy_timer >= 10)
                            {
                                game_world.areas[i].cmd_centers.erase(game_world.areas[i].cmd_centers.begin() + l);
                            }
                        }
                    }

                    for (unsigned int l = 0; l < game_world.areas[i].logi_centers.size(); l++)
                    {
                        if (game_world.areas[i].logi_centers[l].destroying == false)
                        {
                            game_world.areas[i].logi_centers[l].check_spores(game_world.areas[i].area_growth, resources, in_range);
                        }
                        else
                        {
                            game_world.areas[i].logi_centers[l].sprite.setTexture(resources.medium_explosion_texture);
                            game_world.areas[i].logi_centers[l].destroy_timer += 10 * frame_time;
                            if (game_world.areas[i].logi_centers[l].destroy_timer >= 10)
                            {
                                game_world.areas[i].logi_centers.erase(game_world.areas[i].logi_centers.begin() + l);
                            }
                        }
                    }

                    for (unsigned int l = 0; l < game_world.areas[i].harvesters.size(); l++)
                    {
                        if (game_world.areas[i].harvesters[l].destroying == false)
                        {
                            game_world.areas[i].harvesters[l].check_spores(game_world.areas[i].area_growth, resources, in_range);
                            game_world.areas[i].harvesters[l].harvest(resources, game_world.areas[i].area_growth, game_world.inventory, game_world.areas[i].power, frame_time, in_range);
                        }
                        else
                        {
                            game_world.areas[i].harvesters[l].sprite.setTexture(resources.explosion_texture);
                            game_world.areas[i].harvesters[l].destroy_timer += 10 * frame_time;
                            if (game_world.areas[i].harvesters[l].destroy_timer >= 10)
                            {
                                game_world.areas[i].harvesters.erase(game_world.areas[i].harvesters.begin() + l);
                            }
                        }

                    }

                    for (unsigned int l = 0; l < game_world.areas[i].cannons.size(); l++)
                    {
                        if (game_world.areas[i].cannons[l].destroying == false)
                        {
                            game_world.areas[i].cannons[l].check_spores(game_world.areas[i].area_growth, resources, in_range);
                            game_world.areas[i].cannons[l].fire(resources, game_world.areas[i].area_growth, game_world.inventory, game_world.areas[i].power, frame_time, in_range);
                        }
                        else
                        {
                            game_world.areas[i].cannons[l].sprite.setTexture(resources.medium_explosion_texture);
                            game_world.areas[i].cannons[l].destroy_timer += 10 * frame_time;
                            if (game_world.areas[i].cannons[l].destroy_timer >= 10)
                            {
                                game_world.areas[i].cannons.erase(game_world.areas[i].cannons.begin() + l);
                            }
                        }

                    }

                    for (unsigned int l = 0; l < game_world.areas[i].annihilators.size(); l++)
                    {
                        if (game_world.areas[i].annihilators[l].destroying == false)
                        {
                            game_world.areas[i].annihilators[l].check_spores(game_world.areas[i].area_growth, resources, in_range);
                            game_world.areas[i].annihilators[l].fire(resources, game_world.areas[i].area_growth, game_world.inventory, game_world.areas[i].power, frame_time, in_range);
                        }
                        else
                        {
                            game_world.areas[i].annihilators[l].sprite.setTexture(resources.medium_explosion_texture);
                            game_world.areas[i].annihilators[l].destroy_timer += 10 * frame_time;
                            if (game_world.areas[i].annihilators[l].destroy_timer >= 10)
                            {
                                game_world.areas[i].annihilators.erase(game_world.areas[i].annihilators.begin() + l);
                            }
                        }

                    }

                    for (unsigned int l = 0; l < game_world.areas[i].drills.size(); l++)
                    {
                        if (game_world.areas[i].drills[l].destroying == false)
                        {
                            game_world.areas[i].drills[l].check_spores(game_world.areas[i].area_growth, resources, in_range);
                            game_world.areas[i].drills[l].mine(resources, game_world.areas[i].resource_nodes, game_world.inventory, game_world.areas[i].power, frame_time, in_range);
                        }
                        else
                        {
                            game_world.areas[i].drills[l].sprite.setTexture(resources.explosion_texture);
                            game_world.areas[i].drills[l].destroy_timer += 10 * frame_time;
                            if (game_world.areas[i].drills[l].destroy_timer >= 10)
                            {
                                game_world.areas[i].drills.erase(game_world.areas[i].drills.begin() + l);
                            }
                        }
                    }
                }
            }

            bool victory = false;
            if (p_menu.visible == false)
            {
                if (tutorial_game == true)
                {
                    victory = tut.completed;
                }
                else
                {
                    victory = living_growths < 1;
                }
            }

            if (victory == true)
            {
                if (resources.victory_sound.getStatus() != sf::Sound::Playing)
                {
                    resources.victory_sound.setVolume(100 * audio_volume);
                    resources.victory_sound.play();
                }

                tut.visible = false;
                resources.notice.setFont(resources.orbitron);
                resources.notice.setString("VICTORY!");
                sf::Vector2f text_pos;
                text_pos.x = (window.getView().getSize().x / 2) - (resources.notice.getGlobalBounds().width / 2) - 100;
                text_pos.y = (window.getView().getSize().y / 2) - 150;
                resources.notice.setPosition(text_pos);
                window.draw(resources.notice);
                resources.notice.setFont(resources.exoplanetaria);

                victory_timer += 10 * frame_time;
                if (victory_timer >= 60)
                {
                    victory_timer = 0;
                    tut.completed = false;
                    quit_game();
                }
            }

            if (p_menu.visible == true)
            {
                p_menu.draw_menu(window, mouse_pos, frame_time);

                if (p_menu.quit_game == true)
                {
                    quit_game();
                }
            }

            struct gui_draw_params gui_params = { window, game_world, builder, mouse_pos, zoom, area_power, frame_time, fps, show_fps };
            game_gui.draw_gui(gui_params);


            if (show_keys == true && p_menu.visible == false && (tutorial_game == false || tut.visible == false))
            {
                sf::Vector2f bg_pos;
                float x = (window.getView().getSize().x / 2) - 100;
                bg_pos.x = x - (resources.keys.getGlobalBounds().width / 2);
                bg_pos.y = (window.getView().getSize().y / 2) - 175;
                sf::Sprite bg = sf::Sprite(resources.gui_background_texture);
                bg.setPosition(bg_pos);
                bg.setScale(0.1, 0.6);
                window.draw(bg);

                std::string bindings = get_file_contents(cwd + "/bindings.list");
                resources.keys.setString(bindings);
                resources.keys.setPosition(x - 50, (window.getView().getSize().y / 2) - 150);
                window.draw(resources.keys);
            }

            if (tutorial_game == true && tut.visible == true && p_menu.visible == false)
            {
                tut.draw_tutorial(window, game_world);
            }

            window.display();
        }

        fps_finish = std::chrono::high_resolution_clock::now();
        fps = (float)1e9/(float)std::chrono::duration_cast<std::chrono::nanoseconds>(fps_finish-fps_start).count();
        frame_time = 1 / fps;
    }

    return EXIT_SUCCESS;
}
