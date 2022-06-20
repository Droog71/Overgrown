#include "world.h"

world::world()
{
    growth_spawn_timer = 0;
}

// Generates resource nodes
void world::generate_resource_nodes(assets &textures, sf::RenderWindow &window, int index)
{
    for (int i = 0; i < 5; i++)
    {
        int rand_x = rand() % (int)window.getView().getSize().x - 270;
        int rand_y = rand() % (int)window.getView().getSize().y - 70;

        bool encroaching = false;
        for (int j = 0; j <5; j++)
        {
            sf::Vector2f pos = sf::Vector2f(rand_x, rand_y);
            sf::Vector2f other_pos = areas[index].resource_nodes[j].position;
            float distance = get_distance(pos, other_pos);
            if (distance <= 128)
            {
                encroaching = true;
                break;
            }
        }

        while (encroaching == true)
        {
            rand_x = rand() % (int)window.getView().getSize().x - 270;
            rand_y = rand() % (int)window.getView().getSize().y - 70;

            bool repeat = false;
            for (int j = 0; j <5; j++)
            {
                sf::Vector2f pos = sf::Vector2f(rand_x, rand_y);
                sf::Vector2f other_pos = areas[index].resource_nodes[j].position;
                float distance = get_distance(pos, other_pos);
                if (distance <= 128)
                {
                    repeat = true;
                    break;
                }
            }
            encroaching = repeat;
        }

        areas[index].resource_nodes[i].position.x = rand_x;
        areas[index].resource_nodes[i].position.y = rand_y;

        if (areas[index].resource_nodes[i].position.x < 70)
        {
            areas[index].resource_nodes[i].position.x = 70;
        }
        if (areas[index].resource_nodes[i].position.y < 70)
        {
            areas[index].resource_nodes[i].position.y = 70;
        }

        std::string resource_types [3] = { "iron", "copper", "coal" };

        int r = rand() % 3;
        areas[index].resource_nodes[i].type = resource_types[r];
        areas[index].resource_nodes[i].sprite.setTexture(textures.resource_textures[resource_types[r]]);
    }
}

