#include <pause_menu.h>

// Gets the current working directory from main, initializes variables and objects
void pause_menu::init(std::string cwd, assets* resources)
{
    this->cwd = cwd;
    this->resources = resources;
    s_menu.init(cwd, resources);
    visible = false;
    s_menu_open = false;
    exit_prompt_open = false;
    buttons.resize(4);
    button_text.resize(4);
    button_labels.resize(4);
    button_values.resize(4);
    exit_buttons.resize(2);
    abort_button_text.resize(2);
    exit_button_labels.resize(2);
    button_text[0] = "     OPTIONS";
    button_text[1] = "    SAVE GAME";
    button_text[2] = "  RESUME GAME";
    button_text[3] = "   MAIN MENU";
    abort_button_text[0] = "  EXIT";
    abort_button_text[1] = "RESUME";
}

// Displays a notice with the given string
void pause_menu::display_notice(sf::RenderWindow &window, std::string notice, float frame_time)
{
    sf::Vector2f notice_pos;
    notice_pos.x = (window.getView().getSize().x / 2) - (resources->notice.getGlobalBounds().width / 2);
    notice_pos.y = (window.getView().getSize().y / 2) - 100;
    resources->notice.setString(notice);
    resources->notice.setPosition(notice_pos);
    window.draw(resources->notice);

    notice_timer += 10 * frame_time;
    if (notice_timer >= 30)
    {
        notice_timer = 0;
        show_notice = false;
    }
}

// Mouse click events
void pause_menu::handle_events(sf::RenderWindow &window, sf::Event event, world &game_world, sf::Vector2i mouse_position)
{
    if (s_menu.visible == false)
    {
        if (event.type == sf::Event::MouseButtonPressed)
        {
            if(event.mouseButton.button == sf::Mouse::Left)
            {
                if (save_menu_open == false && exit_prompt_open == false)
                {
                    for (unsigned int i = 0; i < buttons.size(); i++)
                    {
                        if (buttons[i].getBounds().contains(mouse_position.x, mouse_position.y))
                        {
                            if (i == 0)
                            {
                                s_menu.visible = true;
                            }
                            else if (i == 1)
                            {
                                save_menu_open = true;
                            }
                            else if (i == 2)
                            {
                                visible = false;
                            }
                            else if (i == 3)
                            {
                                exit_prompt_open = true;
                            }
                        }
                    }
                }
                else if (save_menu_open == true)
                {
                    if (create_save_prompt_open == true)
                    {
                        if (resources->save_game_button_sprite.getGlobalBounds().contains(mouse_position.x, mouse_position.y))
                        {
                            create_save(game_world);
                        }

                        if (resources->cancel_button_sprite.getGlobalBounds().contains(mouse_position.x, mouse_position.y))
                        {
                            create_save_prompt_open = false;
                        }
                    }
                    else
                    {
                        if (resources->create_new_button_sprite.getGlobalBounds().contains(mouse_position.x, mouse_position.y))
                        {
                            create_save_prompt_open = true;
                        }

                        if (resources->cancel_button_sprite.getGlobalBounds().contains(mouse_position.x, mouse_position.y))
                        {
                            save_menu_open = false;
                        }

                        for (unsigned int i = 0; i < saved_game_labels.size(); i++)
                        {
                            if (saved_game_buttons[i].getBounds().contains(mouse_position.x, mouse_position.y))
                            {
                                save_game(i, game_world);
                            }
                        }

                        for (unsigned int i = 0; i < delete_save_labels.size(); i++)
                        {
                            if (delete_save_buttons[i].getBounds().contains(mouse_position.x, mouse_position.y))
                            {
                                delete_save_game(i, game_world);
                                save_menu_open = false;
                            }
                        }
                    }
                }
                else if (exit_prompt_open == true)
                {
                    for (unsigned int i = 0; i < exit_buttons.size(); i++)
                    {
                        if (exit_buttons[i].getBounds().contains(mouse_position.x, mouse_position.y))
                        {
                            if (i == 0)
                            {
                                quit_game = true;
                                exit_prompt_open = false;
                            }
                            else if (i == 1)
                            {
                                exit_prompt_open = false;
                            }
                        }
                    }
                }
            }
        }

        if (event.type == sf::Event::TextEntered && save_menu_open == true)
        {
            if (event.text.unicode != '\b' && event.text.unicode != '`' && input.getSize() < 24)
            {
                input += event.text.unicode;
                resources->input_text.setString(input);
                kp++;
            }
        }

        if (event.type == sf::Event::KeyPressed)
        {
            if (save_menu_open == true)
            {
                if (event.key.code == sf::Keyboard::BackSpace)
                {
                    if (input.getSize() > 0)
                    {
                        input.erase(input.getSize() - 1, 1);
                        resources->input_text.setString(input);
                    }
                }

                if (event.key.code == sf::Keyboard::Escape)
                {
                    save_menu_open = false;
                }
            }

            if (event.key.code == sf::Keyboard::Escape)
            {
                if (s_menu.visible == true)
                {
                    s_menu.visible = false;
                }

                if (exit_prompt_open == true)
                {
                    exit_prompt_open = false;
                }
            }
        }
    }
    else
    {
        s_menu.handle_events(event, mouse_position);
    }
}

