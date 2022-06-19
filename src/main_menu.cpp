#include <main_menu.h>
#include <settings.h>
#include <iostream>
#include <world.h>
#include <math.h>

// Gets current directory, initializes resources and settings menu
void main_menu::init(std::string cwd, assets* resources)
{
    this->cwd = cwd;
    this->resources = resources;
    s_menu.init(cwd, resources);
}

// Loads saved game data from file
void main_menu::load_game(std::string cwd, world &game_world, sf::RenderWindow &window, std::string file)
{
    game_world.load_objects(cwd, file, "cmd_centers", window, resources);
    game_world.load_objects(cwd, file, "logi_centers", window, resources);
    game_world.load_objects(cwd, file, "generators", window, resources);
    game_world.load_objects(cwd, file, "drills", window, resources);
    game_world.load_objects(cwd, file, "harvesters", window, resources);
    game_world.load_objects(cwd, file, "cannons", window, resources);
    game_world.load_objects(cwd, file, "annihilators", window, resources);
    game_world.load_objects(cwd, file, "resource_nodes", window, resources);
    game_world.load_objects(cwd, file, "growths", window, resources);
    game_world.load_objects(cwd, file, "spores", window, resources);
    game_world.load_player_data(cwd, file);
}

// Deletes a saved game
void main_menu::delete_save_game(int i)
{
    std::string path = cwd + "/save/" + load_game_labels[i].getString() + "/";
    std::experimental::filesystem::v1::remove_all(path);

    std::string saves = get_file_contents(cwd + "/save/saves.list");
    std::string delimiter = "\n";
    std::string new_saves;
    std::string token;
    size_t pos = 0;

    while ((pos = saves.find(delimiter)) != std::string::npos)
    {
        token = saves.substr(0, pos);
        if (token != load_game_labels[i].getString())
        {
            new_saves += token + "\n";
        }
        saves.erase(0, pos + delimiter.length());
    }

    new_saves.erase(new_saves.find_last_not_of(" \n\r\t")+1);
    write_to_file(cwd + "/save/saves.list", new_saves);
    load_prompt_open = false;
    show_delete_notice = true;
}

