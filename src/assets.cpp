#include <assets.h>
#include <SFML/Graphics.hpp>
#include <iostream>

// Loads sounds from file
void assets::load_sound_buffers(std::string cwd)
{
    if (!main_menu_music_buffer.loadFromFile(cwd + "/assets/sounds/main_menu.ogg"))
    {
        std::cout << "Error loading sound file main_menu.ogg";
        std::cout << "\n";
    }

    if (!dig_sound_buffer.loadFromFile(cwd + "/assets/sounds/dig.ogg"))
    {
        std::cout << "Error loading sound file dig.ogg";
        std::cout << "\n";
    }

    if (!victory_sound_buffer.loadFromFile(cwd + "/assets/sounds/victory.ogg"))
    {
        std::cout << "Error loading sound file victory.ogg";
        std::cout << "\n";
    }

    if (!annihilator_sound_buffer.loadFromFile(cwd + "/assets/sounds/annihilator.ogg"))
    {
        std::cout << "Error loading sound file annihilator.ogg";
        std::cout << "\n";
    }

    if (!power_buffer_sound_buffer.loadFromFile(cwd + "/assets/sounds/power_buffer.ogg"))
    {
        std::cout << "Error loading sound file power_buffer.ogg";
        std::cout << "\n";
    }

    if (!drill_sound_buffer.loadFromFile(cwd + "/assets/sounds/drill.ogg"))
    {
        std::cout << "Error loading sound file drill.ogg";
        std::cout << "\n";
    }

    if (!harvester_sound_buffer.loadFromFile(cwd + "/assets/sounds/harvester.ogg"))
    {
        std::cout << "Error loading sound file harvester.ogg";
        std::cout << "\n";
    }

    if (!cannon_sound_buffer.loadFromFile(cwd + "/assets/sounds/cannon.ogg"))
    {
        std::cout << "Error loading sound file cannon.ogg";
        std::cout << "\n";
    }

    if (!explosion_sound_buffer.loadFromFile(cwd + "/assets/sounds/explosion.ogg"))
    {
        std::cout << "Error loading sound file explosion.ogg";
        std::cout << "\n";
    }
}