// Loads saved game data from file
void world::load_objects(std::string cwd, std::string dir, std::string type, sf::RenderWindow &window, assets* resources)
{
    int area_index = 0;
    size_t area_pos = 0;
    std::string area_delimiter = "}";
    std::vector<std::string> areastr(1024);
    std::string file_data = get_file_contents(cwd + "/save/" + dir + "/" + type + ".sav");

    while ((area_pos = file_data.find(area_delimiter)) != std::string::npos)
    {
        areastr[area_index] = file_data.substr(0, area_pos);
        file_data.erase(0, area_pos + area_delimiter.length());
        area_index++;
    }

    for (unsigned int i = 0; i < areastr.size(); i++)
    {
        int obj_index = 0;
        size_t obj_pos = 0;
        std::string obj_delim = ">";
        std::vector<std::string> objects(2000);

        while ((obj_pos = areastr[i].find(obj_delim)) != std::string::npos)
        {
            objects[obj_index] = areastr[i].substr(0, obj_pos);
            areastr[i].erase(0, obj_pos + obj_delim.length());
            obj_index++;
        }

        if (type == "cmd_centers")
        {
            areas[i].cmd_centers.resize(obj_index);
        }
        else if (type == "logi_centers")
        {
            areas[i].logi_centers.resize(obj_index);
        }
        if (type == "harvesters")
        {
            areas[i].harvesters.resize(obj_index);
        }
        else if (type == "drills")
        {
            areas[i].drills.resize(obj_index);
        }
        else if (type == "generators")
        {
            areas[i].generators.resize(obj_index);
        }
        else if (type == "cannons")
        {
            areas[i].cannons.resize(obj_index);
        }
        else if (type == "annihilators")
        {
            areas[i].annihilators.resize(obj_index);
        }

        objects.resize(obj_index);
        std::vector<sf::Vector2i> coords (objects.size());
        std::vector<std::string> types (objects.size());

        if (type == "growths")
        {
            sf::Vector2i growth_coords;
            bool growth_alive = false;

            size_t growth_pos = areastr[i].find(":");
            growth_alive = std::stoi(areastr[i].substr(0, growth_pos));
            areastr[i].erase(0, growth_pos + 1);

            size_t coords_pos = areastr[i].find(",");
            growth_coords.x = std::stoi(areastr[i].substr(0, coords_pos));
            growth_coords.y = std::stoi(areastr[i].substr(coords_pos + 1, areastr[i].length()));

            areas[i].area_growth.position.x = growth_coords.x;
            areas[i].area_growth.position.y = growth_coords.y;
            areas[i].area_growth.alive = growth_alive;
        }
        else if (type == "resource_nodes")
        {
            for (unsigned int j = 0; j < objects.size(); j++)
            {
                size_t node_pos = objects[j].find(":");
                types[j] = objects[j].substr(0, node_pos);
                objects[j].erase(0, node_pos + 1);

                size_t coords_pos = objects[j].find(",");
                coords[j].x = std::stoi(objects[j].substr(0, coords_pos));
                coords[j].y = std::stoi(objects[j].substr(coords_pos + 1, objects[j].length()));
            }
        }
        else
        {
            for (unsigned int j = 0; j < objects.size(); j++)
            {
                size_t coords_pos = objects[j].find(",");
                coords[j].x = std::stoi(objects[j].substr(0, coords_pos));
                coords[j].y = std::stoi(objects[j].substr(coords_pos + 1, objects[j].length()));
            }
        }

        for (unsigned int k = 0; k < objects.size(); k++)
        {
            if (type == "cmd_centers")
            {
                areas[i].cmd_centers[k].position.x = coords[k].x;
                areas[i].cmd_centers[k].position.y = coords[k].y;
                areas[i].cmd_centers[k].sprite.setTexture(resources->cmd_center_texture);
            }
            else if (type == "logi_centers")
            {
                areas[i].logi_centers[k].position.x = coords[k].x;
                areas[i].logi_centers[k].position.y = coords[k].y;
                areas[i].logi_centers[k].sprite.setTexture(resources->logi_center_texture);
            }
            else if (type == "drills")
            {
                areas[i].drills[k].position.x = coords[k].x;
                areas[i].drills[k].position.y = coords[k].y;
                areas[i].drills[k].sprite.setTexture(resources->drill_texture);
            }
            else if (type == "generators")
            {
                areas[i].generators[k].position.x = coords[k].x;
                areas[i].generators[k].position.y = coords[k].y;
                areas[i].generators[k].sprite.setTexture(resources->generator_off_texture);
            }
            else if (type == "harvesters")
            {
                areas[i].harvesters[k].position.x = coords[k].x;
                areas[i].harvesters[k].position.y = coords[k].y;
                areas[i].harvesters[k].sprite.setTexture(resources->harvester_texture);
            }
            else if (type == "cannons")
            {
                areas[i].cannons[k].position.x = coords[k].x;
                areas[i].cannons[k].position.y = coords[k].y;
                areas[i].cannons[k].sprite.setTexture(resources->cannon_texture);
            }
            else if (type == "annihilators")
            {
                areas[i].annihilators[k].position.x = coords[k].x;
                areas[i].annihilators[k].position.y = coords[k].y;
                areas[i].annihilators[k].sprite.setTexture(resources->annihilator_texture);
            }
            else if (type == "spores")
            {
                areas[i].area_growth.spores[k].position.x = coords[k].x;
                areas[i].area_growth.spores[k].position.y = coords[k].y;
                areas[i].area_growth.last_pos = areas[i].area_growth.spores[k].position;
                areas[i].area_growth.spores[k].sprite.setTexture(resources->spore_texture);
                areas[i].area_growth.spores[k].alive = true;
            }
            else if (type == "resource_nodes")
            {
                areas[i].resource_nodes[k].position.x = coords[k].x;
                areas[i].resource_nodes[k].position.y = coords[k].y;
                areas[i].resource_nodes[k].type = types[k];
                areas[i].resource_nodes[k].sprite.setTexture(resources->resource_textures[types[k]]);
            }
        }
    }
}

