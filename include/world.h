#ifndef WORLD_H
#define WORLD_H

#include <drill.h>
#include <growth.h>
#include <iostream>
#include <supplies.h>
#include <cannon.h>
#include <harvester.h>
#include <generator.h>
#include <annihilator.h>
#include <logistics_center.h>
#include <command_center.h>
#include <file_handler.h>
#include <resource_node.h>
#include <SFML/Graphics.hpp>
#include <experimental/filesystem>

class world
{
    public:
        world();
        std::map<std::string, int> inventory;
        sf::Vector2i player_coordinates;
        struct area
        {
            int power;
            bool connected;
            growth area_growth;
            sf::Vector2i coordinates;
            std::array<resource_node, 5> resource_nodes;
            std::vector<generator> generators;
            std::vector<harvester> harvesters;
            std::vector<annihilator> annihilators;
            std::vector<logistics_center> logi_centers;
            std::vector<command_center> cmd_centers;
            std::vector<cannon> cannons;
            std::vector<drill> drills;
        };
        std::vector<area> areas;
        std::string get_drill_data();
        std::string get_spore_data();
        std::string get_player_data();
        std::string get_growth_data();
        std::string get_cmd_center_data();
        std::string get_logi_center_data();
        std::string get_generator_data();
        std::string get_harvester_data();
        std::string get_cannon_data();
        std::string get_annihilator_data();
        std::string get_resource_node_data();
        float growth_spawn_timer;
        int get_area_index(sf::Vector2i coords);
        bool spawn_growth(sf::RenderWindow &window, int area_index, float frame_time);
        void generate_resource_nodes(assets &textures, sf::RenderWindow &window, int index);
        void load_player_data(std::string cwd, std::string file);
        void load_objects(std::string cwd, std::string dir, std::string type, sf::RenderWindow &window, assets* resources);
        void save_game(int i, std::string path);
        void delete_save_game(std::string cwd, int i, sf::String dir);
        bool create_save(std::string cwd, sf::String &input);
};

#endif // WORLD_H
