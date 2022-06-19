#ifndef GROWTH_H
#define GROWTH_H

#include <assets.h>

class growth
{
    public:
        struct spore
        {
            bool alive;
            sf::Sprite sprite;
            sf::Vector2f position;
        };
        int health;
        bool alive;
        bool healing;
        bool destroying;
        float strength;
        float spawn_timer;
        float growth_rate;
        float destroy_timer;
        sf::Sprite sprite;
        sf::Vector2f last_pos;
		sf::Vector2f position;
		std::array<spore, 2000> spores;
		std::vector<sf::Vector2f> injuries;
		void heal(assets &resources);
		unsigned int index;
        unsigned int injury_index;
        unsigned int get_spore_index(sf::Vector2f coords);
		void grow(bool targeted, sf::Vector2f target, sf::RenderWindow &window, assets &resources, float frame_time);
		growth();

    private:
        float growth_timer;
        float drift_timer;
};

#endif // GROWTH_H
