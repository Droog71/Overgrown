#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include <world.h>
#include <assets.h>
#include <settings_menu.h>
#include <SFML/Graphics.hpp>
#include <experimental/filesystem>

class main_menu
{
    public:
        bool start_game;
        bool new_game;
        bool tutorial;
        void init(std::string cwd, assets* resources);
        bool draw_menu(sf::RenderWindow &window, world &game_world, float frame_time);

    private:
        assets* resources;
        settings_menu s_menu;
        sf::Vector2i mouse_position;
        bool load_prompt_open;
        bool show_load_notice;
        bool show_delete_notice;
        float delete_notice_timer;
        float load_notice_timer;
        std::string cwd;
        std::vector<sf::VertexArray> load_game_buttons;
        std::vector<sf::Text> load_game_labels;
        std::vector<sf::VertexArray> delete_save_buttons;
        std::vector<sf::Text> delete_save_labels;
        void load_game(std::string cwd, world &game_world, sf::RenderWindow &window, std::string file);
        void delete_save_game(int i);
        void draw_load_menu(sf::RenderWindow &window);
};

#endif // MAIN_MENU_H