// Draws butons associated with saved games
void pause_menu::draw_saved_game_buttons(sf::RenderWindow &window, sf::Vector2i mouse_position)
{
    float x = window.getView().getSize().x / 2 - 150;

    for (unsigned int i = 0; i < saved_game_labels.size(); i++)
    {
        saved_game_buttons[i] = sf::VertexArray(sf::Quads, 4);
        saved_game_buttons[i][0].position = sf::Vector2f(x, (200 + i * 35) - 4);
        saved_game_buttons[i][1].position = sf::Vector2f(x, (200 + i * 35) + 24);
        saved_game_buttons[i][2].position = sf::Vector2f(x + 225, (200 + i * 35) + 24);
        saved_game_buttons[i][3].position = sf::Vector2f(x + 225, (200 + i * 35) - 4);

        sf::VertexArray saved_game_shadow = sf::VertexArray(sf::Quads, 4);
        saved_game_shadow[0].position = sf::Vector2f(x, (200 + i * 35) - 4);
        saved_game_shadow[1].position = sf::Vector2f(x, (200 + i * 35) + 27);
        saved_game_shadow[2].position = sf::Vector2f(x + 228, (200 + i * 35) + 27);
        saved_game_shadow[3].position = sf::Vector2f(x + 228, (200 + i * 35) - 4);

        saved_game_shadow[0].color = sf::Color::Black;
        saved_game_shadow[1].color = sf::Color::Black;
        saved_game_shadow[2].color = sf::Color::Black;
        saved_game_shadow[3].color = sf::Color::Black;

        if (saved_game_buttons[i].getBounds().contains(mouse_position.x, mouse_position.y))
        {
            saved_game_buttons[i][0].color = sf::Color(25, 76, 76, 255);
            saved_game_buttons[i][1].color = sf::Color(25, 76, 76, 255);
            saved_game_buttons[i][2].color = sf::Color(25, 76, 76, 255);
            saved_game_buttons[i][3].color = sf::Color(25, 76, 76, 255);
        }
        else
        {
            saved_game_buttons[i][0].color = sf::Color(16, 51, 51, 255);
            saved_game_buttons[i][1].color = sf::Color(16, 51, 51, 255);
            saved_game_buttons[i][2].color = sf::Color(16, 51, 51, 255);
            saved_game_buttons[i][3].color = sf::Color(16, 51, 51, 255);
        }

        saved_game_labels[i].setFont(resources->exoplanetaria);
        saved_game_labels[i].setCharacterSize(16);
        saved_game_labels[i].setFillColor(sf::Color::Black);
        saved_game_labels[i].setPosition(x + 20, 200 + (i * 35));

        if (saved_game_labels[i].getString() != "")
        {
            window.draw(saved_game_shadow);
            window.draw(saved_game_buttons[i]);
            window.draw(saved_game_labels[i]);
        }
    }
}

