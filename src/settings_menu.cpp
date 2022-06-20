#include <assets.h>
#include <iostream>
#include <settings.h>
#include <settings_menu.h>

// Gets the current working directory from main, initializes variables and objects
void settings_menu::init(std::string cwd, assets* resources)
{
    this->cwd = cwd;
    this->resources = resources;
    visible = false;
    buttons.resize(5);
    button_text.resize(5);
    button_labels.resize(5);
    button_values.resize(5);
    button_text[0] = " ENABLE MUSIC";
    button_text[1] = " AUDIO VOLUME";
    button_text[2] = "   DIFFICULTY";
    button_text[3] = "    GUI SCALE";
    button_text[4] = "    EXIT MENU";
}

// Mouse click events
void settings_menu::handle_events(sf::Event event, sf::Vector2i mouse_position)
{
    if (event.type == sf::Event::MouseButtonPressed)
    {
        if(event.mouseButton.button == sf::Mouse::Left)
        {
            for (unsigned int i = 0; i < buttons.size(); i++)
            {
                if (buttons[i].getBounds().contains(mouse_position.x, mouse_position.y))
                {
                    if (i == 0)
                    {
                        music = !music;
                    }
                    else if (i == 1)
                    {
                        if (audio_volume <= 0.9)
                        {
                            audio_volume += 0.1;
                        }
                        else
                        {
                            audio_volume = 0.1;
                        }
                    }
                    else if (i == 2)
                    {
                        if (difficulty > 0.25f)
                        {
                            difficulty = difficulty / 2.0f;
                        }
                        else
                        {
                            difficulty = 1.0f;
                        }
                    }
                    else if (i == 3)
                    {
                        if (gui_scale < 1.5)
                        {
                            gui_scale += 0.1;
                        }
                        else
                        {
                            gui_scale = 1.0;
                        }
                    }
                    else if (i == 4)
                    {
                        save_settings(cwd);
                        visible = false;
                    }
                }
            }
        }
    }
}

// Draws the menu
void settings_menu::draw_menu(sf::RenderWindow &window, sf::Vector2i mouse_position)
{
    sf::Sprite bg_sprite = sf::Sprite(resources->gui_background_2_texture);
    bg_sprite.setPosition(window.getView().getSize().x / 2 - (100 * gui_scale * 1.5), window.getView().getSize().y / 2 - (100 * gui_scale));
    bg_sprite.setScale(0.19 * gui_scale, 0.6 * gui_scale);
    window.draw(bg_sprite);

    float y = window.getView().getSize().y / 2 - (80 * gui_scale);

    button_values[0].setString(music == true ? "YES" :"NO");
    button_values[1].setString(std::to_string((int)((100 * audio_volume) + 0.5)) + "%");

    std::map<float, std::string> difficulty_str;
    difficulty_str[1] = "EASY";
    difficulty_str[0.5f] = "MEDIUM";
    difficulty_str[0.25f] = "HARD";
    button_values[2].setString(difficulty_str[difficulty]);

    button_values[3].setString(std::to_string((int)(100 * gui_scale)) + "%");

    for (unsigned int i = 0; i < buttons.size(); i++)
    {
        float x = window.getView().getSize().x / 2 - (70 * gui_scale * 1.5);

        buttons[i] = sf::VertexArray(sf::Quads, 4);
        buttons[i][0].position = sf::Vector2f(x, (y + i * 35 * gui_scale) - 4 * gui_scale);
        buttons[i][1].position = sf::Vector2f(x, (y + i * 35 * gui_scale) + 24 * gui_scale);
        buttons[i][2].position = sf::Vector2f(x + (140 * gui_scale), (y + i * 35 * gui_scale) + 24 * gui_scale);
        buttons[i][3].position = sf::Vector2f(x + (140 * gui_scale), (y + i * 35 * gui_scale) - 4 * gui_scale);

        sf::VertexArray button_shadow = sf::VertexArray(sf::Quads, 4);
        button_shadow[0].position = sf::Vector2f(x, (y + i * 35 * gui_scale) - 4 * gui_scale);
        button_shadow[1].position = sf::Vector2f(x, (y + i * 35 * gui_scale) + 27 * gui_scale);
        button_shadow[2].position = sf::Vector2f(x + (143 * gui_scale), (y + i * 35 * gui_scale) + 27 * gui_scale);
        button_shadow[3].position = sf::Vector2f(x + (143 * gui_scale), (y + i * 35 * gui_scale) - 4 * gui_scale);

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
        button_labels[i].setCharacterSize(16 * gui_scale);
        button_labels[i].setFillColor(sf::Color::Black);
        button_labels[i].setString(button_text[i]);

        button_values[i].setFont(resources->exoplanetaria);
        button_values[i].setCharacterSize(14 * gui_scale);
        button_values[i].setFillColor(sf::Color::White);

        if (i == 0)
            button_labels[i].setPosition(x + 12 * gui_scale, y);
        else
            button_labels[i].setPosition(x + 12 * gui_scale, y + (i * 35 * gui_scale));

        if (i == 0)
            button_values[i].setPosition(x + 180 * gui_scale, y);
        else
            button_values[i].setPosition(x + 180 * gui_scale, y + (i * 35 * gui_scale));

        window.draw(button_shadow);
        window.draw(buttons[i]);
        window.draw(button_labels[i]);
        window.draw(button_values[i]);
    }
}
