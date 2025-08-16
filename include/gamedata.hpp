#include <vector>
#include <map>
#include <string>

#ifndef GAMEDATA_HPP
#define GAMEDATA_HPP

enum class Tile
{
    Wall,
    Empty,
    Exit,
};

class Gamedata;

class Entity
{
protected:
    double x_pos_;
    double y_pos_;

public:
    virtual ~Entity() = default;

    std::pair<double, double> get_pos();

    virtual void step(Gamedata &gamedata);

    Entity(double x_pos, double y_pos) : x_pos_(x_pos), y_pos_(y_pos) {}
};

class SCP_939 : public Entity
{
public:
    using Entity::Entity;

    void step(Gamedata &gamedata);
};

class Player : public Entity
{
public:
    using Entity::Entity;

    void step(Gamedata &gamedata);
};

class Orb : public Entity
{
private:
    bool is_collected = false;

public:
    using Entity::Entity;

    void step(Gamedata &gamedata);
};

class Gamedata
{
private:
    std::vector<std::vector<Tile>> tiles;

    std::vector<Entity> enemies;
    Player player;
    std::vector<Orb> orbs;

    std::map<std::string, bool> input;

public:
    std::vector<std::vector<Tile>> get_map();
    std::vector<Entity> get_enemies();
    Player get_player();
    std::vector<Orb> get_orbs();

    void update_input(std::string input_name, bool input_value);

    void step();

    Gamedata();
};

#endif