// Draws buttons used to delete saved games
void pause_menu::draw_delete_buttons(sf::RenderWindow &window, sf::Vector2i mouse_position)
{
    float x = window.getView().getSize().x / 2 + 100;

    for (unsigned int i = 0; i < saved_game_labels.size(); i++)
    {
        delete_save_buttons[i] = sf::VertexArray(sf::Quads, 4);
        delete_save_buttons[i][0].position = sf::Vector2f(x, (200 + i * 35) - 4);
        delete_save_buttons[i][1].position = sf::Vector2f(x, (200 + i * 35) + 24);
        delete_save_buttons[i][2].position = sf::Vector2f(x + 70, (200 + i * 35) + 24);
        delete_save_buttons[i][3].position = sf::Vector2f(x + 70, (200 + i * 35) - 4);

        sf::VertexArray delete_save_shadow = sf::VertexArray(sf::Quads, 4);
        delete_save_shadow[0].position = sf::Vector2f(x, (200 + i * 35) - 4);
        delete_save_shadow[1].position = sf::Vector2f(x, (200 + i * 35) + 27);
        delete_save_shadow[2].position = sf::Vector2f(x + 73, (200 + i * 35) + 27);
        delete_save_shadow[3].position = sf::Vector2f(x + 73, (200 + i * 35) - 4);

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
        delete_save_labels[i].setPosition(x + 10, 200 + (i * 35));
        delete_save_labels[i].setString("DELETE");

        if (saved_game_labels[i].getString() != "")
        {
            window.draw(delete_save_shadow);
            window.draw(delete_save_buttons[i]);
            window.draw(delete_save_labels[i]);
        }
    }
}

// Draws the menu
void pause_menu::draw_menu(sf::RenderWindow &window, sf::Vector2i mouse_position, float frame_time)
{
    if (s_menu.visible == false && save_menu_open == false && exit_prompt_open == false && show_notice == false)
    {
        float y = window.getView().getSize().y / 2 - 80;

        for (unsigned int i = 0; i < buttons.size(); i++)
        {
            float x = window.getView().getSize().x / 2 - 70;

            buttons[i] = sf::VertexArray(sf::Quads, 4);
            buttons[i][0].position = sf::Vector2f(x, (y + i * 35) - 4);
            buttons[i][1].position = sf::Vector2f(x, (y + i * 35) + 24);
            buttons[i][2].position = sf::Vector2f(x + 140, (y + i * 35) + 24);
            buttons[i][3].position = sf::Vector2f(x + 140, (y + i * 35) - 4);

            sf::VertexArray button_shadow = sf::VertexArray(sf::Quads, 4);
            button_shadow[0].position = sf::Vector2f(x, (y + i * 35) - 4);
            button_shadow[1].position = sf::Vector2f(x, (y + i * 35) + 27);
            button_shadow[2].position = sf::Vector2f(x + 143, (y + i * 35) + 27);
            button_shadow[3].position = sf::Vector2f(x + 143, (y + i * 35) - 4);

            button_shadow[0].color = sf::Color::Black;
            button_shadow[1].color = sf::Color::Black;
            button_shadow[2].color = sf::Color::Black;
            button_shadow[3].color = sf::Color::Black;

            if (buttons[i].getBounds().contains(mouse_position.x, mouse_position.y))
            {
                buttons[i][0].color = sf::Color(25, 76, 76, 255);
                buttons[i][1].color = sf::Color(25, 76, 76, 255);
                buttons[i][2].color = sf::Color(25, 76, 76, 255);
                buttons[i][3].color = sf::Color(25, 76, 76, 255);
            }
            else
            {
                buttons[i][0].color = sf::Color(16, 51, 51, 255);
                buttons[i][1].color = sf::Color(16, 51, 51, 255);
                buttons[i][2].color = sf::Color(16, 51, 51, 255);
                buttons[i][3].color = sf::Color(16, 51, 51, 255);
            }

            button_labels[i].setFont(resources->exoplanetaria);
            button_labels[i].setCharacterSize(16);
            button_labels[i].setFillColor(sf::Color::Black);
            button_labels[i].setString(button_text[i]);

            button_values[i].setFont(resources->exoplanetaria);
            button_values[i].setCharacterSize(14);
            button_values[i].setFillColor(sf::Color::White);

            if (i == 0)
                button_labels[i].setPosition(x + 12, y);
            else
                button_labels[i].setPosition(x + 12, y + (i * 35));

            if (i == 0)
                button_values[i].setPosition(x + 180, y);
            else
                button_values[i].setPosition(x + 180, y + (i * 35));

            window.draw(button_shadow);
            window.draw(buttons[i]);
            window.draw(button_labels[i]);
            window.draw(button_values[i]);
        }
    }
    else if (exit_prompt_open == true && save_menu_open == false && s_menu.visible == false && show_notice == false)
    {
        resources->notice.setFont(resources->orbitron);
        resources->notice.setString("EXIT GAME?");
        sf::Vector2f text_pos;
        text_pos.x = (window.getView().getSize().x / 2) - (resources->notice.getGlobalBounds().width / 2);
        text_pos.y = (window.getView().getSize().y / 2) - 150;
        resources->notice.setPosition(text_pos);
        window.draw(resources->notice);
        resources->notice.setFont(resources->exoplanetaria);

        float x = window.getView().getSize().x / 2 - 70;
        float y = window.getView().getSize().y / 2 - 75;

        for (unsigned int i = 0; i < exit_buttons.size(); i++)
        {
            exit_buttons[i] = sf::VertexArray(sf::Quads, 4);
            exit_buttons[i][0].position = sf::Vector2f(x, (y + i * 35) - 4);
            exit_buttons[i][1].position = sf::Vector2f(x, (y + i * 35) + 24);
            exit_buttons[i][2].position = sf::Vector2f(x + 130, (y + i * 35) + 24);
            exit_buttons[i][3].position = sf::Vector2f(x + 130, (y + i * 35) - 4);

            sf::VertexArray button_shadow = sf::VertexArray(sf::Quads, 4);
            button_shadow[0].position = sf::Vector2f(x, (y + i * 35) - 4);
            button_shadow[1].position = sf::Vector2f(x, (y + i * 35) + 27);
            button_shadow[2].position = sf::Vector2f(x + 133, (y + i * 35) + 27);
            button_shadow[3].position = sf::Vector2f(x + 133, (y + i * 35) - 4);

            button_shadow[0].color = sf::Color::Black;
            button_shadow[1].color = sf::Color::Black;
            button_shadow[2].color = sf::Color::Black;
            button_shadow[3].color = sf::Color::Black;

            if (exit_buttons[i].getBounds().contains(mouse_position.x, mouse_position.y))
            {
                exit_buttons[i][0].color = sf::Color(25, 76, 76, 255);
                exit_buttons[i][1].color = sf::Color(25, 76, 76, 255);
                exit_buttons[i][2].color = sf::Color(25, 76, 76, 255);
                exit_buttons[i][3].color = sf::Color(25, 76, 76, 255);
            }
            else
            {
                exit_buttons[i][0].color = sf::Color(16, 51, 51, 255);
                exit_buttons[i][1].color = sf::Color(16, 51, 51, 255);
                exit_buttons[i][2].color = sf::Color(16, 51, 51, 255);
                exit_buttons[i][3].color = sf::Color(16, 51, 51, 255);
            }

            exit_button_labels[i].setFont(resources->exoplanetaria);
            exit_button_labels[i].setCharacterSize(16);
            exit_button_labels[i].setFillColor(sf::Color::Black);
            exit_button_labels[i].setString(abort_button_text[i]);

            if (i == 0)
                exit_button_labels[i].setPosition(x + 38, y);
            else
                exit_button_labels[i].setPosition(x + 38, y + (i * 35));

            window.draw(button_shadow);
            window.draw(exit_buttons[i]);
            window.draw(exit_button_labels[i]);
        }
    }
    else if (s_menu.visible == true && save_menu_open == false && exit_prompt_open == false && show_notice == false)
    {
        s_menu.draw_menu(window, mouse_position);
    }
    else if (save_menu_open == true && s_menu.visible == false && exit_prompt_open == false && show_notice == false)
    {
        draw_save_menu(window, mouse_position);
    }
    else if (show_notice == true)
    {
        display_notice(window, notice, frame_time);
    }
}