// Loads textures from file
void assets::load_textures(std::string cwd)
{
    if (!destroy_texture.loadFromFile(cwd + "/assets/textures/destroy.png"))
    {
        std::cout << "Error loading image file destroy.png";
        std::cout << "\n";
    }

    if (!explosion_texture.loadFromFile(cwd + "/assets/textures/explosion.bmp"))
    {
        std::cout << "Error loading image file explosion.bmp";
        std::cout << "\n";
    }

    if (!medium_explosion_texture.loadFromFile(cwd + "/assets/textures/medium_explosion.bmp"))
    {
        std::cout << "Error loading image file medium_explosion.bmp";
        std::cout << "\n";
    }

    if (!large_explosion_texture.loadFromFile(cwd + "/assets/textures/large_explosion.bmp"))
    {
        std::cout << "Error loading image file large_explosion.bmp";
        std::cout << "\n";
    }

    if (!growth_texture.loadFromFile(cwd + "/assets/textures/growth.bmp"))
    {
        std::cout << "Error loading image file growth.bmp";
        std::cout << "\n";
    }

    if (!spore_texture.loadFromFile(cwd + "/assets/textures/spore.bmp"))
    {
        std::cout << "Error loading image file spore.bmp";
        std::cout << "\n";
    }

    if (!t2_growth_texture.loadFromFile(cwd + "/assets/textures/growth_t2.bmp"))
    {
        std::cout << "Error loading image file growth_t2.bmp";
        std::cout << "\n";
    }

    if (!t2_spore_texture.loadFromFile(cwd + "/assets/textures/spore_t2.bmp"))
    {
        std::cout << "Error loading image file spore_t2.bmp";
        std::cout << "\n";
    }

    if (!t3_growth_texture.loadFromFile(cwd + "/assets/textures/growth_t3.bmp"))
    {
        std::cout << "Error loading image file growth_t3.bmp";
        std::cout << "\n";
    }

    if (!t3_spore_texture.loadFromFile(cwd + "/assets/textures/spore_t3.bmp"))
    {
        std::cout << "Error loading image file spore_t3.bmp";
        std::cout << "\n";
    }

    if (!iron_texture.loadFromFile(cwd + "/assets/textures/iron.png"))
    {
        std::cout << "Error loading image file iron.png";
        std::cout << "\n";
    }

    if (!copper_texture.loadFromFile(cwd + "/assets/textures/copper.png"))
    {
        std::cout << "Error loading image file copper.png";
        std::cout << "\n";
    }

    if (!coal_texture.loadFromFile(cwd + "/assets/textures/coal.png"))
    {
        std::cout << "Error loading image file coal.png";
        std::cout << "\n";
    }

    if (!cmd_center_texture.loadFromFile(cwd + "/assets/textures/cmd_center.bmp"))
    {
        std::cout << "Error loading image file cmd_center.bmp";
        std::cout << "\n";
    }

    if (!logi_center_texture.loadFromFile(cwd + "/assets/textures/logi_center.bmp"))
    {
        std::cout << "Error loading image file logi_center.bmp";
        std::cout << "\n";
    }

    if (!generator_off_texture.loadFromFile(cwd + "/assets/textures/generator_off.bmp"))
    {
        std::cout << "Error loading image file generator_off.bmp";
        std::cout << "\n";
    }

    if (!generator_on_texture.loadFromFile(cwd + "/assets/textures/generator_on.bmp"))
    {
        std::cout << "Error loading image file generator_on.bmp";
        std::cout << "\n";
    }

    if (!drill_texture.loadFromFile(cwd + "/assets/textures/drill.bmp"))
    {
        std::cout << "Error loading image file harvester.bmp";
        std::cout << "\n";
    }

    if (!drill_mining_texture.loadFromFile(cwd + "/assets/textures/drill_mining.bmp"))
    {
        std::cout << "Error loading image file drill_mining.bmp";
        std::cout << "\n";
    }

    if (!cannon_texture.loadFromFile(cwd + "/assets/textures/cannon.bmp"))
    {
        std::cout << "Error loading image file cannon.bmp";
        std::cout << "\n";
    }

    if (!cannon_firing_texture.loadFromFile(cwd + "/assets/textures/cannon_firing.bmp"))
    {
        std::cout << "Error loading image file cannon_firing.bmp";
        std::cout << "\n";
    }

    if (!annihilator_texture.loadFromFile(cwd + "/assets/textures/annihilator.bmp"))
    {
        std::cout << "Error loading image file annihilator.bmp";
        std::cout << "\n";
    }

    if (!annihilator_firing_texture.loadFromFile(cwd + "/assets/textures/annihilator_firing.bmp"))
    {
        std::cout << "Error loading image file annihilator_firing.bmp";
        std::cout << "\n";
    }

    if (!harvester_texture.loadFromFile(cwd + "/assets/textures/harvester.bmp"))
    {
        std::cout << "Error loading image file harvester.bmp";
        std::cout << "\n";
    }

    if (!harvester_firing_texture.loadFromFile(cwd + "/assets/textures/harvester_firing.bmp"))
    {
        std::cout << "Error loading image file harvester_firing.bmp";
        std::cout << "\n";
    }

    if (!terrain_texture.loadFromFile(cwd + "/assets/textures/terrain.bmp"))
    {
        std::cout << "Error loading image file terrain.bmp";
        std::cout << "\n";
    }

    if (!game_background_texture.loadFromFile(cwd + "/assets/textures/game_background.png"))
    {
        std::cout << "Error loading image file game_background.bmp";
        std::cout << "\n";
    }

    if (!title_texture.loadFromFile(cwd + "/assets/textures/title.png"))
    {
        std::cout << "Error loading image file title.png";
        std::cout << "\n";
    }

    if (!gui_background_texture.loadFromFile(cwd + "/assets/textures/gui_background.png"))
    {
        std::cout << "Error loading image file gui_background.bmp";
        std::cout << "\n";
    }

    if (!gui_background_2_texture.loadFromFile(cwd + "/assets/textures/gui_background_2.png"))
    {
        std::cout << "Error loading image file gui_background_2.bmp";
        std::cout << "\n";
    }

    if (!start_game_button_texture.loadFromFile(cwd + "/assets/textures/buttons/start_game_button.png"))
    {
        std::cout << "Error loading image file start_game_button.png";
        std::cout << "\n";
    }

    if (!start_game_button_hover_texture.loadFromFile(cwd + "/assets/textures/buttons/start_game_button_hover.png"))
    {
        std::cout << "Error loading image file start_game_button_hover.png";
        std::cout << "\n";
    }



    if (!tutorial_button_texture.loadFromFile(cwd + "/assets/textures/buttons/tutorial_button.png"))
    {
        std::cout << "Error loading image file tutorial_button.png";
        std::cout << "\n";
    }

    if (!tutorial_button_hover_texture.loadFromFile(cwd + "/assets/textures/buttons/tutorial_button_hover.png"))
    {
        std::cout << "Error loading image file tutorial_button_hover.png";
        std::cout << "\n";
    }



    if (!main_menu_button_texture.loadFromFile(cwd + "/assets/textures/buttons/main_menu_button.png"))
    {
        std::cout << "Error loading image file main_menu_button.png";
        std::cout << "\n";
    }

    if (!main_menu_button_hover_texture.loadFromFile(cwd + "/assets/textures/buttons/main_menu_button_hover.png"))
    {
        std::cout << "Error loading image file main_menu_button_hover.png";
        std::cout << "\n";
    }

    if (!save_game_button_texture.loadFromFile(cwd + "/assets/textures/buttons/save_button.png"))
    {
        std::cout << "Error loading image file save_button.png";
        std::cout << "\n";
    }

    if (!save_game_button_hover_texture.loadFromFile(cwd + "/assets/textures/buttons/save_button_hover.png"))
    {
        std::cout << "Error loading image file save_button_hover.png";
        std::cout << "\n";
    }

    if (!load_game_button_texture.loadFromFile(cwd + "/assets/textures/buttons/load_button.png"))
    {
        std::cout << "Error loading image file load_button.png";
        std::cout << "\n";
    }

    if (!load_game_button_hover_texture.loadFromFile(cwd + "/assets/textures/buttons/load_button_hover.png"))
    {
        std::cout << "Error loading image file load_button_hover.png";
        std::cout << "\n";
    }

    if (!options_button_texture.loadFromFile(cwd + "/assets/textures/buttons/options_button.png"))
    {
        std::cout << "Error loading image file options_button.png";
        std::cout << "\n";
    }

    if (!options_button_hover_texture.loadFromFile(cwd + "/assets/textures/buttons/options_button_hover.png"))
    {
        std::cout << "Error loading image file options_button_hover.png";
        std::cout << "\n";
    }

    if (!exit_game_button_texture.loadFromFile(cwd + "/assets/textures/buttons/exit_game_button.png"))
    {
        std::cout << "Error loading image file exit_game_button.png";
        std::cout << "\n";
    }

    if (!exit_game_button_hover_texture.loadFromFile(cwd + "/assets/textures/buttons/exit_game_button_hover.png"))
    {
        std::cout << "Error loading image file exit_game_button_hover.png";
        std::cout << "\n";
    }

    if (!create_new_button_texture.loadFromFile(cwd + "/assets/textures/buttons/create_new_button.png"))
    {
        std::cout << "Error loading image file create_new_button.png";
        std::cout << "\n";
    }

    if (!create_new_button_hover_texture.loadFromFile(cwd + "/assets/textures/buttons/create_new_button_hover.png"))
    {
        std::cout << "Error loading image file create_new_button_hover.png";
        std::cout << "\n";
    }

    if (!cancel_button_texture.loadFromFile(cwd + "/assets/textures/buttons/cancel_button.png"))
    {
        std::cout << "Error loading image file cancel_button.png";
        std::cout << "\n";
    }

    if (!cancel_button_hover_texture.loadFromFile(cwd + "/assets/textures/buttons/cancel_button_hover.png"))
    {
        std::cout << "Error loading image file cancel_button_hover.png";
        std::cout << "\n";
    }

    if (!term_texture.loadFromFile(cwd + "/assets/textures/term.bmp"))
    {
        std::cout << "Error loading image file term.bmp";
        std::cout << "\n";
    }
}

