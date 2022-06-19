#include "gui.h"

gui::gui()
{
    build_menu_x = 0;

    menu_buttons.resize(3);
    menu_button_labels.resize(3);
    menu_button_labels[0].setString("    BUILD");
    menu_button_labels[1].setString("  DESTROY");
    menu_button_labels[2].setString("    MENU");

    build_buttons.resize(7);
    build_button_labels.resize(7);
    build_button_labels[0].setString("GENERATOR");
    build_button_labels[1].setString("     DRILL");
    build_button_labels[2].setString("HARVESTER");
    build_button_labels[3].setString(" CANNON");
    build_button_labels[4].setString("ANNIHILATOR");
    build_button_labels[5].setString("LOGI CENTER");
    build_button_labels[6].setString("CMD CENTER");
}

void gui::init(std::string cwd, assets* resources)
{
    this->cwd = cwd;
    this->resources = resources;
}

void gui::draw_gui(struct gui_draw_params & params)
{
    std::string x = std::to_string(params.game_world.player_coordinates.x);
    std::string y = std::to_string(params.game_world.player_coordinates.y);
    sf::String player_location_str = "Coordinates: " + x + ", " + y;
    resources->player_location.setString(player_location_str);
    resources->player_location.setPosition(10, params.window.getView().getSize().y * 0.01);
    params.window.draw(resources->player_location);

    sf::String power_string = "Sector Power: " + std::to_string(params.area_power);
    resources->area_power.setString(power_string);
    resources->area_power.setPosition(10, params.window.getView().getSize().y * 0.04);
    params.window.draw(resources->area_power);

    std::string iron = std::to_string(params.game_world.inventory["iron"]);
    std::string copper = std::to_string(params.game_world.inventory["copper"]);
    std::string coal = std::to_string(params.game_world.inventory["coal"]);
    std::string spores = std::to_string(params.game_world.inventory["spores"]);

    sf::String inventory = "IRON: " + iron +
    "          COPPER: " + copper +
    "          COAL: " + coal +
    "          SPORES: " + spores;

    resources->inventory.setString(inventory);
    resources->inventory.setPosition(200, params.window.getView().getSize().y * 0.01);
    params.window.draw(resources->inventory);

    if (params.show_fps == true)
    {
        sf::String fps_string = "FPS: " + std::to_string(params.fps);
        resources->fps_counter.setString(fps_string);
        resources->fps_counter.setPosition(10, params.window.getView().getSize().y * 0.96);
        params.window.draw(resources->fps_counter);
    }

    draw_menu_buttons(params.window, params.mouse_position);

    if (build_menu_open == true)
    {
        draw_build_buttons(params.window, params.builder, params.mouse_position, params.frame_time);
    }

    if (params.builder.building == true)
    {
        std::string build_type = params.builder.build_type;
        std::string large_buildings [3];
        large_buildings[0] = "cannon";
        large_buildings[1] = "logi_center";
        large_buildings[2] = "annihilator";
        bool large_building = false;
        for (int i = 0; i <= 3; i++)
        {
            if (build_type == large_buildings[i])
            {
                large_building = true;
            }
        }
        int offset = build_type == "cmd_center" ? 32 : large_building ? 16 : 8;
        offset = offset * params.zoom.x;
        sf::Sprite building_sprite;
        building_sprite.setTexture(resources->building_textures[params.builder.build_type]);
        building_sprite.setScale(params.zoom);
        building_sprite.setPosition(params.mouse_position.x - offset, params.mouse_position.y - offset);
        params.window.draw(building_sprite);
    }

    if (params.builder.destroying == true)
    {
        sf::Sprite destroying_sprite;
        destroying_sprite.setTexture(resources->destroy_texture);
        destroying_sprite.setScale(params.zoom);
        int offset = 8 * params.zoom.x;
        destroying_sprite.setPosition(params.mouse_position.x - offset, params.mouse_position.y - offset);
        params.window.draw(destroying_sprite);
    }
}