// Draws the save game menu
void pause_menu::draw_save_menu(sf::RenderWindow &window, sf::Vector2i mouse_position)
{
    if (create_save_prompt_open == true)
    {
        sf::Vector2f term_pos;
        sf::Vector2f text_pos;
        term_pos.x = (window.getView().getSize().x / 2) - (resources->term_sprite.getTexture()->getSize().x / 2);
        term_pos.y = (window.getView().getSize().y / 2) - 70;
        text_pos.x = term_pos.x + 8;
        text_pos.y = term_pos.y + 8;
        resources->term_sprite.setPosition(term_pos);
        resources->input_text.setPosition(text_pos);
        window.draw(resources->term_sprite);
        window.draw(resources->input_text);

        sf::Vector2f notice_pos;
        notice_pos.x = (window.getView().getSize().x / 2) - (resources->notice.getGlobalBounds().width / 2);
        notice_pos.y = (window.getView().getSize().y / 2) - 120;
        resources->notice.setString("Enter a name for your saved game.");
        resources->notice.setPosition(notice_pos);
        window.draw(resources->notice);

        // Save Button
        if (resources->save_game_button_sprite.getGlobalBounds().contains(mouse_position.x, mouse_position.y))
        {
            resources->save_game_button_sprite.setTexture(resources->save_game_button_hover_texture);
        }
        else
        {
            resources->save_game_button_sprite.setTexture(resources->save_game_button_texture);
        }
        float b3x = (window.getView().getSize().x / 2) - (resources->save_game_button_texture.getSize().x / 2);
        float b3y = (window.getView().getSize().y / 2) - 20;
        sf::Vector2f b3v(b3x, b3y);
        resources->save_game_button_sprite.setPosition(b3v);
        window.draw(resources->save_game_button_sprite);

        // Cancel Button
        if (resources->cancel_button_sprite.getGlobalBounds().contains(mouse_position.x, mouse_position.y))
        {
            resources->cancel_button_sprite.setTexture(resources->cancel_button_hover_texture);
        }
        else
        {
            resources->cancel_button_sprite.setTexture(resources->cancel_button_texture);
        }
        float b4x = (window.getView().getSize().x / 2) - (resources->load_game_button_texture.getSize().x / 2);
        float b4y = (window.getView().getSize().y / 2) + 20;
        sf::Vector2f b4v(b4x, b4y);
        resources->cancel_button_sprite.setPosition(b4v);
        window.draw(resources->cancel_button_sprite);
    }
    else
    {
        // Create new save button
        if (resources->create_new_button_sprite.getGlobalBounds().contains(mouse_position.x, mouse_position.y))
        {
            resources->create_new_button_sprite.setTexture(resources->create_new_button_hover_texture);
        }
        else
        {
            resources->create_new_button_sprite.setTexture(resources->create_new_button_texture);
        }
        float bx = (window.getView().getSize().x / 2) - (resources->create_new_button_texture.getSize().x / 2);
        float by = 150;
        sf::Vector2f bv(bx, by);
        resources->create_new_button_sprite.setPosition(bv);
        window.draw(resources->create_new_button_sprite);

        // Cancel button
        if (resources->cancel_button_sprite.getGlobalBounds().contains(mouse_position.x, mouse_position.y))
        {
            resources->cancel_button_sprite.setTexture(resources->cancel_button_hover_texture);
        }
        else
        {
            resources->cancel_button_sprite.setTexture(resources->cancel_button_texture);
        }
        float cx = (window.getView().getSize().x / 2) - (resources->cancel_button_texture.getSize().x / 2);
        float cy = 100;
        sf::Vector2f cv(cx, cy);
        resources->cancel_button_sprite.setPosition(cv);
        window.draw(resources->cancel_button_sprite);

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

        // Resize arrays
        saved_game_buttons.resize(index);
        saved_game_labels.resize(index);
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
            saved_game_labels[index].setString(token);
            saves.erase(0, pos + delimiter.length());
            index++;
        }

        // Save game buttons
        draw_saved_game_buttons(window, mouse_position);

        // Delete save buttons
        draw_delete_buttons(window, mouse_position);
    }
}