// Loads fonts from file
void assets::load_fonts(std::string cwd)
{
    if (!orbitron.loadFromFile(cwd + "/assets/Orbitron Medium.ttf"))
    {
        std::cout << "Error loading font file Orbitron Medium.ttf";
        std::cout << "\n";
    }

    if (!exoplanetaria.loadFromFile(cwd + "/assets/Exoplanetaria-gxxJ5.ttf"))
    {
        std::cout << "Error loading font file Exoplanetaria-gxxJ5.ttf";
        std::cout << "\n";
    }
}

// Assigns sound buffers
void assets::init_sounds()
{
    main_menu_music.setBuffer(main_menu_music_buffer);
    dig_sound.setBuffer(dig_sound_buffer);
    power_buffer_sound.setBuffer(power_buffer_sound_buffer);
    annihilator_sound.setBuffer(annihilator_sound_buffer);
    victory_sound.setBuffer(victory_sound_buffer);

    for (int i = 0; i < 10; i++)
    {
        drill_sounds[i].setBuffer(drill_sound_buffer);
    }

    for (int i = 0; i < 10; i++)
    {
        harvester_sounds[i].setBuffer(harvester_sound_buffer);
    }

    for (int i = 0; i < 10; i++)
    {
        cannon_sounds[i].setBuffer(cannon_sound_buffer);
    }

    for (int i = 0; i < 10; i++)
    {
        explosion_sounds[i].setBuffer(explosion_sound_buffer);
    }
}