// Loads saved game data from file
void world::load_player_data(std::string cwd, std::string dir)
{
    int index = 0;
    size_t pos = 0;
    std::string token;
    std::string delimiter = "\n";
    std::vector<std::string> values(7);
    std::string file_data = get_file_contents(cwd + "/save/" + dir + "/player.sav");

    while ((pos = file_data.find(delimiter)) != std::string::npos)
    {
        values[index] = file_data.substr(0, pos);
        file_data.erase(0, pos + delimiter.length());
        index++;
    }

    player_coordinates.x = std::stoi(values[0]);
    player_coordinates.y = std::stoi(values[1]);
    inventory["iron"] = std::stoi(values[2]);
    inventory["copper"] = std::stoi(values[3]);
    inventory["coal"] = std::stoi(values[4]);
    inventory["spores"] = std::stoi(values[5]);
}

// Returns saved game data as a single string
std::string world::get_growth_data()
{
    std::string save_data = "";
    for (unsigned int i = 0; i < areas.size(); i++)
    {
        save_data += std::to_string(areas[i].area_growth.alive) + ":";
        save_data += std::to_string(areas[i].area_growth.position.x) + ",";
        save_data += std::to_string(areas[i].area_growth.position.y) + "}";
    }
    return save_data;
}

// Returns saved game data as a single string
std::string world::get_spore_data()
{
    std::string save_data = "";
    for (unsigned int i = 0; i < areas.size(); i++)
    {
        for (unsigned int j = 0; j < areas[i].area_growth.spores.size(); j++)
        {
            if (areas[i].area_growth.spores[j].alive == true)
            {
                save_data += std::to_string(areas[i].area_growth.spores[j].position.x) + ",";
                save_data += std::to_string(areas[i].area_growth.spores[j].position.y) + ">";
            }
        }
        save_data += "}";
    }
    return save_data;
}

// Returns saved game data as a single string
std::string world::get_cmd_center_data()
{
    std::string save_data = "";
    for (unsigned int i = 0; i < areas.size(); i++)
    {
        for (unsigned int j = 0; j < areas[i].cmd_centers.size(); j++)
        {
            save_data += std::to_string(areas[i].cmd_centers[j].position.x) + ",";
            save_data += std::to_string(areas[i].cmd_centers[j].position.y) + ">";
        }
        save_data += "}";
    }
    return save_data;
}

// Returns saved game data as a single string
std::string world::get_logi_center_data()
{
    std::string save_data = "";
    for (unsigned int i = 0; i < areas.size(); i++)
    {
        for (unsigned int j = 0; j < areas[i].logi_centers.size(); j++)
        {
            save_data += std::to_string(areas[i].logi_centers[j].position.x) + ",";
            save_data += std::to_string(areas[i].logi_centers[j].position.y) + ">";
        }
        save_data += "}";
    }
    return save_data;
}

// Returns saved game data as a single string
std::string world::get_harvester_data()
{
    std::string save_data = "";
    for (unsigned int i = 0; i < areas.size(); i++)
    {
        for (unsigned int j = 0; j < areas[i].harvesters.size(); j++)
        {
            save_data += std::to_string(areas[i].harvesters[j].position.x) + ",";
            save_data += std::to_string(areas[i].harvesters[j].position.y) + ">";
        }
        save_data += "}";
    }
    return save_data;
}

