#ifndef PAUSE_MENU_H
#define PAUSE_MENU_H

#include <world.h>
#include <assets.h>
#include <string.h>
#include <iostream>
#include <harvester.h>
#include <pause_menu.h>
#include <file_handler.h>
#include <settings_menu.h>

class pause_menu
{
    public:
        bool visible;
        bool quit_game;
        void init(std::string cwd, assets* resources);
        void draw_menu(sf::RenderWindow &window, sf::Vector2i mouse_position, float frame_time);
        void handle_events(sf::RenderWindow &window, sf::Event event, world &game_world, sf::Vector2i mouse_position);
    private:
        assets* resources;
        settings_menu s_menu;
        sf::String input;
        sf::Vector2i mouse_position;
        int kp;
        float notice_timer;
        bool show_notice;
        bool exit_prompt_open;
        bool save_menu_open;
        bool create_save_prompt_open;
        bool s_menu_open;
        std::string cwd;
        std::string notice;
        std::vector<sf::VertexArray> buttons;
        std::vector<sf::VertexArray> exit_buttons;
        std::vector<sf::Text> button_labels;
        std::vector<sf::Text> exit_button_labels;
        std::vector<sf::Text> button_values;
        std::vector<sf::VertexArray> saved_game_buttons;
        std::vector<sf::VertexArray> delete_save_buttons;
        std::vector<sf::Text> delete_save_labels;
        std::vector<sf::Text> saved_game_labels;
        std::vector<std::string> button_text;
        std::vector<std::string> abort_button_text;
        void delete_save_game(int i, world &game_world);
        void save_game(int i, world &game_world);
        void create_save(world &game_world);
        void display_notice(sf::RenderWindow &window, std::string notice, float frame_time);
        void draw_save_menu(sf::RenderWindow &window, sf::Vector2i mouse_position);
        void draw_saved_game_buttons(sf::RenderWindow &window, sf::Vector2i mouse_position);
        void draw_delete_buttons(sf::RenderWindow &window, sf::Vector2i mouse_position);
};

#endif // PAUSE_MENU_H