// Assigns textures to sprites
void assets::init_sprites()
{
    terrain_sprite.setTexture(terrain_texture);
    title_sprite.setTexture(title_texture);
    game_background_sprite.setTexture(game_background_texture);
    start_game_button_sprite.setTexture(start_game_button_texture);
    main_menu_button_sprite.setTexture(main_menu_button_texture);
    save_game_button_sprite.setTexture(save_game_button_texture);
    load_game_button_sprite.setTexture(load_game_button_texture);
    options_button_sprite.setTexture(options_button_texture);
    exit_game_button_sprite.setTexture(exit_game_button_texture);
    create_new_button_sprite.setTexture(create_new_button_texture);
    cancel_button_sprite.setTexture(cancel_button_texture);
    term_sprite.setTexture(term_texture);
}

// Sets up text objects
void assets::init_text()
{
    fps_counter.setFont(orbitron);
    fps_counter.setString("0");
    fps_counter.setCharacterSize(12);
    fps_counter.setFillColor(sf::Color::White);

    keys.setFont(exoplanetaria);
    keys.setString("");
    keys.setCharacterSize(12);
    keys.setFillColor(sf::Color::White);

    inventory.setFont(orbitron);
    inventory.setString("");
    inventory.setCharacterSize(12);
    inventory.setFillColor(sf::Color::White);

    player_location.setFont(orbitron);
    player_location.setString("0");
    player_location.setCharacterSize(12);
    player_location.setFillColor(sf::Color::White);

    area_power.setFont(orbitron);
    area_power.setString("0");
    area_power.setCharacterSize(12);
    area_power.setFillColor(sf::Color::White);

    notice.setFont(exoplanetaria);
    notice.setString("");
    notice.setCharacterSize(24);
    notice.setFillColor(sf::Color::White);

    input_text.setFont(orbitron);
    input_text.setString("");
    input_text.setCharacterSize(12);
    input_text.setFillColor(sf::Color::White);
}

// Initializes all assets
void assets::init(std::string cwd)
{
    load_sound_buffers(cwd);
    load_textures(cwd);
    load_fonts(cwd);

    init_sounds();
    init_sprites();
    init_text();

    resource_textures["iron"] = iron_texture;
    resource_textures["copper"] = copper_texture;
    resource_textures["coal"] = coal_texture;

    building_textures["drill"] = drill_texture;
    building_textures["harvester"] = harvester_texture;
    building_textures["cannon"] = cannon_texture;
    building_textures["generator"] = generator_off_texture;
    building_textures["annihilator"] = annihilator_texture;
    building_textures["cmd_center"] = cmd_center_texture;
    building_textures["logi_center"] = logi_center_texture;

    game_background_texture.setRepeated(true);
    terrain_texture.setRepeated(true);
}