// Returns saved game data as a single string
std::string world::get_cannon_data()
{
    std::string save_data = "";
    for (unsigned int i = 0; i < areas.size(); i++)
    {
        for (unsigned int j = 0; j < areas[i].cannons.size(); j++)
        {
            save_data += std::to_string(areas[i].cannons[j].position.x) + ",";
            save_data += std::to_string(areas[i].cannons[j].position.y) + ">";
        }
        save_data += "}";
    }
    return save_data;
}

// Returns saved game data as a single string
std::string world::get_annihilator_data()
{
    std::string save_data = "";
    for (unsigned int i = 0; i < areas.size(); i++)
    {
        for (unsigned int j = 0; j < areas[i].annihilators.size(); j++)
        {
            save_data += std::to_string(areas[i].annihilators[j].position.x) + ",";
            save_data += std::to_string(areas[i].annihilators[j].position.y) + ">";
        }
        save_data += "}";
    }
    return save_data;
}

// Returns saved game data as a single string
std::string world::get_generator_data()
{
    std::string save_data = "";
    for (unsigned int i = 0; i < areas.size(); i++)
    {
        for (unsigned int j = 0; j < areas[i].generators.size(); j++)
        {
            save_data += std::to_string(areas[i].generators[j].position.x) + ",";
            save_data += std::to_string(areas[i].generators[j].position.y) + ">";
        }
        save_data += "}";
    }
    return save_data;
}

// Returns saved game data as a single string
std::string world::get_drill_data()
{
    std::string save_data = "";
    for (unsigned int i = 0; i < areas.size(); i++)
    {
        for (unsigned int j = 0; j < areas[i].drills.size(); j++)
        {
            save_data += std::to_string(areas[i].drills[j].position.x) + ",";
            save_data += std::to_string(areas[i].drills[j].position.y) + ">";
        }
        save_data += "}";
    }
    return save_data;
}

// Returns saved game data as a single string
std::string world::get_resource_node_data()
{
    std::string save_data = "";
    for (unsigned int i = 0; i < areas.size(); i++)
    {
        for (int j = 0; j < 5; j++)
        {
            save_data += areas[i].resource_nodes[j].type + ":";
            save_data += std::to_string(areas[i].resource_nodes[j].position.x) + ",";
            save_data += std::to_string(areas[i].resource_nodes[j].position.y) + ">";
        }
        save_data += "}";
    }
    return save_data;
}

// Returns saved game data as a single string
std::string world::get_player_data()
{
    return std::to_string(player_coordinates.x) + "\n" +
           std::to_string(player_coordinates.y) + "\n" +
           std::to_string(inventory["iron"]) + "\n" +
           std::to_string(inventory["copper"]) + "\n" +
           std::to_string(inventory["coal"]) + "\n" +
           std::to_string(inventory["spores"]);
}

// Overwrites an existing save game
void world::save_game(int i, std::string path)
{
    if (!std::experimental::filesystem::exists(path))
    {
        std::experimental::filesystem::v1::create_directory(path);
    }

    write_to_file(path + "spores.sav", get_spore_data());
    write_to_file(path + "drills.sav", get_drill_data());
    write_to_file(path + "growths.sav", get_growth_data());
    write_to_file(path + "player.sav", get_player_data());
    write_to_file(path + "generators.sav", get_generator_data());
    write_to_file(path + "cmd_centers.sav", get_cmd_center_data());
    write_to_file(path + "logi_centers.sav", get_logi_center_data());
    write_to_file(path + "harvesters.sav", get_harvester_data());
    write_to_file(path + "cannons.sav", get_cannon_data());
    write_to_file(path + "annihilators.sav", get_annihilator_data());
    write_to_file(path + "resource_nodes.sav", get_resource_node_data());
}

