#ifndef GUI_H
#define GUI_H

#include <iostream>
#include <assets.h>
#include <world.h>
#include <pause_menu.h>
#include <build_controller.h>
#include <SFML/Graphics.hpp>

struct gui_event_params
{
    sf::RenderWindow &window;
    pause_menu &p_menu;
    world &game_world;
    build_controller &builder;
    sf::Event event;
    sf::Vector2i mouse;
};

struct gui_draw_params
{
    sf::RenderWindow &window;
    world &game_world;
    build_controller &builder;
    sf::Vector2i mouse_position;
    sf::Vector2f zoom;
    int area_power;
    float frame_time;
    float fps;
    bool show_fps;
};

class gui
{
    public:
        void init(std::string cwd, assets* resources);
        void draw_gui(struct gui_draw_params & params);
        void draw_menu_buttons(sf::RenderWindow &window, sf::Vector2i mouse_position);
        void draw_build_buttons(sf::RenderWindow &window, build_controller &builder, sf::Vector2i mouse_position, float frame_time);
        void handle_events(struct gui_event_params &params);
        gui();

    private:
        assets* resources;
        float build_menu_x;
        bool closing_build_menu;
        bool build_menu_open;
        std::string cwd;
        std::vector<sf::VertexArray> menu_buttons;
        std::vector<sf::VertexArray> build_buttons;
        std::vector<sf::Text> menu_button_labels;
        std::vector<sf::Text> build_button_labels;
};

#endif // GUI_H
