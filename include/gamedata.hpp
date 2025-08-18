#ifndef GAMEDATA_HPP
#define GAMEDATA_HPP

namespace ent
{
    class Entity;
    class Player;
    class Orb;
    class SCP_939;
}

#include <vector>
#include <map>
#include <string>

enum class Tile
{
    Wall,
    Empty,
    Exit
};

enum class Direction
{
    Up,
    Down,
    Left,
    Right
};

class Gamedata
{
private:
    std::vector<std::vector<Tile>> tiles_;

    std::vector<ent::Entity *> enemies_;
    ent::Player *player_;
    std::vector<ent::Orb *> orbs_;

    std::map<std::string, bool> input_;

public:
    std::vector<std::vector<Tile>> get_map();

    std::vector<ent::Entity *> get_enemies();

    ent::Player *get_player();

    std::vector<ent::Orb *> get_orbs();

    void update_input(std::string input_name, bool input_value);

    void step();

    Gamedata(std::string filename);

    ~Gamedata();
};

#endif