// Creates a new save game
bool world::create_save(std::string cwd, sf::String &input)
{
    std::string saves = get_file_contents(cwd + "/save/saves.list");
    std::string delimiter = "\n";
    std::string token;

    int index = 0;
    size_t pos = 0;
    while ((pos = saves.find(delimiter)) != std::string::npos)
    {
        token = saves.substr(0, pos);
        saves.erase(0, pos + delimiter.length());
        index++;
    }

    if (index < 10)
    {
        std::string path = cwd + "/save/" + input + "/";

        if (!std::experimental::filesystem::exists(path))
        {
            std::experimental::filesystem::v1::create_directory(path);
        }

        append_file(cwd + "/save/saves.list", input);
        write_to_file(path + "spores.sav", get_spore_data());
        write_to_file(path + "drills.sav", get_drill_data());
        write_to_file(path + "growths.sav", get_growth_data());
        write_to_file(path + "player.sav", get_player_data());
        write_to_file(path + "generators.sav", get_generator_data());
        write_to_file(path + "cmd_centers.sav", get_cmd_center_data());
        write_to_file(path + "logi_centers.sav", get_logi_center_data());
        write_to_file(path + "harvesters.sav", get_harvester_data());
        write_to_file(path + "cannons.sav", get_cannon_data());
        write_to_file(path + "annihilators.sav", get_annihilator_data());
        write_to_file(path + "resource_nodes.sav", get_resource_node_data());
        return true;
    }
    return false;
}

// Deletes a saved game
void world::delete_save_game(std::string cwd, int i, sf::String dir)
{
    std::string path = cwd + "/save/" + dir + "/";
    std::experimental::filesystem::v1::remove_all(path);

    std::string saves = get_file_contents(cwd + "/save/saves.list");
    std::string delimiter = "\n";
    std::string new_saves;
    std::string token;
    size_t pos = 0;

    while ((pos = saves.find(delimiter)) != std::string::npos)
    {
        token = saves.substr(0, pos);
        if (token != dir && token != "")
        {
            new_saves += token + "\n";
        }
        saves.erase(0, pos + delimiter.length());
    }

    new_saves.erase(new_saves.find_last_not_of(" \n\r\t")+1);
    write_to_file(cwd + "/save/saves.list", new_saves);
}

bool world::spawn_growth(sf::RenderWindow &window, int area_index, float frame_time)
{
    bool spawning = false;

    sf::Vector2i up_v = sf::Vector2i(areas[area_index].coordinates.x, areas[area_index].coordinates.y + 1);
    sf::Vector2i down_v = sf::Vector2i(areas[area_index].coordinates.x, areas[area_index].coordinates.y - 1);
    sf::Vector2i left_v = sf::Vector2i(areas[area_index].coordinates.x - 1, areas[area_index].coordinates.y);
    sf::Vector2i right_v = sf::Vector2i(areas[area_index].coordinates.x + 1, areas[area_index].coordinates.y);

    int up = get_area_index(up_v);
    int down = get_area_index(down_v);
    int left =  get_area_index(left_v);
    int right = get_area_index(right_v);

    int dirs [4] = { up, down, left, right };

    for (int i = 0; i < 4; i++)
    {
        if (dirs[i] != -1)
        {
            if (areas[dirs[i]].area_growth.alive == true)
            {
                spawning = true;
            }
        }
    }

    if (spawning == false)
    {
        spawning = areas[area_index].generators.size() > 1;
    }

    if (spawning == true)
    {
        int old_x = areas[area_index].area_growth.position.x;
        int old_y = areas[area_index].area_growth.position.y;

        if (old_x == 0 && old_y == 0)
        {
            int x = rand() % (int)window.getView().getSize().x - 300;
            int y = rand() % (int)window.getView().getSize().y - 100;

            x = x < 100 ? 100 : x;
            y = y < 100 ? 100 : y;

            areas[area_index].area_growth.position.x = x;
            areas[area_index].area_growth.position.y = y;
        }

        areas[area_index].area_growth.alive = true;
    }

    return spawning;
}

int world::get_area_index(sf::Vector2i coords)
{
    for (unsigned int i = 0; i < areas.size(); i++)
    {
        if (areas[i].coordinates.x == coords.x && areas[i].coordinates.y == coords.y)
        {
            return i;
        }
    }
    return -1;
}