// Overwrites an existing save game
void pause_menu::save_game(int i, world &game_world)
{
    std::string path = cwd + "/save/" + saved_game_labels[i].getString() + "/";
    game_world.save_game(i, path);
    save_menu_open = false;
    notice = "GAME SAVED";
    show_notice = true;
}

// Creates a new save game
void pause_menu::create_save(world &game_world)
{
    bool invalid = false;

    if (input == "")
    {
        invalid = true;
    }

    for (unsigned int i = 0; i < saved_game_labels.size(); i++)
    {
        if (input == saved_game_labels[i].getString())
        {
            invalid = true;
            break;
        }
    }

    if (invalid == false)
    {
        if (game_world.create_save(cwd, input))
        {
            save_menu_open = false;
            create_save_prompt_open = false;
            notice = "GAME SAVED";
            show_notice = true;
        }
        else
        {
            notice = "SAVE LIMIT REACHED";
            show_notice = true;
        }
    }
    else
    {
        notice = "INVALID NAME";
        show_notice = true;
    }

    input = "";
    resources->input_text.setString(input);
}

// Deletes a saved game
void pause_menu::delete_save_game(int i, world &game_world)
{
    game_world.delete_save_game(cwd, i, saved_game_labels[i].getString());
    notice = "SAVE DELETED";
    show_notice = true;
}