// Draws the load game menu
void main_menu::draw_load_menu(sf::RenderWindow &window)
{
    int index = 0;
    size_t pos = 0;
    std::string saves = get_file_contents(cwd + "/save/saves.list");
    std::string delimiter = "\n";
    std::string token;

    // Get the number of saved games
    while ((pos = saves.find(delimiter)) != std::string::npos)
    {
        token = saves.substr(0, pos);
        saves.erase(0, pos + delimiter.length());
        index++;
    }

    load_game_buttons.resize(index);
    load_game_labels.resize(index);
    delete_save_buttons.resize(index);
    delete_save_labels.resize(index);

    // Reset variables
    pos = 0;
    index = 0;
    saves = get_file_contents(cwd + "/save/saves.list");

    // Create text objects for all existing save files
    while ((pos = saves.find(delimiter)) != std::string::npos)
    {
        token = saves.substr(0, pos);
        load_game_labels[index].setString(token);
        saves.erase(0, pos + delimiter.length());
        index++;
    }

    // Load game buttons
    for (unsigned int i = 0; i < load_game_labels.size(); i++)
    {
        float x = window.getView().getSize().x / 2 - 150;

        load_game_buttons[i] = sf::VertexArray(sf::Quads, 4);
        load_game_buttons[i][0].position = sf::Vector2f(x, (250 + i * 35) - 4);
        load_game_buttons[i][1].position = sf::Vector2f(x, (250 + i * 35) + 24);
        load_game_buttons[i][2].position = sf::Vector2f(x + 225, (250 + i * 35) + 24);
        load_game_buttons[i][3].position = sf::Vector2f(x + 225, (250 + i * 35) - 4);

        sf::VertexArray load_game_shadow = sf::VertexArray(sf::Quads, 4);
        load_game_shadow[0].position = sf::Vector2f(x, (250 + i * 35) - 4);
        load_game_shadow[1].position = sf::Vector2f(x, (250 + i * 35) + 27);
        load_game_shadow[2].position = sf::Vector2f(x + 228, (250 + i * 35) + 27);
        load_game_shadow[3].position = sf::Vector2f(x + 228, (250 + i * 35) - 4);

        load_game_shadow[0].color = sf::Color::Black;
        load_game_shadow[1].color = sf::Color::Black;
        load_game_shadow[2].color = sf::Color::Black;
        load_game_shadow[3].color = sf::Color::Black;

        if (load_game_buttons[i].getBounds().contains(mouse_position.x, mouse_position.y))
        {
            load_game_buttons[i][0].color = sf::Color(25, 76, 76, 255);
            load_game_buttons[i][1].color = sf::Color(25, 76, 76, 255);
            load_game_buttons[i][2].color = sf::Color(25, 76, 76, 255);
            load_game_buttons[i][3].color = sf::Color(25, 76, 76, 255);
        }
        else
        {
            load_game_buttons[i][0].color = sf::Color(16, 51, 51, 255);
            load_game_buttons[i][1].color = sf::Color(16, 51, 51, 255);
            load_game_buttons[i][2].color = sf::Color(16, 51, 51, 255);
            load_game_buttons[i][3].color = sf::Color(16, 51, 51, 255);
        }

        load_game_labels[i].setFont(resources->exoplanetaria);
        load_game_labels[i].setCharacterSize(16);
        load_game_labels[i].setFillColor(sf::Color::Black);
        load_game_labels[i].setPosition(x + 20, 250 + (i * 35));

        if (load_game_labels[i].getString() != "")
        {
            window.draw(load_game_shadow);
            window.draw(load_game_buttons[i]);
            window.draw(load_game_labels[i]);
        }
    }

    // Delete save buttons
    for (unsigned int i = 0; i < load_game_labels.size(); i++)
    {
        float x = window.getView().getSize().x / 2 + 100;

        delete_save_buttons[i] = sf::VertexArray(sf::Quads, 4);
        delete_save_buttons[i][0].position = sf::Vector2f(x, (250 + i * 35) - 4);
        delete_save_buttons[i][1].position = sf::Vector2f(x, (250 + i * 35) + 24);
        delete_save_buttons[i][2].position = sf::Vector2f(x + 70, (250 + i * 35) + 24);
        delete_save_buttons[i][3].position = sf::Vector2f(x + 70, (250 + i * 35) - 4);

        sf::VertexArray delete_save_shadow = sf::VertexArray(sf::Quads, 4);
        delete_save_shadow[0].position = sf::Vector2f(x, (250 + i * 35) - 4);
        delete_save_shadow[1].position = sf::Vector2f(x, (250 + i * 35) + 27);
        delete_save_shadow[2].position = sf::Vector2f(x + 73, (250 + i * 35) + 27);
        delete_save_shadow[3].position = sf::Vector2f(x + 73, (250 + i * 35) - 4);

        delete_save_shadow[0].color = sf::Color::Black;
        delete_save_shadow[1].color = sf::Color::Black;
        delete_save_shadow[2].color = sf::Color::Black;
        delete_save_shadow[3].color = sf::Color::Black;

        if (delete_save_buttons[i].getBounds().contains(mouse_position.x, mouse_position.y))
        {
            delete_save_buttons[i][0].color = sf::Color(25, 76, 76, 255);
            delete_save_buttons[i][1].color = sf::Color(25, 76, 76, 255);
            delete_save_buttons[i][2].color = sf::Color(25, 76, 76, 255);
            delete_save_buttons[i][3].color = sf::Color(25, 76, 76, 255);
        }
        else
        {
            delete_save_buttons[i][0].color = sf::Color(16, 51, 51, 255);
            delete_save_buttons[i][1].color = sf::Color(16, 51, 51, 255);
            delete_save_buttons[i][2].color = sf::Color(16, 51, 51, 255);
            delete_save_buttons[i][3].color = sf::Color(16, 51, 51, 255);
        }

        delete_save_labels[i].setFont(resources->exoplanetaria);
        delete_save_labels[i].setCharacterSize(16);
        delete_save_labels[i].setFillColor(sf::Color::Black);
        delete_save_labels[i].setPosition(x + 10, 250 + (i * 35));
        delete_save_labels[i].setString("DELETE");

        if (load_game_labels[i].getString() != "")
        {
            window.draw(delete_save_shadow);
            window.draw(delete_save_buttons[i]);
            window.draw(delete_save_labels[i]);
        }
    }

    // Cancel Button
    if (resources->cancel_button_sprite.getGlobalBounds().contains(mouse_position.x, mouse_position.y))
    {
        resources->cancel_button_sprite.setTexture(resources->cancel_button_hover_texture);
    }
    else
    {
        resources->cancel_button_sprite.setTexture(resources->cancel_button_texture);
    }
    float bx = (window.getView().getSize().x / 2) - (resources->cancel_button_texture.getSize().x / 2);
    float by = 200;
    sf::Vector2f bv(bx, by);
    resources->cancel_button_sprite.setPosition(bv);
    window.draw(resources->cancel_button_sprite);
}

