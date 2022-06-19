#include <tutorial.h>

// Constructor
tutorial::tutorial(std::string cwd)
{
    step = 0;
    visible = true;
    completed = false;

    if (!gui_background_texture.loadFromFile(cwd + "/assets/textures/gui_background.png"))
    {
        std::cout << "Failed to load textures.";
    }
    gui_background_sprite.setTexture(gui_background_texture);

    if (!tutorial_font.loadFromFile(cwd + "/assets/Exoplanetaria-gxxJ5.ttf"))
    {
        std::cout << "Failed to load font.";
    }
}

// Draws tutorial messages
void tutorial::draw_tutorial(sf::RenderWindow &window, world &game_world)
{
    if (step == 0)
    {
        sf::String text = std::string("Welcome to Overgrown!\n\n") +
                          std::string("To get started, you will need to build a command center.\n") +
                          std::string("Click the 'build' button, then the 'cmd center' button.\n") +
                          std::string("Click anywhere in the sector to place the command center.\n") +
                          std::string("The tutorial will continue when you are finished.\n\n") +
                          std::string("Press F1 to toggle the visibility of these messages.\n") +
                          std::string("Press F2 show key bindings.\n") +
                          std::string("Press F3 to toggle frame rate display.\n");
        tutorial_text.setString(text);

        for (unsigned int i = 0; i < game_world.areas.size(); i++)
        {
            if (game_world.areas[i].cmd_centers.size() > 0)
            {
                step = 1;
                break;
            }
        }
    }
    else if (step == 1)
    {
        sf::String text = std::string("Mining drills are used to gather resources and require electricity.\n") +
                          std::string("Go ahead and build a drill in the same sector as your command center.\n") +
                          std::string("Place the drill on any resource node in the sector.\n") +
                          std::string("If you would like to move a building, click the 'destroy' button.\n") +
                          std::string("Click on the building and it will be destroyed. 50 percent of the\n") +
                          std::string("materials used to construct the building will be refunded to you.\n") +
                          std::string("The tutorial will continue when you are finished.");
        tutorial_text.setString(text);

        for (unsigned int i = 0; i < game_world.areas.size(); i++)
        {
            if (game_world.areas[i].drills.size() > 0)
            {
                step = 2;
                break;
            }
        }
    }
    else if (step == 2)
    {
        sf::String text = std::string("Drills require electricity to operate. This means you will need to build\n") +
                          std::string("generators in this sector before the drill will begin to mine the ore.\n") +
                          std::string("Go ahead and build a generator in the same sector as your other buildings.\n") +
                          std::string("The tutorial will continue when you are finished.");
        tutorial_text.setString(text);

        for (unsigned int i = 0; i < game_world.areas.size(); i++)
        {
            if (game_world.areas[i].generators.size() > 0)
            {
                step = 3;
                break;
            }
        }
    }
    else if (step == 3)
    {
        sf::String text = std::string("Generators consume coal. You will need to keep an eye on your reserves\n") +
                          std::string("To ensure the supply is meeting or exceeding the demand. Keep in mind\n") +
                          std::string("that building multiple generators in one sector will attract the enemy.\n\n") +
                          std::string("You will need to build in multiple sectors to succeed. Go ahead and move\n") +
                          std::string("one sector to the north or east using the arrow keys on your keyboard.\n") +
                          std::string("When you arrive at sector (0, 1) or (1, 0), the tutorial will continue.\n") +
                          std::string("Your coordinates are displayed at the top left corner of the screen.");
        tutorial_text.setString(text);

        sf::Vector2i pos = game_world.player_coordinates;
        if (pos == sf::Vector2i(0, 1) || pos == sf::Vector2i(1, 0))
        {
            step = 4;
        }
    }
    else if (step == 4)
    {
        sf::String text = std::string("For generators in other sectors to operate, coal must be transported to them.\n") +
                          std::string("This means a logistics center must be built in the sector. Your first\n") +
                          std::string("logistics center must be built in a sector adjacent to your command center.\n") +
                          std::string("The next must be built in a sector adjacent to the first, and so on.\n") +
                          std::string("Go ahead and build a logistics center now.\n") +
                          std::string("The tutorial will continue when you are finished.");
        tutorial_text.setString(text);

        sf::Vector2i pos = game_world.player_coordinates;
        int index = game_world.get_area_index(pos);
        if (game_world.areas[index].logi_centers.size() > 0)
        {
            step = 5;
        }
    }
    else if (step == 5)
    {
        sf::String text = std::string("Building more than one generator in a sector will attract enemy spore colonies.\n") +
                          std::string("Go ahead and build 2 or 3 generators in this sector to attract the enemy.\n") +
                          std::string("The tutorial will continue when you are finished.");
        tutorial_text.setString(text);

        sf::Vector2i pos = game_world.player_coordinates;
        int index = game_world.get_area_index(pos);
        unsigned int gens = game_world.areas[index].generators.size();
        if (gens > 1)
        {
            step = 6;
        }
    }
    else if (step == 6)
    {
        sf::String text = std::string("Harvesters are used to collect spores from colonies. Spores are used to construct\n") +
                          std::string("cannons and annihilators. You will need these buildings to defend your equipment\n") +
                          std::string("and defeat the enemy. When all spore colonies in the world have been destroyed,\n") +
                          std::string("the enemy is defeated and you have won the game. After the colony appears in this\n") +
                          std::string("sector, go ahead and build a harvester and a cannon.");
        tutorial_text.setString(text);

        sf::Vector2i pos = game_world.player_coordinates;
        int index = game_world.get_area_index(pos);
        int cannons = game_world.areas[index].cannons.size();
        int harvesters = game_world.areas[index].harvesters.size();
        if (cannons > 0 && harvesters > 0)
        {
            step = 7;
        }
    }
    else if (step == 7)
    {
        sf::String text = std::string("Annihilators are used to destroy colonies. Build an annihilator within firing range\n") +
                          std::string("of the colony in this sector (the tentacled monster). The annihilator needs to charge\n") +
                          std::string("before firing. This requires a lot of power, so you will need to build several generators.\n") +
                          std::string("Keep in mind that the more power you generate, the faster the colony will grow.\n") +
                          std::string("The colony will also tend to grow toward your generators.\n") +
                          std::string("This means you will need to protect your buildings using cannons and harvesters.\n") +
                          std::string("Defeat the colony in this sector to complete the tutorial.");
        tutorial_text.setString(text);

        sf::Vector2i pos = game_world.player_coordinates;
        int index = game_world.get_area_index(pos);
        if (game_world.areas[index].area_growth.alive == false)
        {
            completed = true;
        }
    }

    sf::Vector2f bg_pos;
    bg_pos.x = (window.getView().getSize().x / 2) - 150 - (tutorial_text.getGlobalBounds().width / 2);
    bg_pos.y = (window.getView().getSize().y / 2) - 170;
    gui_background_sprite.setPosition(bg_pos);
    gui_background_sprite.setScale(tutorial_text.getGlobalBounds().width * 0.00075, tutorial_text.getGlobalBounds().height * 0.006);
    window.draw(gui_background_sprite);

    tutorial_text.setFont(tutorial_font);
    tutorial_text.setCharacterSize(14);
    tutorial_text.setFillColor(sf::Color::White);
    sf::Vector2f text_pos;
    text_pos.x = (window.getView().getSize().x / 2) - 125 - (tutorial_text.getGlobalBounds().width / 2);
    text_pos.y = (window.getView().getSize().y / 2) - 150;
    tutorial_text.setPosition(text_pos);
    window.draw(tutorial_text);
}