void gui::handle_events(struct gui_event_params &params)
{
    if (params.event.type == sf::Event::MouseButtonPressed)
    {
        bool on_button = false;

        for (unsigned int i = 0; i < menu_button_labels.size(); i++)
        {
            if (menu_buttons[i].getBounds().contains(params.mouse.x, params.mouse.y))
            {
                if (i == 0)
                {
                    if (build_menu_open == false)
                    {
                        build_menu_open = true;
                        params.builder.destroying = false;
                    }
                    else
                    {
                        closing_build_menu = true;
                    }
                }
                else if (i == 1)
                {
                    params.builder.destroying = true;
                    params.builder.building = false;
                    closing_build_menu = true;
                }
                else if (i == 2)
                {
                    params.p_menu.visible = true;
                }
                on_button = true;
            }
        }

        if (build_menu_open == true)
        {
            for (unsigned int i = 0; i < build_button_labels.size(); i++)
            {
                if (build_menu_x < params.window.getView().getSize().x - 300)
                {
                    if (build_buttons[i].getBounds().contains(params.mouse.x, params.mouse.y))
                    {
                        if (i == 0)
                        {
                            params.builder.building = true;
                            params.builder.destroying = false;
                            params.builder.build_type = "generator";
                        }
                        if (i == 1)
                        {
                            params.builder.building = true;
                            params.builder.destroying = false;
                            params.builder.build_type = "drill";
                        }

                        if (i == 2)
                        {
                            params.builder.building = true;
                            params.builder.destroying = false;
                            params.builder.build_type = "harvester";
                        }

                        if (i == 3)
                        {
                            params.builder.building = true;
                            params.builder.destroying = false;
                            params.builder.build_type = "cannon";
                        }

                        if (i == 4)
                        {
                            params.builder.building = true;
                            params.builder.destroying = false;
                            params.builder.build_type = "annihilator";
                        }

                        if (i == 5)
                        {
                            params.builder.building = true;
                            params.builder.destroying = false;
                            params.builder.build_type = "logi_center";
                        }

                        if (i == 6)
                        {
                            params.builder.building = true;
                            params.builder.destroying = false;
                            params.builder.build_type = "cmd_center";
                        }

                        closing_build_menu = true;
                        on_button = true;
                    }
                }
            }
        }

        if(params.event.mouseButton.button == sf::Mouse::Left)
        {
            if (params.builder.building == true && on_button == false)
            {
                if (params.builder.build_type == "generator")
                {
                    params.builder.build_generator(params.game_world, params.mouse);
                }

                if (params.builder.build_type == "harvester")
                {
                    params.builder.build_harvester(params.game_world, params.mouse);
                }

                if (params.builder.build_type == "drill")
                {
                    params.builder.build_drill(params.game_world,  params.mouse);
                }

                if (params.builder.build_type == "cannon")
                {
                    params.builder.build_cannon(params.game_world, params.mouse);
                }

                if (params.builder.build_type == "annihilator")
                {
                    params.builder.build_annihilator(params.game_world, params.mouse);
                }

                if (params.builder.build_type == "logi_center")
                {
                    params.builder.build_logi_center(params.game_world, params.mouse);
                }

                if (params.builder.build_type == "cmd_center")
                {
                    params.builder.build_cmd_center(params.game_world, params.mouse);
                }
            }

            if (params.builder.destroying == true)
            {
                params.builder.destroy(params.game_world, params.mouse, resources);
            }
        }
        else if(params.event.mouseButton.button == sf::Mouse::Right)
        {
            params.builder.building = false;
            params.builder.destroying = false;
            if (build_menu_open == true)
            {
                closing_build_menu = true;
            }
        }
    }
}

// Draws buttons
void gui::draw_menu_buttons(sf::RenderWindow &window, sf::Vector2i mouse_position)
{
    float x = window.getView().getSize().x - 200;

    for (unsigned int i = 0; i < 3; i++)
    {
        menu_buttons[i] = sf::VertexArray(sf::Quads, 4);
        menu_buttons[i][0].position = sf::Vector2f(x, (200 + i * 35) - 4);
        menu_buttons[i][1].position = sf::Vector2f(x, (200 + i * 35) + 24);
        menu_buttons[i][2].position = sf::Vector2f(x + 125, (200 + i * 35) + 24);
        menu_buttons[i][3].position = sf::Vector2f(x + 125, (200 + i * 35) - 4);

        sf::VertexArray menu_button_shadow = sf::VertexArray(sf::Quads, 4);
        menu_button_shadow[0].position = sf::Vector2f(x, (200 + i * 35) - 4);
        menu_button_shadow[1].position = sf::Vector2f(x, (200 + i * 35) + 27);
        menu_button_shadow[2].position = sf::Vector2f(x + 128, (200 + i * 35) + 27);
        menu_button_shadow[3].position = sf::Vector2f(x + 128, (200 + i * 35) - 4);

        menu_button_shadow[0].color = sf::Color::Black;
        menu_button_shadow[1].color = sf::Color::Black;
        menu_button_shadow[2].color = sf::Color::Black;
        menu_button_shadow[3].color = sf::Color::Black;

        if (menu_buttons[i].getBounds().contains(mouse_position.x, mouse_position.y))
        {
            menu_buttons[i][0].color = sf::Color(25, 76, 76, 255);
            menu_buttons[i][1].color = sf::Color(25, 76, 76, 255);
            menu_buttons[i][2].color = sf::Color(25, 76, 76, 255);
            menu_buttons[i][3].color = sf::Color(25, 76, 76, 255);
        }
        else
        {
            menu_buttons[i][0].color = sf::Color(16, 51, 51, 255);
            menu_buttons[i][1].color = sf::Color(16, 51, 51, 255);
            menu_buttons[i][2].color = sf::Color(16, 51, 51, 255);
            menu_buttons[i][3].color = sf::Color(16, 51, 51, 255);
        }

        menu_button_labels[i].setFont(resources->exoplanetaria);
        menu_button_labels[i].setCharacterSize(16);
        menu_button_labels[i].setFillColor(sf::Color::Black);
        menu_button_labels[i].setPosition(x + 20, 200 + (i * 35));

        if (menu_button_labels[i].getString() != "")
        {
            window.draw(menu_button_shadow);
            window.draw(menu_buttons[i]);
            window.draw(menu_button_labels[i]);
        }
    }
}

