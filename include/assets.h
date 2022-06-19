#ifndef ASSETS_H
#define ASSETS_H

#include <array>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

class assets
{
    public:
        // Sounds
        sf::SoundBuffer main_menu_music_buffer;
        sf::Sound main_menu_music;

        sf::SoundBuffer dig_sound_buffer;
        sf::Sound dig_sound;

        sf::SoundBuffer power_buffer_sound_buffer;
        sf::Sound power_buffer_sound;

        sf::SoundBuffer annihilator_sound_buffer;
        sf::Sound annihilator_sound;

        sf::SoundBuffer victory_sound_buffer;
        sf::Sound victory_sound;

        sf::SoundBuffer explosion_sound_buffer;
        std::array<sf::Sound, 10> explosion_sounds;

        sf::SoundBuffer drill_sound_buffer;
        std::array<sf::Sound, 10> drill_sounds;

        sf::SoundBuffer harvester_sound_buffer;
        std::array<sf::Sound, 10> harvester_sounds;

        sf::SoundBuffer cannon_sound_buffer;
        std::array<sf::Sound, 10> cannon_sounds;

        // Textures
        sf::Texture spore_texture;
        sf::Texture growth_texture;
        sf::Texture t2_spore_texture;
        sf::Texture t2_growth_texture;
        sf::Texture t3_spore_texture;
        sf::Texture t3_growth_texture;
        sf::Texture iron_texture;
        sf::Texture copper_texture;
        sf::Texture coal_texture;
        sf::Texture destroy_texture;
        sf::Texture cmd_center_texture;
        sf::Texture logi_center_texture;
        sf::Texture generator_off_texture;
        sf::Texture generator_on_texture;
        sf::Texture drill_texture;
        sf::Texture drill_mining_texture;
        sf::Texture harvester_texture;
        sf::Texture harvester_firing_texture;
        sf::Texture cannon_texture;
        sf::Texture cannon_firing_texture;
        sf::Texture annihilator_texture;
        sf::Texture annihilator_firing_texture;
        sf::Texture explosion_texture;
        sf::Texture medium_explosion_texture;
        sf::Texture large_explosion_texture;
        sf::Texture terrain_texture;
        sf::Texture game_background_texture;

        sf::Texture gui_background_texture;
        sf::Texture gui_background_2_texture;

        sf::Texture title_texture;
        sf::Texture term_texture;

        sf::Texture start_game_button_texture;
        sf::Texture start_game_button_hover_texture;
        sf::Texture tutorial_button_texture;
        sf::Texture tutorial_button_hover_texture;
        sf::Texture main_menu_button_texture;
        sf::Texture main_menu_button_hover_texture;
        sf::Texture save_game_button_texture;
        sf::Texture save_game_button_hover_texture;
        sf::Texture load_game_button_texture;
        sf::Texture load_game_button_hover_texture;
        sf::Texture next_mission_button_texture;
        sf::Texture next_mission_button_hover_texture;
        sf::Texture market_button_texture;
        sf::Texture market_button_hover_texture;
        sf::Texture exit_game_button_texture;
        sf::Texture exit_game_button_hover_texture;
        sf::Texture create_new_button_texture;
        sf::Texture create_new_button_hover_texture;
        sf::Texture cancel_button_texture;
        sf::Texture cancel_button_hover_texture;
        sf::Texture options_button_texture;
        sf::Texture options_button_hover_texture;

        // Sprites
        sf::Sprite terrain_sprite;
        sf::Sprite term_sprite;

        sf::Sprite start_game_button_sprite;
        sf::Sprite tutorial_button_sprite;
        sf::Sprite main_menu_button_sprite;
        sf::Sprite save_game_button_sprite;
        sf::Sprite create_new_button_sprite;
        sf::Sprite cancel_button_sprite;
        sf::Sprite load_game_button_sprite;
        sf::Sprite options_button_sprite;
        sf::Sprite next_mission_button_sprite;
        sf::Sprite exit_game_button_sprite;
        sf::Sprite title_sprite;
        sf::Sprite game_background_sprite;

        // Fonts
        sf::Font orbitron;
        sf::Font exoplanetaria;

        // Text Objects

        sf::Text keys;
        sf::Text notice;
        sf::Text inventory;
        sf::Text input_text;
        sf::Text fps_counter;
        sf::Text area_power;
        sf::Text player_location;

        std::map<std::string, sf::Texture> resource_textures;
        std::map<std::string, sf::Texture> building_textures;

        void init(std::string cwd);

    private:
        void load_sound_buffers(std::string cwd);
        void load_textures(std::string cwd);
        void load_fonts(std::string cwd);
        void init_sounds();
        void init_sprites();
        void init_text();
};

#endif // ASSETS_H