// Handles all drawing and interaction with the menu
bool main_menu::draw_menu(sf::RenderWindow &window, world &game_world, float frame_time)
{
    if (start_game == false)
    {
        // Play music
        resources->main_menu_music.setVolume(25 * audio_volume);

        if (music && resources->main_menu_music.getStatus() != sf::Sound::Playing)
        {
            resources->main_menu_music.play();
        }

        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if(event.type == sf::Event::MouseMoved)
            {
                mouse_position = sf::Mouse().getPosition(window);
            }

            if (event.type == sf::Event::Resized)
            {
                sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                window.setView(sf::View(visibleArea));
            }

            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            if (s_menu.visible == false)
            {
                if (event.type == sf::Event::MouseButtonPressed)
                {
                    if(event.mouseButton.button == sf::Mouse::Left)
                    {
                        if (load_prompt_open == false)
                        {
                            if (resources->start_game_button_sprite.getGlobalBounds().contains(mouse_position.x, mouse_position.y))
                            {
                                resources->main_menu_music.stop();
                                new_game = true;
                                start_game = true;
                            }

                            if (resources->tutorial_button_sprite.getGlobalBounds().contains(mouse_position.x, mouse_position.y))
                            {
                                resources->main_menu_music.stop();
                                new_game = true;
                                tutorial = true;
                                start_game = true;
                            }

                            if (resources->options_button_sprite.getGlobalBounds().contains(mouse_position.x, mouse_position.y))
                            {
                                s_menu.visible = true;
                            }

                            if (resources->load_game_button_sprite.getGlobalBounds().contains(mouse_position.x, mouse_position.y))
                            {
                                load_prompt_open = true;
                            }

                            if (resources->exit_game_button_sprite.getGlobalBounds().contains(mouse_position.x, mouse_position.y))
                            {
                                window.close();
                            }
                        }
                        else
                        {
                            if (resources->cancel_button_sprite.getGlobalBounds().contains(mouse_position.x, mouse_position.y))
                            {
                                load_prompt_open = false;
                            }

                            for (unsigned int i = 0; i < load_game_labels.size(); i++)
                            {
                                if (load_game_buttons[i].getBounds().contains(mouse_position.x, mouse_position.y))
                                {
                                    load_game(cwd, game_world, window, load_game_labels[i].getString());
                                    load_prompt_open = false;
                                    show_load_notice = true;
                                }
                            }

                            for (unsigned int i = 0; i < delete_save_labels.size(); i++)
                            {
                                if (delete_save_buttons[i].getBounds().contains(mouse_position.x, mouse_position.y))
                                {
                                    delete_save_game(i);
                                }
                            }
                        }
                    }
                }

                if (event.type == sf::Event::KeyPressed)
                {
                    if (load_prompt_open == true)
                    {
                        if (event.key.code == sf::Keyboard::Escape)
                        {
                            load_prompt_open = false;
                        }
                    }
                    else if (s_menu.visible == true)
                    {
                        if (event.key.code == sf::Keyboard::Escape)
                        {
                            s_menu.visible = false;
                        }
                    }
                }
            }
            else
            {
                s_menu.handle_events(event, mouse_position);
            }
        }
        window.clear();

        // Draw the background
        resources->game_background_sprite.setPosition(0,0);
        sf::IntRect bgr = sf::IntRect(0, 0, window.getView().getSize().x, window.getView().getSize().y);
        resources->game_background_sprite.setTextureRect(bgr);
        window.draw(resources->game_background_sprite);

        // Draw the title
        float title_x = window.getView().getSize().x / 2 - resources->title_texture.getSize().x / 2;
        float title_y = 0;
        resources->title_sprite.setPosition(title_x, title_y);
        window.draw(resources->title_sprite);

        float button_y = (window.getView().getSize().y / 2) - 100;

        if (load_prompt_open == false && s_menu.visible == false && show_load_notice == false && show_delete_notice == false)
        {
            // Start Game Button
            if (resources->start_game_button_sprite.getGlobalBounds().contains(mouse_position.x, mouse_position.y))
            {
                resources->start_game_button_sprite.setTexture(resources->start_game_button_hover_texture);
            }
            else
            {
                resources->start_game_button_sprite.setTexture(resources->start_game_button_texture);
            }
            float bx = (window.getView().getSize().x / 2) - (resources->start_game_button_texture.getSize().x);
            float by = button_y - 40;
            sf::Vector2f bv(bx, by);
            resources->start_game_button_sprite.setPosition(bv);
            resources->start_game_button_sprite.setScale(2, 2);
            window.draw(resources->start_game_button_sprite);

            //Tutorial Button
            if (resources->tutorial_button_sprite.getGlobalBounds().contains(mouse_position.x, mouse_position.y))
            {
                resources->tutorial_button_sprite.setTexture(resources->tutorial_button_hover_texture);
            }
            else
            {
                resources->tutorial_button_sprite.setTexture(resources->tutorial_button_texture);
            }
            float b1x = (window.getView().getSize().x / 2) - (resources->tutorial_button_texture.getSize().x);
            float b1y = button_y + 40;
            sf::Vector2f b1v(b1x, b1y);
            resources->tutorial_button_sprite.setPosition(b1v);
            resources->tutorial_button_sprite.setScale(2, 2);
            window.draw(resources->tutorial_button_sprite);

            // Load Game Button
            if (resources->load_game_button_sprite.getGlobalBounds().contains(mouse_position.x, mouse_position.y))
            {
                resources->load_game_button_sprite.setTexture(resources->load_game_button_hover_texture);
            }
            else
            {
                resources->load_game_button_sprite.setTexture(resources->load_game_button_texture);
            }
            float b2x = (window.getView().getSize().x / 2) - (resources->load_game_button_texture.getSize().x);
            float b2y = button_y + 120;
            sf::Vector2f b2v(b2x, b2y);
            resources->load_game_button_sprite.setPosition(b2v);
            resources->load_game_button_sprite.setScale(2, 2);
            window.draw(resources->load_game_button_sprite);

            // Options
            if (resources->options_button_sprite.getGlobalBounds().contains(mouse_position.x, mouse_position.y))
            {
                resources->options_button_sprite.setTexture(resources->options_button_hover_texture);
            }
            else
            {
                resources->options_button_sprite.setTexture(resources->options_button_texture);
            }
            float b3x = (window.getView().getSize().x / 2) - (resources->options_button_texture.getSize().x);
            float b3y = button_y + 200;
            sf::Vector2f b3v(b3x, b3y);
            resources->options_button_sprite.setPosition(b3v);
            resources->options_button_sprite.setScale(2, 2);
            window.draw(resources->options_button_sprite);

            // Exit Button
            if (resources->exit_game_button_sprite.getGlobalBounds().contains(mouse_position.x, mouse_position.y))
            {
                resources->exit_game_button_sprite.setTexture(resources->exit_game_button_hover_texture);
            }
            else
            {
                resources->exit_game_button_sprite.setTexture(resources->exit_game_button_texture);
            }
            float b4x = (window.getView().getSize().x / 2) - (resources->exit_game_button_texture.getSize().x);
            float b4y = button_y + 280;
            sf::Vector2f b4v(b4x, b4y);
            resources->exit_game_button_sprite.setPosition(b4v);
            resources->exit_game_button_sprite.setScale(2, 2);
            window.draw(resources->exit_game_button_sprite);
        }
        else if (load_prompt_open == true)
        {
            draw_load_menu(window);
        }
        else if (show_load_notice == true && show_delete_notice == false)
        {
            sf::Vector2f text_pos;
            text_pos.x = (window.getView().getSize().x / 2) - (resources->notice.getGlobalBounds().width / 2);
            text_pos.y = (window.getView().getSize().y / 2) - 100;
            resources->notice.setString("GAME LOADED");
            resources->notice.setPosition(text_pos);
            window.draw(resources->notice);

            load_notice_timer += 10 * frame_time;
            if (load_notice_timer >= 30)
            {
                resources->main_menu_music.stop();
                load_notice_timer = 0;
                show_load_notice = false;
                start_game = true;
            }
        }
        else if (show_load_notice == false && show_delete_notice == true)
        {
            sf::Vector2f text_pos;
            text_pos.x = (window.getView().getSize().x / 2) - (resources->notice.getGlobalBounds().width / 2);
            text_pos.y = (window.getView().getSize().y / 2) - 100;
            resources->notice.setString("SAVE DELETED");
            resources->notice.setPosition(text_pos);
            window.draw(resources->notice);

            delete_notice_timer += 10 * frame_time;
            if (delete_notice_timer >= 30)
            {
                delete_notice_timer = 0;
                show_delete_notice = false;
            }
        }
        else if (s_menu.visible == true)
        {
            s_menu.draw_menu(window, mouse_position);
        }

        window.display();
        return true;
    }
    else
    {
        return false;
    }
}