// Draws buttons
void gui::draw_build_buttons(sf::RenderWindow &window, build_controller &builder, sf::Vector2i mouse_position, float frame_time)
{
    float window_x = window.getView().getSize().x;

    if (build_menu_x == 0)
    {
        build_menu_x = window_x - 200;
    }
    else if (closing_build_menu == true && build_menu_x < window_x - 200)
    {
        build_menu_x += 500 * frame_time;
    }
    else if (closing_build_menu == false && build_menu_x > window_x - 350)
    {
        build_menu_x -= 500 * frame_time;
    }
    else if (closing_build_menu == true)
    {
        closing_build_menu = false;
        build_menu_open = false;
    }

    float x = build_menu_x;

    sf::Text cost;
    cost.setString("");

    for (unsigned int i = 0; i < 7; i++)
    {
        build_buttons[i] = sf::VertexArray(sf::Quads, 4);
        build_buttons[i][0].position = sf::Vector2f(x, (200 + i * 35) - 4);
        build_buttons[i][1].position = sf::Vector2f(x, (200 + i * 35) + 24);
        build_buttons[i][2].position = sf::Vector2f(x + 125, (200 + i * 35) + 24);
        build_buttons[i][3].position = sf::Vector2f(x + 125, (200 + i * 35) - 4);

        sf::VertexArray build_button_shadow = sf::VertexArray(sf::Quads, 4);
        build_button_shadow[0].position = sf::Vector2f(x, (200 + i * 35) - 4);
        build_button_shadow[1].position = sf::Vector2f(x, (200 + i * 35) + 27);
        build_button_shadow[2].position = sf::Vector2f(x + 128, (200 + i * 35) + 27);
        build_button_shadow[3].position = sf::Vector2f(x + 128, (200 + i * 35) - 4);

        build_button_shadow[0].color = sf::Color::Black;
        build_button_shadow[1].color = sf::Color::Black;
        build_button_shadow[2].color = sf::Color::Black;
        build_button_shadow[3].color = sf::Color::Black;

        if (build_buttons[i].getBounds().contains(mouse_position.x, mouse_position.y))
        {
            build_buttons[i][0].color = sf::Color(25, 76, 76, 255);
            build_buttons[i][1].color = sf::Color(25, 76, 76, 255);
            build_buttons[i][2].color = sf::Color(25, 76, 76, 255);
            build_buttons[i][3].color = sf::Color(25, 76, 76, 255);
        }
        else
        {
            build_buttons[i][0].color = sf::Color(16, 51, 51, 255);
            build_buttons[i][1].color = sf::Color(16, 51, 51, 255);
            build_buttons[i][2].color = sf::Color(16, 51, 51, 255);
            build_buttons[i][3].color = sf::Color(16, 51, 51, 255);
        }

        build_button_labels[i].setFont(resources->exoplanetaria);
        build_button_labels[i].setCharacterSize(16);
        build_button_labels[i].setFillColor(sf::Color::Black);
        build_button_labels[i].setPosition(x + 20, 200 + (i * 35));

        if (build_button_labels[i].getString() != "")
        {
            window.draw(build_button_shadow);
            window.draw(build_buttons[i]);
            window.draw(build_button_labels[i]);
        }

        if (build_buttons[i].getBounds().contains(mouse_position.x, mouse_position.y) && build_menu_x < window_x - 300)
        {
            std::string cost_str = "COST\n----\n" +
            std::to_string(builder.build_cost[i][0]) + " IRON\n" +
            std::to_string(builder.build_cost[i][1]) + " COPPER\n" +
            std::to_string(builder.build_cost[i][2]) + " SPORES";
            cost.setString(cost_str);
            cost.setFont(resources->exoplanetaria);
            cost.setCharacterSize(16);
            cost.setFillColor(sf::Color::White);
            cost.setPosition(window.getView().getSize().x - 200, window.getView().getSize().y - 150);
        }
    }

    window.draw(cost);
}
