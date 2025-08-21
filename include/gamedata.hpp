#ifndef GAMEDATA_HPP
#define GAMEDATA_HPP

#include <vector>
#include <array>
#include <map>
#include <string>
#include "events.hpp"

namespace ent
{
    class Entity;
    class Player;
    class Orb;
    class SCP_939;
}

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

    EventsArray events_;

    int mouse_x_;
    int mouse_y_;
    bool is_mouse_pressed_;
    bool is_mouse_down_;
    bool is_mouse_released_;
    bool is_mouse_up_;

    Event last_pressed_direction_;

public:
    std::vector<std::vector<Tile>> get_map();

    std::vector<ent::Entity *>& get_enemies();

    ent::Player *get_player();

    std::vector<ent::Orb *>& get_orbs();

    void update_event(Event event_name, bool event_value);

    void update_mouse(int mouse_x_, int mouse_y_, bool is_mouse_pressed, bool is_mouse_down, bool is_mouse_released, bool is_mouse_up);

    Event get_last_pressed_direction();

    std::pair <int, int> get_mouse_pos();

    EventsArray get_events();

    void step();

    Gamedata(std::string filename);

    ~Gamedata();
};

#endif